#include "sokoban.h"
#include "audio_with_SDLMixer.h"

void play(SDL_Surface *screen)
{
	//declaration
	SDL_Surface *player1[4];
	SDL_Surface *playerCurrent;
	SDL_Surface *manual, *end, *fail_end;

	SDL_Rect p;
	SDL_Rect p_J;
	SDL_Rect p_manual, p_end, p_fail;
	SDL_Event event;

	bool pass = true;
	bool catch_p1 =false;
	int obj_rest = 0;
	int i, j;
	int map[N_HEIGHT][N_WIDTH], background[N_HEIGHT][N_WIDTH] = {0};

	// 界面
	manual = IMG_Load("src/screen/play_instructions.png");
	p_manual.x = 0;
	p_manual.y = 0;

	// 勝利畫面
	end = IMG_Load("src/screen/game_won.png");
	p_end.x = 0;
	p_end.y = 0;

	// 失敗畫面
	fail_end = IMG_Load("src/screen/game_lost.png");
	p_fail.x = 0;
	p_fail.y = 0;
	
	// //地圖物件
	// block = IMG_Load("src/sprites/stone.png");
	// peanut = IMG_Load("src/sprites/peanut.png");
	// peanutOK = IMG_Load("src/sprites/full_shopping_bag.png");
	// goal = IMG_Load("src/sprites/shopping_bag.png");

	// // 洞 & 背景
	// dog = IMG_Load("src/sprites/bond_defense.png");
	// dogOK = IMG_Load("src/sprites/bond_rest.png");
	// grass = IMG_Load("src/sprites/tile.png");

	// player 1 四個面向
	player1[UP] = IMG_Load("src/sprites/anya_up.png");
	player1[DOWN] = IMG_Load("src/sprites/anya_down.png");
	player1[LEFT] = IMG_Load("src/sprites/anya_left.png");
	player1[RIGHT] = IMG_Load("src/sprites/anya_right.png");

	// 初始角色圖片
	playerCurrent = player1[DOWN];
	
	show_manual(screen, manual, p_manual);

Initial:
	if (!load_lvl(map, background))
		exit(EXIT_FAILURE);

	// 抓人物位置
	for (i = 0; i < N_HEIGHT; i++)
	{
		for (j = 0; j < N_WIDTH; j++)
		{
			// 清除超過一個的角色
			if (catch_p1 == true && map[i][j] == ROLE) 
            {
                map [i][j] = 0;
                continue;
            }
			if (map[i][j] == ROLE)
			{
				p_J.y = i;
				p_J.x = j;
				map[i][j] = NONE;
				catch_p1 = true;
			}
		}
	}

	SDL_EnableKeyRepeat(200, 50); // 鍵盤靈敏度

	while (pass)
	{
		// 等待下一事件發生
		SDL_WaitEvent(&event);

		// 抓按鍵 or 滑鼠輸入
		switch (event.type)
		{
		// clicking closure botton
		case SDL_QUIT:
			pass = 0;
			break;
		
		// 鍵盤輸入
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			// esc to break
			case SDLK_ESCAPE:
				pass = 0;
				break;

			//up, down, left, right to control player 1
			case SDLK_UP:
				playerCurrent = player1[UP];
				move_player(map, &p_J, UP, background);
				break;
			case SDLK_DOWN:
				playerCurrent = player1[DOWN];
				move_player(map, &p_J, DOWN, background);
				break;
			case SDLK_RIGHT:
				playerCurrent = player1[RIGHT];
				move_player(map, &p_J, RIGHT, background);
				break;
			case SDLK_LEFT:
				playerCurrent = player1[LEFT];
				move_player(map, &p_J, LEFT, background);
				break;
			case SDLK_r: // Reset
				goto Initial;
				break;
			default:
				break;
			}
			break;
		}

		// 134 - 182 行 -> 判斷地圖物件並繪製
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		obj_rest = 0;

		// grass & and dog OK
		for (i = 0; i < N_HEIGHT; i++)
		{
			for (j = 0; j < N_WIDTH; j++)
			{
				p.y = i * PEANUT_SIZE;
				p.x = j * PEANUT_SIZE;
				switch (background[i][j])
				{
				case GRASS:
					SDL_BlitSurface(grass, NULL, screen, &p);
					break;
				case DOG_OK:
					SDL_BlitSurface(dogOK, NULL, screen, &p);
					break;
				}
			}
		}
		
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
				case PEANUT_OK:
					SDL_BlitSurface(peanutOK, nullptr, screen, &p);
					break;
				case GOAL:
					SDL_BlitSurface(goal, nullptr, screen, &p);
					obj_rest = 1;
					break;
				case DOG:
					SDL_BlitSurface(dog, NULL, screen, &p);
					break;
				}
			}
		}

		// 確認未填滿之目標數量 (非零 -> 繼續遊戲, 零 -> 遊戲結束)
		if (!obj_rest)
		{
			pass = false;
			show_manual(screen, end, p_end);
		}
		p.x = p_J.x * PEANUT_SIZE;
		p.y = p_J.y * PEANUT_SIZE;

		// 踩到狗狗結束
		if (map[p_J.y][p_J.x] == DOG)
		{
			pass = 0;
			show_manual(screen, fail_end, p_fail);
		}

		// 以新的位置重新繪製角色
		SDL_BlitSurface(playerCurrent, nullptr, screen, &p);
		// 刷新螢幕
		SDL_Flip(screen);
	}

	// 釋放 surface
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(block);
	SDL_FreeSurface(peanut);
	SDL_FreeSurface(peanutOK);
	SDL_FreeSurface(goal);
	i = -1;
	while (++i < 4)
		SDL_FreeSurface(player1[i]);
}

