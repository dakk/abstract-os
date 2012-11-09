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
/**
 * \file kernel/include/klibc/time.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef KLIBC_TIME_H
#define KLIBC_TIME_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef long int clock_t;
typedef long int time_t;

struct tm
{
	int Y, M, D, h, m, s;
	int tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec;
};


struct tm *localtime ( const time_t * timer);

#ifdef __cplusplus
};
#endif


#endif
