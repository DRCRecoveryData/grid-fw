/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include "grid_esp32_port.h"


static const char *TAG = "PORT";


void grid_esp32_port_task(void *arg)
{



    static uint32_t loopcounter = 0;

    while (1) {

        loopcounter++;




        //ESP_LOGI(TAG, "Ping!");
        if (loopcounter%30 == 0){

            grid_protocol_send_heartbeat(); // Put ping into UI rx_buffer
        }


        if (loopcounter%4 == 0){

            if (grid_ui_event_count_istriggered_local(&grid_ui_state)){

                //CRITICAL_SECTION_ENTER()
                grid_port_process_ui_local_UNSAFE(&grid_ui_state);
                //CRITICAL_SECTION_LEAVE()
            
            }
			if (grid_ui_event_count_istriggered(&grid_ui_state)){

				grid_ui_state.port->cooldown += 3;	

				//CRITICAL_SECTION_ENTER()
				grid_port_process_ui_UNSAFE(&grid_ui_state); 
				//CRITICAL_SECTION_LEAVE()
			}


        }



	    grid_port_receive_task(&GRID_PORT_H); // USB
	    grid_port_receive_task(&GRID_PORT_U); // UI
        
        // INBOUND
        grid_port_process_inbound(&GRID_PORT_U, 1); // Loopback , put rx_buffer content to each CONNECTED port's tx_buffer
        // ... GRID UART PORTS ...
        grid_port_process_inbound(&GRID_PORT_H, 0);





        // OUTBOUND
        // ... GRID UART PORTS ...
        grid_port_process_outbound_usb(&GRID_PORT_H);       
        grid_port_process_outbound_ui(&GRID_PORT_U);

        //GRID_PORT_U.rx_buffer.read_start = 0;        
        //GRID_PORT_U.rx_buffer.read_stop = 0;  

    

        //GRID_PORT_H.rx_buffer.read_start = 0;        
        //GRID_PORT_H.rx_buffer.write_start = 0;  

        //grid_platform_usb_serial_write(TAG, strlen(TAG));

        vTaskDelay(pdMS_TO_TICKS(10));



    }


    ESP_LOGI(TAG, "Deinit PORT");
    vTaskSuspend(NULL);
}