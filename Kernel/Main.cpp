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
#include <arch.h>
#include <kernel.h>
#include <config.h>
#include <syscall.h>
#include <mm/mm.h>
#include <stdio.h>
#include <iostream.hpp>
#include <Driver.hpp>
#include <DriverManager.hpp>
#include <Device.hpp>
#include <DeviceManager.hpp>
#include <TaskManager.hpp>
#include <Elf.hpp>
#include <Task.hpp>
#include <Managers.hpp>
#include <Shell.hpp>
#include <vfs/VFSManager.hpp>
#include <ui/UiManager.hpp>
#include <network/NetworkManager.hpp>
#include <print/PrintManager.hpp>
#include <media/MediaManager.hpp>
#include <security/SecurityManager.hpp>
#include <Kernel/arch/x86/multiboot.h>
			

/* Instance of static var */
Managers *Managers::Instance = (Managers*) NULL;


void *Instance;


/** Main function of the kernel */ 
int 
main() 
{
	uint16_t err;
	char args[12][128];
	extern multiboot_info_t *multiboot;

	
	err = arch_init();
	
	if(err)
	{
		arch_shutdown();
		while(1);
	}

	/* kernel start message */
	arch_kclear();
	arch_ksetcl(COL_H);
	printf("* %s %s (rev %s on %s)\n", NAME, RELEASE_NAME, REVISION, ARCH);
	arch_ksetcl(COL_N);
	puts("Loading...\n");
	printf("Kernel compiled with: %s\n", CONTENTS);
	
	/* mem initialization */
	printf("MemoryManager init, %s\n", ((!mm_init(arch_mem_total())) ? "done" : "fail"));
	

	/* Create all singleton elements */
	Managers::Instance = (Managers *) /*SINGLETON_ADDRESS; */ new Managers();
	Managers::Instance->archManager = new ArchManager();
	Managers::Instance->deviceManager = new DeviceManager();
	Managers::Instance->driverManager = new DriverManager();
	Managers::Instance->taskManager = new TaskManager();
	#ifdef VFS
		Managers::Instance->vfsManager = new VFSManager();
	#endif
	#ifdef NETWORK
		Managers::Instance->netManager = new NetworkManager();
	#endif
	#ifdef PCIBUS
		Managers::Instance->pciBus = new PciBus();
	#endif
	#ifdef UI
		Managers::Instance->uiManager = new UiManager();
	#endif
	#ifdef PRINT
		Managers::Instance->printManager = new PrintManager();
	#endif
	#ifdef MEDIA
		Managers::Instance->mediaManager = new MediaManager();
	#endif
	#ifdef SECURITY
		Managers::Instance->securityManager = new SecurityManager();
	#endif

	Instance = (void *) Managers::Instance;

	/* Parse cmdline commands */
	#ifdef X86
	{
		char *cmd = (char *) multiboot->cmdline;
		int i = 0;
		int k = 0;

		while(*cmd != 0)
		{
			if(*cmd == ' ')
			{
				args[k][i] = 0;
				k++;
				i = 0;
			}
			else
				args[k][i++] = *cmd;
			cmd++;
		}
		args[k][i] = 0;
		args[k+1][0] = 0;
	}
	#endif
	#ifdef PCIBUS
		Managers::Instance->pciBus->Update();
	#endif

	/* Probing all devices */
	printf("Probing devices: ");
	printf("%s\n", Managers::Instance->deviceManager->Probe() == 0 ? "none" : " ");


	/* Mounting filesystems */
	#ifdef VFS
		/* Parse kernel arguments to find a valid fs */
		char fs[16] = {};
		char dev[16] = {};

		int i;
		for(i = 0; (i < 12) && (args[i][0] != 0); i++)
		{
			if(strncmp(args[i], "dev=", strlen("dev=")) == 0)
				strcpy(dev, args[i]+strlen("dev="));
			else if(strncmp(args[i], "fs=", strlen("fs=")) == 0)
				strcpy(fs, args[i]+strlen("fs="));
		}


		/* If there's fs and dev infos, mount the partition */
		if((fs[0] != 0) && (dev[0] != 0))
		{
			bool state;

			printf("Mounting %s with %s, ", dev, fs);

			state = Managers::Instance->vfsManager->Mount("/", Managers::Instance->deviceManager->getDevice(dev), fs);
			state ? printf("done\n") : printf("fail\n");

			#if 0
			ReadDir d;
			i = 0;
			printf("Listing directory /\n");
			while(Managers::Instance->vfsManager->readDir("/", &d, i))
			{
				printf("\t%d -> %s\n", d.Node, d.Name);
				i++;
			}
			#endif
		}
	#endif

	/* Probing all network iface */
	#ifdef NETWORK
		printf("Probing network interfaces: ");
		printf("%s\n", Managers::Instance->netManager->Probe() == 0 ? "none" : " ");
	#endif

	Shell();
	#ifdef TEST
		/* Syscall test */
		printf("Testing syscall and global singleton... ");
		extern void TestSyscall();
		TestSyscall();

		/* Test elf file loading */
		printf("Executing test app\n");
		Managers::Instance->taskManager->Exec("/test", NULL, NULL);
	#endif

	#ifdef UI
		/*  if(!*/Managers::Instance->uiManager->Setup(); //)
		/* {
			printf("Cannot start ui.\n");
			#ifdef SHELL
				Shell();
			#endif
		}
		else*/
			Managers::Instance->uiManager->mainLoop();
	#endif
	#ifndef UI
		#ifdef SHELL
			Shell();
		#endif
	#endif

	printf("\nNothing to do. Infinite loop\n");

	while(1);
	return 0;	
}	



