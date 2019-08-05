#include <SFML/Graphics.hpp>
#include <map.h>

int Macro_To_Micro(sf::String *macro,
                   sf::String *micro)
{
        int x, y;
        for (int i = 0; i < SIZE_MICRO_MAP_Y; i++){
                for(int j = 0; j < 4; j++){
                        micro_tile[i][j] = METAL;
                        micro_tile[i][SIZE_MICRO_MAP_X-1-j] = METAL;
                }
        }

        for (int i = 0; i < SIZE_MICRO_MAP_X; i++){
                for(int j = 0; j < 4; j++){
                        micro_tile[j][i] = METAL;
                        micro_tile[SIZE_MICRO_MAP_X-1-j][i] = METAL;
                }
        }

        for (int i = 4; i < SIZE_MICRO_MAP_Y-4; i++)
                for(int j = 0; j < SIZE_MICRO_MAP_X-4; j++){
                        x = j/4 - 1;
                        y = i/4 - 1;
                        switch(macro_tile[y][x]){
                                case '0':
                                        micro_tile[i][j] = EMPTY;
                                        break;
                                case '1':
                                        micro_tile[i][j] = BRICK;
                                        break;
                                case '2':
                                        if ((i % 4) < 1) micro_tile[i][j] = BRICK;
                                        break;
                                case '3':
                                        if ((i % 4) > 1) micro_tile[i][j] = BRICK;
                                        break;
                                case '4':
                                        if ((j % 4) < 1) micro_tile[i][j] = BRICK;
                                        break;
                                case '5':
                                        if ((j % 4) > 1) micro_tile[i][j] = BRICK;
                                        break;
                                case '6':
                                        micro_tile[i][j] = TREE;
                                        break;
                                case '7':
                                        micro_tile[i][j] = METAL;
                                        break;
                                case '8':
                                        if ((i % 4) < 1) micro_tile[i][j] = METAL;
                                        break;
                                case '9':
                                        if ((i % 4) > 1) micro_tile[i][j] = METAL;
                                        break;
                                case 'A':
                                        if ((j % 4) < 1) micro_tile[i][j] = METAL;
                                        break;
                                case 'B':
                                        if ((j % 4) > 1) micro_tile[i][j] = METAL;
                                        break;
                                case 'C':
                                        micro_tile[i][j] = WATER;
                                        break;
                                case 'D':
                                        micro_tile[i][j] = ICE;
                                case 'E':
                                        micro_tile[i][j] = BASE;
                                        break;
                                default:
                                        return -1;
                                        break;
                        }
                }
        return 0;
}

