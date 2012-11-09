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
#include "Vesa.hpp"
#include <Driver.hpp>


VesaDriver::Info *vci;
VesaDriver::ModeInfo *vmi;
extern multiboot_info_t *multiboot;


/**
 * Return the vesa mode info
 */
VesaDriver::ModeInfo *
VesaDriver::getModeInfo()
{
	return vmi;
}



/**
 * Draw a pixel in the screen
 */
void 
VesaDriver::drawPixel(unsigned x, unsigned y, uint32_t cl)
{
	register char *ptmp;
	
	//if (x < 0 || x > vmi->width || y < 0 || y > vmi->height) return;
	
	x = (x * (vmi->bits_per_pixel >> 3));
	y = (y * vmi->bytes_per_scan_line);
	
	char *asd = (char *)vmi->phys_base_ptr;
	ptmp = &asd[x+y];
	ptmp[0] = cl & 0xff;
	ptmp[1] = (cl>>8) & 0xff;
	ptmp[2] = (cl>>16) & 0xff;
}




/**
 * Get a pixel from the screen
 */
uint32_t 
VesaDriver::getPixel(unsigned x, unsigned y)
{
	register char *ptmp = NULL;
	
	if (x < 0 || x > vmi->width || y < 0 || y > vmi->height) return 0;
	
	x = (x * (vmi->bits_per_pixel >> 3));
	y = (y * vmi->bytes_per_scan_line);
	
	char *asd = (char *)vmi->phys_base_ptr;
	*ptmp = asd[x+y];
	return *ptmp;	
}




/**
 * Set a video mode
 */
bool
VesaDriver::setMode(unsigned x, unsigned y, unsigned bits)
{
	return 0;	
}




/**
 * Create the vesa driver with a custom resolution
 */
VesaDriver::VesaDriver(unsigned x, unsigned y, unsigned bpp) : Driver("Vesa", "ve")
{	
	vci = (VesaDriver::Info *) multiboot->vbe_control_info;
	vmi = (VesaDriver::ModeInfo *) multiboot->vbe_mode_info;

	Memory = (char *) vmi->phys_base_ptr;
}


/**
 * Create the vesa driver
 */
VesaDriver::VesaDriver() : Driver("Vesa", "ve")
{
	VesaDriver(800,600,32);
}


/**
 * Destroy vesa driver
 */
VesaDriver::~VesaDriver()
{
	
}



/**
 * Return X dimension
 */
unsigned 
VesaDriver::getX()
{
	return vmi->width;
}


/**
 * Return 
 */
unsigned 
VesaDriver::getBpsl()
{
	return vmi->bytes_per_scan_line;
}

/**
 * Return Y dimension
 */
unsigned 
VesaDriver::getY()
{
	return vmi->height;	
}



/**
 * Return Bpp
 */
unsigned 
VesaDriver::getBpp()
{
	return vmi->bits_per_pixel;	
}


/**
 * Probe the driver
 */
bool 
VesaDriver::Probe() 
{
	if(multiboot->vbe_control_info != 0)
		return true;
	else
		return false;
}
