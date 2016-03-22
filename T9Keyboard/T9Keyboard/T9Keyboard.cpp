#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

//窗口的坐标
#define WINDOW_X		100
#define WINDOW_Y		100
//窗口的大小
#define WINDOW_WIDTH	300
#define WINDOW_HEIGHT	400
//输出框的高度
#define SCREEN_HEIGHT	100
//键盘宫格的大小
#define KEY_UNIT_X		100
#define KEY_UNIT_Y		100
//键盘的大小
#define KEY_ROW			3
#define KEY_COLUMN		3
//最多显示的字符数
#define MAX_BUFF		12
//可修改输入的最大时间间隔
#define CLICK_INTERVAL	30
//字体
#define FONT_STYLE		"simfang.ttf"

//窗体，渲染器，键盘，字符串，文字，颜色等变量定义
SDL_Window   *window    = nullptr;
SDL_Renderer *renderer  = nullptr;
SDL_Texture  *keyboard  = nullptr;
SDL_Texture	 *character = nullptr;
SDL_Surface	 *letter    = NULL;
SDL_Color	  color		= {255,255,255};

//字符串相关变量定义及初始化
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

//加载png图片
SDL_Texture* LoadImage(SDL_Renderer *renderer,char *file) {
	SDL_Texture *tex = nullptr;

	//加载图片
	tex = IMG_LoadTexture(renderer,file);
	if (tex == nullptr)
        throw runtime_error("Failed to load image." + string(file) + IMG_GetError());

	return tex;
}

//加载字体
SDL_Surface *Load_ttfText(char *filename,int size,const char *text,SDL_Color color)
{
	TTF_Font *font;
	SDL_Surface *ptext;

	//打开字体库
	font = TTF_OpenFont(filename,20);
	if (font == NULL) {
		printf ("TTF_OpenFont fail:%s",SDL_GetError());
	}

	//创建文字
	ptext = TTF_RenderText_Solid(font,text,color);
	if (ptext == NULL) {
		printf ("TTF_RenderText_Solid fail:%s",SDL_GetError());
	}

	//关闭字体库
    TTF_CloseFont(font);

	return ptext;
}

//功能函数：判断数值是否落入区间内
bool IsInInterval(double lower,double upper,double pos) {
	if (pos > lower && pos < upper) {
		return true;
	}
	else {
		return false;
	}
}

//判断点击事件发生的位置
int ClickPos() {
	//区间头
	int x_upper,x_lower;
	//区间尾
	int y_upper,y_lower;

	SDL_Event event;
	
	if (SDL_PollEvent (&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				//获取点击位置
				int x = event.button.x;
				int y = event.button.y-SCREEN_HEIGHT;

				//i行，j列
				for (int i = 0;i < KEY_ROW;i++) {
					for (int j = 0;j < KEY_COLUMN;j++) {
						x_lower = KEY_UNIT_X * j;
						x_upper = KEY_UNIT_X + x_lower;
						y_lower = KEY_UNIT_Y * i;
						y_upper = KEY_UNIT_Y + y_lower;

						//判断点击位置是否落入i*3+j号宫格内
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

//当显示字符到达上限时，所有字符左移
void LeftShift(char *buff,char ch) {
	for (int i = 0;i < MAX_BUFF-1;i++) {
		buff[i] = buff[i+1];
	}
	buff[MAX_BUFF-1] = ch;
}

//显示最新的buff
void Display(SDL_Renderer *renderer,SDL_Texture *keyboard,SDL_Texture *character,SDL_Surface *letter,SDL_Color color,char *buff,int buff_cnt) {
	letter = Load_ttfText(FONT_STYLE, 60, buff, color);
	character = SDL_CreateTextureFromSurface(renderer, letter);
	SDL_RenderClear(renderer);

	//将更新后的character加载到渲染器上
	SDL_Rect  rect_character   = {20,30,20*(buff_cnt+1),60};
	SDL_Point center_character = {0,0};
	SDL_RenderCopyEx(renderer,character,NULL,&rect_character,0,&center_character,SDL_FLIP_NONE);

	//将更新后的keyboard加载到渲染器上
	SDL_Rect  rect_keyboard   = {0,100,WINDOW_WIDTH,WINDOW_HEIGHT-SCREEN_HEIGHT};
	SDL_Point center_keyboard = {0,0};
	SDL_RenderCopyEx(renderer,keyboard,NULL,&rect_keyboard,0,&center_keyboard,SDL_FLIP_NONE);

	//展示渲染器
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	//初始化
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout << SDL_GetError() << endl;
		return 1;
	}

	//创建窗口
	window = SDL_CreateWindow("T9KeyBoard",WINDOW_X,WINDOW_Y,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << SDL_GetError() << endl;
		return 2;
	}

	//创建渲染器
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cout << SDL_GetError() << endl;
		return 3;
	}

	//初始化字体库
	if (TTF_Init() == -1) {
		cout << TTF_GetError() << endl;
		return 4;
	}

	//清空渲染器
	SDL_RenderClear(renderer);

	//加载图片
	keyboard = LoadImage(renderer,"../T9keyboard.png");

	//将keyboard加载到渲染器上
	SDL_Rect  rect   = {0,100,WINDOW_WIDTH,WINDOW_HEIGHT-SCREEN_HEIGHT};
	SDL_Point center = {0,0};
	SDL_RenderCopyEx(renderer,keyboard,NULL,&rect,0,&center,SDL_FLIP_NONE);
	
	//展示渲染器
	SDL_RenderPresent(renderer);

	while(true) {
		//计时器
		int timer		= 0;
		//表示该宫格的第几个字符
		int sub_pos		= 0;
		//是否已经显示在屏幕上
		int has_record	= 0;

		//获取点击的宫格号
		int pos = ClickPos();
		
		for (int i = 0;i < KEY_ROW*KEY_COLUMN;i++) {
			//找到该宫格
			if (i == pos) {
				while (true) {
					timer++;

					//设置延时
					SDL_Delay(CLICK_INTERVAL);
					if (ClickPos() == pos) {
						timer = 0;

						sub_pos++;
						
						//多次点击同一个宫格，字符循环
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

					//超过最大时间间隔，自动确定输入字符
					if (timer >= CLICK_INTERVAL) {
						break;
					}

					//判断显示字符数到达上限以及是否显示在屏幕上
					if (buff_cnt < MAX_BUFF || has_record == 1) {
						buff[buff_cnt] = keychar[pos][sub_pos];
						
					}
					else {
						has_record = 1;
						LeftShift(buff,keychar[pos][sub_pos]);
					}

					//展示最新已输入的字符串
					Display(renderer,keyboard,character,letter,color,buff,buff_cnt);
				}

				//字符数增加一，如已达到上限则不增加
				if (buff_cnt < MAX_BUFF) {
					buff_cnt++;
				}
			}
		}
	}

	//释放
	SDL_DestroyTexture(keyboard);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();

	return 0;
}