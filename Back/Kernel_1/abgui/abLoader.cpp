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
#include "abLoader.hpp"
#include <arch.h>

using namespace abGui;

Loader::Loader() : Widget()
{
}




void 
Loader::setStep(unsigned i)
{
	abGui->drawRect(0, 29, abGui->SizeX, 41, 0xFFFFFF, false);

	switch(i)
	{
		case ST_NETWORK:
			abGui->drawRect(0, 30, abGui->SizeX, 40, 0x643979, true);
			//Text("Network!", 100, 10 + i * 10, 0xFFFFFF);
			break;

		case ST_VFS:
			abGui->drawRect(0, 30, abGui->SizeX / 2, 40, 0x643979, true);
			//abGui->drawText("VFS!", 100, 10 + i * 10, 0xFFFFFF);
			break;

		case ST_DEVICES:
			abGui->drawRect(0, 30, abGui->SizeX / 3, 40, 0x643979, true);
			//abGui->drawText("Devices!", 100, 10 + i * 10, 0xFFFFFF);
			break;
	};
	
	abGui->swapBuffer();

	//int sec = arch_get_clock_data()->seconds;
	//while(arch_get_clock_data()->seconds == sec);

	//arch_sleep(9000000);
}


void 
Loader::End()
{

}