void move_player(int map[][N_HEIGHT], SDL_Rect *p, int way, int background[][N_HEIGHT])
{
	switch (way)
	{
	case UP:
		if (p->y < 1)
			break;
		if (map[p->y - 1][p->x] == WALL)
			break;
		// (上面一格是花生 || 上面一格是裝好的花生) && (上兩格超出邊界 || 上兩格是牆壁 || 上兩格是花生 || 上面二格是裝好的花生)
		if ((map[p->y - 1][p->x] == PEANUT || map[p->y - 1][p->x] == PEANUT_OK) && (p->y - 2 < 0 || map[p->y - 2][p->x] == WALL || map[p->y - 2][p->x] == PEANUT || map[p->y - 2][p->x] == PEANUT_OK))
			break;
		move_peanut (&map[p->y - 1][p->x], &map[p->y - 2][p->x], &background[p->y - 2][p->x]);
		p->y--;
		break;

	case DOWN:
		if (p->y > N_HEIGHT - 2) // 邊界
			break;
		if (map[p->y + 1][p->x] == WALL)
			break;
		// (下面一格是花生 || 下面一格是裝好的花生) && (下兩格超出邊界 || 下兩格是牆壁 || 下兩格是花生 || 下面二格是裝好的花生)
		if ((map[p->y + 1][p->x] == PEANUT || map[p->y + 1][p->x] == PEANUT_OK) && (p->y + 2 >= N_HEIGHT || map[p->y + 2][p->x] == WALL || map[p->y + 2][p->x] == PEANUT || map[p->y + 2][p->x] == PEANUT_OK))
			break;
		move_peanut(&map[p->y + 1][p->x], &map[p->y + 2][p->x], &background[p->y + 2][p->x]);
		p->y++;
		break;

	case LEFT:
		if (p->x < 1)
			break;
		if (map[p->y][p->x - 1] == WALL)
			break;
		//  (左邊一格是花生 || 左邊一格是裝好的花生) && (左邊兩格超出邊界 || 左邊兩格是牆壁 || 左邊兩格是花生 || 左邊二格是裝好的花生)
		if ((map[p->y][p->x - 1] == PEANUT || map[p->y][p->x - 1] == PEANUT_OK) && (p->x - 2 < 0 || map[p->y][p->x - 2] == WALL || map[p->y][p->x - 2] == PEANUT || map[p->y][p->x - 2] == PEANUT_OK))
			break;
		move_peanut(&map[p->y][p->x - 1], &map[p->y][p->x - 2], &background[p->y][p->x - 2]);
		p->x--;
		break;

	case RIGHT:
		if (p->x > N_WIDTH - 2) // 邊界
			break;
		if (map[p->y][p->x + 1] == WALL)
			break;
		//  (右邊一格是花生 || 右邊一格是裝好的花生) && (右邊兩格超出邊界 || 右邊兩格是牆壁 || 右邊兩格是花生 || 右邊二格是裝好的花生)
		if ((map[p->y][p->x + 1] == PEANUT || map[p->y][p->x + 1] == PEANUT_OK) && (p->x + 2 >= N_WIDTH || map[p->y][p->x + 2] == WALL || map[p->y][p->x + 2] == PEANUT || map[p->y][p->x + 2] == PEANUT_OK))
			break;
		move_peanut(&map[p->y][p->x + 1], &map[p->y][p->x + 2], &background[p->y][p->x + 2]);
		p->x++;
		break;
	}
}


void move_peanut(int *first, int *second, int *b_second)
{
	if (*first == PEANUT || *first == PEANUT_OK)
	{
		if (*second == GOAL)
			*second = PEANUT_OK;
		else if (*second == DOG)
		{
			*second = NONE;
			*b_second = DOG_OK;
		}
		else
			*second = PEANUT;
		if (*first == PEANUT_OK)
			*first = GOAL;
		else
			*first = 0; 
	}
}
