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
extern "C"
{
	#include <mm/mm.h>
	#include <klibc/string.h>
	#include <klibc/stdio.h>
}
#include <iostream.hpp>


#ifdef __cplusplus
extern "C" 
{
#endif
//	atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
//	uarch_t __atexit_func_count = 0;
 
//	void *__dso_handle = 0; 
 /*
	int __cxa_atexit(void (*f)(void *), void *objptr, void *dso)
	{
		if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {return -1;};
		__atexit_funcs[__atexit_func_count].destructor_func = f;
			__atexit_funcs[__atexit_func_count].obj_ptr = objptr;
		__atexit_funcs[__atexit_func_count].dso_handle = dso;
		__atexit_func_count++;
		return 0; //I would prefer if functions returned 1 on success, but the ABI says...
	};
 
	void __cxa_finalize(void *f)
	{
		uarch_t i = __atexit_func_count;
		if (!f)
		{
			while (--i)
			{
				if (__atexit_funcs[i].destructor_func)
				{
					(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
				};
			};
			return;
		};
 
		for ( ; i >= 0; )
		{
			if (__atexit_funcs[i].destructor_func == f)
			{
				(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
				__atexit_funcs[i].destructor_func = 0;
 			};
		};
	};*/
 

int __cdecl_purecall(){ return 0; }
void __cxa_finalize(void *f){}
void __cxa_atexit(void (*f)(void *), void *p, void *d){ }
void __cxa_pure_virtual(){ }
int __cxa_guard_acquire(){ return 1; }
void __cxa_guard_release(){ }


ostream cout;
istream cin;

void 
_Unwind_Resume(struct _Unwind_Exception *object)
{
	return;
}




/**
 * New operator
 */
void *operator 
new(size_t size)
{
    return mm_alloc(size * 4);
}


/**
 * New operator for arrays
 */ 
void *operator 
new[](size_t size)
{
    return mm_alloc(size * 4);
}
 
 
/**
 * Delete operator
 */
void operator 
delete(void *p)
{
    mm_free(p);
}


/**
 * Delete operator for arrays
 */ 
void operator 
delete[](void *p)
{
	mm_free(p);
}






/**
 * Put a char* in the stream
 */
void 
ostream::operator<<(char *str)
{
	puts(str);
}




/**
 * Put a number in the stream
 */
void 
ostream::operator<<(int n)
{
	puts(itoa(n));
}


/**
 * Get a char* from the stream
 */
void 
istream::operator>>(char *str)
{
	scanf("%s", str);
}




/**
 * Get a number from the stream
 */
void 
istream::operator>>(int n)
{
	scanf("%d", &n);
}


#ifdef __cplusplus
};
#endif

