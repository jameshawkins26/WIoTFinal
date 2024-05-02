#include <stdio.h>
#include <stdlib.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>

#include <nfc_t2t_lib.h>
#include <nfc/ndef/msg.h>
#include <nfc/ndef/text_rec.h>

#include <dk_buttons_and_leds.h>

#include <stdbool.h>
#include <zephyr/types.h>
#include <zephyr/drivers/sensor.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/dt-bindings/gpio/gpio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>
#include <nfc/ndef/uri_rec.h>
#include <zephyr/kernel.h>
#include <soc.h>
#include <zephyr/device.h>
#include <string.h>
#include <zephyr/fs/nvs.h>
#include <nfc/t4t/ndef_file.h>
#include <nfc/ndef/uri_msg.h>
#include <zephyr/storage/flash_map.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>

#include <nfc_t2t_lib.h>
#include <nfc/ndef/msg.h>
#include <nfc/ndef/uri_rec.h>

#include <dk_buttons_and_leds.h>

#include <zephyr/kernel.h>
#include <soc.h>
#include <zephyr/device.h>
#include <string.h>
#include <zephyr/fs/nvs.h>
#include <nfc/t4t/ndef_file.h>
#include <nfc/ndef/uri_msg.h>
#include <zephyr/storage/flash_map.h>


#define MAX_REC_COUNT       3
#define NDEF_MSG_BUF_SIZE   128

#define NFC_FIELD_LED       DK_LED1

#define LAB2_SERVICE_UUID BT_UUID_128_ENCODE(0x5253FF4B, 0xE47C, 0x4EC8, 0x9792, 0x69FDF4923B4A)

uint32_t characteristic_value = 0x0;

// Set up the advertisement data.
#define DEVICE_NAME "group2"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
//BDFC9792-8234-405E-AE02-35EF4174B299
#define NEW_SERVICE_UUID BT_UUID_128_ENCODE(0xBDFC9792, 0x8234, 0x405E, 0xAE02, 0x35EF4174B299)
#define CUSTOM_SERVICE_UUID BT_UUID_128_ENCODE(0xBDFC9792, 0x8234, 0x405E, 0xAE02, 0x35EF4174B299)

static uint8_t en_payload[5]; // Changed to 3 bytes
static const uint8_t en_code[] = {'e', 'n'};

// static const uint8_t m_url[] = 
// 	{'c', 's', '.', 'v', 'i', 'r', 'g', 'i', 'n', 'i', 'a', '.', 'e', 'd', 'u', '/','~', 'j', 'r', 'h', '4', 'a', 'z', '/', 'w', 'i', 'o', 't', 'f', 'i', 'n', 'a', 'l', '.', 'h', 't', 'm', 'l'
// };


#define FLASH_URL_ADDRESS_ID 5

//static const uint8_t url_prefix[] = {'h', 't', 't', 'p', ':', '/', '/'};
//static const uint8_t url_payload[] = {'c', 's', '.', 'v', 'i', 'r', 'g', 'i', 'n', 'i', 'a', '.', 'e', 'd', 'u', '/','~', 'j', 'r', 'h', '4', 'a', 'z', '/', 'w', 'i', 'o', 't', 'f', 'i', 'n', 'a', 'l', '.', 'h', 't', 'm', 'l'};

/* Buffer used to hold an NFC NDEF message. */
static uint8_t ndef_msg_buf[NDEF_MSG_BUF_SIZE];


int randomNumber;

BT_GATT_SERVICE_DEFINE(lab2_service,
    BT_GATT_PRIMARY_SERVICE(
        BT_UUID_DECLARE_128(NEW_SERVICE_UUID)
    ));

// Setup callbacks when devices connect and disconnect.
static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printk("Connection failed (err 0x%02x)\n", err);
    } else {
        printk("Connected\n");
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    printk("Disconnected (reason 0x%02x)\n", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

static struct bt_data ad[2]; 
static void bt_ready(int err)
{
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    // Convert the random number to a string
    char random_str[5]; // Assuming the random number is within 99999
    snprintf(random_str, sizeof(random_str), "%d", randomNumber);

    // Explicitly set advertisement data elements
    ad[0] = (struct bt_data)BT_DATA(BT_DATA_NAME_COMPLETE, random_str, strlen(random_str));
    ad[1] = (struct bt_data)BT_DATA_BYTES(BT_DATA_UUID128_ALL, NEW_SERVICE_UUID);

    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    printk("Advertising successfully started\n");

    // for (size_t i = 0; i < ARRAY_SIZE(ad); i++) {
    //     switch (ad[i].type) {
    //         case BT_DATA_NAME_SHORTENED:
    //             printk("Number (shortened): %.*s\n", ad[i].data_len, ad[i].data);
    //             break;
    //         case BT_DATA_NAME_COMPLETE:
    //             printk("Number (complete): %.*s\n", ad[i].data_len, ad[i].data);
    //             printk(ad[i].data);
    //             break;
    //     }
    // }
}

/* Function to generate a random number */
static int generateRandomNumber() {
    return rand() % 1000001;
}

/* Function to encode the NDEF text message */
static int welcome_msg_encode(uint8_t *buffer, uint32_t *len, int randomNumber)
{
    int err;

    /* Convert random number to character array */
    snprintf(en_payload, sizeof(en_payload), "%d", randomNumber);

    /* Create NFC NDEF text record description in English */
    NFC_NDEF_TEXT_RECORD_DESC_DEF(nfc_en_text_rec,
                                  UTF_8,
                                  en_code,
                                  sizeof(en_code),
                                  en_payload,
                                  sizeof(en_payload));

    /* Create NFC NDEF message description, capacity - MAX_REC_COUNT
     * records
     */
    NFC_NDEF_MSG_DEF(nfc_text_msg, MAX_REC_COUNT);

    /* Add text record to NDEF text message */
    err = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_text_msg),
                                   &NFC_NDEF_TEXT_RECORD_DESC(nfc_en_text_rec));
    if (err < 0) {
        printk("Cannot add record!\n");
        return err;
    }


    err = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_text_msg),
                              buffer,
                              len);
    if (err < 0) {
        printk("Cannot encode message!\n");
    }
    //  err = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_uri_msg),
    //                           buffer,
    //                           len);
    // if (err < 0) {
    //     printk("Cannot encode message!\n");
    // }

    return err;
}

