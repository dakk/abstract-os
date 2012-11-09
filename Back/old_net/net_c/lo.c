#include <net/lo.h>
#include <net/if.h>
#include <net/packet.h>
#include <types.h>

netlink_t nl_lo = 
	{
		.name = "lo",
		.mtu = 1024,
		.handle_packet = lo_handle_packet,
		.send_packet = lo_send_packet,
	};
	

uint32_t 
lo_handle_packet(netif_t *nif, packet_t *p)
{
	nif->rx_bytes += p->size;

	if(nif->netproto != NULL)
	{
		//((netproto_t *) (nif->netproto));
	}
	return 0;
}


uint32_t 
lo_send_packet(netif_t *nif, packet_t *p)
{
	nif->tx_bytes += p->size;
	return lo_handle_packet(nif, p);	
}
