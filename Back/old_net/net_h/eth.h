#ifndef __ETH_H
#define __ETH_H

#include <net/if.h>
#include <net/packet.h>
#include <types.h>

uint32_t eth_handle_packet(netif_t *, packet_t *);
uint32_t eth_send_packet(netif_t *, packet_t *);

extern netlink_t nl_eth;


#endif
