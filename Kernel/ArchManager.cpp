#include <ArchManager.hpp>

void 
ArchManager::Putch(uint8_t c, int16_t x, int16_t y)
{
	arch_kputch(c, x, y);
}

uint64_t 
ArchManager::getTotalMemory()
{
	return arch_mem_total();
}

void 
ArchManager::Sleep(uint32_t x)
{
	arch_sleep(x);
}


uint32_t 
ArchManager::getClock()
{
	return arch_get_clock();
}


uint32_t 
ArchManager::getTick()
{
	return arch_get_tick();
}


clock_data_t *
ArchManager::getClockData()
{
	return arch_get_clock_data();
}

void 
ArchManager::Shutdown()
{
	arch_shutdown();
}


void 
ArchManager::Reboot()
{
	arch_reboot();
}

void 
ArchManager::Standby()
{
	arch_standby();
}

void 
ArchManager::critStart()
{
	arch_crit_start();
}

void 
ArchManager::critEnd()
{
	arch_crit_end();
}

