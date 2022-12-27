#include "sokoban.h"
void print(int[][N_WIDTH]);

// 2p mode
void play_2P(SDL_Surface *screen)
{
    // declaration
    SDL_Surface *player1[4], *player2[4];
    SDL_Surface *manual, *end_anya, *end_damian;
    SDL_Surface *player1Current, *player2Current;

    SDL_Rect p, p1, p2;
    SDL_Rect p1_J, p2_J;
    SDL_Rect p_manual, p_end_anya, p_end_damian;
    SDL_Event event;

    bool pass = true;
    bool catch_p1 = false, catch_p2 = false;
    int obj_rest_p1, obj_rest_p2;
    int i, j;
    int map[N_HEIGHT][N_WIDTH], background[N_HEIGHT][N_WIDTH] = {0};

    // 界面
    manual = IMG_Load("src/screen/play_instructions_2p.png");
    p_manual.x = 0;
    p_manual.y = 0;

    // anya 勝利畫面
    end_anya = IMG_Load("src/screen/anya_won.png");
    p_end_anya.x = 0;
    p_end_anya.y = 0;

    // damian 勝利畫面
    end_damian = IMG_Load("src/screen/damian_won.png");
    p_end_damian.x = 0;
    p_end_damian.y = 0;


    // player 1 四個面向
    player1[UP] = IMG_Load("src/sprites/anya_up.png");
    player1[DOWN] = IMG_Load("src/sprites/anya_down.png");
    player1[LEFT] = IMG_Load("src/sprites/anya_left.png");
    player1[RIGHT] = IMG_Load("src/sprites/anya_right.png");

    // player 2 四個面向
    player2[UP] = IMG_Load("src/sprites/damian_up.png");
    player2[DOWN] = IMG_Load("src/sprites/damian_down.png");
    player2[LEFT] = IMG_Load("src/sprites/damian_left.png");
    player2[RIGHT] = IMG_Load("src/sprites/damian_right.png");

    // 初始角色圖片
    player1Current = player1[DOWN];
    player2Current = player2[DOWN];

    // show manual
    show_manual(screen, manual, p_manual);

Initial:
    if (!load_lvl_2P(map, background))
        exit(EXIT_FAILURE);

    // 抓人物位置
    for (i = 0; i < N_HEIGHT; i++)
    {
        for (j = 0; j < N_WIDTH; j++)
        {
            // 清除超過一個的角色
            if ((catch_p1 == true && map[i][j] == ROLE_1) || (catch_p2 == true && map[i][j] == ROLE_2))
            {
                map[i][j] = 0;
                continue;
            }
            if (map[i][j] == ROLE_1)
            {
                p1_J.y = i;
                p1_J.x = j;
                map[i][j] = ROLE_1;
                catch_p1 = true;
            }
            else if (map[i][j] == ROLE_2)
            {
                p2_J.y = i;
                p2_J.x = j;
                map[i][j] = ROLE_2;
                catch_p2 = true;
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

            // up, down, left, right to control player 1
            case SDLK_UP:
                player1Current = player1[UP];
                move_player_2P(map, &p1_J, UP, background);
                break;
            case SDLK_DOWN:
                player1Current = player1[DOWN];
                move_player_2P(map, &p1_J, DOWN, background);
                break;
            case SDLK_RIGHT:
                player1Current = player1[RIGHT];
                move_player_2P(map, &p1_J, RIGHT, background);
                break;
            case SDLK_LEFT:
                player1Current = player1[LEFT];
                move_player_2P(map, &p1_J, LEFT, background);
                break;

            // w, s, a, d to control player 2
            case SDLK_w:
                player2Current = player2[UP];
                move_player_2P(map, &p2_J, UP, background);
                break;
            case SDLK_s:
                player2Current = player2[DOWN];
                move_player_2P(map, &p2_J, DOWN, background);
                break;
            case SDLK_d:
                player2Current = player2[RIGHT];
                move_player_2P(map, &p2_J, RIGHT, background);
                break;
            case SDLK_a:
                player2Current = player2[LEFT];
                move_player_2P(map, &p2_J, LEFT, background);
                break;
            case SDLK_r: // Reset
                goto Initial;
                break;
            default:
                break;
            }
            break;
        }

        // 168 - 225 行 -> 判斷地圖物件並繪製
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        obj_rest_p1 = 0, obj_rest_p2 = 0;

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
                case PEANUT_OK_p1:
                    SDL_BlitSurface(peanutOK1, nullptr, screen, &p);
                    break;
                case PEANUT_OK_p2:
                    SDL_BlitSurface(peanutOK2, nullptr, screen, &p);
                    break;
                case GOAL_1:
                    SDL_BlitSurface(goal1, nullptr, screen, &p);
                    obj_rest_p1 = 1;
                    break;
                case GOAL_2:
                    SDL_BlitSurface(goal2, nullptr, screen, &p);
                    obj_rest_p2 = 1;
                    break;
                case DOG:
                    SDL_BlitSurface(dog, NULL, screen, &p);
                    break;
                }
            }
        }

        // 確認未填滿之目標數量 (非零 -> 繼續遊戲, 零 -> 遊戲結束)
        if (!(obj_rest_p1 && obj_rest_p2))
        {
            pass = false;
            if (!obj_rest_p1)
                show_manual(screen, end_anya, p_end_anya);
            else
                show_manual(screen, end_damian, p_end_damian);
            sleep(1);
        }

        p1.x = p1_J.x * PEANUT_SIZE;
        p1.y = p1_J.y * PEANUT_SIZE;
        p2.x = p2_J.x * PEANUT_SIZE;
        p2.y = p2_J.y * PEANUT_SIZE;

        // 以新的位置重新繪製角色
        SDL_BlitSurface(player1Current, nullptr, screen, &p1);
        SDL_BlitSurface(player2Current, nullptr, screen, &p2);

        //?
        if (map[p1_J.y][p1_J.x] == 0)
            map[p1_J.y][p1_J.x] = ROLE_1;
        if (map[p2_J.y][p2_J.x] == 0)
            map[p2_J.y][p2_J.x] = ROLE_2;

        // 踩到狗狗結束
        if (map[p1_J.y][p1_J.x] == DOG)
        {
            pass = 0;
            show_manual(screen, end_damian, p_end_damian);
            sleep(1);
        }
        else if (map[p2_J.y][p2_J.x] == DOG)
        {
            pass = 0;
            show_manual(screen, end_anya, p_end_anya);
            sleep(1);
        }
        // 更新畫面
        SDL_Flip(screen);
    }

    // 釋放 surface
    SDL_EnableKeyRepeat(0, 0);
    SDL_FreeSurface(block);
    SDL_FreeSurface(peanut);
    SDL_FreeSurface(peanutOK1);
    SDL_FreeSurface(goal1);
    SDL_FreeSurface(peanutOK2);
    SDL_FreeSurface(goal2);

    i = -1;
    while (++i < 4)
    {
        SDL_FreeSurface(player1[i]);
        SDL_FreeSurface(player2[i]);
    }
}

