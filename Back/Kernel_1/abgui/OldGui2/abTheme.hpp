#ifndef ABTHEME_HPP
#define ABTHEME_HPP


#include "abImage.hpp"

namespace abGui
{
	class Theme
	{
		public:
			Theme(char *theme_path);
			Theme();
			~Theme();

			bool Save(char *theme_path);
			bool Load(char *theme_path);

			Image *PanelImage;
			Image *CursorImage;
			unsigned BackgroundColor;
			unsigned WindowBackgroundColor;
	};
};

#endif
