#ifndef ARCHMANAGER_HPP
#define ARCHMANAGER_HPP

#include <arch.h>

class ArchManager
{
	public:
		static const unsigned SYSCALL = 0x80;

						ArchManager(){}
						~ArchManager(){}

		void			Putch(uint8_t, int16_t, int16_t);

		uint64_t		getTotalMemory();

		void			Sleep(uint32_t);
		uint32_t		getClock();
		uint32_t		getTick();
		clock_data_t *	getClockData();

		void 			Shutdown();
		void			Reboot();
		void			Standby();

		void			critStart();
		void			critEnd();
};


#endif
