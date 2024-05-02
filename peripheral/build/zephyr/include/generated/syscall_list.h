/* auto-generated by gen_syscalls.py, don't edit */

#ifndef ZEPHYR_SYSCALL_LIST_H
#define ZEPHYR_SYSCALL_LIST_H

#define K_SYSCALL_CLOCK_GETTIME 0
#define K_SYSCALL_DEVICE_GET_BINDING 1
#define K_SYSCALL_DEVICE_IS_READY 2
#define K_SYSCALL_ENTROPY_GET_ENTROPY 3
#define K_SYSCALL_FLASH_ERASE 4
#define K_SYSCALL_FLASH_EX_OP 5
#define K_SYSCALL_FLASH_GET_PAGE_COUNT 6
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_IDX 7
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_OFFS 8
#define K_SYSCALL_FLASH_GET_PARAMETERS 9
#define K_SYSCALL_FLASH_GET_WRITE_BLOCK_SIZE 10
#define K_SYSCALL_FLASH_READ 11
#define K_SYSCALL_FLASH_READ_JEDEC_ID 12
#define K_SYSCALL_FLASH_SFDP_READ 13
#define K_SYSCALL_FLASH_WRITE 14
#define K_SYSCALL_GPIO_GET_PENDING_INT 15
#define K_SYSCALL_GPIO_PIN_CONFIGURE 16
#define K_SYSCALL_GPIO_PIN_GET_CONFIG 17
#define K_SYSCALL_GPIO_PIN_INTERRUPT_CONFIGURE 18
#define K_SYSCALL_GPIO_PORT_CLEAR_BITS_RAW 19
#define K_SYSCALL_GPIO_PORT_GET_DIRECTION 20
#define K_SYSCALL_GPIO_PORT_GET_RAW 21
#define K_SYSCALL_GPIO_PORT_SET_BITS_RAW 22
#define K_SYSCALL_GPIO_PORT_SET_MASKED_RAW 23
#define K_SYSCALL_GPIO_PORT_TOGGLE_BITS 24
#define K_SYSCALL_K_BUSY_WAIT 25
#define K_SYSCALL_K_CONDVAR_BROADCAST 26
#define K_SYSCALL_K_CONDVAR_INIT 27
#define K_SYSCALL_K_CONDVAR_SIGNAL 28
#define K_SYSCALL_K_CONDVAR_WAIT 29
#define K_SYSCALL_K_EVENT_CLEAR 30
#define K_SYSCALL_K_EVENT_INIT 31
#define K_SYSCALL_K_EVENT_POST 32
#define K_SYSCALL_K_EVENT_SET 33
#define K_SYSCALL_K_EVENT_SET_MASKED 34
#define K_SYSCALL_K_EVENT_WAIT 35
#define K_SYSCALL_K_EVENT_WAIT_ALL 36
#define K_SYSCALL_K_FLOAT_DISABLE 37
#define K_SYSCALL_K_FLOAT_ENABLE 38
#define K_SYSCALL_K_FUTEX_WAIT 39
#define K_SYSCALL_K_FUTEX_WAKE 40
#define K_SYSCALL_K_IS_PREEMPT_THREAD 41
#define K_SYSCALL_K_MSGQ_ALLOC_INIT 42
#define K_SYSCALL_K_MSGQ_GET 43
#define K_SYSCALL_K_MSGQ_GET_ATTRS 44
#define K_SYSCALL_K_MSGQ_NUM_FREE_GET 45
#define K_SYSCALL_K_MSGQ_NUM_USED_GET 46
#define K_SYSCALL_K_MSGQ_PEEK 47
#define K_SYSCALL_K_MSGQ_PEEK_AT 48
#define K_SYSCALL_K_MSGQ_PURGE 49
#define K_SYSCALL_K_MSGQ_PUT 50
#define K_SYSCALL_K_MUTEX_INIT 51
#define K_SYSCALL_K_MUTEX_LOCK 52
#define K_SYSCALL_K_MUTEX_UNLOCK 53
#define K_SYSCALL_K_OBJECT_ACCESS_GRANT 54
#define K_SYSCALL_K_OBJECT_ALLOC 55
#define K_SYSCALL_K_OBJECT_ALLOC_SIZE 56
#define K_SYSCALL_K_OBJECT_RELEASE 57
#define K_SYSCALL_K_PIPE_ALLOC_INIT 58
#define K_SYSCALL_K_PIPE_BUFFER_FLUSH 59
#define K_SYSCALL_K_PIPE_FLUSH 60
#define K_SYSCALL_K_PIPE_GET 61
#define K_SYSCALL_K_PIPE_PUT 62
#define K_SYSCALL_K_PIPE_READ_AVAIL 63
#define K_SYSCALL_K_PIPE_WRITE_AVAIL 64
#define K_SYSCALL_K_POLL 65
#define K_SYSCALL_K_POLL_SIGNAL_CHECK 66
#define K_SYSCALL_K_POLL_SIGNAL_INIT 67
#define K_SYSCALL_K_POLL_SIGNAL_RAISE 68
#define K_SYSCALL_K_POLL_SIGNAL_RESET 69
#define K_SYSCALL_K_QUEUE_ALLOC_APPEND 70
#define K_SYSCALL_K_QUEUE_ALLOC_PREPEND 71
#define K_SYSCALL_K_QUEUE_CANCEL_WAIT 72
#define K_SYSCALL_K_QUEUE_GET 73
#define K_SYSCALL_K_QUEUE_INIT 74
#define K_SYSCALL_K_QUEUE_IS_EMPTY 75
#define K_SYSCALL_K_QUEUE_PEEK_HEAD 76
#define K_SYSCALL_K_QUEUE_PEEK_TAIL 77
#define K_SYSCALL_K_SEM_COUNT_GET 78
#define K_SYSCALL_K_SEM_GIVE 79
#define K_SYSCALL_K_SEM_INIT 80
#define K_SYSCALL_K_SEM_RESET 81
#define K_SYSCALL_K_SEM_TAKE 82
#define K_SYSCALL_K_SLEEP 83
#define K_SYSCALL_K_STACK_ALLOC_INIT 84
#define K_SYSCALL_K_STACK_POP 85
#define K_SYSCALL_K_STACK_PUSH 86
#define K_SYSCALL_K_STR_OUT 87
#define K_SYSCALL_K_THREAD_ABORT 88
#define K_SYSCALL_K_THREAD_CREATE 89
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_GET 90
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_SET 91
#define K_SYSCALL_K_THREAD_DEADLINE_SET 92
#define K_SYSCALL_K_THREAD_JOIN 93
#define K_SYSCALL_K_THREAD_NAME_COPY 94
#define K_SYSCALL_K_THREAD_NAME_SET 95
#define K_SYSCALL_K_THREAD_PRIORITY_GET 96
#define K_SYSCALL_K_THREAD_PRIORITY_SET 97
#define K_SYSCALL_K_THREAD_RESUME 98
#define K_SYSCALL_K_THREAD_STACK_ALLOC 99
#define K_SYSCALL_K_THREAD_STACK_FREE 100
#define K_SYSCALL_K_THREAD_STACK_SPACE_GET 101
#define K_SYSCALL_K_THREAD_START 102
#define K_SYSCALL_K_THREAD_SUSPEND 103
#define K_SYSCALL_K_THREAD_TIMEOUT_EXPIRES_TICKS 104
#define K_SYSCALL_K_THREAD_TIMEOUT_REMAINING_TICKS 105
#define K_SYSCALL_K_TIMER_EXPIRES_TICKS 106
#define K_SYSCALL_K_TIMER_REMAINING_TICKS 107
#define K_SYSCALL_K_TIMER_START 108
#define K_SYSCALL_K_TIMER_STATUS_GET 109
#define K_SYSCALL_K_TIMER_STATUS_SYNC 110
#define K_SYSCALL_K_TIMER_STOP 111
#define K_SYSCALL_K_TIMER_USER_DATA_GET 112
#define K_SYSCALL_K_TIMER_USER_DATA_SET 113
#define K_SYSCALL_K_UPTIME_TICKS 114
#define K_SYSCALL_K_USLEEP 115
#define K_SYSCALL_K_WAKEUP 116
#define K_SYSCALL_K_YIELD 117
#define K_SYSCALL_LOG_BUFFERED_CNT 118
#define K_SYSCALL_LOG_FILTER_SET 119
#define K_SYSCALL_LOG_PANIC 120
#define K_SYSCALL_LOG_PROCESS 121
#define K_SYSCALL_NRF_QSPI_NOR_XIP_ENABLE 122
#define K_SYSCALL_SYS_CLOCK_HW_CYCLES_PER_SEC_RUNTIME_GET 123
#define K_SYSCALL_SYS_CSRAND_GET 124
#define K_SYSCALL_SYS_RAND32_GET 125
#define K_SYSCALL_SYS_RAND_GET 126
#define K_SYSCALL_UART_CONFIGURE 127
#define K_SYSCALL_UART_CONFIG_GET 128
#define K_SYSCALL_UART_DRV_CMD 129
#define K_SYSCALL_UART_ERR_CHECK 130
#define K_SYSCALL_UART_IRQ_ERR_DISABLE 131
#define K_SYSCALL_UART_IRQ_ERR_ENABLE 132
#define K_SYSCALL_UART_IRQ_IS_PENDING 133
#define K_SYSCALL_UART_IRQ_RX_DISABLE 134
#define K_SYSCALL_UART_IRQ_RX_ENABLE 135
#define K_SYSCALL_UART_IRQ_TX_DISABLE 136
#define K_SYSCALL_UART_IRQ_TX_ENABLE 137
#define K_SYSCALL_UART_IRQ_UPDATE 138
#define K_SYSCALL_UART_LINE_CTRL_GET 139
#define K_SYSCALL_UART_LINE_CTRL_SET 140
#define K_SYSCALL_UART_POLL_IN 141
#define K_SYSCALL_UART_POLL_IN_U16 142
#define K_SYSCALL_UART_POLL_OUT 143
#define K_SYSCALL_UART_POLL_OUT_U16 144
#define K_SYSCALL_UART_RX_DISABLE 145
#define K_SYSCALL_UART_RX_ENABLE 146
#define K_SYSCALL_UART_RX_ENABLE_U16 147
#define K_SYSCALL_UART_TX 148
#define K_SYSCALL_UART_TX_ABORT 149
#define K_SYSCALL_UART_TX_U16 150
#define K_SYSCALL_ZEPHYR_FPUTC 151
#define K_SYSCALL_ZEPHYR_FWRITE 152
#define K_SYSCALL_ZEPHYR_READ_STDIN 153
#define K_SYSCALL_ZEPHYR_WRITE_STDOUT 154
#define K_SYSCALL_Z_CURRENT_GET 155
#define K_SYSCALL_Z_LOG_MSG_RUNTIME_VCREATE 156
#define K_SYSCALL_Z_LOG_MSG_STATIC_CREATE 157
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_LOCK 158
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_UNLOCK 159
#define K_SYSCALL_BAD 160
#define K_SYSCALL_LIMIT 161


