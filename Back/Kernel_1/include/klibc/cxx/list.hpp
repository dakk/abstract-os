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
#ifndef LIST_HPP
#define LIST_HPP

#include <string.h>
#include <malloc.h>

template <class T>
class list
{
	public:
		list();
		~list();

		bool addNode(T *elem);
		bool addEndNode(T *elem);
		bool delNode(unsigned i);
		T *getNode(unsigned i);
		void Clear();

		bool delNodeByName(char *name);
		bool delNodeByObject(T *elem);
		T *getNodeByName(char *name);	
		T *getList();
		
		unsigned Len;
	protected:
		T *m_List;
};



template <class T>
list<T>::list()
{ 
	m_List = NULL;
	Len = 0;
}


template <class T>
list<T>::~list()
{
	Clear();
}


template <class T>
bool 
list<T>::addNode(T *elem)
{
	elem->Next = m_List;
	m_List = elem;
	Len++;

	return true;
}



template <class T>
bool 
list<T>::addEndNode(T *elem)
{
	T *e = getNode(Len - 1);
	elem->Next = NULL;
	e->Next = elem;
	Len++;

	return true;
}




template <class T>
bool 
list<T>::delNode(unsigned i)
{
	T *tmp = m_List;
	T *tmp2 = NULL;
	unsigned n = 0;

	while(tmp != NULL)
	{
		if(n == i)
		{
			if(tmp2 == NULL)
			{
				m_List = tmp->Next;
				free(tmp);
				Len--;
				return true;
			}
			else
			{
				Len--;
				tmp2->Next = tmp->Next;
				free(tmp);
				return true;
			}
		}

		tmp2 = tmp;
		tmp = tmp->Next;
		n++;
	}
	return false;
}




template <class T>
T*
list<T>::getList()
{
	return m_List;
}


template <class T>
T* 
list<T>::getNode(unsigned i)
{
	T *l = m_List;
	unsigned j = 0;

	while((l != NULL) && (j <= i))
	{
		if(j == i)
			return l;
		j++;
		l = l->Next;
	}

	return (T *) NULL;
}


template <class T>
void
list<T>::Clear()
{
	T *tmp = m_List;
	T *tmp2 = NULL;

	while(tmp != NULL)
	{
		tmp2 = tmp->Next;
		free(tmp);
	}
	Len = 0;
}



template <class T>
bool 
list<T>::delNodeByName(char *name)
{
	T *tmp = m_List;
	T *tmp2 = NULL;

	while(tmp != NULL)
	{
		if(strcmp(tmp->getName(), name) == 0)
		{
			if(tmp2 == NULL)
			{
				m_List = tmp->Next;
				free(tmp);
				Len--;
				return true;
			}
			else
			{
				tmp2->Next = tmp->Next;
				free(tmp);
				Len--;
				return true;
			}
		}

		tmp2 = tmp;
		tmp = tmp->Next;
	}
	return false;
}



template <class T>
T* 
list<T>::getNodeByName(char *name)
{
	T *tmp = m_List;

	while(tmp != NULL)
	{
		if(strcmp(tmp->getName(), name) == 0)
			return tmp;
		
		tmp = tmp->Next;
	}
	return (T *) NULL;
}



template <class T>
bool 
list<T>::delNodeByObject(T *elem)
{
	T *tmp = m_List;
	T *tmp2 = NULL;

	while(tmp != NULL)
	{
		if(tmp == elem)
		{
			if(tmp2 == NULL)
			{
				m_List = tmp->Next;
				free(tmp);
				Len--;
				return true;
			}
			else
			{
				Len--;
				tmp2->Next = tmp->Next;
				free(tmp);
				return true;
			}
		}

		tmp2 = tmp;
		tmp = tmp->Next;
	}
	return false;
}



#endif
