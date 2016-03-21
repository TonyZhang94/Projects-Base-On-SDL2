#include "Game.h"
#include "utility.h"
#include "Vector2D.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{

	Uint32 frameStart, frameTime;
	

	cout << "game init attempt...\n";
	if(TheGame::Instance()->init("Chapter 1", 100, 50, WINDOW_WIDTH, WINDOW_HEIGHT,
		false))
	{
		cout << "game init success!\n";
		while(TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;
			if(frameTime< DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}
	cout << "game closing...\n";
	TheGame::Instance()->clean();
	return 0;
}