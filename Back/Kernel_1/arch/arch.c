#include <arch.h>

clock_data_t *
arch_get_clock_data()
{
	return &clock_data;
}
