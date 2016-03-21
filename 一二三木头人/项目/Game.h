#ifndef __GGGG__
#define __GGGG__

#include "utility.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "GameStateMachine.h"

typedef class Game
{
public:
	~Game() {}
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	/*void draw();*/
	void handleEvents();
	void clean();
	bool running() { return m_bRunning; }
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	static Game* Instance();
	void quit() { SDL_Quit(); exit(0); }   //!
	GameStateMachine* getStateMachine(){ return m_pGameStateMachine; }

private:
	Game() {}
private:
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	vector<GameObject*> m_gameObjects;

	GameStateMachine* m_pGameStateMachine;
}TheGame;

#endif /* defined(__Game__) */