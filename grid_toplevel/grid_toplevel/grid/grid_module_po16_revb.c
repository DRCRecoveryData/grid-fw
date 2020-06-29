#include "grid_module_po16_revb.h"

volatile uint8_t grid_module_po16_revb_hardware_transfer_complete = 0;
volatile uint8_t grid_module_po16_revb_mux =0;
volatile uint8_t grid_module_po16_revb_mux_lookup[16] = {0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14, 15};

void grid_module_po16_revb_hardware_start_transfer(void){
	
	adc_async_start_conversion(&ADC_0);
	adc_async_start_conversion(&ADC_1);
	
}

static void grid_module_po16_revb_hardware_transfer_complete_cb(void){

	
	if (grid_module_po16_revb_hardware_transfer_complete == 0){
		grid_module_po16_revb_hardware_transfer_complete++;
		return;
	}
	

	
	/* Read mapmode state*/
	
	
	struct grid_ui_model* mod = &grid_ui_state;
		
	/* Read conversion results */
	
	uint16_t adcresult_0 = 0;
	uint16_t adcresult_1 = 0;
	
	uint8_t adc_index_0 = grid_module_po16_revb_mux_lookup[grid_module_po16_revb_mux+8];
	uint8_t adc_index_1 = grid_module_po16_revb_mux_lookup[grid_module_po16_revb_mux+0];
	
	/* Update the multiplexer */
	
	grid_module_po16_revb_mux++;
	grid_module_po16_revb_mux%=8;
	
	gpio_set_pin_level(MUX_A, grid_module_po16_revb_mux/1%2);
	gpio_set_pin_level(MUX_B, grid_module_po16_revb_mux/2%2);
	gpio_set_pin_level(MUX_C, grid_module_po16_revb_mux/4%2);
	
	
	
	adc_async_read_channel(&ADC_0, 0, &adcresult_0, 2);
	adc_async_read_channel(&ADC_1, 0, &adcresult_1, 2);
	

	// FAKE CALIBRATION
	uint32_t input_0 = adcresult_0*1.03;	
	if (input_0 > (1<<16)-1){
		input_0 = (1<<16)-1;
	}
	adcresult_0 = input_0;
	
	uint32_t input_1 = adcresult_1*1.03;	
	if (input_1 > (1<<16)-1){
		input_1 = (1<<16)-1;
	}
	adcresult_1 = input_1;


	// POT POLARITY IS REVERSED ON PO16_RevC
	if (grid_sys_get_hwcfg() == GRID_MODULE_PO16_RevC){
		
		// Reverse the 16bit result
		adcresult_0	= 65535 - adcresult_0;
		adcresult_1 = 65535 - adcresult_1;
	}


	grid_ain_add_sample(adc_index_0, adcresult_0);
	grid_ain_add_sample(adc_index_1, adcresult_1);

	
	//CRITICAL_SECTION_ENTER()

	if (grid_ain_get_changed(adc_index_0)){
		
		uint8_t value = grid_ain_get_average(adc_index_0, 7);	
		
		grid_sys_write_hex_string_value(&mod->report_ui_array[adc_index_0].payload[7], 2, adc_index_0);
		grid_sys_write_hex_string_value(&mod->report_ui_array[adc_index_0].payload[9], 2, value);	
		mod->report_ui_array[adc_index_0].helper[0] = value;
		
		grid_report_ui_set_changed_flag(mod, adc_index_0);
			
		grid_sys_write_hex_string_value(&mod->report_ui_array[adc_index_0+16].payload[9], 2, value*2);
				
		grid_report_ui_set_changed_flag(mod, adc_index_0+16);
	}
	
	//CRITICAL_SECTION_LEAVE()
	
	
	//CRITICAL_SECTION_ENTER()

	if (grid_ain_get_changed(adc_index_1)){
		
		uint8_t value = grid_ain_get_average(adc_index_1, 7);
		
		grid_sys_write_hex_string_value(&mod->report_ui_array[adc_index_1].payload[7], 2, adc_index_1);
		grid_sys_write_hex_string_value(&mod->report_ui_array[adc_index_1].payload[9], 2, value);		
		mod->report_ui_array[adc_index_1].helper[0] = value;
		
		grid_report_ui_set_changed_flag(mod, adc_index_1);
				
		grid_sys_write_hex_string_value(&mod->report_ui_array[adc_index_1+16].payload[9], 2, value*2);
				
		grid_report_ui_set_changed_flag(mod, adc_index_1+16);
	}
	
	//CRITICAL_SECTION_LEAVE()
	
	
	grid_module_po16_revb_hardware_transfer_complete = 0;
	grid_module_po16_revb_hardware_start_transfer();
}

void grid_module_po16_revb_hardware_init(void){
	
	adc_async_register_callback(&ADC_0, 0, ADC_ASYNC_CONVERT_CB, grid_module_po16_revb_hardware_transfer_complete_cb);
	adc_async_register_callback(&ADC_1, 0, ADC_ASYNC_CONVERT_CB, grid_module_po16_revb_hardware_transfer_complete_cb);
		
	adc_async_enable_channel(&ADC_0, 0);
	adc_async_enable_channel(&ADC_1, 0);

}




void grid_module_po16_revb_init(struct grid_ui_model* mod){
	
	// 16 pot, depth of 5, 14bit internal, 7bit result;
	grid_ain_init(16, 5, 14, 7);
	grid_led_init(&grid_led_state, 16);
	
	grid_ui_model_init(mod, 32);
	
	
	for(uint8_t i=0; i<32; i++){
			
		uint8_t payload_template[30] = {0};
		enum grid_report_type_t type;
		
		if (i<16){ // Control Change
			
			type = GRID_REPORT_TYPE_BROADCAST;
			
			sprintf(payload_template, "%c%02x%02x%02x%02x%02x%c",

			GRID_CONST_STX,
			GRID_CLASS_MIDI,
			0, // (cable<<4) + channel
			GRID_COMMAND_MIDI_CONTROLCHANGE,
			i,
			0,
			GRID_CONST_ETX

			);			
			
		}
		else{ // LED
			
			type = GRID_REPORT_TYPE_LOCAL;
			
			sprintf(payload_template, "%c%02x%02x%02x%02x%02x%c",
			
			GRID_CONST_STX,
			GRID_CLASS_LED,
			GRID_LED_LAYER_UI_A, // layer
			GRID_COMMAND_LED_SETPHASE,
			i-16,
			0,
			GRID_CONST_ETX

			);
			
			
		}
		

			
		

		
		uint8_t payload_length = strlen(payload_template);

		uint8_t helper_template[2];
		
		helper_template[0] = 0;
		helper_template[1] = 0;
		
		uint8_t helper_length = 2;
		
		grid_report_ui_init(mod, i, type, payload_template, payload_length, helper_template, helper_length);
		
	}
	
	grid_report_sys_init(mod);
		
	

	
	grid_module_po16_revb_hardware_init();
	grid_module_po16_revb_hardware_start_transfer();
	
}