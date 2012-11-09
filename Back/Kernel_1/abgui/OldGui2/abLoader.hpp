#ifndef ABLOADER_HPP
#define ABLOADER_HPP

#include "abImage.hpp"
#include "abWidget.hpp"

using namespace abGui;

namespace abGui
{
	class Loader : public Widget
	{
		public:	
			static const unsigned ST_NETWORK = 3;
			static const unsigned ST_VFS = 2;
			static const unsigned ST_DEVICES = 1;

			virtual void Draw(){};

			Loader();
			~Loader();

			void setStep(unsigned i);
			void End();
	};
};

#endif
