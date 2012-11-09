#ifndef ABLABEL_HPP
#define ABLABEL_HPP

#include "abWidget.hpp"
#include "abContainer.hpp"

namespace abGui
{
	class Label : public Widget
	{
		public:
			Label(char *label);

			virtual void Draw();

		protected:
			char m_Label[256];

	};
};


#endif
