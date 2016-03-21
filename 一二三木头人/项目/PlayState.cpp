#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h";
#include "BackGround.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "LevelState.h"

const string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if(TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}


	if(m_s == LEVEL3)
	{
		if(InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			SDL_Delay(1000);
			Vector2D *mou_pos = TheInputHandler::Instance()->getMousePosition();
			//鼠标点击位置
			int xpos = mou_pos->getX();   
			int ypos = mou_pos->getY();

			Vector2D tar_pos = m_gameObjects[1]->getPosition();
			//目标位置
			int _xpos_ = tar_pos.getX();
			int _ypos_ = tar_pos.getY();
			int width = m_gameObjects[1]->getWidth();
			int height = m_gameObjects[1]->getHeight();
			if(xpos > _xpos_ && xpos < (_xpos_ + width) && ypos > _ypos_ && ypos < (_ypos_ + height))
			{
				GameState * o = new GameOverState(WIN);
				o->setPS(m_s);
				TheGame::Instance()->getStateMachine()->changeState(o);
			}
			else
			{
				GameState * o = new GameOverState(LOSE);
				o->setPS(m_s);
				TheGame::Instance()->getStateMachine()->changeState(o);
			}
		}
	}
	else 
	{
		if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && 
			p_id < m_gameObjects.size())
		{
			p_id++;
			if(p_id == m_gameObjects.size())
			{
				SDL_Delay(1000);
				int tmpFrame = m_gameObjects[1]->getFrame();
				for(int i = 2 ; i < p_id; i++)
				{
					if(m_gameObjects[i]->getFrame() != tmpFrame)
					{
						GameState * o = new GameOverState(LOSE);
						o->setPS(m_s);
						TheGame::Instance()->getStateMachine()->changeState(o);
						return;
					}
				}
				GameState * o = new GameOverState(WIN);
				o->setPS(m_s);
				TheGame::Instance()->getStateMachine()->changeState(o);
			}
			TheInputHandler::Instance()->reset();	
		}
	}

	for(int i = p_id; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	//走出窗口，认为游戏失败
	for(int i = 1; i < m_gameObjects.size(); i++)
	{
		int xpos = m_gameObjects[i]->getPosition().getX();
		int ypos = m_gameObjects[i]->getPosition().getY();
		if( !( (xpos <= WINDOW_WIDTH) && (xpos >= 0) && (ypos <= WINDOW_HEIGHT) && (ypos >= 0) ) )
		{
			GameState * o = new GameOverState(LOSE);
			o->setPS(m_s);
			TheGame::Instance()->getStateMachine()->changeState(o);
		}
	}
}

void PlayState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	PlayState::p_id = 1;
	TheInputHandler::Instance()->reset();

	if(m_s == LEVEL1)
	{
		if(!TheTextureManager::Instance()->load("setting/d.png",
			"c", TheGame::Instance()->getRenderer()))
		{
			return false;
		}

		if(!TheTextureManager::Instance()->load("setting/back.png",
			"back", TheGame::Instance()->getRenderer()))
		{
			return false;
		}
		GameObject* back = new BackGround(new LoaderParams(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "back"));
		GameObject* player1 = new Player(new LoaderParams(100, 100, 71, 90, "c"), new Vector2D(2.0, 0.0), 4, 500, 1);
		GameObject* player2 = new Player(new LoaderParams(100, 300, 71, 90, "c"), new Vector2D(1.0, 0.0), 4, 500, 3);

		m_gameObjects.push_back(back);
		m_gameObjects.push_back(player1);
		m_gameObjects.push_back(player2);
	}
	else if(m_s == LEVEL2)
	{
		if(!TheTextureManager::Instance()->load("setting/a.png",
			"c", TheGame::Instance()->getRenderer()))
		{
			return false;
		}

		if(!TheTextureManager::Instance()->load("setting/third.png",
			"back", TheGame::Instance()->getRenderer()))
		{
			return false;
		}
		GameObject* back = new BackGround(new LoaderParams(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "back"));
		GameObject* player1 = new Player(new LoaderParams(50, 50, 128, 82, "c"), new Vector2D(1.0, 1.0), 6, 500, 0);
		GameObject* player2 = new Player(new LoaderParams(50, 300, 128, 82, "c"), new Vector2D(1.0,0.0), 6, 200, 3);
		GameObject* player3 = new Player(new LoaderParams(50, 600, 128, 82, "c"), new Vector2D(1.0,-1.0), 6, 300, 5);
	
		m_gameObjects.push_back(back);
		m_gameObjects.push_back(player1);
		m_gameObjects.push_back(player2);
		m_gameObjects.push_back(player3);
	}
	else if(m_s == LEVEL3)
	{
		if(!TheTextureManager::Instance()->load("setting/z.png",
			"c", TheGame::Instance()->getRenderer()))
		{
			return false;
		}

		if(!TheTextureManager::Instance()->load("setting/second.png",
			"back", TheGame::Instance()->getRenderer()))
		{
			return false;
		}

		GameObject* back = new BackGround(new LoaderParams(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "back"));
		GameObject* player[4]; 
		player[0] = new Player(new LoaderParams(50, 50, 40, 40, "c"), new Vector2D(20.0, 8.0), 1, 100);
		player[1] = new Player(new LoaderParams(50, 550, 40, 40, "c"), new Vector2D(0.0, -10.0), 1, 100);
		player[2] = new Player(new LoaderParams(900, 550, 40, 40, "c"), new Vector2D(-15.0, 0.0), 1, 100);
		player[3] = new Player(new LoaderParams(550, 550, 40, 40, "c"), new Vector2D(8.0, -10.0), 1, 100);

		int x = rand()%4;

		m_gameObjects.push_back(back);
		m_gameObjects.push_back(player[x]);
	}
	
	std::cout << "entering PlayState\n";

	return true;
}


bool PlayState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("c");
	TheTextureManager::Instance()->clearFromTextureMap("back");
	std::cout << "exiting PlayState\n";
	return true;
}