void move_player_2P(int map[][N_HEIGHT], SDL_Rect *p, int way, int background[][N_WIDTH])
{
    switch (way)
    {
    case UP:
        if (p->y < 1) // 上方邊界
            break;
        if (map[p->y - 1][p->x] == WALL)
            break;
        // (上面一格是花生 || 上面一格是 p1 / p2 裝好的花生) && (上兩格超出邊界 || 上兩格是牆壁 || 上兩格是花生 || 上面二格是 p1 / p2 裝好的花生 || 上面二格是 p1 / p2)
        if ((map[p->y - 1][p->x] == PEANUT || map[p->y - 1][p->x] == PEANUT_OK_p1 || map[p->y - 1][p->x] == PEANUT_OK_p2) && (p->y - 2 < 0 || map[p->y - 2][p->x] == WALL || map[p->y - 2][p->x] == PEANUT || map[p->y - 2][p->x] == PEANUT_OK_p1 || map[p->y - 2][p->x] == PEANUT_OK_p2 || map[p->y - 2][p->x] == ROLE_1 || map[p->y - 2][p->x] == ROLE_2))
            break;
        move_peanut_2P(&map[p->y - 1][p->x], &map[p->y - 2][p->x], &background[p->y - 2][p->x]);
        p->y--;
        // 處理角色疊圖
        if (map[p->y + 1][p->x] == ROLE_1 || map[p->y + 1][p->x] == ROLE_2)
            map[p->y + 1][p->x] = 0;
        break;

    case DOWN:
        if (p->y > N_HEIGHT - 2) // 下方邊界
            break;
        if (map[p->y + 1][p->x] == WALL)
            break;
        // (下面一格是花生 || 下面一格是 p1 / p2 裝好的花生) && (下兩格超出邊界 || 下兩格是牆壁 || 下兩格是花生 || 下面二格是 p1 / p2 裝好的花生 || 下面二格是 p1 / p2)
        if ((map[p->y + 1][p->x] == PEANUT || map[p->y + 1][p->x] == PEANUT_OK_p1 || map[p->y + 1][p->x] == PEANUT_OK_p2) && (p->y + 2 >= N_HEIGHT || map[p->y + 2][p->x] == WALL || map[p->y + 2][p->x] == PEANUT || map[p->y + 2][p->x] == PEANUT_OK_p1 || map[p->y + 2][p->x] == PEANUT_OK_p2 || map[p->y + 2][p->x] == ROLE_1 || map[p->y + 2][p->x] == ROLE_2))
            break;
        move_peanut_2P(&map[p->y + 1][p->x], &map[p->y + 2][p->x], &background[p->y + 2][p->x]);
        p->y++;
        if (map[p->y - 1][p->x] == ROLE_1 || map[p->y - 1][p->x] == ROLE_2)
            map[p->y - 1][p->x] = 0;
        break;

    case LEFT:
        if (p->x < 1) // 左方邊界
            break;
        if (map[p->y][p->x - 1] == WALL)
            break;
        //  (左邊一格是花生 || 左邊一格是 p1 / p2 裝好的花生) && (左邊兩格超出邊界 || 左邊兩格是牆壁 || 左邊兩格是花生 || 左邊二格是 p1 / p2 裝好的花生 || 左邊二格是 p1 / p2)
        if ((map[p->y][p->x - 1] == PEANUT || map[p->y][p->x - 1] == PEANUT_OK_p1 || map[p->y][p->x - 1] == PEANUT_OK_p2) && (p->x - 2 < 0 || map[p->y][p->x - 2] == WALL || map[p->y][p->x - 2] == PEANUT || map[p->y][p->x - 2] == PEANUT_OK_p1 || map[p->y][p->x - 2] == PEANUT_OK_p2 || map[p->y][p->x - 2] == ROLE_1 || map[p->y][p->x - 2] == ROLE_2))
            break;
        move_peanut_2P(&map[p->y][p->x - 1], &map[p->y][p->x - 2], &background[p->y][p->x - 2]);
        p->x--;
        if (map[p->y][p->x + 1] == ROLE_1 || map[p->y][p->x + 1] == ROLE_2)
            map[p->y][p->x + 1] = 0;
        break;
    case RIGHT:
        if (p->x > N_WIDTH - 2) // 右方邊界
            break;
        if (map[p->y][p->x + 1] == WALL)
            break;
        //  (右邊一格是花生 || 右邊一格是 p1 / p2 裝好的花生) && (右邊兩格超出邊界 || 右邊兩格是牆壁 || 右邊兩格是花生 || 右邊二格是 p1 / p2 裝好的花生 || 右邊二格是 p1 / p2)
        if ((map[p->y][p->x + 1] == PEANUT || map[p->y][p->x + 1] == PEANUT_OK_p1 || map[p->y][p->x + 1] == PEANUT_OK_p2) && (p->x + 2 >= N_WIDTH || map[p->y][p->x + 2] == WALL || map[p->y][p->x + 2] == PEANUT || map[p->y][p->x + 2] == PEANUT_OK_p1 || map[p->y][p->x + 2] == PEANUT_OK_p2 || map[p->y][p->x + 2] == ROLE_1 || map[p->y][p->x + 2] == ROLE_2))
            break;
        move_peanut_2P(&map[p->y][p->x + 1], &map[p->y][p->x + 2], &background[p->y][p->x + 2]);
        p->x++;
        if (map[p->y][p->x - 1] == ROLE_1 || map[p->y][p->x - 1] == ROLE_2)
            map[p->y][p->x - 1] = 0;
        break;
    }
}

void move_peanut_2P(int *first, int *second, int *b_second)
{
    if (*first == PEANUT || *first == PEANUT_OK_p1 || *first == PEANUT_OK_p2)
    {
        if (*second == GOAL_1)
            *second = PEANUT_OK_p1;
        else if (*second == GOAL_2)
            *second = PEANUT_OK_p2;
        else if (*second == DOG)
        {
            *second = NONE;
            *b_second = DOG_OK;
        }
        else
            *second = PEANUT;

        if (*first == PEANUT_OK_p1)
            *first = GOAL_1;
        else if (*first == PEANUT_OK_p2)
            *first = GOAL_2;
        else
            *first = NONE;
    }
}

void print(int map[][N_WIDTH])
{
    for (int i = 0; i < N_HEIGHT; i++)
    {
        for (int j = 0; j < N_WIDTH; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
