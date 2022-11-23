/*
 * grid_msg.c
 *
 * Created: 9/23/2020 2:35:51 PM
 *  Author: suku
 */ 


#include "grid_msg.h"

struct grid_msg_model grid_msg_state;

void grid_msg_init(struct grid_msg_model* mod){


	mod->sessionid = grid_platform_get_random_8();

	for (uint8_t i=0; i<GRID_MSG_LASTHEADER_INDEX_COUNT; i++){
		grid_msg_store_lastheader(mod, i, 0);
	}

	mod->editor_heartbeat_lastrealtime = 0;	
	mod->heartbeat_type = 0;

}

void grid_msg_set_heartbeat_type(struct grid_msg_model* mod, uint8_t type){
	mod->heartbeat_type = type;
}

uint8_t grid_msg_get_heartbeat_type(struct grid_msg_model* mod){
	return mod->heartbeat_type;
}


void grid_msg_store_lastheader(struct grid_msg_model* mod, enum grid_msg_lastheader_index_t index, uint8_t value){

	mod->lastheader[index].id = value;
	mod->lastheader[index].state = -1; // -1 means not completed operation

}

uint8_t grid_msg_get_lastheader_state(struct grid_msg_model* mod, enum grid_msg_lastheader_index_t index){
	return mod->lastheader[index].state;
}

uint8_t grid_msg_get_lastheader_id(struct grid_msg_model* mod, enum grid_msg_lastheader_index_t index){
	return mod->lastheader[index].id;
}

void grid_msg_clear_lastheader(struct grid_msg_model* mod, enum grid_msg_lastheader_index_t index){

	mod->lastheader[index].state = 0; // 0 means operation completed
}



void grid_msg_set_editor_heartbeat_lastrealtime(struct grid_msg_model* mod, uint32_t timestamp){
	mod->editor_heartbeat_lastrealtime = timestamp;
}

uint32_t grid_msg_get_editor_heartbeat_lastrealtime(struct grid_msg_model* mod){
	return mod->editor_heartbeat_lastrealtime;
}


// ======================= GRID MSG LEN ======================//
void	grid_msg_header_set_len(struct grid_msg* msg, uint16_t len){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_LEN_offset, GRID_BRC_LEN_length, len, &error);
	
}

uint16_t grid_msg_header_get_len(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_LEN_offset, GRID_BRC_LEN_length, &error);
}

// ======================= GRID MSG ID ======================//
void	grid_msg_header_set_id(struct grid_msg* msg, uint8_t id){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_ID_offset, GRID_BRC_ID_length, id, &error);
	
}


uint8_t grid_msg_header_get_id(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_ID_offset, GRID_BRC_ID_length, &error);
}

// ======================= GRID MSG DX ======================//
void	grid_msg_header_set_dx(struct grid_msg* msg, uint8_t dx){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_DX_offset, GRID_BRC_DX_length, dx, &error);
	
}


uint8_t grid_msg_header_get_dx(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_DX_offset, GRID_BRC_DX_length, &error);
}


// ======================= GRID MSG DY ======================//
void	grid_msg_header_set_dy(struct grid_msg* msg, uint8_t dy){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_DY_offset, GRID_BRC_DY_length, dy, &error);
	
}


uint8_t grid_msg_header_get_dy(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_DY_offset, GRID_BRC_DY_length, &error);
}

// ======================= GRID MSG SX ======================//
void	grid_msg_header_set_sx(struct grid_msg* msg, uint8_t sx){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_SX_offset, GRID_BRC_SX_length, sx, &error);
	
}


uint8_t grid_msg_header_get_sx(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_SX_offset, GRID_BRC_SX_length, &error);
}

// ======================= GRID MSG SY ======================//
void	grid_msg_header_set_sy(struct grid_msg* msg, uint8_t sy){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_SY_offset, GRID_BRC_SY_length, sy, &error);
	
}


uint8_t grid_msg_header_get_sy(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_SY_offset, GRID_BRC_SY_length, &error);
}



// ======================= GRID MSG ROT ======================//
void	grid_msg_header_set_rot(struct grid_msg* msg, uint8_t rot){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_ROT_offset, GRID_BRC_ROT_length, rot, &error);
	
}


uint8_t grid_msg_header_get_rot(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_ROT_offset, GRID_BRC_ROT_length, &error);
}

// ======================= GRID MSG AGE ======================//
void	grid_msg_header_set_age(struct grid_msg* msg, uint8_t age){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_MSGAGE_offset, GRID_BRC_MSGAGE_length, age, &error);
	
}

