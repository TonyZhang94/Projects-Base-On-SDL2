#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <string>
#include <iostream>
using namespace std;

//定义window窗口的长宽高
const int SCREEN_WIDTH  = 600;
const int SCREEN_HEIGHT = 500;

char *WDAY[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

SDL_Window	 *window	= nullptr;//窗口
SDL_Renderer *renderer	= nullptr;//渲染器
SDL_Texture  *watch		= nullptr;//时钟表盘
SDL_Texture	 *date		= nullptr;//星期日期
SDL_Texture  *hour		= nullptr;//时针
SDL_Texture  *minute	= nullptr;//分针
SDL_Texture  *second	= nullptr;//秒针
 
//加载png图片
SDL_Texture* LoadImage(SDL_Renderer *renderer,char *file) {
	SDL_Texture *tex = nullptr;
	tex = IMG_LoadTexture(renderer,file);
	if (tex == nullptr)
        throw runtime_error("Failed to load image." + string(file) + IMG_GetError());

	return tex;
}

//显示图片在window窗口中
void ApplySurface(int x,int y,SDL_Texture *tex,SDL_Renderer *rend) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_QueryTexture(tex,NULL,NULL,&pos.w,&pos.h);
 
    SDL_RenderCopy(rend,tex,NULL,&pos);
}

//显示图片
void Display() {
	ApplySurface(0,0,watch,renderer);
	//ApplySurface(0,0,date,renderer);
	ApplySurface(0,0,hour,renderer);
	ApplySurface(0,0,minute,renderer);
	ApplySurface(0,0,second,renderer);
}

//将string字符串转换成SDL_Texture*
SDL_Texture* Transform(string wday_mday_str) {
    TTF_Font *font  = nullptr;//字体
	SDL_Color color = {0, 0, 0};//颜色
	int size        = 128;//字体大小

    font = TTF_OpenFont("simfang.ttf",size);
    if (font == nullptr)
        throw std::runtime_error("Failed to load font: " + string("simfang.ttf") + TTF_GetError());
	
	// Display();
    SDL_Surface *surf	 = TTF_RenderText_Blended(font,wday_mday_str.c_str(),color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_FreeSurface(surf);

	// Display();
	ApplySurface(0,0,texture,renderer);
    TTF_CloseFont(font);
    
	return texture;
}

void ShowTime(int &t_wday,int &t_mday,int &t_hour,int &t_minute,int &t_second) {
	SDL_Point point = {300,250};//时分秒针的位置
	//星期日期的位置及图片大小
	int pic_x     = 350;
	int pic_y	  = 230;
	int pic_width = 80;
	int pic_hight = pic_width / 2;
	SDL_Rect pos  = {pic_x,pic_y,pic_width,pic_hight};
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	//计算当前时间的时分秒针角度
	double rad_hour   = 30 * (t_hour + t_minute / 60.0 + t_second / 3600.0);
	double rad_minute = 6 * (t_minute + t_second / 60.0);
	double rad_second = 6 * t_second;

	//每秒改变一次时钟状态
	while (true) {
		//计算每秒时分秒针改变的角度
		rad_hour   += 0.1/60;
		rad_minute += 0.1;
		rad_second += 6;
		t_second++;

		//秒针每转一圈，秒针从零开始，分针+1
		if (t_second == 60) {
			rad_second = 0.0;
			t_second   = 0;
			t_minute++;

			//分针每转一圈，分针从零开始，时针+1
			if (t_minute == 60) {
				rad_minute = 0.0;
				t_minute   = 0;
				t_hour++;

				//时针每转两圈，时针从零开始，星期+1，日期+1
				if (rad_hour == 24.0) {
					rad_hour = 0.0;
					t_hour   = 0;
					t_wday = (t_wday + 1) % 7;
					t_mday = (t_mday + 1) % 31;
				}
			}
		}

		//将星期和日期转换成SDL_Texture*
		try {
			char str[10];
			itoa(t_mday, str, 10);

			date = Transform(WDAY[t_wday] + string(" ") + string(str));
		}
		catch (const std::runtime_error &e) {
			std::cout << e.what() << std::endl;
		}

		//显示时钟
		SDL_RenderClear(renderer);//清空渲染器
		SDL_RenderCopy(renderer,watch,NULL,NULL);//背景图片显示
		SDL_RenderCopy(renderer,date,NULL,&pos);//星期日期显示
		SDL_RenderCopyEx(renderer,hour, NULL,NULL,rad_hour,&point,flip);//时针
		SDL_RenderCopyEx(renderer,minute, NULL,NULL,rad_minute,&point,flip);//分针
		SDL_RenderCopyEx(renderer,second, NULL,NULL,rad_second,&point,flip);//秒针
		SDL_RenderPresent(renderer);

		SDL_Delay(1000);//每隔一秒执行一次
	}
}

void Initialize(int &t_wday,int &t_mday,int &t_hour,int &t_minute,int &t_second) {
	//获取系统时间，并转换成tm格式
	struct tm *p_time;
	time_t now_time;

	now_time = time(NULL);
	p_time	 = localtime(&now_time);
	
	t_wday	 = p_time->tm_wday;
	t_mday	 = p_time->tm_mday;
	t_hour	 = p_time->tm_hour;
	t_minute = p_time->tm_min;
	t_second = p_time->tm_sec;

	//调用显示函数
	ShowTime(t_wday,t_mday,t_hour,t_minute,t_second);
}

int main(int argc, char* argv[]) {
	//初始化
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout << SDL_GetError() << std::endl;
		return 1;
	}

	//创建窗口
	window = SDL_CreateWindow("Watch5083",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << SDL_GetError() << std::endl;
		return 2;
	}

	//创建渲染器
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cout << SDL_GetError() << std::endl;
		return 3;
	}

	if (TTF_Init() == -1)//初始化字体库
	{
		std::cout << TTF_GetError() << std::endl;
		return 4;
	}

	SDL_RenderClear(renderer);//清空渲染器

	//加载图片
	watch  = LoadImage(renderer,"../watch.png");
//	date   = LoadImage(renderer,"../date.png");
	hour   = LoadImage(renderer,"../hour.png");
	minute = LoadImage(renderer,"../minute.png");
	second = LoadImage(renderer,"../second.png");
	
	//显示初始状态
	//Display();

	int t_wday;
	int t_mday;
	int t_hour;
	int t_minute;
	int t_second;

	Initialize(t_wday,t_mday,t_hour,t_minute,t_second);
	
	SDL_DestroyTexture(watch);
//	SDL_DestroyTexture(date);
	SDL_DestroyTexture(hour);
	SDL_DestroyTexture(minute);
	SDL_DestroyTexture(second);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}