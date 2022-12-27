#include "sokoban.h"
#include <string>

void edit(SDL_Surface *screen)
{
	//declaration
	SDL_Surface *manual;

	SDL_Rect p;
	SDL_Rect p_manual;
	SDL_Event event;
	bool pass;
	int is_click_left;
	int is_click_right;
	int obj_now;
	int map[N_HEIGHT][N_WIDTH] = {0}, background[N_HEIGHT][N_WIDTH] = {0};
	int i, j;

	pass = 1;
	is_click_left = 0;
	is_click_right = 0;
	obj_now = WALL;
	i = 0;
	j = 0;

	// manual
	manual = IMG_Load("src/screen/edit_instructions.png");
	p_manual.x = 0;
	p_manual.y = 0;

	// show manual
	show_manual(screen, manual, p_manual);

Initial:
	if (!load_lvl(map, background))
		exit(EXIT_FAILURE);
	while (pass)
	{
		// 等待下一事件發生
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		// clicking the closure botton
		case SDL_QUIT:
			pass = 0;
			break;

		// 按下滑鼠 (放下當前物件)
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				map[event.button.y / PEANUT_SIZE][event.button.x / PEANUT_SIZE] = obj_now;
				is_click_left = 1;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				map[event.button.y / PEANUT_SIZE][event.button.x / PEANUT_SIZE] = 0; // NONE改0
				is_click_right = 1;
			}
			break;

		// 鬆開滑鼠
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				is_click_left = 0;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				is_click_right = 0;
			break;
		case SDL_MOUSEMOTION:
			// 左鍵新增東西
			if (is_click_left)
				map[event.motion.y / PEANUT_SIZE][event.motion.x / PEANUT_SIZE] = obj_now;
			// 右鍵取消
			else if (is_click_right)
				map[event.motion.y / PEANUT_SIZE][event.motion.x / PEANUT_SIZE] = 0; 
			break;

		// 鍵盤輸入 (設定放下之地圖物件)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			// 按 esc
			case SDLK_ESCAPE:
				pass = 0;
				break;
			case SDLK_s:
				save_lvl(map, background);
				break;
			case SDLK_c:
				load_lvl(map, background);
				break;
			case SDLK_KP1:
			case SDLK_1:
				obj_now = WALL;
				break;
			case SDLK_KP2:
			case SDLK_2:
				obj_now = PEANUT;
				break;
			case SDLK_KP3:
			case SDLK_3:
				obj_now = GOAL;
				break;
			case SDLK_KP4:
			case SDLK_4:
				obj_now = ROLE;
				break;
			case SDLK_h:
				obj_now = DOG;
				break;
			default:
				break;
			}
			break;
		}

		SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 255, 255, 255));

		// 填背景
		for (i = 0; i < N_HEIGHT; i++)
		{
			for (j = 0; j < N_WIDTH; j++)
			{
				p.y = i * PEANUT_SIZE;
				p.x = j * PEANUT_SIZE;
				SDL_BlitSurface(grass, nullptr, screen, &p);
			}
		}
		
		//填入地圖物件
		for (i = 0; i < N_HEIGHT; i++)
		{
			for (j = 0; j < N_WIDTH; j++)
			{
				p.y = i * PEANUT_SIZE;
				p.x = j * PEANUT_SIZE;

				switch (map[i][j])
				{
				case WALL:
					SDL_BlitSurface(block, nullptr, screen, &p);
					break;
				case PEANUT:
					SDL_BlitSurface(peanut, nullptr, screen, &p);
					break;
				case GOAL:
					SDL_BlitSurface(goal, nullptr, screen, &p);
					break;
				case ROLE:
					SDL_BlitSurface(player1, nullptr, screen, &p);
					break;
				case DOG:
					SDL_BlitSurface(dog, nullptr, screen, &p);
					break;
				}
			}
		}
		// 刷新頁面
		SDL_Flip(screen);
	}

	SDL_FreeSurface(block);
	SDL_FreeSurface(peanut);
	SDL_FreeSurface(goal);
	SDL_FreeSurface(player1);
	SDL_FreeSurface(dog);
	SDL_FreeSurface(dogOK);
	SDL_FreeSurface(grass);
}


bool load_lvl(int lvl[][N_WIDTH], int bg[][N_WIDTH])
{

	int i;
	int j;
	// Load background
	FILE *file0;
	char inline_file0[N_WIDTH * N_HEIGHT + 1];
	i = -1;
	file0 = nullptr;
	file0 = fopen("level/bg.lvl", "r");
	if (file0 == nullptr)
		return 0;

	// 讀入背景檔案
	fgets(inline_file0, N_WIDTH * N_HEIGHT + 1, file0);
	while (++i < N_HEIGHT)
	{
		j = -1;
		while (++j < N_WIDTH)
		{
			switch (inline_file0[i * N_WIDTH + j])
			{
			case '0':
				bg[i][j] = 0;
				break;
			case '1':
				bg[i][j] = 1;
				break;
			}
		}
	}
	// close file
	fclose(file0);

	// Load MAP
	FILE *file1;
	char inline_file1[N_WIDTH * N_HEIGHT + 1];
	i = -1;
	file1 = nullptr;
	file1 = fopen("level/level.lvl", "r");
	if (file1 == nullptr)
		return 0;

	fgets(inline_file1, N_WIDTH * N_HEIGHT + 1, file1);

	while (++i < N_HEIGHT)
	{
		j = -1;
		while (++j < N_WIDTH)
		{
			switch (inline_file1[i * N_WIDTH + j])
			{
			case '0':
				lvl[i][j] = 0;
				break;
			case '1':
				lvl[i][j] = 1;
				break;
			case '2':
				lvl[i][j] = 2;
				break;
			case '3':
				lvl[i][j] = 3;
				break;
			case '4':
				lvl[i][j] = 4;
				break;
			case 'h':
				lvl[i][j] = 10;
				break;
			}
		}
	}
	fclose(file1);
	return true;
}

bool save_lvl(int lvl[][N_WIDTH], int bg[][N_WIDTH])
{
	int i;
	int j;

	FILE *file0;
	file0 = fopen("./level/bg.lvl", "w+");
	if (file0 == nullptr)
		return 0;
	i = -1;

	// 將改動寫入背景檔案
	while (++i < N_HEIGHT)
	{
		j = -1;
		while (++j < N_WIDTH)
			fprintf(file0, "%d", bg[i][j]);
	}
	fclose(file0);

	// 將改動寫入地圖檔案
	FILE *file1;
	file1 = fopen("./level/level.lvl", "w+");
	if (file1 == nullptr)
		return 0;
	i = -1;
	while (++i < N_HEIGHT)
	{
		j = -1;
		while (++j < N_WIDTH)
			if (lvl[i][j] == 10)
				fprintf(file1, "h");
			else
				fprintf(file1, "%d", lvl[i][j]);
	}
	fclose(file1);
	return true;
}
