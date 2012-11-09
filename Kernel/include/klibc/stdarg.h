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
 * \file kernel/include/klibc/stdarg.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef KLIBC_STDARG_H
#define KLIBC_STDARG_H


#ifdef __cplusplus
extern "C"
{
#endif

/** Argument list type */
typedef void * va_list;

#define va_start(list, lastpar) (list = &lastpar)
#define va_arg(list, type) *((type *)(list += sizeof(int)))
#define va_end(list) do {} while(0)

#ifdef __cplusplus
};
#endif


#endif