uint8_t grid_msg_header_get_age(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_MSGAGE_offset, GRID_BRC_MSGAGE_length, &error);
}

// ======================= GRID MSG session ======================//
void	grid_msg_header_set_session(struct grid_msg* msg, uint8_t session){
	
	uint8_t error = 0;
	grid_msg_set_parameter(msg->header, GRID_BRC_SESSION_offset, GRID_BRC_SESSION_length, session, &error);
	
}

uint8_t grid_msg_header_get_session(struct grid_msg* msg){
	
	uint8_t error = 0;
	return grid_msg_get_parameter(msg->header, GRID_BRC_SESSION_offset, GRID_BRC_SESSION_length, &error);
}

// ======================= MSG GET PACKET LENGTH ======================//
uint32_t grid_msg_packet_get_length(struct grid_msg* msg){
	
	return (msg->header_length + msg->body_length + msg->footer_length);
}

// ======================= MSG GET HEADER LENGTH ======================//
uint32_t grid_msg_header_get_length(struct grid_msg* msg){
	
	return (msg->header_length);
}

// ======================= MSG GET BODY LENGTH ======================//
uint32_t grid_msg_body_get_length(struct grid_msg* msg){
	
	return (msg->body_length);
}

// ======================= MSG GET FOOTER LENGTH ======================//
uint32_t grid_msg_footer_get_length(struct grid_msg* msg){
	
	return (msg->footer_length);
}


void	grid_msg_body_append_text(struct grid_msg* msg, uint8_t* str){

	uint32_t len = strlen(str);
	
	for(uint32_t i=0; i<len; i++){
		
		msg->body[msg->body_length + i] = str[i];
	}
	
	msg->body_length += len;
	msg->last_appended_length  += len;

}



void grid_msg_body_append_printf(struct grid_msg* msg, char const *fmt, ...){

	va_list ap;


	va_start(ap, fmt);

	vsprintf(&msg->body[msg->body_length], fmt, ap);

	va_end(ap);
	

	msg->last_appended_length = strlen(&msg->body[msg->body_length]);

	msg->body_length += msg->last_appended_length;

	return;
}
void grid_msg_body_append_parameter(struct grid_msg* msg,  uint8_t parameter_offset, uint8_t parameter_length, uint32_t value){

	uint8_t text_start_offset = msg->body_length - msg->last_appended_length;

	grid_msg_text_set_parameter(msg, text_start_offset, parameter_offset, parameter_length, value);

}

uint32_t grid_msg_text_get_parameter(struct grid_msg* msg, uint32_t text_start_offset, uint8_t parameter_offset, uint8_t parameter_length){
	
	uint8_t error;
	
	return grid_msg_read_hex_string_value(&msg->body[text_start_offset + parameter_offset], parameter_length, error);
	
}

void grid_msg_text_set_parameter(struct grid_msg* msg, uint32_t text_start_offset, uint8_t parameter_offset, uint8_t parameter_length, uint32_t value){
	
	return grid_msg_write_hex_string_value(&msg->body[text_start_offset + parameter_offset], parameter_length, value);
	
}


// ======================= MSG INIT HEADER======================//

void	grid_msg_init_header(struct grid_msg_model* mod, struct grid_msg* msg, uint8_t dx, uint8_t dy){
	
	msg->header_length = 0;
	msg->body_length = 0;
	msg->last_appended_length = 0;
	msg->footer_length = 0;
	

	// No need to initialize array

	// for (uint32_t i=0; i<GRID_MSG_HEADER_maxlength; i++)
	// {
	// 	msg->header[i] = 0;
	// }
	
	// for (uint32_t i=0; i<GRID_MSG_BODY_maxlength; i++)
	// {
	// 	msg->body[i] = 0;
	// }
	
	// for (uint32_t i=0; i<GRID_MSG_FOOTER_maxlength; i++)
	// {
	// 	msg->footer[i] = 0;
	// }
    
    uint8_t session = mod->sessionid;
    
	sprintf(msg->header, GRID_BRC_frame_quick, GRID_CONST_SOH, GRID_CONST_BRC, session, dx, dy , GRID_CONST_EOB);
	msg->header_length = strlen(msg->header);
	
	// grid_msg_header_set_dx(msg, dx);
	// grid_msg_header_set_dy(msg, dy);

	// grid_msg_header_set_sx(msg, GRID_SYS_DEFAULT_POSITION);
	// grid_msg_header_set_sy(msg, GRID_SYS_DEFAULT_POSITION);
	// grid_msg_header_set_rot(msg, rot);
	// grid_msg_header_set_age(msg, GRID_SYS_DEFAULT_AGE);

	// grid_msg_header_set_session(msg, session);
	
	
}

