#ifndef __IHIHIH__
#define __IHIHIH__

#include "utility.h"
#include "Game.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

typedef class InputHandler
{
public:
	static InputHandler* Instance();
	void reset();

	 // update and clean the input handler
    void update();
	void clean() {}

	  // keyboard events
    bool isKeyDown(SDL_Scancode key) const;

	 // mouse events
    bool getMouseButtonState(int buttonNumber) const;
    Vector2D* getMousePosition() const;
private:
	InputHandler();
	~InputHandler();
	 InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);
	// handle keyboard events
	void onKeyDown();
	void onKeyUp();
	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
private:
	static InputHandler* s_pInstance;
	   
	// keyboard specific
    const Uint8* m_keystates;

	// mouse specific
    vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
}TheInputHandler;

#endif