/*!
	@file
	@author		Albert Semenov
	@date		09/2009
*/

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <MyGUI.h>
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace input
{
	class InputManager
	{
	public:
		InputManager();
		virtual ~InputManager();

		void createInput();
		void destroyInput();
		void captureInput();
		void setInputViewSize(int _width, int _height);
		
		// following five methods are to be implemented in BaseManager class
		virtual void injectMouseMove(int _absx, int _absy, int _absz){};
		virtual void injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id){};
		virtual void injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id){};
		virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text){};
		virtual void injectKeyRelease(MyGUI::KeyCode _key){};

		virtual void onFileDrop(const std::wstring& _filename) { }
		virtual bool onWinodwClose(size_t _handle) { return true; }

		void setMousePosition(int _x, int _y);
		void updateCursorPosition();

	protected:
		void frameEvent(float _time);
		void computeMouseMove();

		virtual bool mouseMoved(SDL_MouseMotionEvent &evt);
		virtual bool mousePressed(SDL_MouseButtonEvent &evt);
		virtual bool mouseReleased(SDL_MouseButtonEvent &evt);
		virtual bool keyPressed(SDL_Keycode &key, const char* text);
		virtual bool keyReleased(SDL_KeyboardEvent &key);

		void checkPosition();

		void buildVKeyMap();
		void buildMouseButtonMap();
	private:
		int mMouseX;
		int mMouseY;
		int mMouseZ;
		bool mMouseMove;
		int mWidth;
		int mHeight;
		std::map<int, MyGUI::KeyCode> mSDLVKeyMap;
		std::map<int, MyGUI::MouseButton> mSDLMouseMap;
	};

} // namespace input

#endif // INPUT_MANAGER_H_
