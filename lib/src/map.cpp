#include <SFML/Graphics.hpp>
#include <cursedtanks.h>
#include <map_func.h>
#include <iostream>

int Macro_To_Micro(sf::String *macro,
                   sf::String *micro)
{
        int x, y;
    /*    for (int i = 0; i < SIZE_MICRO_MAP_Y; i++){
                for(int j = 0; j < 4; j++){
                        micro[i][j] = METAL;
                        micro[i][SIZE_MICRO_MAP_X-1-j] = METAL;
                }
        }*/
//	micro [SIZE_MICRO_MAP_Y-1-0][5] = METAL;
//	micro [0][5] = METAL;
//std::cout << micro_tile[0];
//	micro[SIZE_MICRO_MAP_Y-1][SIZE_MICRO_MAP_X-1] =
        for (int i = 0; i < SIZE_MICRO_MAP_X; i++){
                for(int j = 0; j < 2; j++){
			micro[j][i] = METAL;
                       	micro[SIZE_MICRO_MAP_Y-(1)-j][i] = METAL;
//                	std::cout << micro [j];
		}
        }

   /*     for (int i = 4; i < SIZE_MICRO_MAP_Y-4; i++)
                for(int j = 0; j < SIZE_MICRO_MAP_X-4; j++){
                        x = j/4 - 1;
                        y = i/4 - 1;
                        switch(macro[y][x]){
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
                }*/
        return 0;
}

