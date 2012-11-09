#include <net/eth.h>
#include <net/if.h>
#include <net/packet.h>
#include <types.h>

netlink_t nl_eth = 
	{
		.name = "eth",
		.mtu = 1024,
		.handle_packet = eth_handle_packet,
		.send_packet = eth_send_packet,
	};
	

uint32_t 
eth_handle_packet(netif_t *nif, packet_t *p)
{
	nif->rx_bytes += p->size;

	if((nif == NULL) || (nif->netproto == NULL) || (p == NULL))
	{
		return 0;
	}
	
	//((netproto_t *) (nif->netproto));
	return 0;
}


uint32_t 
eth_send_packet(netif_t *nif, packet_t *p)
{
	nif->tx_bytes += p->size;
	
	return 0;
}
