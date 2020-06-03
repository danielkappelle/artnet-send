#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "net.h"

#define HEADER_LENGTH 18

void init_buf(char* buf, uint16_t packet_length);
void set_channel(char* buf, uint16_t channel, uint8_t val);

int main() {
	FILE *ptr;
	uint16_t packet_length = 100;
	unsigned char buffer[packet_length + HEADER_LENGTH];

	init_buf(buffer, packet_length);

	set_channel(buffer, 0, 255);
	set_channel(buffer, 6, 255);
	set_channel(buffer, 12, 255);
	set_channel(buffer, 13, 255);
	set_channel(buffer, 16, 255);

	send_udp_packet(buffer, packet_length + HEADER_LENGTH, "192.168.2.2", 6454);

	return 0;
}

void init_buf(char* buf, uint16_t packet_length) {
	uint16_t i;

	strcpy(buf, "Art-Net");
	buf[7]=0;
	buf[8]=0x00;
	buf[9]=0x50;
	buf[10]=0;
	buf[11]=14;
	buf[12]=0;
	buf[13]=0;
	buf[14]=0;
	buf[15]=0;
	buf[16]= packet_length >> 8;
	buf[17]= packet_length;

	for(i = 0; i < packet_length; i++) {
		buf[HEADER_LENGTH + i] = 0;
	}
}

void set_channel(char* buf, uint16_t channel, uint8_t val) {
	buf[channel + HEADER_LENGTH] = val;
}