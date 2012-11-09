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
#include <klibc/string.h>

char *strstr(char *a, char *b)
{
	return a;
}

/* copy a string in another after first n byte */
void 
strncpy2(char *str1, char *str2, size_t n)
{
	str2 = str2 + n;
	
	strcpy(str1, str2);
}



/* return the len of a string */
size_t 
strlen(const char *str)
{
	size_t x = 0;

	while(*str++ != '\0') x++;
		
	return x;
}


/* copy a string in another */
void 
strcpy(char *str1, char *str2)
{
	while(*str2 != '\0')
	{
		*str1 = *str2;
		str1++; str2++;
	}
	*str1 = '\0';
}


/* join 2 strings */
void 
strcat(char *str1, char *str2)
{
	while(*str1 != '\0') str1++;
	
	while(*str2 != '\0')
	{
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
}


/* compare two strings */
int 
strcmp(const char *s1, const char *s2)
{	
	while(1)
	{
		if(*s1 != *s2) return 1;
		else if(*s1 == '\0' && *s2 == '\0') return 0;
		s1++; 
		s2++;
	}
}



/* full a memory area with c */
void *
memset(void *s, int c, size_t n)
{
	if((n % 8) == 0)
	{
		register uint64_t *a = (uint64_t *) s;	
		for (; 0 < n; n -= 8, a++)
			*a = c;
	}
	else if((n % 4) == 0)
	{
		register uint32_t *a = (uint32_t *) s;	
		for (; 0 < n; n -= 4, a++)
			*a = c;
	}
	else
	{
		register char *a = s;	
		for (; 0 < n; n--, a++)
			*a = c;
	}
	return s;
}



/* compare the first n bytes of two strings */
int 
strncmp(const char *s1, const char *s2, size_t dim)
{
	int a = 0;
	
	while(a < dim)
	{
		if(*s1 != *s2) return 1;
		else if(*s1 == '\0' && *s2 == '\0') return 0;
		s1++; 
		s2++;
		a++;
	}	
	return 0;
}



/** Copy a memory area */
void *
memcpy(char *b , const char *a, size_t n)
{
	if((n % 8) == 0)
	{
		register uint64_t *s1 = (uint64_t *) b;
		register const uint64_t *s2 = (uint64_t *) a;
		for(; 0 < n; n-=8)
			*s1++ = *s2++;
	}
	else if((n % 4) == 0)
	{
		register uint32_t *s1 = (uint32_t *) b;
		register const uint32_t *s2 = (uint32_t *) a;
		for(; 0 < n; n-=4)
			*s1++ = *s2++;
	}
	else
	{
		register char *s1 = b;
		register const char *s2 = a;
		for(; 0<n; --n)
			*s1++ = *s2++;
	}

	return (void *) b;
}


/* move a memory area */
void *
memmove(void *a, void *b, size_t dim)
{
	return NULL;
}


/* compare two memory areas */
int 
memcmp(const void *a, const void *b, size_t dim)
{
	return 0;
}
