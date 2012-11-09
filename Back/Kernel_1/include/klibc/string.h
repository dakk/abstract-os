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
 * \file kernel/include/klibc/string.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef KLIBC_STRING_H
#define KLIBC_STRING_H

#ifdef __cplusplus
extern "C" 
{
#endif

#include <klibc/ctype.h>


int strcmp(const char *, const char *);
size_t strlen(const char *);
void strcpy(char *, char *);
void strcat(char *, char *);

int strncmp(const char *, const char *, size_t);
void strncpy2(char *, char *, size_t);
void *memset(void *, int, size_t );
void *memcpy(char *, const char *, size_t );
void *memmove(void *, void *, size_t );
int memcmp(const void *, const void *, size_t );
char *strstr(char *, char *);

#ifdef __cplusplus
};
#endif


#endif