// ======================= MSG RECEIVE CHAR ======================//
void	grid_msg_packet_receive_char(struct grid_msg* msg, uint8_t nextchar){
	
	if (msg->body_length == 0){
		
		if (nextchar != GRID_CONST_EOB){
			msg->header[msg->header_length] = nextchar;
			msg->header_length++;
		}
		else{
			msg->body[msg->body_length] = nextchar;
			msg->body_length++;
			
		}
		
	}
	else if(msg->footer_length == 0){
		
		if (nextchar != GRID_CONST_EOT){
			msg->body[msg->body_length] = nextchar;
			msg->body_length++;
		}
		else{
			msg->footer[msg->footer_length] = nextchar;
			msg->footer_length++;
			
		}		
		
	}
	else{
		
		msg->footer[msg->footer_length] = nextchar;
		msg->footer_length++;
		
	}
	
}

// ======================= GRID MSG SEND CHAR ======================//

uint8_t	grid_msg_packet_send_char(struct grid_msg* msg, uint32_t charindex){
	
	if (charindex < msg->header_length){
		
		return msg->header[charindex];
	}
	else if (charindex < msg->body_length + msg->header_length){
	
		return msg->body[charindex - msg->header_length];
	}
	else if (charindex < msg->footer_length + msg->body_length + msg->header_length){
	
		return msg->footer[charindex - msg->header_length - msg->body_length];
	}
	else{
		// OVERRUN
		return -1;
	}
	
	
}



uint8_t	grid_msg_packet_close(struct grid_msg_model* mod, struct grid_msg* msg){
	

	
	sprintf(&msg->footer[msg->footer_length], "%c", GRID_CONST_EOT);
	msg->footer_length += strlen(&msg->footer[msg->footer_length]);
	
	grid_msg_header_set_len(msg, msg->header_length + msg->body_length + msg->footer_length);
	grid_msg_header_set_session(msg, mod->sessionid);	
	grid_msg_header_set_id(msg, mod->next_broadcast_message_id);	
	
	mod->next_broadcast_message_id++;
	

	
	uint8_t checksum = 0;
	
	for (uint32_t i=0; i<msg->header_length; i++){
		checksum ^= msg->header[i];
	}
		
	for (uint32_t i=0; i<msg->body_length; i++){
		checksum ^= msg->body[i];
	}
		
	for (uint32_t i=0; i<msg->footer_length; i++){
		checksum ^= msg->footer[i];
	}
	
	sprintf(&msg->footer[msg->footer_length], "%02x\n", checksum);
	msg->footer_length += strlen(&msg->footer[msg->footer_length]);
	
	
}





uint8_t grid_msg_string_validate(uint8_t* packet){

// Cannot check everything because we don't have time for that.
// Later we might extend 

	return 0;
}




// RECENT MESSAGES

uint8_t grid_msg_find_recent(struct grid_msg_model* model, uint32_t fingerprint){
	
	for(GRID_MSG_RECENT_MESSAGES_INDEX_T i = 0; i<GRID_MSG_RECENT_MESSAGES_LENGTH; i++){
		
		if (model->recent_messages[i%GRID_MSG_RECENT_MESSAGES_LENGTH] == fingerprint){
			
			return 1;
			
		}
		
	}
	
	return 0;
}

void grid_msg_push_recent(struct grid_msg_model* model, uint32_t fingerprint){
	
	model->recent_messages_index+=1;
	model->recent_messages_index%=GRID_MSG_RECENT_MESSAGES_LENGTH;
	
	model->recent_messages[model->recent_messages_index] = fingerprint;
	
}




uint8_t grid_msg_calculate_checksum_of_packet_string(uint8_t* str, uint32_t length){
	
	uint8_t checksum = 0;
	for (uint32_t i=0; i<length-3; i++){
		checksum ^= str[i];
	}
	
	return checksum;
	
}

uint8_t grid_msg_calculate_checksum_of_string(uint8_t* str, uint32_t length){
	
	uint8_t checksum = 0;
	for (uint32_t i=0; i<length; i++){
		checksum ^= str[i];
	}
	
	return checksum;
	
}


uint8_t grid_msg_checksum_read(uint8_t* str, uint32_t length){
	uint8_t error_flag;
	return grid_msg_read_hex_string_value(&str[length-3], 2, &error_flag);
}

