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
#ifndef __KERNEL_H
#define __KERNEL_H

#define REVISION		"48"
#define NAME			"AbstractOs"
#define RELEASE_NAME	"0.0.7 nightly build"

#define COL_H			0x02
#define COL_N			0x07
#define COL_S			0x04

#define	SINGLETON_ADDRESS	0x00011234

void shutdown(int);

#endif
