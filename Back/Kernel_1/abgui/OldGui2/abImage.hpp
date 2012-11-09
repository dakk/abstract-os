#ifndef ABIMAGE_HPP
#define ABIMAGE_HPP

namespace abGui
{
	class Image
	{
		public:
			Image(char *filepath);
			Image(void *buf, unsigned dx, unsigned dy, unsigned bpp);
			~Image();

			void *Buffer;
			unsigned SizeX;
			unsigned SizeY;
			unsigned Bpp;
	};
};

#endif
