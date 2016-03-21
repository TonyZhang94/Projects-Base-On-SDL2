#include "LevelState.h"
#include "Game.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "BackGround.h"
#include "PlayState.h"
#include "LevelState.h"

const string LevelState::s_menuID = "LEVELSTATE";

void LevelState::update()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void LevelState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool LevelState::onEnter()
{
	TheInputHandler::Instance()->reset();

	if(!TheTextureManager::Instance()->load("setting/level1.png", 
		"level1", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("setting/level2.png",
		"level2", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("setting/level3.png",
		"level3", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("setting/bg.png",
		"bg", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* Button1 = new MenuButton(new LoaderParams(100, 225, 250,
		63, "level1"),  s_ToLevel1);
	GameObject* Button2 = new MenuButton(new LoaderParams(100, 325, 250,
		63, "level2"),  s_ToLevel2);
	GameObject* Button3 = new MenuButton(new LoaderParams(100, 425, 250,
		63, "level3"),  s_ToLevel3);
	GameObject* back = new BackGround(new LoaderParams(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "bg"));

	m_gameObjects.push_back(back);
	m_gameObjects.push_back(Button1);
	m_gameObjects.push_back(Button2);
	m_gameObjects.push_back(Button3);
	cout << "entering MenuState\n";
	return true;
}

bool LevelState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("bg");    
	TheTextureManager::Instance()->clearFromTextureMap("level1");
	TheTextureManager::Instance()->clearFromTextureMap("level2");
	TheTextureManager::Instance()->clearFromTextureMap("level3");    //my add
	cout << "exiting MenuState\n";
	return true;
}

void LevelState::s_ToLevel1()
{
	GameState *p = new PlayState();
	p->setS(LEVEL1);
	TheGame::Instance()->getStateMachine()->changeState(p);
}

void LevelState::s_ToLevel2()
{
	GameState *p = new PlayState();
	p->setS(LEVEL2);
	TheGame::Instance()->getStateMachine()->changeState(p);
}

void LevelState::s_ToLevel3()
{
	GameState *p = new PlayState();
	p->setS(LEVEL3);
	TheGame::Instance()->getStateMachine()->changeState(p);
}
