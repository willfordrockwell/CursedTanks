#include <SFML/Graphics.hpp>
#include <cursedtanks.h>
#include <map_func.h>
#include <iostream>

//! 0 - empty, 1 - 5 - bricks, 6 - tree, 7-B - metal, C - water, D - ice, E - base ?
//! for ranged figure: +0 - full, +1 - up, +2 - down, +3 - left, +4 - rigth ?


int Macro_To_Micro(sf::String * macro,
                   sf::String * micro)
{
    int add_x, add_y;
    add_x = (SIZE_MICRO_MAP_X - (SIZE_MACRO_MAP_X * SIZE_TILE)) / 2;
    add_y = (SIZE_MICRO_MAP_Y - (SIZE_MACRO_MAP_Y * SIZE_TILE)) / 2;
    int x, y;
    for (int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
        for (int j = 0; j < add_x; j++) {
            micro[i][j] = NONE;
            micro[i][SIZE_MICRO_MAP_X - 1 - j] = NONE;
        }
    }

    for (int i = 0; i < SIZE_MICRO_MAP_X; i++) {
        for (int j = 0; j < add_y; j++) {
            micro[j][i] = NONE;
            micro[SIZE_MICRO_MAP_Y - 1 - j][i] = NONE;
        }
    }

    for (int i = add_y; i < SIZE_MICRO_MAP_Y - add_y; i++)
        for (int j = add_x; j < SIZE_MICRO_MAP_X - add_x; j++) {
            x = (j / SIZE_TILE) - add_x / SIZE_TILE;
            y = (i / SIZE_TILE) - add_y / SIZE_TILE;
            switch (macro[y][x]) {
            case '0':
                micro[i][j] = EMPTY;
                break;
            case '1':
                micro[i][j] = BRICK;
                break;
            case '2':
                if ((i % 4) < 1) micro[i][j] = BRICK;
                break;
            case '3':
                if ((i % 4) > 1) micro[i][j] = BRICK;
                break;
            case '4':
                if ((j % 4) < 1) micro[i][j] = BRICK;
                break;
            case '5':
                if ((j % 4) > 1) micro[i][j] = BRICK;
                break;
            case '6':
                micro[i][j] = TREE;
                break;
            case '7':
                micro[i][j] = METAL;
                break;
            case '8':
                if ((i % 4) < 1) micro[i][j] = METAL;
                break;
            case '9':
                if ((i % 4) > 1) micro[i][j] = METAL;
                break;
            case 'A':
                if ((j % 4) < 1) micro[i][j] = METAL;
                break;
            case 'B':
                if ((j % 4) > 1) micro[i][j] = METAL;
                break;
            case 'C':
                micro[i][j] = WATER;
                break;
            case 'D':
                micro[i][j] = ICE;
            case 'E':
                micro[i][j] = BASE;
                break;
            default:
                return -1;
                break;
            }
        }
    return 0;
}
