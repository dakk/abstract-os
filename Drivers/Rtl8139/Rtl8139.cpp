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
#include "Rtl8139.hpp"
#include <Driver.hpp>
 

const PciBus::Entry Rtl8139Driver::PciList[] = 
{
	{ 0x10ec, 0x8139 },	/* Realtek RTL8139 */
	{ 0x02ac, 0x1012 },	/* SpeedStream 1012 PCMCIA 10/100 */
	{ 0x1065, 0x8139 },	/* Texas Microsystems 8139C Network Card */
	{ 0x1113, 0x1211 },	/* Accton MPX5030 or SMC1211TX EZCard 10/100 */
	{ 0x1186, 0x1300 },	/* D-Link DFE530TX+/DFE538TX */
	{ 0x1186, 0x1340 },	/* D-Link DFE690TXD */
	{ 0x11db, 0x1234 },	/* Sega Dreamcast HIT-400 */
	{ 0x1259, 0xa117 },	/* Allied Telesyn 8139 */
	{ 0x1259, 0xa11e },	/* Allied Telesyn 8139 */
	{ 0x126c, 0x1211 },	/* Northern Telecom 10/100BaseTX*/
	{ 0x13d1, 0xab06 },	/* AboCom FE2000VX */
	{ 0x1432, 0x9130 },	/* Edimax Computer Co. RTL81xx */
	{ 0x14ea, 0xab06 },	/* Planex FNW-3603-TX */
	{ 0x14ea, 0xab07 },	/* Planex FNW-3800-TX */
	{ 0x1500, 0x1360 },	/* Delta Electronics RealTek Ethernet */
	{ 0x1743, 0x8139 },	/* Peppercon AG 8139  ROL/F-100 */
	{ 0x4033, 0x1360 },	/* Addtron Technology 8139 */
	{ 0x0000, 0x0000 }
};



/**
 * Create the driver
 */
Rtl8139Driver::Rtl8139Driver() : Driver("Rtl8139", "rt")
{
}


/**
 * Destroy driver
 */
Rtl8139Driver::~Rtl8139Driver()
{
	
}



bool
Rtl8139Driver::Probe()
{
	#ifdef PCI
		PciBus::Device *d = Managers::Instance->pciBus->getDevice(PciList, PciListSize);

		if(d != NULL)
			return true;
	#endif

	return false;
}


