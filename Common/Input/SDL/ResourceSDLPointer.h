/*!
	@file
	@author		Albert Semenov
	@date		11/2009
	@module
*/

#ifndef RESOURCE_W32_POINTER_H_
#define RESOURCE_W32_POINTER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_IResource.h"

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

namespace input
{

	class ResourceSDLPointer :
		public MyGUI::IResource
	{
		MYGUI_RTTI_DERIVED( ResourceSDLPointer );

	public:
		ResourceSDLPointer();
		virtual ~ResourceSDLPointer() { }

		virtual void deserialization(MyGUI::xml::ElementPtr _node, MyGUI::Version _version);

		SDL_SystemCursor getPointerType()
		{
			return mCursorType;
		}

	private:
		SDL_SystemCursor mCursorType;
	};

}

#endif // RESOURCE_W32_POINTER_H_
