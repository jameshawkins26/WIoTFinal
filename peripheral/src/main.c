/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *
 * @defgroup nfc_writable_ndef_msg_example_main main.c
 * @{
 * @ingroup nfc_writable_ndef_msg_example
 * @brief The application main file of NFC writable NDEF message example.
 *
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>
#include <stdbool.h>
#include <nfc_t4t_lib.h>

#include <nfc_t2t_lib.h>
#include <nfc/ndef/msg.h>
#include <nfc/ndef/text_rec.h>

#include <nfc/ndef/msg.h>
#include <nfc/t4t/ndef_file.h>

#include <dk_buttons_and_leds.h>

#include "ndef_file_m.h"

#include <stdio.h>
#include <stdlib.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>

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


#define NFC_FIELD_LED		DK_LED1
#define NFC_WRITE_LED		DK_LED2
#define NFC_READ_LED		DK_LED4

#define NDEF_RESTORE_BTN_MSK	DK_BTN1_MSK

#define MAX_REC_COUNT       3
#define NEW_NDEF_MSG_BUF_SIZE   512

#define NFC_FIELD_LED       DK_LED1

#define LAB2_SERVICE_UUID BT_UUID_128_ENCODE(0x5253FF4B, 0xE47C, 0x4EC8, 0x9792, 0x69FDF4923B4A)

// Set up the advertisement data.
#define DEVICE_NAME "group2"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
//BDFC9792-8234-405E-AE02-35EF4174B299
#define NEW_SERVICE_UUID BT_UUID_128_ENCODE(0xBDFC9792, 0x8234, 0x405E, 0xAE02, 0x35EF4174B299)
#define CUSTOM_SERVICE_UUID BT_UUID_128_ENCODE(0xBDFC9792, 0x8234, 0x405E, 0xAE02, 0x35EF4174B299)

static uint8_t en_payload[5]; // Changed to 3 bytes
static const uint8_t en_code[] = {'e', 'n'};

/* Buffer used to hold an NFC NDEF message. */
static uint8_t new_ndef_msg_buf[NEW_NDEF_MSG_BUF_SIZE];


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
}

/* Function to generate a random number */
static int generateRandomNumber() {
    return rand() % 1000001;
}

static uint8_t ndef_msg_buf[512]; /**< Buffer for NDEF file. */

enum {
	FLASH_WRITE_FINISHED,
	FLASH_BUF_PREP_STARTED,
	FLASH_BUF_PREP_FINISHED,
	FLASH_WRITE_STARTED,
};
static atomic_t op_flags;
static uint8_t flash_buf[CONFIG_NDEF_FILE_SIZE]; /**< Buffer for flash update. */
static uint8_t flash_buf_len; /**< Length of the flash buffer. */

static void flash_buffer_prepare(size_t data_length)
{
	if (atomic_cas(&op_flags, FLASH_WRITE_FINISHED,
			FLASH_BUF_PREP_STARTED)) {
		flash_buf_len = data_length + NFC_NDEF_FILE_NLEN_FIELD_SIZE;
		memcpy(flash_buf, ndef_msg_buf, sizeof(flash_buf));

		atomic_set(&op_flags, FLASH_BUF_PREP_FINISHED);
	} else {
		printk("Flash update pending. Discarding new data...\n");
	}

}

static int welcome_msg_encode(uint8_t *buffer, uint32_t *len, int randomNumber)
{
	printk("in welcome message encode");
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
	printk("record added");

    err = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_text_msg),
                              buffer,
                              len);
	printk("message encoded");
	printk(err);
    if (err < 0) {
        printk("Cannot encode message!\n");
    }
	printk("welcome msg done");
    return err;
	
}

/**
 * @brief Callback function for handling NFC events.
 */
