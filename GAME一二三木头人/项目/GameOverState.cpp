#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "BackGround.h"
#include "LevelState.h"


const string GameOverState::s_gameOverID = "GAMEOVER";
int GameOverState::pre_sta = LEVEL1;

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new
		MenuState());
}

//*********************************************************
void GameOverState::s_restartPlay()
{
	GameState *p =  new PlayState();
	p->setS(pre_sta);
	TheGame::Instance()->getStateMachine()->changeState(p);
}

bool GameOverState::onEnter()
{
	TheInputHandler::Instance()->reset();

	if(m_state == LOSE)
	{
		if(!TheTextureManager::Instance()->load("setting/gameover.png",
			"over", TheGame::Instance()->getRenderer()))
		{
			return false;
		}
	}
	else
	{
		if(!TheTextureManager::Instance()->load("setting/win.png",
			"over", TheGame::Instance()->getRenderer()))
		{
			return false;
		}
	}
	
	if(!TheTextureManager::Instance()->load("setting/main.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("setting/restart.png",
		"restartbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* gameOverText = new BackGround(new LoaderParams(400, 100, 190, 50, "over"));
	GameObject* button1 = new MenuButton(new LoaderParams(350, 200,
		300, 120, "mainbutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(350, 400,
		300, 120, "restartbutton"), s_restartPlay);
	
	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	
	cout << "entering GaveOverState\n";
	return true;
}

void GameOverState::update()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
	TheTextureManager::Instance()->clearFromTextureMap("gameover");
	
	std::cout << "exiting GaveOverState\n";
	return true;
}