/* Following syscalls are not used in image */
#define K_SYSCALL_ADC_CHANNEL_SETUP 162
#define K_SYSCALL_ADC_READ 163
#define K_SYSCALL_ADC_READ_ASYNC 164
#define K_SYSCALL_ATOMIC_ADD 165
#define K_SYSCALL_ATOMIC_AND 166
#define K_SYSCALL_ATOMIC_CAS 167
#define K_SYSCALL_ATOMIC_NAND 168
#define K_SYSCALL_ATOMIC_OR 169
#define K_SYSCALL_ATOMIC_PTR_CAS 170
#define K_SYSCALL_ATOMIC_PTR_SET 171
#define K_SYSCALL_ATOMIC_SET 172
#define K_SYSCALL_ATOMIC_SUB 173
#define K_SYSCALL_ATOMIC_XOR 174
#define K_SYSCALL_AUXDISPLAY_BACKLIGHT_GET 175
#define K_SYSCALL_AUXDISPLAY_BACKLIGHT_SET 176
#define K_SYSCALL_AUXDISPLAY_BRIGHTNESS_GET 177
#define K_SYSCALL_AUXDISPLAY_BRIGHTNESS_SET 178
#define K_SYSCALL_AUXDISPLAY_CAPABILITIES_GET 179
#define K_SYSCALL_AUXDISPLAY_CLEAR 180
#define K_SYSCALL_AUXDISPLAY_CURSOR_POSITION_GET 181
#define K_SYSCALL_AUXDISPLAY_CURSOR_POSITION_SET 182
#define K_SYSCALL_AUXDISPLAY_CURSOR_SET_ENABLED 183
#define K_SYSCALL_AUXDISPLAY_CURSOR_SHIFT_SET 184
#define K_SYSCALL_AUXDISPLAY_CUSTOM_CHARACTER_SET 185
#define K_SYSCALL_AUXDISPLAY_CUSTOM_COMMAND 186
#define K_SYSCALL_AUXDISPLAY_DISPLAY_OFF 187
#define K_SYSCALL_AUXDISPLAY_DISPLAY_ON 188
#define K_SYSCALL_AUXDISPLAY_DISPLAY_POSITION_GET 189
#define K_SYSCALL_AUXDISPLAY_DISPLAY_POSITION_SET 190
#define K_SYSCALL_AUXDISPLAY_IS_BUSY 191
#define K_SYSCALL_AUXDISPLAY_POSITION_BLINKING_SET_ENABLED 192
#define K_SYSCALL_AUXDISPLAY_WRITE 193
#define K_SYSCALL_BBRAM_CHECK_INVALID 194
#define K_SYSCALL_BBRAM_CHECK_POWER 195
#define K_SYSCALL_BBRAM_CHECK_STANDBY_POWER 196
#define K_SYSCALL_BBRAM_GET_SIZE 197
#define K_SYSCALL_BBRAM_READ 198
#define K_SYSCALL_BBRAM_WRITE 199
#define K_SYSCALL_BC12_SET_RESULT_CB 200
#define K_SYSCALL_BC12_SET_ROLE 201
#define K_SYSCALL_CAN_ADD_RX_FILTER_MSGQ 202
#define K_SYSCALL_CAN_CALC_TIMING 203
#define K_SYSCALL_CAN_CALC_TIMING_DATA 204
#define K_SYSCALL_CAN_GET_CAPABILITIES 205
#define K_SYSCALL_CAN_GET_CORE_CLOCK 206
#define K_SYSCALL_CAN_GET_MAX_BITRATE 207
#define K_SYSCALL_CAN_GET_MAX_FILTERS 208
#define K_SYSCALL_CAN_GET_STATE 209
#define K_SYSCALL_CAN_GET_TIMING_DATA_MAX 210
#define K_SYSCALL_CAN_GET_TIMING_DATA_MIN 211
#define K_SYSCALL_CAN_GET_TIMING_MAX 212
#define K_SYSCALL_CAN_GET_TIMING_MIN 213
#define K_SYSCALL_CAN_RECOVER 214
#define K_SYSCALL_CAN_REMOVE_RX_FILTER 215
#define K_SYSCALL_CAN_SEND 216
#define K_SYSCALL_CAN_SET_BITRATE 217
#define K_SYSCALL_CAN_SET_BITRATE_DATA 218
#define K_SYSCALL_CAN_SET_MODE 219
#define K_SYSCALL_CAN_SET_TIMING 220
#define K_SYSCALL_CAN_SET_TIMING_DATA 221
#define K_SYSCALL_CAN_START 222
#define K_SYSCALL_CAN_STOP 223
#define K_SYSCALL_COUNTER_CANCEL_CHANNEL_ALARM 224
#define K_SYSCALL_COUNTER_GET_FREQUENCY 225
#define K_SYSCALL_COUNTER_GET_GUARD_PERIOD 226
#define K_SYSCALL_COUNTER_GET_MAX_TOP_VALUE 227
#define K_SYSCALL_COUNTER_GET_NUM_OF_CHANNELS 228
#define K_SYSCALL_COUNTER_GET_PENDING_INT 229
#define K_SYSCALL_COUNTER_GET_TOP_VALUE 230
#define K_SYSCALL_COUNTER_GET_VALUE 231
#define K_SYSCALL_COUNTER_GET_VALUE_64 232
#define K_SYSCALL_COUNTER_IS_COUNTING_UP 233
#define K_SYSCALL_COUNTER_SET_CHANNEL_ALARM 234
#define K_SYSCALL_COUNTER_SET_GUARD_PERIOD 235
#define K_SYSCALL_COUNTER_SET_TOP_VALUE 236
#define K_SYSCALL_COUNTER_START 237
#define K_SYSCALL_COUNTER_STOP 238
#define K_SYSCALL_COUNTER_TICKS_TO_US 239
#define K_SYSCALL_COUNTER_US_TO_TICKS 240
#define K_SYSCALL_DAC_CHANNEL_SETUP 241
#define K_SYSCALL_DAC_WRITE_VALUE 242
#define K_SYSCALL_DMA_CHAN_FILTER 243
#define K_SYSCALL_DMA_RELEASE_CHANNEL 244
#define K_SYSCALL_DMA_REQUEST_CHANNEL 245
#define K_SYSCALL_DMA_RESUME 246
#define K_SYSCALL_DMA_START 247
#define K_SYSCALL_DMA_STOP 248
#define K_SYSCALL_DMA_SUSPEND 249
#define K_SYSCALL_EEPROM_GET_SIZE 250
#define K_SYSCALL_EEPROM_READ 251
#define K_SYSCALL_EEPROM_WRITE 252
#define K_SYSCALL_ESPI_CONFIG 253
#define K_SYSCALL_ESPI_FLASH_ERASE 254
#define K_SYSCALL_ESPI_GET_CHANNEL_STATUS 255
#define K_SYSCALL_ESPI_READ_FLASH 256
#define K_SYSCALL_ESPI_READ_LPC_REQUEST 257
#define K_SYSCALL_ESPI_READ_REQUEST 258
#define K_SYSCALL_ESPI_RECEIVE_OOB 259
#define K_SYSCALL_ESPI_RECEIVE_VWIRE 260
#define K_SYSCALL_ESPI_SAF_ACTIVATE 261
#define K_SYSCALL_ESPI_SAF_CONFIG 262
#define K_SYSCALL_ESPI_SAF_FLASH_ERASE 263
#define K_SYSCALL_ESPI_SAF_FLASH_READ 264
#define K_SYSCALL_ESPI_SAF_FLASH_WRITE 265
#define K_SYSCALL_ESPI_SAF_GET_CHANNEL_STATUS 266
#define K_SYSCALL_ESPI_SAF_SET_PROTECTION_REGIONS 267
#define K_SYSCALL_ESPI_SEND_OOB 268
#define K_SYSCALL_ESPI_SEND_VWIRE 269
#define K_SYSCALL_ESPI_WRITE_FLASH 270
#define K_SYSCALL_ESPI_WRITE_LPC_REQUEST 271
#define K_SYSCALL_ESPI_WRITE_REQUEST 272
#define K_SYSCALL_FLASH_SIMULATOR_GET_MEMORY 273
#define K_SYSCALL_FUEL_GAUGE_BATTERY_CUTOFF 274
#define K_SYSCALL_FUEL_GAUGE_GET_BUFFER_PROP 275
#define K_SYSCALL_FUEL_GAUGE_GET_PROP 276
#define K_SYSCALL_FUEL_GAUGE_SET_PROP 277
#define K_SYSCALL_HWINFO_CLEAR_RESET_CAUSE 278
#define K_SYSCALL_HWINFO_GET_DEVICE_ID 279
#define K_SYSCALL_HWINFO_GET_RESET_CAUSE 280
#define K_SYSCALL_HWINFO_GET_SUPPORTED_RESET_CAUSE 281
#define K_SYSCALL_HWSPINLOCK_GET_MAX_ID 282
#define K_SYSCALL_HWSPINLOCK_LOCK 283
#define K_SYSCALL_HWSPINLOCK_TRYLOCK 284
#define K_SYSCALL_HWSPINLOCK_UNLOCK 285
#define K_SYSCALL_I2C_CONFIGURE 286
#define K_SYSCALL_I2C_GET_CONFIG 287
#define K_SYSCALL_I2C_RECOVER_BUS 288
#define K_SYSCALL_I2C_TARGET_DRIVER_REGISTER 289
#define K_SYSCALL_I2C_TARGET_DRIVER_UNREGISTER 290
#define K_SYSCALL_I2C_TRANSFER 291
#define K_SYSCALL_I2S_BUF_READ 292
#define K_SYSCALL_I2S_BUF_WRITE 293
#define K_SYSCALL_I2S_CONFIGURE 294
#define K_SYSCALL_I2S_TRIGGER 295
#define K_SYSCALL_I3C_DO_CCC 296
#define K_SYSCALL_I3C_TRANSFER 297
#define K_SYSCALL_IPM_COMPLETE 298
#define K_SYSCALL_IPM_MAX_DATA_SIZE_GET 299
#define K_SYSCALL_IPM_MAX_ID_VAL_GET 300
#define K_SYSCALL_IPM_SEND 301
#define K_SYSCALL_IPM_SET_ENABLED 302
#define K_SYSCALL_IVSHMEM_ENABLE_INTERRUPTS 303
#define K_SYSCALL_IVSHMEM_GET_ID 304
#define K_SYSCALL_IVSHMEM_GET_MAX_PEERS 305
#define K_SYSCALL_IVSHMEM_GET_MEM 306
#define K_SYSCALL_IVSHMEM_GET_OUTPUT_MEM_SECTION 307
#define K_SYSCALL_IVSHMEM_GET_PROTOCOL 308
#define K_SYSCALL_IVSHMEM_GET_RW_MEM_SECTION 309
#define K_SYSCALL_IVSHMEM_GET_STATE 310
#define K_SYSCALL_IVSHMEM_GET_VECTORS 311
#define K_SYSCALL_IVSHMEM_INT_PEER 312
#define K_SYSCALL_IVSHMEM_REGISTER_HANDLER 313
#define K_SYSCALL_IVSHMEM_SET_STATE 314
#define K_SYSCALL_KSCAN_CONFIG 315
#define K_SYSCALL_KSCAN_DISABLE_CALLBACK 316
#define K_SYSCALL_KSCAN_ENABLE_CALLBACK 317
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_IN_GET 318
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_OUT_GET 319
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_EVICTION_GET 320
#define K_SYSCALL_K_MEM_PAGING_STATS_GET 321
#define K_SYSCALL_K_MEM_PAGING_THREAD_STATS_GET 322
#define K_SYSCALL_LED_BLINK 323
#define K_SYSCALL_LED_GET_INFO 324
#define K_SYSCALL_LED_OFF 325
#define K_SYSCALL_LED_ON 326
#define K_SYSCALL_LED_SET_BRIGHTNESS 327
#define K_SYSCALL_LED_SET_CHANNEL 328
#define K_SYSCALL_LED_SET_COLOR 329
#define K_SYSCALL_LED_WRITE_CHANNELS 330
#define K_SYSCALL_MAXIM_DS3231_GET_SYNCPOINT 331
#define K_SYSCALL_MAXIM_DS3231_REQ_SYNCPOINT 332
#define K_SYSCALL_MBOX_MAX_CHANNELS_GET 333
#define K_SYSCALL_MBOX_MTU_GET 334
#define K_SYSCALL_MBOX_SEND 335
#define K_SYSCALL_MBOX_SET_ENABLED 336
#define K_SYSCALL_MDIO_BUS_DISABLE 337
#define K_SYSCALL_MDIO_BUS_ENABLE 338
#define K_SYSCALL_MDIO_READ 339
#define K_SYSCALL_MDIO_WRITE 340
#define K_SYSCALL_NET_ADDR_NTOP 341
#define K_SYSCALL_NET_ADDR_PTON 342
#define K_SYSCALL_NET_ETH_GET_PTP_CLOCK_BY_INDEX 343
#define K_SYSCALL_NET_IF_GET_BY_INDEX 344
#define K_SYSCALL_NET_IF_IPV4_ADDR_ADD_BY_INDEX 345
#define K_SYSCALL_NET_IF_IPV4_ADDR_LOOKUP_BY_INDEX 346
#define K_SYSCALL_NET_IF_IPV4_ADDR_RM_BY_INDEX 347
#define K_SYSCALL_NET_IF_IPV4_SET_GW_BY_INDEX 348
#define K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_INDEX 349
#define K_SYSCALL_NET_IF_IPV6_ADDR_ADD_BY_INDEX 350
#define K_SYSCALL_NET_IF_IPV6_ADDR_LOOKUP_BY_INDEX 351
#define K_SYSCALL_NET_IF_IPV6_ADDR_RM_BY_INDEX 352
#define K_SYSCALL_PECI_CONFIG 353
#define K_SYSCALL_PECI_DISABLE 354
#define K_SYSCALL_PECI_ENABLE 355
#define K_SYSCALL_PECI_TRANSFER 356
#define K_SYSCALL_PHY_CONFIGURE_LINK 357
#define K_SYSCALL_PHY_GET_LINK_STATE 358
#define K_SYSCALL_PHY_LINK_CALLBACK_SET 359
#define K_SYSCALL_PHY_READ 360
#define K_SYSCALL_PHY_WRITE 361
#define K_SYSCALL_PS2_CONFIG 362
#define K_SYSCALL_PS2_DISABLE_CALLBACK 363
#define K_SYSCALL_PS2_ENABLE_CALLBACK 364
#define K_SYSCALL_PS2_READ 365
#define K_SYSCALL_PS2_WRITE 366
#define K_SYSCALL_PTP_CLOCK_GET 367
#define K_SYSCALL_PWM_CAPTURE_CYCLES 368
#define K_SYSCALL_PWM_DISABLE_CAPTURE 369
#define K_SYSCALL_PWM_ENABLE_CAPTURE 370
#define K_SYSCALL_PWM_GET_CYCLES_PER_SEC 371
#define K_SYSCALL_PWM_SET_CYCLES 372
#define K_SYSCALL_RESET_LINE_ASSERT 373
#define K_SYSCALL_RESET_LINE_DEASSERT 374
#define K_SYSCALL_RESET_LINE_TOGGLE 375
#define K_SYSCALL_RESET_STATUS 376
#define K_SYSCALL_RETAINED_MEM_CLEAR 377
#define K_SYSCALL_RETAINED_MEM_READ 378
#define K_SYSCALL_RETAINED_MEM_SIZE 379
#define K_SYSCALL_RETAINED_MEM_WRITE 380
#define K_SYSCALL_RTC_ALARM_GET_SUPPORTED_FIELDS 381
#define K_SYSCALL_RTC_ALARM_GET_TIME 382
#define K_SYSCALL_RTC_ALARM_IS_PENDING 383
#define K_SYSCALL_RTC_ALARM_SET_CALLBACK 384
#define K_SYSCALL_RTC_ALARM_SET_TIME 385
#define K_SYSCALL_RTC_GET_CALIBRATION 386
#define K_SYSCALL_RTC_GET_TIME 387
#define K_SYSCALL_RTC_SET_CALIBRATION 388
#define K_SYSCALL_RTC_SET_TIME 389
#define K_SYSCALL_RTC_UPDATE_SET_CALLBACK 390
#define K_SYSCALL_RTIO_CQE_COPY_OUT 391
#define K_SYSCALL_RTIO_CQE_GET_MEMPOOL_BUFFER 392
#define K_SYSCALL_RTIO_RELEASE_BUFFER 393
#define K_SYSCALL_RTIO_SQE_CANCEL 394
#define K_SYSCALL_RTIO_SQE_COPY_IN_GET_HANDLES 395
#define K_SYSCALL_RTIO_SUBMIT 396
#define K_SYSCALL_SDHC_CARD_BUSY 397
#define K_SYSCALL_SDHC_CARD_PRESENT 398
#define K_SYSCALL_SDHC_EXECUTE_TUNING 399
#define K_SYSCALL_SDHC_GET_HOST_PROPS 400
#define K_SYSCALL_SDHC_HW_RESET 401
#define K_SYSCALL_SDHC_REQUEST 402
#define K_SYSCALL_SDHC_SET_IO 403
#define K_SYSCALL_SENSOR_ATTR_GET 404
#define K_SYSCALL_SENSOR_ATTR_SET 405
#define K_SYSCALL_SENSOR_CHANNEL_GET 406
#define K_SYSCALL_SENSOR_GET_DECODER 407
#define K_SYSCALL_SENSOR_RECONFIGURE_READ_IODEV 408
#define K_SYSCALL_SENSOR_SAMPLE_FETCH 409
#define K_SYSCALL_SENSOR_SAMPLE_FETCH_CHAN 410
#define K_SYSCALL_SIP_SUPERVISORY_CALL 411
#define K_SYSCALL_SIP_SVC_PLAT_ASYNC_RES_REQ 412
#define K_SYSCALL_SIP_SVC_PLAT_ASYNC_RES_RES 413
#define K_SYSCALL_SIP_SVC_PLAT_FORMAT_TRANS_ID 414
#define K_SYSCALL_SIP_SVC_PLAT_FREE_ASYNC_MEMORY 415
#define K_SYSCALL_SIP_SVC_PLAT_FUNC_ID_VALID 416
#define K_SYSCALL_SIP_SVC_PLAT_GET_ERROR_CODE 417
#define K_SYSCALL_SIP_SVC_PLAT_GET_TRANS_IDX 418
#define K_SYSCALL_SIP_SVC_PLAT_UPDATE_TRANS_ID 419
#define K_SYSCALL_SMBUS_BLOCK_PCALL 420
#define K_SYSCALL_SMBUS_BLOCK_READ 421
#define K_SYSCALL_SMBUS_BLOCK_WRITE 422
#define K_SYSCALL_SMBUS_BYTE_DATA_READ 423
#define K_SYSCALL_SMBUS_BYTE_DATA_WRITE 424
#define K_SYSCALL_SMBUS_BYTE_READ 425
#define K_SYSCALL_SMBUS_BYTE_WRITE 426
#define K_SYSCALL_SMBUS_CONFIGURE 427
#define K_SYSCALL_SMBUS_GET_CONFIG 428
#define K_SYSCALL_SMBUS_HOST_NOTIFY_REMOVE_CB 429
#define K_SYSCALL_SMBUS_HOST_NOTIFY_SET_CB 430
#define K_SYSCALL_SMBUS_PCALL 431
#define K_SYSCALL_SMBUS_QUICK 432
#define K_SYSCALL_SMBUS_SMBALERT_REMOVE_CB 433
#define K_SYSCALL_SMBUS_SMBALERT_SET_CB 434
#define K_SYSCALL_SMBUS_WORD_DATA_READ 435
#define K_SYSCALL_SMBUS_WORD_DATA_WRITE 436
#define K_SYSCALL_SPI_RELEASE 437
#define K_SYSCALL_SPI_TRANSCEIVE 438
#define K_SYSCALL_SYSCON_GET_BASE 439
#define K_SYSCALL_SYSCON_GET_SIZE 440
#define K_SYSCALL_SYSCON_READ_REG 441
#define K_SYSCALL_SYSCON_WRITE_REG 442
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_AND_INVD_RANGE 443
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_RANGE 444
#define K_SYSCALL_SYS_CACHE_DATA_INVD_RANGE 445
#define K_SYSCALL_UART_MUX_FIND 446
#define K_SYSCALL_UPDATEHUB_AUTOHANDLER 447
#define K_SYSCALL_UPDATEHUB_CONFIRM 448
#define K_SYSCALL_UPDATEHUB_PROBE 449
#define K_SYSCALL_UPDATEHUB_REBOOT 450
#define K_SYSCALL_UPDATEHUB_UPDATE 451
#define K_SYSCALL_USER_FAULT 452
#define K_SYSCALL_W1_CHANGE_BUS_LOCK 453
#define K_SYSCALL_W1_CONFIGURE 454
#define K_SYSCALL_W1_GET_SLAVE_COUNT 455
#define K_SYSCALL_W1_READ_BIT 456
#define K_SYSCALL_W1_READ_BLOCK 457
#define K_SYSCALL_W1_READ_BYTE 458
#define K_SYSCALL_W1_RESET_BUS 459
#define K_SYSCALL_W1_SEARCH_BUS 460
#define K_SYSCALL_W1_WRITE_BIT 461
#define K_SYSCALL_W1_WRITE_BLOCK 462
#define K_SYSCALL_W1_WRITE_BYTE 463
#define K_SYSCALL_WDT_DISABLE 464
#define K_SYSCALL_WDT_FEED 465
#define K_SYSCALL_WDT_SETUP 466
#define K_SYSCALL_ZSOCK_ACCEPT 467
#define K_SYSCALL_ZSOCK_BIND 468
#define K_SYSCALL_ZSOCK_CLOSE 469
#define K_SYSCALL_ZSOCK_CONNECT 470
#define K_SYSCALL_ZSOCK_FCNTL 471
#define K_SYSCALL_ZSOCK_GETHOSTNAME 472
#define K_SYSCALL_ZSOCK_GETPEERNAME 473
#define K_SYSCALL_ZSOCK_GETSOCKNAME 474
#define K_SYSCALL_ZSOCK_GETSOCKOPT 475
#define K_SYSCALL_ZSOCK_GET_CONTEXT_OBJECT 476
#define K_SYSCALL_ZSOCK_INET_PTON 477
#define K_SYSCALL_ZSOCK_IOCTL 478
#define K_SYSCALL_ZSOCK_LISTEN 479
#define K_SYSCALL_ZSOCK_POLL 480
#define K_SYSCALL_ZSOCK_RECVFROM 481
#define K_SYSCALL_ZSOCK_SELECT 482
#define K_SYSCALL_ZSOCK_SENDMSG 483
#define K_SYSCALL_ZSOCK_SENDTO 484
#define K_SYSCALL_ZSOCK_SETSOCKOPT 485
#define K_SYSCALL_ZSOCK_SHUTDOWN 486
#define K_SYSCALL_ZSOCK_SOCKET 487
#define K_SYSCALL_ZSOCK_SOCKETPAIR 488
#define K_SYSCALL_Z_ERRNO 489
#define K_SYSCALL_Z_ZSOCK_GETADDRINFO_INTERNAL 490


#ifndef _ASMLANGUAGE

#include <stdarg.h>
#include <stdint.h>

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_SYSCALL_LIST_H */
