#include <stddef.h>
#include <errno.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/types.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#define SEARCH_UUID BT_UUID_128_ENCODE(0xBDFC9792, 0x8234, 0x405E, 0xAE02, 0x35EF4174B299)

// Max number of coasters
#define MAX_COASTERS 20

struct random_number_node {
	int random_number;
};

// List of coasters received
struct random_number_node random_numbers[MAX_COASTERS];
int num_random_numbers = 0;

// Print list of coasters
void print_random_numbers() {
    printk("Random numbers: ");
    for (int i = 0; i < num_random_numbers; i++) {
        printk("%d ", random_numbers[i].random_number);
    }
    printk("\n");
}

// Add coaster received to list
void add_random_number(int number) {
    if (num_random_numbers < MAX_COASTERS) {
        // Check if the number already exists in the list
        int exists = 0;
        for (int i = 0; i < num_random_numbers; i++) {
            if (random_numbers[i].random_number == number) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            // Number does not exist
            random_numbers[num_random_numbers].random_number = number;
            num_random_numbers++;
            printk("Added random number: %d\n", number);
            print_random_numbers();
        } else {
            printk("Random number %d already exists in the list\n", number);
        }
    } else {
        printk("Maximum number of coasters reached\n");
    }
}



static void start_scan(void);

static struct bt_conn *default_conn;

static struct bt_gatt_discover_params discover_params;

struct discovered_gatt_descriptor {
	uint16_t handle;
	struct bt_uuid_128 uuid;
};

struct discovered_gatt_characteristic {
	uint16_t handle;
	uint16_t value_handle;
	struct bt_uuid_128 uuid;
	int num_descriptors;
	struct discovered_gatt_descriptor descriptors[10];
};

struct discovered_gatt_service {
	uint16_t handle;
	uint16_t end_handle;
	struct bt_uuid_128 uuid;
	int num_characteristics;
	struct discovered_gatt_characteristic characteristics[10];
};

int num_discovered_services = 0;
struct discovered_gatt_service services[10];

enum discovering_state {
	DISC_STATE_SERVICES = 0,
	DISC_STATE_CHARACTERISTICS = 1,
	DISC_STATE_DESCRIPTORS = 2,
	DISC_STATE_DONE = 3,
};

enum discovering_state disc_state = DISC_STATE_SERVICES;
int discovering_index_svc = 0;


static struct bt_gatt_subscribe_params subscribe_params[5000]; 
static int num_subscriptions = 0;

static void notification_received_cb(struct bt_conn *conn,
                                     struct bt_gatt_subscribe_params *params,
                                     const void *data, uint16_t length)
{

    // Find the characteristic UUID
    uint16_t value_handle = params->value_handle;
    const char *char_uuid_str = NULL;
    for (int s = 0; s < num_discovered_services; s++) {
        for (int c = 0; c < services[s].num_characteristics; c++) {
            if (services[s].characteristics[c].value_handle == value_handle) {
                // Get UUID of characterisitc
                char_uuid_str = bt_uuid_str((struct bt_uuid *) &services[s].characteristics[c].uuid);
            }
        }
    }
	// Process the data received from notification
    const uint8_t *data_bytes = data;

	return BT_GATT_ITER_CONTINUE;

}



static void enable_notifications_and_subscribe(uint16_t cccd_handle, uint16_t value_handle, struct bt_conn *conn) {
    if (num_subscriptions >= sizeof(subscribe_params) / sizeof(subscribe_params[0])) {
        printk("Maximum number of subscriptions reached\n");
        return;
    }

    uint8_t enable_notifications[2] = {0x01, 0x00};
    int err;

    // Enable notifications
    err = bt_gatt_write_without_response(conn, cccd_handle, &enable_notifications, sizeof(enable_notifications), false);
    if (err) {
        printk("Error enabling notifications: %d\n", err);
        return;
    } else {
        //printk("Notifications enabled on handle: 0x%04x\n", cccd_handle);
    }

    // Set up subscription parameters
    struct bt_gatt_subscribe_params *params = &subscribe_params[num_subscriptions++];
    params->ccc_handle = cccd_handle;
    params->value_handle = value_handle;
    params->value = BT_GATT_CCC_NOTIFY;
    params->notify = notification_received_cb;

    // Subscribe to notifications
    err = bt_gatt_subscribe(conn, params);
    if (err && err != -EALREADY) {
        printk("Subscription failed (err %d)\n", err);
    } else {
        //printk("Subscribed to notifications on handle: 0x%04x\n", value_handle);
    }
}

