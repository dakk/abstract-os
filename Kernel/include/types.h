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
#ifndef TYPES_H
#define TYPES_H

#define true	1
#define false	0
#define NULL	0

#include <config.h>

#ifdef BIT32
	typedef unsigned int 	     u_int32;
	typedef unsigned short       u_int16;
	typedef signed char          int8_t;
	typedef unsigned char        uint8_t;
	typedef short                int16_t;
	typedef unsigned short       uint16_t;
	typedef int                  int32_t;
	typedef unsigned             uint32_t;
	typedef long long            int64_t;
	typedef unsigned long long   uint64_t;
	typedef unsigned char        byte;
	typedef unsigned short int   word;
	typedef unsigned int         dword;
	typedef unsigned long long   qword;
#endif

typedef unsigned 	     	 size_t;
typedef unsigned char 	     u_char;
typedef unsigned int 	     u_int;
typedef int32_t				 gid_t;
typedef int32_t				 uid_t;
typedef int32_t				 pid_t;


#endif
