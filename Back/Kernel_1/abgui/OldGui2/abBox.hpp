#ifndef ABBOX_HPP
#define ABBOX_HPP

#include "abContainer.hpp"
#include <list.hpp>

namespace abGui
{
	class Box : public Container
	{
		public:
			Box(bool vert, bool expand, unsigned margin);
			
			bool addWidget(Widget *t);

		protected:
			bool m_VerticalBox;
			unsigned m_Margin;
	};

};

#endif
