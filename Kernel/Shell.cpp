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
#include <Shell.hpp>
#include <stdio.h>
#include <string.h>
#include <kernel.h>
#include <config.h>
#include <arch.h>
#include <Managers.hpp>

#ifdef VFS
	char path[1024];
#endif


int ShellHelp			(int argc, char **argv);
int ShellShutdown		(int argc, char **argv);
int ShellLsPci			(int argc, char **argv);
int ShellPwd			(int argc, char **argv);
int ShellCd				(int argc, char **argv);
int ShellLs				(int argc, char **argv);
int ShellClear			(int argc, char **argv);
int ShellUmount			(int argc, char **argv);




ShellCommand _commands[] =
{
	#ifdef PCIBUS
		{ "lspci", "List pci devices", ShellLsPci },
	#endif

	{ "help", "This help", ShellHelp },

	#ifdef VFS
		{ "pwd", "Show current directory", ShellPwd },
		{ "cd", " ", ShellCd },
		{ "ls", " ", ShellLs },
		{ "umount", " ", ShellUmount },
	#endif

	{ "clear", " ", ShellClear },
	{ "shutdown", "Shutdown or reboot the system", ShellShutdown }
};


#define _COMMANDS_N		(sizeof(_commands) / sizeof(ShellCommand))


#ifdef VFS
int ShellUmount(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("usage:\numount path\n");
		return 0;
	}

	Managers::Instance->vfsManager->Umount(argv[1]);

	return 0;
}

int ShellCd(int argc, char **argv)
{
	if(argc == 1)
		strcpy(path, "/");
	else if(argc == 2)
		strcpy(path, argv[1]);

	return 0;
}


int ShellLs(int argc, char **argv)
{
	VFSManager *v = Managers::Instance->vfsManager;
	ReadDir rd;
	unsigned i = 0;

	while(v->readDir(path, &rd, i))
	{
		printf("  %s\n", rd.Name);
		i++;
	}

	return 0;
}


int ShellPwd(int argc, char **argv)
{
	printf("%s\n", path);

	return 0;
}
#endif


int ShellClear(int argc, char **argv)
{
	arch_kclear();

	return 0;
}


int ShellHelp(int argc, char **argv)
{
	unsigned i;

	for(i = 0; i < _COMMANDS_N; i++)
		printf("%s - %s\n", _commands[i].Name, _commands[i].Description);

	return 0;
}


int ShellShutdown(int argc, char **argv)
{
	if(argc == 2)
	{
		if(strcmp(argv[1], "-r") == 0)
			shutdown(2);
	}
	shutdown(1);
	return 0;
}


#ifdef PCIBUS
int ShellLsPci(int argc, char **argv)
{
	PciBus::Device *d = Managers::Instance->pciBus->getDeviceList()->getNode(0);

	while(d != NULL)
	{
		printf("%d:%d.%d %s: %s\n", d->Bus, d->Function, d->Device, d->Class, d->ClassDesc);
		d = d->Next;
	}
	
	return 0;
}
#endif



void 
Shell()
{
	char ch;
	unsigned i;
	bool exit = false;
	char string[1024];
	unsigned p;

	#ifdef VFS
	strcpy(path, "/");
	#endif

	printf("\nShell started.\n\n");

	while(!exit)
	{
		arch_ksetcl(COL_H);
		#ifdef VFS
		printf("%s", path);
		#endif
		printf("$ ");
		arch_ksetcl(COL_N);

		p = 0;

		while((ch = getchar()) != '\n')
		{
			if((ch == '\b') && (p == 0))
				continue;

			putchar(ch);
			if(ch == '\b')
			{
				p--;
			}
			else
			{
				string[p] = ch;
				p++;
			}
		}
		string[p] = 0;
		putchar('\n');

		for(i = 0; i < _COMMANDS_N; i++)
		{
			if(strcmp(string, _commands[i].Name) == 0)
				_commands[i].Call(0, NULL);
		}
	}
}
