#ifndef IPV4_H
#define IPV4_H

#include <types.h>
#include <config.h>
#include <network/NetworkIface.hpp>

/** \addtogroup net
 * @{
 */

class NetprotoIpv4
{
	public:
		static const unsigned ADDR_LEN 		=	4;

		static const unsigned PROTO_ICMP	=	1;
		static const unsigned PROTO_TCP		=	6;
		static const unsigned PROTO_UDP		=	17;
		static const unsigned PROTO_IPV6	=	41;
	
		typedef struct
		{
			uint8_t version:4;
			uint8_t head_len:4;
			uint8_t tos;				///< Type of service
			uint16_t total_len;
			uint16_t ident;
			uint8_t flags:3;
			uint16_t offset:13;
			uint8_t time_to_live;
			uint8_t protocol;
			uint16_t header_checksum;
			uint32_t source;
			uint32_t dest;
		} Header;

		virtual int sendPacket(NetworkIface *iface, Packet *p, char *addr /*int proto?*/);
		virtual int handlePacket(NetworkIface *iface, Packet *p);
};


/** @} */

#endif
