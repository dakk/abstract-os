#ifndef __LO_H
#define __LO_H

#include <net/if.h>
#include <net/packet.h>
#include <types.h>

uint32_t lo_handle_packet(netif_t *, packet_t *);
uint32_t lo_send_packet(netif_t *, packet_t *);

extern netlink_t nl_lo;


#endif
