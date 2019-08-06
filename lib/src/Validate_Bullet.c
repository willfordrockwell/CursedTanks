#include "../include/logic.h"

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet *bullet, //ptr to bullet
                     struct tank *tanks)    //all tanks
{
    int x_bullet = Get_Map_From_Pix(bullet->coord.x);
    int y_bullet = Get_Map_From_Pix(bullet->coord.y);
    
    	//check tanks;
	switch(bullet->direct)
	case: UP
		for(int i; i<4; i++)
			if(x_bullet==Get_Map_From_Pix(tanks->coord.x+4*i)&&y_bullet==Get_Map_From_Pix(tanks->coord.y+12)){
				bullet->coord.x = -16;
				bullet->coord.y = -16;
				tanks->health--;
				return 2;
			}			
		break;
	case: RIGHT
		for(int i; i<4; i++)
			if(x_bullet==Get_Map_From_Pix(tanks->coord.x)&&y_bullet==Get_Map_From_Pix(tanks->coord.y+4*i)){
				bullet->coord.x = -16;
				bullet->coord.y = -16;
				tanks->health--;
				return 2;
			}			
		break;
	case: LEFT
		for(int i; i<4; i++)
			if(x_bullet==Get_Map_From_Pix(tanks->coord.x+12)&&y_bullet==Get_Map_From_Pix(tanks->coord.y+4*i)){
				bullet->coord.x = -16;
				bullet->coord.y = -16;
				tanks->health--;
				return 2;
			}			
		break;
	case: DOWN
		for(int i; i<4; i++)
			if(x_bullet==Get_Map_From_Pix(tanks->coord.x+4*i)&&y_bullet==Get_Map_From_Pix(tanks->coord.y)){
				bullet->coord.x = -16;
				bullet->coord.y = -16;
				tanks->health--;
				return 2;
			}			
		break;
    

    switch(map[x_bullet][y_bullet])
    {
    case EMPTY:
    case WATER:
    case TREE:
    case ICE:
        return 0;
    case BRICK:
        map[x_bullet][y_bullet] = EMPTY;
    case METAL:
        bullet->coord.x = -16;
        bullet->coord.y = -16;
        return 0;
    default:
        return 1;
    }
}
