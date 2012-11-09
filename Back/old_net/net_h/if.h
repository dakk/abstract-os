#ifndef __IF_H
#define __IF_H

#include <types.h>
#include <device.h>
#include <driver.h>
#include <net/packet.h>


typedef struct netif_p
{
	char name[32];
	
	dev_t *device;
	drv_t *driver;

	uint32_t mtu;
	uint64_t rx_bytes;
	uint64_t tx_bytes;
	
	/* datalink proto */
	void *netlink;
	
	/* network proto */
	void *netproto;
	
	struct netif_p *next;
} netif_t;


typedef struct
{
	char name[32];
	uint32_t mtu;

	uint32_t (*handle_packet)(netif_t *, packet_t *);
	uint32_t (*send_packet)(netif_t *, packet_t *);
} netlink_t;


typedef struct
{
	char name[32];
	uint32_t mtu;	

	uint32_t (*handle_packet)(netif_t *, packet_t *);
} netproto_t;


netif_t *netif_list;

netif_t *netif_iget(int);
int netif_init();
netif_t *netif_add(netlink_t *, netproto_t *, drv_t *, dev_t *);
int netif_probe();

#endif
