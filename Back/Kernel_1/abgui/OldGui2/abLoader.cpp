#include "abLoader.hpp"
#include <arch.h>

using namespace abGui;

Loader::Loader() : Widget()
{
}




void 
Loader::setStep(unsigned i)
{
	switch(i)
	{
		case ST_NETWORK:
			abGui->drawRect(0, 30, abGui->SizeX, 40, 0x00AA00, true);
			//Text("Network!", 100, 10 + i * 10, 0xFFFFFF);
			break;

		case ST_VFS:
			abGui->drawRect(0, 30, abGui->SizeX / 2, 40, 0x008800, true);
			//abGui->drawText("VFS!", 100, 10 + i * 10, 0xFFFFFF);
			break;

		case ST_DEVICES:
			abGui->drawRect(0, 30, abGui->SizeX / 3, 40, 0x005500, true);
			//abGui->drawText("Devices!", 100, 10 + i * 10, 0xFFFFFF);
			break;
	};
	
	abGui->swapBuffer();

	//int sec = arch_get_clock_data()->seconds;
	//while(arch_get_clock_data()->seconds == sec);

	//arch_sleep(900000);
}


void 
Loader::End()
{

}