void enable_notifications_for_all_characteristics(struct bt_conn *conn) {
    for (int s = 0; s < num_discovered_services; s++) {
        for (int c = 0; c < services[s].num_characteristics; c++) {
            for (int d = 0; d < services[s].characteristics[c].num_descriptors; d++) {
                struct discovered_gatt_descriptor* desc = &services[s].characteristics[c].descriptors[d];
                if (bt_uuid_cmp((struct bt_uuid*)&desc->uuid, BT_UUID_GATT_CCC) == 0) {
                    // Enable notifications and subscribe
                    enable_notifications_and_subscribe(desc->handle, services[s].characteristics[c].value_handle, conn);
                }
            }
        }
    }
}

static uint8_t discover_func(struct bt_conn *conn,
			                 const struct bt_gatt_attr *attr,
			                 struct bt_gatt_discover_params *params)
{
	int err;

	if (!attr) {
		if (disc_state == DISC_STATE_SERVICES) {
			disc_state = DISC_STATE_CHARACTERISTICS;
			discovering_index_svc = 0;

			if (num_discovered_services > 0) {
				discover_params.uuid = NULL;
				discover_params.func = discover_func;
				discover_params.start_handle = services[discovering_index_svc].handle + 1;
				discover_params.end_handle = services[discovering_index_svc].end_handle;
				discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
				err = bt_gatt_discover(conn, &discover_params);
			}
		}
		else if (disc_state == DISC_STATE_CHARACTERISTICS) {
			discovering_index_svc += 1;

			if (discovering_index_svc < num_discovered_services) {
				discover_params.uuid = NULL;
				discover_params.func = discover_func;
				discover_params.start_handle = services[discovering_index_svc].handle + 1;
				discover_params.end_handle = services[discovering_index_svc].end_handle;
				discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
				err = bt_gatt_discover(conn, &discover_params);
			} else {
				// Descriptors
				disc_state = DISC_STATE_DESCRIPTORS;
				discovering_index_svc = 0;

				discover_params.uuid = NULL;
				discover_params.func = discover_func;
				discover_params.start_handle = services[discovering_index_svc].handle + 1;
				discover_params.end_handle = services[discovering_index_svc].end_handle;
				discover_params.type = BT_GATT_DISCOVER_DESCRIPTOR;
				err = bt_gatt_discover(conn, &discover_params);
			}
		} else if (disc_state == DISC_STATE_DESCRIPTORS) {
			discovering_index_svc += 1;
			if (discovering_index_svc < num_discovered_services) {
				discover_params.uuid = NULL;
				discover_params.func = discover_func;
				discover_params.start_handle = services[discovering_index_svc].handle + 1;
				discover_params.end_handle = services[discovering_index_svc].end_handle;
				discover_params.type = BT_GATT_DISCOVER_DESCRIPTOR;
				err = bt_gatt_discover(conn, &discover_params);
			} else {
				disc_state = DISC_STATE_DONE;
				uint16_t cccd_handle = 0;
				for (int s = 0; s < num_discovered_services; s++) {
					for (int c = 0; c < services[s].num_characteristics; c++) {
						for (int d = 0; d < services[s].characteristics[c].num_descriptors; d++) {
							if (bt_uuid_cmp(&services[s].characteristics[c].descriptors[d].uuid, BT_UUID_GATT_CCC) == 0) {
								cccd_handle = services[s].characteristics[c].descriptors[d].handle;
								// Enable notifications
								enable_notifications_for_all_characteristics(conn);
								break;
							}
						}
					}
				}

				// Print everything discovered
				char str[128];
				int s, c, d;
				for (s=0; s<num_discovered_services; s++) {
					struct discovered_gatt_service* disc_serv = &services[s];
					bt_uuid_to_str((struct bt_uuid*) &disc_serv->uuid, str, 128);
					for (c=0; c<disc_serv->num_characteristics; c++) {
						struct discovered_gatt_characteristic* disc_char = &disc_serv->characteristics[c];
						bt_uuid_to_str((struct bt_uuid*) &disc_char->uuid, str, 128);
						//printk("  -Characteristic [%s] - handle: 0x%02x\n", str, disc_char->handle);
						//printk("  ---Value handle: 0x%02x\n", disc_char->value_handle);
						for (d=0; d<disc_char->num_descriptors; d++) {
							struct discovered_gatt_descriptor* disc_desc = &disc_char->descriptors[d];
							if (bt_uuid_cmp((struct bt_uuid*) &disc_desc->uuid, BT_UUID_GATT_CCC) == 0) {
								//printk("  ---CCC - handle: 0x%02x\n", disc_desc->handle);
							} else {
								bt_uuid_to_str((struct bt_uuid*) &disc_desc->uuid, str, 128);
								//printk("  ---Descriptor [%s] - handle: 0x%02x\n", str, disc_char->handle);
							}
						}
					}
				}
			}
		}

		return BT_GATT_ITER_STOP;
	}

