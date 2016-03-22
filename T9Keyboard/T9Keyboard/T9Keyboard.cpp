#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

//���ڵ�����
#define WINDOW_X		100
#define WINDOW_Y		100
//���ڵĴ�С
#define WINDOW_WIDTH	300
#define WINDOW_HEIGHT	400
//�����ĸ߶�
#define SCREEN_HEIGHT	100
//���̹���Ĵ�С
#define KEY_UNIT_X		100
#define KEY_UNIT_Y		100
//���̵Ĵ�С
#define KEY_ROW			3
#define KEY_COLUMN		3
//�����ʾ���ַ���
#define MAX_BUFF		12
//���޸���������ʱ����
#define CLICK_INTERVAL	30
//����
#define FONT_STYLE		"simfang.ttf"

//���壬��Ⱦ�������̣��ַ��������֣���ɫ�ȱ�������
SDL_Window   *window    = nullptr;
SDL_Renderer *renderer  = nullptr;
SDL_Texture  *keyboard  = nullptr;
SDL_Texture	 *character = nullptr;
SDL_Surface	 *letter    = NULL;
SDL_Color	  color		= {255,255,255};

//�ַ�����ر������弰��ʼ��
int  buff_cnt = 0;
char buff[MAX_BUFF];
char keychar[][5]	 = {{'.','_','@','/','#'},
						{'a','b','c'},
						{'d','e','f'},
						{'g','h','i'},
						{'j','k','l'},
						{'m','n','o'},
						{'p','q','r','s'},
						{'t','u','v'},
						{'w','x','y','z'}};

//����pngͼƬ
SDL_Texture* LoadImage(SDL_Renderer *renderer,char *file) {
	SDL_Texture *tex = nullptr;

	//����ͼƬ
	tex = IMG_LoadTexture(renderer,file);
	if (tex == nullptr)
        throw runtime_error("Failed to load image." + string(file) + IMG_GetError());

	return tex;
}

//��������
SDL_Surface *Load_ttfText(char *filename,int size,const char *text,SDL_Color color)
{
	TTF_Font *font;
	SDL_Surface *ptext;

	//�������
	font = TTF_OpenFont(filename,20);
	if (font == NULL) {
		printf ("TTF_OpenFont fail:%s",SDL_GetError());
	}

	//��������
	ptext = TTF_RenderText_Solid(font,text,color);
	if (ptext == NULL) {
		printf ("TTF_RenderText_Solid fail:%s",SDL_GetError());
	}

	//�ر������
    TTF_CloseFont(font);

	return ptext;
}

//���ܺ������ж���ֵ�Ƿ�����������
bool IsInInterval(double lower,double upper,double pos) {
	if (pos > lower && pos < upper) {
		return true;
	}
	else {
		return false;
	}
}

//�жϵ���¼�������λ��
int ClickPos() {
	//����ͷ
	int x_upper,x_lower;
	//����β
	int y_upper,y_lower;

	SDL_Event event;
	
	if (SDL_PollEvent (&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				//��ȡ���λ��
				int x = event.button.x;
				int y = event.button.y-SCREEN_HEIGHT;

				//i�У�j��
				for (int i = 0;i < KEY_ROW;i++) {
					for (int j = 0;j < KEY_COLUMN;j++) {
						x_lower = KEY_UNIT_X * j;
						x_upper = KEY_UNIT_X + x_lower;
						y_lower = KEY_UNIT_Y * i;
						y_upper = KEY_UNIT_Y + y_lower;

						//�жϵ��λ���Ƿ�����i*3+j�Ź�����
						if (IsInInterval(x_lower,x_upper,x) && IsInInterval(y_lower,y_upper,y)) {
							return i*3+j;
						}
					}
				}
			}
		}
	}

	return -1;
}

//����ʾ�ַ���������ʱ�������ַ�����
void LeftShift(char *buff,char ch) {
	for (int i = 0;i < MAX_BUFF-1;i++) {
		buff[i] = buff[i+1];
	}
	buff[MAX_BUFF-1] = ch;
}

