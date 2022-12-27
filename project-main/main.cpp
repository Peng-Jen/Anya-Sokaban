#include "sokoban.h"

int main(int ac, char **av)
{
	//declaration
	SDL_Surface *screen;
	SDL_Surface *menu;
	SDL_Event event;
	SDL_Event chooseLvl;
	SDL_Rect p_menu;
	
	bool pass = true;

	// 初始化 SDL (INIT_EVERYTHING 可以開啟所有 SDL 的子系統)
	SDL_Init(SDL_INIT_EVERYTHING);

	// 設定在桌面顯示的圖示
	SDL_WM_SetIcon(IMG_Load("src/sprites/anya_down.jpg"), nullptr);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	// 設定在桌面顯示的檔案名
	SDL_WM_SetCaption("ANYA's Sokoban", nullptr);
	menu = IMG_Load("src/screen/menu.png");
	p_menu.x = 0;
	p_menu.y = 0;

	while (pass)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			pass = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				pass = false;
				break;
			// 進入單人遊玩
			case SDLK_KP1:
			case SDLK_1:
				play(screen);
				break;
			// 進入單人編輯
			case SDLK_2:
			case SDLK_KP2:
				edit(screen);
				break;
			// 進入雙人遊玩
			case SDLK_KP3:
			case SDLK_3:
				play_2P(screen);
				break;
			// 進入雙人編輯
			case SDLK_KP4:
			case SDLK_4:
				edit_2P(screen);
				break;
			default:
				break;
			}
			break;
		}

		// 跳回首頁
		SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(menu, nullptr, screen, &p_menu);
		SDL_Flip(screen);
	}

	SDL_FreeSurface(menu);
	SDL_Quit();

	return EXIT_SUCCESS;
}

