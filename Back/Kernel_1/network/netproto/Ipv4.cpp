/*
 * AbastractOS
 * Copyright (C) 2011 Davide Gessa
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <network/netproto/Ipv4.hpp>


int 
NetprotoIpv4::handlePacket(NetworkIface *iface, Packet *p)
{
	uint32_t protocol;
	
	Header *iphead = (Header *) p->Data;
	protocol = iphead->protocol;
	
	switch(protocol)
	{
		case PROTO_ICMP:
		case PROTO_UDP:
		case PROTO_TCP:	
		case PROTO_IPV6:			
			break;
	}
	
	return 0;
}





int 
NetprotoIpv4::sendPacket(NetworkIface *iface, Packet *p, char *addr)
{
	Header header;
	memcpy((char *) &(header.dest), addr, ADDR_LEN);
	memcpy((char *) &(header.source), (iface->Address), ADDR_LEN);
	header.protocol = PROTO_UDP;

	p->addHeader(sizeof(Header), (char *) &header);
	return (iface->LinkProto)->sendPacket(iface, p);

	// Verifica la dimensione e la mtu dell'interfaccia
	/*if((p->size + ((netlink_t *) (iface->link_protocol))->header_size) > ((netlink_t *) (iface->link_protocol))->frame_max_size)
	{
		// Crea l'header
		ip_header_t *fragheader;
		uint32_t i;
		//...
		
		uint32_t nf = (p->size + ((netlink_t *) (iface->link_protocol))->header_size) / 
					((netlink_t *) (iface->link_protocol))->frame_max_size;
		uint32_t offset = 0;
		
		for(i = 0; i < nf; i++)
		{
			// Imposta frammento
			packet_t *frag = packet_create(0, 1);
			fragheader = (ip_header_t *) frag->data;
			
			fragheader->offset = offset;
			fragheader->time_to_live = 255;
			
			// Invia frammento
			((netlink_t *) (iface->link_protocol))->send_frame(iface, frag);
		}
		
	}
	else
		((netlink_t *) (iface->link_protocol))->send_frame(iface, p);

	return 0;*/
}
