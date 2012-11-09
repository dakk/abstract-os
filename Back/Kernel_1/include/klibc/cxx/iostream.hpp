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
#ifndef IOSTREAM_HPP
#define IOSTREAM_HPP


#define ATEXIT_MAX_FUNCS	128
 
#ifdef __cplusplus
extern "C" 
{
#endif
 
typedef unsigned uarch_t;
 
struct atexit_func_entry_t
{	
	void (*destructor_func)(void *);
	void *obj_ptr;
	void *dso_handle;
};


void __cxa_finalize(void *f);
void __cxa_atexit(void (*f)(void *), void *p, void *d);
void __cxa_pure_virtual();
int __cxa_guard_acquire();
void __cxa_guard_release();
int __cdecl_purecall();


struct _Unwind_Exception
{
	int value;
};

void _Unwind_Resume(struct _Unwind_Exception *object);



/**
 * OStream class
 */
class ostream
{
	public:
		void operator<<(char *str);
		void operator<<(int n);
};


/**
 * IStream class
 */
class istream
{
	public:
		void operator>>(char *str);
		void operator>>(int n);
};


extern istream cin;			///< Standard input
extern ostream cout;		///< Standard output


#ifdef __cplusplus
};
#endif

#endif
