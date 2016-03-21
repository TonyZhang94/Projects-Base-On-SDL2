#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"


Game* Game::s_pInstance = 0;

Game* Game::Instance()
{
	if(s_pInstance == 0)
	{
		s_pInstance = new Game();
		return s_pInstance;

	}
	return s_pInstance;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(m_pWindow != 0) // window init success
		{
			cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer != 0) // renderer init success
			{
				cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
				if(1)
				{
					m_pGameStateMachine = new GameStateMachine();
					m_pGameStateMachine->changeState(new MenuState());

				/*	m_gameObjects.push_back(new BackGround(new LoaderParams(0, 0, 800, 501, "back")));
					m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "a", 200)));
					m_gameObjects.push_back(new Player(new LoaderParams(200, 200, 128, 82, "a", 300)));*/
					
				}
				else 
				{
					return false;
				}
			}
			else
			{
				cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully,start the main loop
	return true;
}

//void Game::draw()
//{
//	for(std::vector<GameObject*>::size_type i = 0; i !=
//		m_gameObjects.size(); i++)
//	{
//		m_gameObjects[i]->draw();
//	}
//}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
	//if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	//{
	//	m_pGameStateMachine->changeState(new PlayState());
	//}
}

//void Game::handleEvents()
//{
//	SDL_Event event;
//	if(SDL_PollEvent(&event))
//	{
//		switch (event.type)
//		{
//		case SDL_QUIT:
//			m_bRunning = false;break;
//		case SDL_KEYDOWN:
//            switch( event.key.keysym.sym )
//            {
//            case SDLK_a: SDL_Delay(1000); break;
//            }
//            break;
//		default:
//			break;
//		}
//	}
//}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

