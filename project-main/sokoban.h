#ifndef SOKOBAN_H
#define SOKOBAN_H

// #include <windows.h>
#include <unistd.h>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
const int PEANUT_SIZE = 50;
const int N_WIDTH = 15;
const int N_HEIGHT = 15;
const int WIDTH = PEANUT_SIZE * N_WIDTH;
const int HEIGHT = PEANUT_SIZE * N_HEIGHT;

// all pictures
extern SDL_Surface *block;
extern SDL_Surface *peanut;
extern SDL_Surface *peanutOK, *peanutOK1, *peanutOK2;
extern SDL_Surface *goal, *goal1, *goal2;
extern SDL_Surface *dog, *dogOK, *grass;
extern SDL_Surface *player1, *player2;

// background
#define GRASS 0
#define DOG_OK 1

// direction
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// objects
#define NONE 0
#define WALL 1
#define PEANUT 2
#define GOAL 3
#define ROLE 4
#define PEANUT_OK 5
#define DOG 10

// 2P
#define GOAL_1 3
#define ROLE_1 4
#define GOAL_2 6 
#define ROLE_2 7 
#define PEANUT_OK_p1 8
#define PEANUT_OK_p2 9


void edit(SDL_Surface *screen);
void play(SDL_Surface *screen);
void move_player(int map[][N_HEIGHT], SDL_Rect *p, int way);
void move_player(int map[][N_HEIGHT], SDL_Rect *p, int way, int background[][N_HEIGHT]);
bool save_lvl(int lvl[][N_WIDTH]);
bool load_lvl(int lvl[][N_WIDTH]);
void move_peanut(int *first, int *second);
void move_peanut(int *first, int *second, int* b_second);

// load & save
bool load_lvl(int lvl[][N_WIDTH], int bg[][N_WIDTH]);
bool save_lvl(int lvl[][N_WIDTH], int bg[][N_WIDTH]);

void edit_2P(SDL_Surface *screen);
void play_2P(SDL_Surface *screen);
void move_player_2P(int map[][N_HEIGHT], SDL_Rect *p, int way, int background[][N_HEIGHT]);
bool save_lvl_2P(int lvl[][N_WIDTH], int bg[][N_WIDTH]);
bool load_lvl_2P(int lvl[][N_WIDTH], int bg[][N_WIDTH]);
void move_peanut_2P(int *first, int *second, int *b_second);

void playFix(SDL_Surface *screen, int level = 1);
bool load_fix_lvl(int lvl[][N_WIDTH], int level);

void show_manual(SDL_Surface *screen, SDL_Surface *manual, SDL_Rect& p_manual);
#endif
