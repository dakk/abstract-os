#include <net/lo.h>
#include <net/eth.h>
#include <net/if.h>
#include <net/packet.h>
#include <malloc.h>
#include <driver.h>
#include <device.h>
#include <string.h>


/* probe all net ifaces */
int
netif_probe()
{
	netif_add(&nl_lo, NULL, NULL, NULL);
	netif_add(&nl_eth, NULL, NULL, NULL);
	
	/* probe all ifaces */
	//netif_list = &n1;
	//n1.next = NULL;
		
	return 0;
}



/* create an iface and add it to the ifaces list */
netif_t *
netif_add(netlink_t *ln, netproto_t *pr, drv_t *dr, dev_t *dv)
{
	//if((pr == NULL) || (ln == NULL) || (dr == NULL) || (dv == NULL))
	//	return NULL;
		
	netif_t *n = (netif_t *) malloc(sizeof(netif_t));
	
	n->tx_bytes = 0;
	n->rx_bytes = 0;
	
	if(ln->mtu < pr->mtu)
		n->mtu = ln->mtu;
	else
		n->mtu = pr->mtu;
		
	char num[3];
	num[0] = '0';
	num[1] = 0;
	n->device = dv;
	n->driver = dr;
	n->netlink = ln;
	n->netproto = pr;
	strcpy(n->name, ln->name);
	strcat(n->name, num);
	
	n->next = netif_list;
	netif_list = n;
	
	return n;
}



/* get the i iface */
netif_t *
netif_iget(int i)
{
	int j = 0;
	netif_t *n = netif_list;
	
	while(n != NULL)
	{
		if(j == i)
			return n;
		
		n = n->next;
		j++;
	}
	return (netif_t *) NULL;	
}



/* init the networking */
int
netif_init()
{
	netif_list = NULL;
	
	return netif_probe();
}