static void nfc_callback(void *context,
			 nfc_t4t_event_t event,
			 const uint8_t *data,
			 size_t data_length,
			 uint32_t flags)
{
	ARG_UNUSED(context);
	ARG_UNUSED(data);
	ARG_UNUSED(flags);

	switch (event) {
	case NFC_T4T_EVENT_FIELD_ON:
		dk_set_led_on(NFC_FIELD_LED);
		break;

	case NFC_T4T_EVENT_FIELD_OFF:
		dk_set_leds(DK_NO_LEDS_MSK);
		break;

	case NFC_T4T_EVENT_NDEF_READ:
		dk_set_led_on(NFC_READ_LED);
		break;

	case NFC_T4T_EVENT_NDEF_UPDATED:
		if (data_length > 0) {
			dk_set_led_on(NFC_WRITE_LED);
			flash_buffer_prepare(data_length);
		}
		break;

	default:
		break;
	}
}

static int board_init(void)
{
	int err;

	err = dk_buttons_init(NULL);
	if (err) {
		printk("Cannot init buttons (err: %d)\n", err);
		return err;
	}

	err = dk_leds_init();
	if (err) {
		printk("Cannot init LEDs (err: %d)\n", err);
	}

	return err;
}

/**
 * @brief   Function for application main entry.
 */
int main(void)
{
	printk("Starting Nordic NFC Writable NDEF Message example\n");

	/* Configure LED-pins as outputs. */
	if (board_init() < 0) {
		printk("Cannot initialize board!\n");
		goto fail;
	}
	/* Initialize NVS. */
	if (ndef_file_setup() < 0) {
		printk("Cannot setup NDEF file!\n");
		goto fail;
	}
	/* Load NDEF message from the flash file. */
	if (ndef_file_load(ndef_msg_buf, sizeof(ndef_msg_buf)) < 0) {
		printk("Cannot load NDEF file!\n");
		goto fail;
	}

	/* Restore default NDEF message if button is pressed. */
	uint32_t button_state;

	dk_read_buttons(&button_state, NULL);
	if (button_state & NDEF_RESTORE_BTN_MSK) {
		if (ndef_restore_default(ndef_msg_buf,
					 sizeof(ndef_msg_buf)) < 0) {
			printk("Cannot flash NDEF message!\n");
			goto fail;
		}
		printk("Default NDEF message restored!\n");
	}
	/* Set up NFC */
	int err = nfc_t4t_setup(nfc_callback, NULL);

	if (err < 0) {
		printk("Cannot setup t4t library!\n");
		goto fail;
	}

	srand(k_cycle_get_32());

    /* Generate random number */
    randomNumber = generateRandomNumber();

    int new_err;

    uint32_t len = sizeof(new_ndef_msg_buf);

	if (welcome_msg_encode(new_ndef_msg_buf, &len, randomNumber) < 0) {
        printk("Cannot encode message!\n");
        goto fail;
    }

    new_err = bt_enable(bt_ready);
    if (new_err) {
        printk("Bluetooth init failed (err %d)\n", new_err);
        return;
    }

	

	/* Run Read-Write mode for Type 4 Tag platform */
	if (nfc_t4t_ndef_rwpayload_set(ndef_msg_buf,
				       sizeof(ndef_msg_buf)) < 0) {
		printk("Cannot set payload!\n");
		goto fail;
	}
	/* Start sensing NFC field */
	if (nfc_t4t_emulation_start() < 0) {
		printk("Cannot start emulation!\n");
		goto fail;
	}

	
	// printk("Starting NFC Writable NDEF Message example\n");

	// uint32_t len = sizeof(ndef_msg_buf);

	// if (welcome_msg_encode(new_ndef_msg_buf, &len, randomNumber) < 0) {
    //     printk("Cannot encode message!\n");
    //     goto fail;
    // }

	// printk("after welcome msg encode");

	while (true) {
        printk("in while loop");
		if (atomic_cas(&op_flags, FLASH_BUF_PREP_FINISHED,
				FLASH_WRITE_STARTED)) {
					
			if (ndef_file_update(flash_buf, flash_buf_len) < 0) {
				printk("Cannot flash NDEF message!\n");
			} else {
				printk("NDEF message successfully flashed.\n");
			}

			atomic_set(&op_flags, FLASH_WRITE_FINISHED);
		}

		k_cpu_atomic_idle(irq_lock());
	}
	
	

fail:
	#if CONFIG_REBOOT
		sys_reboot(SYS_REBOOT_COLD);
	#endif /* CONFIG_REBOOT */
		return -EIO;
}
/** @} */
