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
	#include <arch.h>
	#include <kernel.h>
	#include <config.h>
};

#include <mm/mm.h>
#include <stdio.h>
#include <iostream.hpp>
#include <Driver.hpp>
#include <DriverManager.hpp>
#include <Device.hpp>
#include <DeviceManager.hpp>
#include <TaskManager.hpp>
#include <Task.hpp>
#include <abgui/abGuiManager.hpp>
#include <abgui/abLoader.hpp>
#include <Managers.hpp>
#include <vfs/VFSManager.hpp>
#include <network/NetworkManager.hpp>

using namespace abGui;



/* Instance of static var */
Managers *Managers::Instance = (Managers*) NULL;


/**
 * Main function of the kernel
 */ 
int 
main() 
{
	uint16_t err;
	char args[12][128];
	Loader *loader;

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
	Managers::Instance = new Managers();
	Managers::Instance->deviceManager = new DeviceManager();
	Managers::Instance->driverManager = new DriverManager();
	Managers::Instance->taskManager = new TaskManager();
	#ifdef VFS
		Managers::Instance->vfsManager = new VFSManager();
	#endif
	#ifdef NETWORK
		Managers::Instance->netManager = new NetworkManager();
	#endif
	#ifdef ABGUI
		Managers::Instance->guiManager = new abGuiManager();
	#endif
	#ifdef PCIBUS
		Managers::Instance->pciBus = new PciBus();
	#endif

	/* Parse cmdline commands */
	#ifdef X86
	{
		#include "Kernel/arch/x86/multiboot.h"
			
		extern multiboot_info_t *multiboot;
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

	#ifdef ABGUI
		if(Managers::Instance->guiManager->Probe())
		{
			Managers::Instance->guiManager->Init();
			
			#ifdef ABGUI_LOADER
				loader = Managers::Instance->guiManager->guiLoader;
				loader->setStep(Loader::ST_DEVICES);
			#endif
		}
	#endif

	

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
			state = Managers::Instance->vfsManager->Mount("/", 
														Managers::Instance->deviceManager->getDevice(dev), fs);
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
		#ifdef ABGUI_LOADER
			loader->setStep(Loader::ST_VFS);
		#endif
	#endif

	
	/* Probing all network iface */
	#ifdef NETWORK
		printf("Probing network interfaces: ");
		printf("%s\n", Managers::Instance->netManager->Probe() == 0 ? "none" : " ");

		#ifdef ABGUI_LOADER
			loader->setStep(Loader::ST_NETWORK);
		#endif
	#endif


	/* If compiled, start inkernel gui, abstractgui */
	#ifdef ABGUI
		if(Managers::Instance->guiManager->Probe())
			Managers::Instance->guiManager->mainLoop();
	#endif


	printf("Infinite loop\n");

	while(1);
	return 0;	
}	



/**
 * Shutdown and reboot
 */
void 
shutdown(int type)
{	
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