	if (params->type == BT_GATT_DISCOVER_PRIMARY) {
		struct bt_gatt_service_val* gatt_service = (struct bt_gatt_service_val*) attr->user_data;
		services[num_discovered_services] = (struct discovered_gatt_service) {
			.handle = attr->handle,
			.end_handle = gatt_service->end_handle,
			.num_characteristics = 0
		};
		memcpy(&services[num_discovered_services].uuid, BT_UUID_128(gatt_service->uuid),
			       sizeof(services[num_discovered_services].uuid));

		num_discovered_services += 1;
	}
	else if (params->type == BT_GATT_DISCOVER_CHARACTERISTIC) {

		struct bt_gatt_chrc* gatt_characteristic = (struct bt_gatt_chrc*) attr->user_data;

		struct discovered_gatt_service* disc_serv_loc = &services[discovering_index_svc];
		struct discovered_gatt_characteristic* disc_char_loc = &disc_serv_loc->characteristics[disc_serv_loc->num_characteristics];

		*disc_char_loc = (struct discovered_gatt_characteristic) {
			.handle = attr->handle,
			.value_handle = gatt_characteristic->value_handle,
			.num_descriptors = 0,
		};
		memcpy(&disc_char_loc->uuid, BT_UUID_128(gatt_characteristic->uuid), sizeof(disc_char_loc->uuid));

		services[discovering_index_svc].num_characteristics += 1;
	}
	else if (params->type == BT_GATT_DISCOVER_DESCRIPTOR) {
		uint16_t handle = attr->handle;
		int i;

		int matched_characteristic = 0;
		for (i=1; i<services[discovering_index_svc].num_characteristics; i++) {
			if (handle < services[discovering_index_svc].characteristics[i].handle) {
				break;
			}
			matched_characteristic = i;
		}

		struct discovered_gatt_service* disc_serv_loc = &services[discovering_index_svc];
		struct discovered_gatt_characteristic* disc_char_loc = &disc_serv_loc->characteristics[matched_characteristic];
		struct discovered_gatt_descriptor* disc_desc_loc = &disc_char_loc->descriptors[disc_char_loc->num_descriptors];

		*disc_desc_loc = (struct discovered_gatt_descriptor) {
			.handle = handle,
		};
		memcpy(&disc_desc_loc->uuid, BT_UUID_128(attr->uuid), sizeof(disc_desc_loc->uuid));

		disc_char_loc->num_descriptors += 1;
	}

	return BT_GATT_ITER_CONTINUE;
}

