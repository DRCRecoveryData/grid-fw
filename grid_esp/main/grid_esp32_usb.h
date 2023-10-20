/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>


#include "esp_check.h"

#include "rom/ets_sys.h" // For ets_printf

#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_log.h"


#include "tinyusb.h"
#include "driver/gpio.h"


//#include "../../grid_common/grid_port.h"
#include "grid_usb.h"
//#include "../../grid_common/grid_sys.h"




#ifdef __cplusplus
extern "C" {
#endif





//------------- CLASS -------------//
#define CFG_TUD_CDC             1
#define CFG_TUD_HID             1
#define CFG_TUD_MIDI            1
#define CFG_TUD_MSC             0
#define CFG_TUD_VENDOR          0


/* HID Mouse Class Pointer Move Type */
static enum mouse_move_type { X_AXIS_MV = 0x01, Y_AXIS_MV = 0x02, SCROLL_MV = 0x03 };

static enum gamepad_axis_t { GAMEPAD_AXIS_X = 0, GAMEPAD_AXIS_Y, GAMEPAD_AXIS_Z, GAMEPAD_AXIS_RX, GAMEPAD_AXIS_RY, GAMEPAD_AXIS_RZ };



/** Helper defines **/

void grid_esp32_usb_init(void);
void grid_esp32_usb_task(void *arg);

extern void grid_platform_sync1_pulse_send();


int32_t grid_platform_usb_serial_write(char* buffer, uint32_t length);

int32_t grid_platform_usb_midi_write(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3);

int32_t grid_platform_usb_midi_write_status(void);


int32_t grid_platform_usb_mouse_button_change(uint8_t b_state, uint8_t type);
int32_t grid_platform_usb_mouse_move(int8_t position, uint8_t axis);


int32_t grid_platform_usb_gamepad_axis_move(int8_t position, uint8_t axis);


#ifdef __cplusplus
}
#endif
