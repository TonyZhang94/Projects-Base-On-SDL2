#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "BackGround.h"
#include "InputHandler.h"
#include "LevelState.h"

const string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	TheInputHandler::Instance()->reset();

	if(!TheTextureManager::Instance()->load("setting/f.png", 
		"first", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("setting/play.png",
		"playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("setting/exit.png",
		"exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(100, 225, 250,
		63, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 375, 250,
		63, "exitbutton"), s_exitFromMenu);
	GameObject* back = new BackGround(new LoaderParams(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "first"));

	m_gameObjects.push_back(back);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("first");    //my add
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
	cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new LevelState());
}

void MenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}