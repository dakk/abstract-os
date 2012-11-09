#ifndef ABEDITOR_HPP
#define ABEDITOR_HPP

#include <Managers.hpp>
#include <abgui/AbGuiManager.hpp>

class abEditor
{
	public:
		abEditor();
		~abEditor();

		void saveCallback();
		void openCallback();
		void closeCallback();

	private:
		abWindow *m_Window;


};

#endif
