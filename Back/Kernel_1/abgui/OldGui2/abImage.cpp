#include "abImage.hpp"
#include <malloc.h>
#include <string.h>

using namespace abGui;

Image::Image(char *filepath)
{

}


Image::Image(void *buf, unsigned dx, unsigned dy, unsigned bpp)
{
	Buffer = (void *) malloc(bpp * dx * dy);
	memcpy((char *) Buffer, (char *) buf, dx * dy * bpp);
	Bpp = bpp;
	SizeX = dx;
	SizeY = dy;
}


Image::~Image()
{
	free(Buffer);
}


