#pragma once
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <string>

void start_screen();
void enter_names();
bool is_winner();
bool filled_board();
void display_board();
void setpos();
void update_board();
void update_board_ai();
void change_player();
void take_turn();
void game_end();
void ai_win();
void play_again();
void reset_board();
void save_to_file();
void game_ai();