//��ʾ���µ�buff
void Display(SDL_Renderer *renderer,SDL_Texture *keyboard,SDL_Texture *character,SDL_Surface *letter,SDL_Color color,char *buff,int buff_cnt) {
	letter = Load_ttfText(FONT_STYLE, 60, buff, color);
	character = SDL_CreateTextureFromSurface(renderer, letter);
	SDL_RenderClear(renderer);

	//�����º��character���ص���Ⱦ����
	SDL_Rect  rect_character   = {20,30,20*(buff_cnt+1),60};
	SDL_Point center_character = {0,0};
	SDL_RenderCopyEx(renderer,character,NULL,&rect_character,0,&center_character,SDL_FLIP_NONE);

	//�����º��keyboard���ص���Ⱦ����
	SDL_Rect  rect_keyboard   = {0,100,WINDOW_WIDTH,WINDOW_HEIGHT-SCREEN_HEIGHT};
	SDL_Point center_keyboard = {0,0};
	SDL_RenderCopyEx(renderer,keyboard,NULL,&rect_keyboard,0,&center_keyboard,SDL_FLIP_NONE);

	//չʾ��Ⱦ��
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	//��ʼ��
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout << SDL_GetError() << endl;
		return 1;
	}

	//��������
	window = SDL_CreateWindow("T9KeyBoard",WINDOW_X,WINDOW_Y,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << SDL_GetError() << endl;
		return 2;
	}

	//������Ⱦ��
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cout << SDL_GetError() << endl;
		return 3;
	}

	//��ʼ�������
	if (TTF_Init() == -1) {
		cout << TTF_GetError() << endl;
		return 4;
	}

	//�����Ⱦ��
	SDL_RenderClear(renderer);

	//����ͼƬ
	keyboard = LoadImage(renderer,"../T9keyboard.png");

	//��keyboard���ص���Ⱦ����
	SDL_Rect  rect   = {0,100,WINDOW_WIDTH,WINDOW_HEIGHT-SCREEN_HEIGHT};
	SDL_Point center = {0,0};
	SDL_RenderCopyEx(renderer,keyboard,NULL,&rect,0,&center,SDL_FLIP_NONE);
	
	//չʾ��Ⱦ��
	SDL_RenderPresent(renderer);

	while(true) {
		//��ʱ��
		int timer		= 0;
		//��ʾ�ù���ĵڼ����ַ�
		int sub_pos		= 0;
		//�Ƿ��Ѿ���ʾ����Ļ��
		int has_record	= 0;

		//��ȡ����Ĺ����
		int pos = ClickPos();
		
		for (int i = 0;i < KEY_ROW*KEY_COLUMN;i++) {
			//�ҵ��ù���
			if (i == pos) {
				while (true) {
					timer++;

					//������ʱ
					SDL_Delay(CLICK_INTERVAL);
					if (ClickPos() == pos) {
						timer = 0;

						sub_pos++;
						
						//��ε��ͬһ�������ַ�ѭ��
						if (pos == 0) {
							sub_pos %= 5;
						}
						else if (pos == 6 || pos == 8) {
							sub_pos %= 4;
						}
						else {
							sub_pos %= 3;
						}
					}

					//�������ʱ�������Զ�ȷ�������ַ�
					if (timer >= CLICK_INTERVAL) {
						break;
					}

					//�ж���ʾ�ַ������������Լ��Ƿ���ʾ����Ļ��
					if (buff_cnt < MAX_BUFF || has_record == 1) {
						buff[buff_cnt] = keychar[pos][sub_pos];
						
					}
					else {
						has_record = 1;
						LeftShift(buff,keychar[pos][sub_pos]);
					}

					//չʾ������������ַ���
					Display(renderer,keyboard,character,letter,color,buff,buff_cnt);
				}

				//�ַ�������һ�����Ѵﵽ����������
				if (buff_cnt < MAX_BUFF) {
					buff_cnt++;
				}
			}
		}
	}

	//�ͷ�
	SDL_DestroyTexture(keyboard);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();

	return 0;
}