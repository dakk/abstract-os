#ifndef ABCONTAINER_HPP
#define ABCONTAINER_HPP

#include "abWidget.hpp"
#include <list.hpp>

using namespace abGui;

namespace abGui
{
	class Container : public Widget
	{
		public:
			Container();
			~Container();

			void Draw();
	
			bool addWidget(Widget *w);


		protected:
			list<Widget> *m_WidgetList;
	};

};

#endif
