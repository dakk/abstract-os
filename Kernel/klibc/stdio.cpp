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

#include <klibc/stdio.h>
#include <klibc/stdarg.h>
#include <klibc/string.h>
#include <config.h>
#include <arch.h>
#include <Managers.hpp>


/* print a char */
void 
putchar(char ch)
{
	arch_kputch(ch, -1, -1);
}


/* print a string */
void 
puts(char *str)
{
	while(*str != '\0')
	{
		putchar(*str);
		str++;
	}
}




/* printf */
int 
printf(const char *format, ...)
{
	int len = 0;
	char output[255];
	char *current = &output[0];
	va_list ap;

	va_start(ap, format);


	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;

			switch (*format)
			{
				/* print a string */
				case 's':
					current = va_arg(ap, char *);
					puts(current);
					break;
					
				/* print a char */
				case 'c':
					current = va_arg(ap, char *);
					putchar(current[0]);
					break;

				/* print an hex */
				case 'x':
					puts(itox(va_arg(ap, int)));
					break;
					
				/* print a decimal */
				case 'd':
					puts(itoa(va_arg(ap, int)));
					break;


				/* % escape */
				case '%':
					putchar('%');
					break;
			}
		}
		else
			putchar(*format);

		format++;
		len++;
	}
	return len;
}



/* scanf */
int 
scanf(const char *format, ...)
{
	int len = 0;
	char buffer[255];
	char *current = &buffer[0];
	int *num;
	va_list ap;

	va_start(ap, format);

	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;

			switch (*format)
			{
				/* read a string */
				case 's':
					current = va_arg(ap, char *);
					gets(current);
					break;

				/* read a character */
				case 'c':
					current = va_arg(ap, char *);
					/* here? */
					break;

				/* read a decimal */
				case 'd':
					num = va_arg(ap, int *);
					gets(buffer);
					*num = atoi(buffer);
					break;
			}
		}

		format++;
		len++;
	}
	return len;
}




/* getchar */
int 
getchar()
{
	char c; 
	
	while((c = getch()) == 0); // printf("%d", c);
	
	return c;
}


/* getch */
int 
getch()
{	
	return arch_kgetch();

	#if 0
	Device *d = Managers::Instance->deviceManager->getDevice("kb0");

	if(d == NULL)
		return 0;
	else
	{
		uint8_t c;
		char ch;

		char keyboard_standard_charset[] = {
			0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 0, '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   
			0, 0, '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, 0, 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
			'-', 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
		};
		
		d->getDriver()->Read(&c, 1, 1);
		ch = keyboard_standard_charset[c];
		//printf("%c\n", ch);

		return ch;
	}
	#endif
}



/* get a string */
char *
gets(char *string)
{
	int count = 0;
	while(1)
	{
		*string = (char) getchar(); 
	
		if(*string == '\n') break;
		else if(*string == '\b')
		{
			if(count > 0)
			{
				string--;
				count--;
				//video_backspace();
			}
		}
		else
		{
			putchar(*string);
			string++;
			count++;
		}
	}
	putchar('\n');
	*string = '\0';
	return string;
}