void grid_msg_checksum_write(uint8_t* message, uint32_t length, uint8_t checksum){
	
// 	uint8_t checksum_string[4];
// 
// 	sprintf(checksum_string, "%02x", checksum);
// 
// 	message[length-3] = checksum_string[0];
// 	message[length-2] = checksum_string[1];
	
	grid_msg_write_hex_string_value(&message[length-3], 2, checksum);
	
}


// MESSAGE PARAMETER FUNCTIONS

uint32_t grid_msg_get_parameter(uint8_t* message, uint8_t offset, uint8_t length, uint8_t* error){
		
	return grid_msg_read_hex_string_value(&message[offset], length, error);	
}

uint32_t grid_msg_set_parameter(uint8_t* message, uint8_t offset, uint8_t length, uint32_t value, uint8_t* error){
	
	grid_msg_write_hex_string_value(&message[offset], length, value);
	
}


uint8_t grid_msg_read_hex_char_value(uint8_t ascii, uint8_t* error_flag){
		
	uint8_t result = 0;
	
	if (ascii>47 && ascii<58){
		result = ascii-48;
	}
	else if(ascii>96 && ascii<103){
		result = ascii - 97 + 10;
	}
	else{
		// wrong input
		if (error_flag != 0){
			*error_flag = ascii;
		}
	}
	
	return result;	
}

uint32_t grid_msg_read_hex_string_value(uint8_t* start_location, uint8_t length, uint8_t* error_flag){
	
	uint32_t result  = 0;
	
	for(uint8_t i=0; i<length; i++){
		
		result += grid_msg_read_hex_char_value(start_location[i], error_flag) << (length-i-1)*4;

		
	}

	return result;
}

void grid_msg_write_hex_string_value(uint8_t* start_location, uint8_t size, uint32_t value){
	
	uint8_t str[10];
	
	sprintf(str, "%08x", value);
		
	for(uint8_t i=0; i<size; i++){	
		start_location[i] = str[8-size+i];	
	}

}




void grid_debug_print_text(uint8_t* debug_string){
	
	uint32_t debug_string_length = strlen(debug_string);
	
	struct grid_msg message;
	
	grid_msg_init_header(&grid_msg_state, &message, GRID_SYS_GLOBAL_POSITION, GRID_SYS_GLOBAL_POSITION);

	grid_msg_body_append_printf(&message, GRID_CLASS_DEBUGTEXT_frame_start);
	grid_msg_body_append_parameter(&message, GRID_INSTR_offset, GRID_INSTR_length, GRID_INSTR_EXECUTE_code);
	grid_msg_body_append_printf(&message, debug_string);
	grid_msg_body_append_printf(&message, GRID_CLASS_DEBUGTEXT_frame_end);

	grid_msg_packet_close(&grid_msg_state, &message);
	grid_sys_packet_send_everywhere(&message);
		
}


void grid_websocket_print_text(uint8_t* debug_string){
	
	uint32_t debug_string_length = strlen(debug_string);
	
	struct grid_msg message;
	
	grid_msg_init_header(&grid_msg_state, &message, GRID_SYS_GLOBAL_POSITION, GRID_SYS_GLOBAL_POSITION);

	grid_msg_body_append_printf(&message, GRID_CLASS_WEBSOCKET_frame_start);
	grid_msg_body_append_parameter(&message, GRID_INSTR_offset, GRID_INSTR_length, GRID_INSTR_EXECUTE_code);
	grid_msg_body_append_printf(&message, debug_string);
	grid_msg_body_append_printf(&message, GRID_CLASS_WEBSOCKET_frame_end);

	grid_msg_packet_close(&grid_msg_state, &message);
	grid_sys_packet_send_everywhere(&message);
		
}

void grid_debug_printf(char const *fmt, ...){

	va_list ap;


	uint8_t temp[100] = {0};

	va_start(ap, fmt);

	vsnprintf(temp, 99, fmt, ap);

	va_end(ap);

	grid_debug_print_text(temp);

	return;
}




uint8_t	grid_sys_packet_send_everywhere(struct grid_msg* msg){
	
	uint32_t message_length = grid_msg_packet_get_length(msg);
	
	if (grid_buffer_write_init(&GRID_PORT_U.rx_buffer, message_length)){

		for(uint32_t i = 0; i<message_length; i++){

			grid_buffer_write_character(&GRID_PORT_U.rx_buffer, grid_msg_packet_send_char(msg, i));
		}

		grid_buffer_write_acknowledge(&GRID_PORT_U.rx_buffer);

		return 1;
	}
	else{
		
		return 0;
	}
	
	
}
