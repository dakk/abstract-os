#include <malloc.h>
#include <string.h>
#include <net/packet.h>


void 
packet_add_header(packet_t *p, uint32_t h_size)
{
	char *data = (char *) malloc(p->size + h_size);
	memcpy(data + h_size, p->data, p->size);
	free(p->data);
	p->data = data; 
	p->size = p->size + h_size;	
}


void 
packet_del_header(packet_t *p, uint32_t h_size)
{
	char *data = (char *) malloc(p->size - h_size);
	memcpy(data, p->data + h_size, p->size - h_size);
	free(p->data);
	p->data = data;
	p->size = p->size - h_size;
}



packet_t *
packet_create(char *data, uint32_t size)
{
	packet_t *p = (packet_t *) malloc(sizeof(packet_t));
	p->data = (char *) malloc(size);
	
	if(data != NULL)
		memcpy(p->data, data, size);
	p->size = size;
	return p;
}


uint32_t 
packet_checksum(packet_t *p, uint32_t len)
{
	
	return 0;
}