/** Shutdown and reboot */
void 
shutdown(int type)
{
	#ifdef VFS
		delete Managers::Instance->vfsManager;
	#endif
	#ifdef NETWORK
		delete Managers::Instance->netManager;
	#endif
	#ifdef PCIBUS
		delete Managers::Instance->pciBus;
	#endif
	#ifdef UI
		delete Managers::Instance->uiManager;
	#endif
	#ifdef PRINT
		delete Managers::Instance->printManager;
	#endif
	#ifdef MEDIA
		delete  Managers::Instance->mediaManager;
	#endif
	#ifdef SECURITY
		delete Managers::Instance->securityManager;
	#endif


	arch_ksetcl(12);
	printf("\nThe system is going down: ");	
	arch_ksetcl(0x0F);
	
	switch(type)
	{
		case 1:
			puts("Shutdown.\n");
			arch_shutdown();
			break;
		case 2:
			puts("Reboot.\n");
			arch_reboot();
			break;
	}
	while(1);
}




/** Handle system calls */
void 
syscall_handler(regs_t *r)
{
	uint32_t v;

	printf("Syscall!\n");
	/*printf("%x\n", r->eax);
	printf("%x\n", r->ebx);
	printf("%x\n", r->ecx);
	printf("%x\n", r->edx);
	*/

	switch(r->eax)
	{
		case SYSCALL_POSIX_EXIT:
			v = Managers::Instance->taskManager->Kill(
					(pid_t) Managers::Instance->taskManager->getPid(), 0);
			break;

		case SYSCALL_POSIX_EXECVE:
			v = Managers::Instance->taskManager->Exec((char *) r->ebx, (char **) r->ecx, (char **) r->edx);
			break;

		case SYSCALL_POSIX_GETPID:
			v = Managers::Instance->taskManager->getPid();
			break;

		case SYSCALL_POSIX_FORK:
			v = Managers::Instance->taskManager->Fork();
			break;

		case SYSCALL_POSIX_KILL:
			v = Managers::Instance->taskManager->Kill((pid_t) r->ebx, (int) r->ecx);
			break;

		case SYSCALL_POSIX_WAIT:
			break;

		case SYSCALL_POSIX_ISATTY:
			v = 0;
			break;

		case SYSCALL_POSIX_CLOSE:
			{
				File *f = (File *) r->ebx;

				if(f->isOpen())
				{
					f->Close();
					v = 1;
				}
				else
					v = 0;
			}
			break;

		case SYSCALL_POSIX_LINK:
			v = Managers::Instance->vfsManager->Link((char *) r->ebx, (char *) r->ecx);
			break;

		case SYSCALL_POSIX_LSEEK:
			break;

		case SYSCALL_POSIX_OPEN:
			{
				VFSManager *m = Managers::Instance->vfsManager;

				File *ff = m->getFile((char *) r->ebx);
				if(ff->Open((char *) r->ecx))
					v = (uint32_t) ff;
				else
					v = -1;
			}
			break;

		case SYSCALL_POSIX_READ:
			{
				File *f = (File *) r->ebx;

				if(!f->isOpen())
					v = 0;
				else
					v = f->Read((char *) r->ecx, (int) r->edx);
			}
			break;

		case SYSCALL_POSIX_FSTAT:
			break;

		case SYSCALL_POSIX_STAT:
			break;

		case SYSCALL_POSIX_UNLINK:
			v = Managers::Instance->vfsManager->Unlink((char *) r->ebx);
			break;

		case SYSCALL_POSIX_SBRK:
			break;

		case SYSCALL_POSIX_GETTIMEOFDAY:
			break;

		case SYSCALL_GET_SINGLETON:
			v = (uint32_t) Managers::Instance;
			break;

		case SYSCALL_PUTS:
			printf("%s\n", (char *) r->ebx);
			break;

		default:
			v = 0;
	}

	r->eax = v;
}