static void connected(struct bt_conn *conn, uint8_t conn_err)
{
	char addr[BT_ADDR_LE_STR_LEN];
	int err;

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (conn_err) {
		printk("Failed to connect to %s (%u)\n", addr, conn_err);

		bt_conn_unref(default_conn);
		default_conn = NULL;

		start_scan();
		return;
	}

	printk("Connected: %s\n", addr);

	if (conn == default_conn) {
		discover_params.uuid = NULL;
		discover_params.func = discover_func;
		discover_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
		discover_params.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE;
		discover_params.type = BT_GATT_DISCOVER_PRIMARY;

		disc_state = DISC_STATE_SERVICES;

		err = bt_gatt_discover(default_conn, &discover_params);
		if (err) {
			printk("Discover failed(err %d)\n", err);
			return;
		}
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Disconnected: %s (reason 0x%02x)\n", addr, reason);

	if (default_conn != conn) {
		return;
	}

	bt_conn_unref(default_conn);
	default_conn = NULL;

	start_scan();
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

// Called for each advertising data element in the advertising data.
static bool ad_found(struct bt_data *data, void *user_data)
{
	bt_addr_le_t *addr = user_data;

	switch (data->type) {
	case BT_DATA_UUID128_ALL:
		if (data->data_len != 16) {
			printk("AD malformed\n");
			return true;
		}

		struct bt_le_conn_param *param;
		struct bt_uuid uuid;
		int err;

		bt_uuid_create(&uuid, data->data, 16);
		if (bt_uuid_cmp(&uuid, BT_UUID_DECLARE_128(SEARCH_UUID)) == 0) {
			printk("Found matching advertisement\n");

			err = bt_le_scan_stop();
			printk("[AD]: type %u, data_len %u\n", data->type, data->data_len);
			for (int i = 0; i < data->data_len; i++) {
				printk("%02x ", data->data[i]);
			}
			printk("\n");
			if (err) {
				printk("Stop LE scan failed (err %d)\n", err);
				return false;
			}

			param = BT_LE_CONN_PARAM_DEFAULT;
			err = bt_conn_le_create(addr, BT_CONN_LE_CREATE_CONN, param, &default_conn);
			if (err) {
				printk("Create conn failed (err %d)\n", err);
				start_scan();
			}
		}

		return false;
	case BT_DATA_NAME_COMPLETE:

		// Check if received data is a number
		bool is_number = true;
		for (int i = 0; i < data->data_len; i++) {
			if (!isdigit(data->data[i])) {
				is_number = false;
				break;
			}
		}
		if (is_number) {
			// Convert received data to integer
			printk("Received data: %.*s\n", data->data_len, data->data);
			int random_number = atoi(data->data);

			// Print the received random number
			//printk("Converted random number: %d\n", random_number);

			// Add random number to the list
			add_random_number(random_number);

			// Print the list of random numbers for debugging
			// printk("Current list of random numbers:\n");
			// for (int i = 0; i < num_random_numbers; i++) {
			// 	printk("%d\n", random_numbers[i].random_number);
			// }

			// Print random numbers
			print_random_numbers();
		} else {
			printk("Received data is not a number\n");
		}

		return false;
		}

	return true;
}

static void device_found(const bt_addr_le_t *addr, int8_t rssi, uint8_t type,
			 struct net_buf_simple *ad)
{
	char dev[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(addr, dev, sizeof(dev));

	// Connectable devices.
	if (type == BT_GAP_ADV_TYPE_ADV_IND ||
	    type == BT_GAP_ADV_TYPE_ADV_DIRECT_IND) {

		bt_data_parse(ad, ad_found, (void*) addr);
	}
}

static void start_scan(void)
{
	int err;

	struct bt_le_scan_param scan_param = {
		.type       = BT_LE_SCAN_TYPE_PASSIVE,
		.options    = BT_LE_SCAN_OPT_NONE,
		.interval   = BT_GAP_SCAN_FAST_INTERVAL,
		.window     = BT_GAP_SCAN_FAST_WINDOW,
	};

	err = bt_le_scan_start(&scan_param, device_found);
	if (err) {
		printk("Scanning failed to start (err %d)\n", err);
		return;
	}

	printk("Scanning successfully started\n");
}

static void bt_ready(int err)
{
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");

	start_scan();
}

int main(void)
{
	int err;

	err = bt_enable(bt_ready);

	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return -1;
	}

	return 0;
}
