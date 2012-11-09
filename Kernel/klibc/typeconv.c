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
#include <klibc/typeconv.h>
#include <klibc/stdio.h>
#include <klibc/string.h>


/** Convert a bcd to binary */
unsigned char 
bcd2bin(unsigned char bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


/** Convert an int into a char* */
char *
itoa(int num)
{
	static char buff[10];
	char *str = buff + 9;
	int j = num;
	*str-- = 0;

	do 
		*str-- = num % 10 + '0';  
	while ((num = num / 10));

	if(j < 0)
		*str-- = '-';

	return ++str;
}




/** Convert an int into a char* hex */
char *
itox(int num)
{
	static char buff[10];
	char *str = buff + 9;
	*str-- = 0;

	do 
	{
		unsigned n = num % 16;
		char x;
		
		if(n <= 9) 
			x = n + '0';
		else
			x = (n - 9) + 'A' - 1;
		*str-- = x;  
	}
	while ((num = num / 16));

	return ++str;
}



/** Convert a string to int */
int 
atoi(const char *str)
{
	int num = 0;
	int pot = 1;

	str += strlen(str)-1;

	while(*str != '\0')
	{
		num += ((int)(*str)-48) * pot;
		pot *= 10;
		str--;		
	}

	return num;
}
