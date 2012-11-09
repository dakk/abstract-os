/*
 * AbastractOS
 * Copyright (C) 2011 Davide Gessa
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
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