static int uri_msg_encode(uint8_t *buffer, uint32_t *len)
{
    int err;

    /* Create NFC NDEF URI record description for Google */
   /* Create NFC NDEF URI record description for Google */
	NFC_NDEF_URI_RECORD_DESC_DEF(nfc_uri_google_rec,
                              NFC_URI_HTTPS,
                              "cs.virginia.edu/~jrh4az/wiotfinal.html",
                              sizeof("cs.virginia.edu/~jrh4az/wiotfinal.html"));


    /* Create NFC NDEF message description, capacity - MAX_REC_COUNT
     * records
     */
    NFC_NDEF_MSG_DEF(nfc_uri_msg, MAX_REC_COUNT);

    /* Add URI record to NDEF URI message */
    err = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_uri_msg),
                                   &NFC_NDEF_URI_RECORD_DESC(nfc_uri_google_rec));
    if (err < 0) {
        printk("Cannot add URI record!\n");
        return err;
    }

    err = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_uri_msg),
                               buffer,
                               len);
    if (err < 0) {
        printk("Cannot encode message!\n");
    }

    return err;
}

static void nfc_callback(void *context,
                         nfc_t2t_event_t event,
                         const uint8_t *data,
                         size_t data_length)
{
    ARG_UNUSED(context);
    ARG_UNUSED(data);
    ARG_UNUSED(data_length);

    switch (event) {
    case NFC_T2T_EVENT_FIELD_ON:
        dk_set_led_on(NFC_FIELD_LED);
        break;
    case NFC_T2T_EVENT_FIELD_OFF:
        dk_set_led_off(NFC_FIELD_LED);
        break;
    default:
        break;
    }
}

int main(void)
{
    uint32_t len = sizeof(ndef_msg_buf);
    uint8_t uri_msg_buf[NDEF_MSG_BUF_SIZE];
    uint32_t uri_len = sizeof(uri_msg_buf);

    printk("Starting NFC Text Record example\n");

    /* Configure LED-pins as outputs */
    if (dk_leds_init() < 0) {
        printk("Cannot init LEDs!\n");
        goto fail;
    }

    /* Set up NFC */
    if (nfc_t2t_setup(nfc_callback, NULL) < 0) {
        printk("Cannot setup NFC T2T library!\n");
        goto fail;
    }

    /* Seed the random number generator using system uptime */
    srand(k_cycle_get_32());

    /* Generate random number */
    randomNumber = generateRandomNumber();

    int err;

    err = bt_enable(bt_ready);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    /* Encode welcome message with the generated random number */
    if (welcome_msg_encode(ndef_msg_buf, &len, randomNumber) < 0) {
        printk("Cannot encode message!\n");
        goto fail;
    }

    /* Encode URI message */
    if (uri_msg_encode(uri_msg_buf, &uri_len) < 0) {
        printk("Cannot encode URI message!\n");
        goto fail;
    }

    /* Combine URI message and text message into a single NDEF message */
    if (len + uri_len > NDEF_MSG_BUF_SIZE) {
        printk("Combined message too large!\n");
        goto fail;
    }

    memcpy(ndef_msg_buf + len, uri_msg_buf, uri_len);
    len += uri_len;


    /* Set created message as the NFC payload */
    if (nfc_t2t_payload_set(ndef_msg_buf, len) < 0) {
        printk("Cannot set payload!\n");
        goto fail;
    }

    /* Start sensing NFC field */
    if (nfc_t2t_emulation_start() < 0) {
        printk("Cannot start emulation!\n");
        goto fail;
    }
    printk("NFC configuration done\n");

    return 0;

fail:
#if CONFIG_REBOOT
    sys_reboot(SYS_REBOOT_COLD);
#endif /* CONFIG_REBOOT */

    return -EIO;
}


