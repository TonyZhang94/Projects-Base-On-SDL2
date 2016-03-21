#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include "utility.h"

class TextureManager
{
public:
	bool load(string fileName, string id, SDL_Renderer* pRenderer);
	void draw(string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(string id, int x, int y, int width, int height, 
		int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static TextureManager* Instance();
	void clearFromTextureMap(string id);
private:
	TextureManager() {}
	
private:
	static TextureManager* s_pInstance;
	map<string, SDL_Texture*> m_textureMap;
};
typedef TextureManager TheTextureManager;

#endif