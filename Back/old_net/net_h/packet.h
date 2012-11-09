#ifndef __PACKET_H
#define __PACKET_H

#include <types.h>

typedef struct packet_p
{
	uint32_t size;
	char *data;
	
	struct packet_p *next;
} packet_t;


void packet_add_header(packet_t *, uint32_t);
void packet_del_header(packet_t *, uint32_t);
packet_t *packet_create(char *, uint32_t);
uint32_t packet_checksum(packet_t *, uint32_t);

#endif
