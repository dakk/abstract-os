#include "abTheme.hpp"
#include <types.h>

#define B 0x60606060

using namespace abGui;

Theme::Theme()
{
	uint32_t cursor[][12] =
	{
		{ 0, B, B, B, B, B, B, B, B, B, B, 0 },
		{ B, 0, B, B, B, B, B, B, B, B, 0, B },
		{ B, B, 0, B, B, B, B, B, B, 0, B, B },
		{ B, B, B, 0, B, B, B, B, 0, B, B, B },
		{ B, B, B, B, 0, B, B, 0, B, B, B, B },
		{ B, B, B, B, B, 0, 0, B, B, B, B, B },
		{ B, B, B, B, B, 0, 0, B, B, B, B, B },
		{ B, B, B, B, 0, B, B, 0, B, B, B, B },
		{ B, B, B, 0, B, B, B, B, 0, B, B, B },
		{ B, B, 0, B, B, B, B, B, B, 0, B, B },
		{ B, 0, B, B, B, B, B, B, B, B, 0, B },
		{ 0, B, B, B, B, B, B, B, B, B, B, 0 }
	};

	CursorImage = new Image((void *) cursor, 12, 12, 4);


	uint32_t panel[][1] = 
	{
		{ 0x00C6C6C6 } ,
		{ 0x00C4C4C4 } ,
		{ 0x00C2C2C2 } ,
		{ 0x00BFBFBF } ,
		{ 0x00BDBDBD } ,
		{ 0x00BBBBBB } ,
		{ 0x00B9B9B9 } ,
		{ 0x00B7B7B7 } ,
		{ 0x00B5B5B5 } ,
		{ 0x00B3B3B3 } ,
		{ 0x00B3B3B3 } ,
		{ 0x00B5B5B5 } ,
		{ 0x00B7B7B7 } ,
		{ 0x00B9B9B9 } ,
		{ 0x00BBBBBB } ,
		{ 0x00BDBDBD } ,
		{ 0x00BFBFBF } ,
		{ 0x00C2C2C2 } ,
		{ 0x00C4C4C4 } ,
		{ 0x00C6C6C6 }
	};
	PanelImage = new Image((void *) panel, 1, 20, 4);
	BackgroundColor = 0x643979;//0x785b9b;

	WindowBackgroundColor = 0xAAAAAA;
}

Theme::Theme(char *theme_dir)
{

}


Theme::~Theme()
{

}
