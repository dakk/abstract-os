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
 * \file kernel/include/klibc/stdio.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef KLIBC_STDIO_H
#define KLIBC_STDIO_H

#ifdef __cplusplus
extern "C"
{
#endif

void putchar(char);
void puts(char *);
char *itoa(int);
int atoi(const char *);
int printf(const char *, ...);
int scanf(const char *, ...);
int getchar();
int getch();
char *gets(char *);
char *itox(int);

#ifdef __cplusplus
};
#endif

#endif
