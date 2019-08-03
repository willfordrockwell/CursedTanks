#include "../include/logic.h"

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet *bullet, //ptr to bullet
                     struct tank *tanks     //all tanks
)
{
    int x_bullet = Get_Map_From_Pix(bullet->coord.x);
    int y_bullet = Get_Map_From_Pix(bullet->coord.y);

    //if material non-blocking as empty, tree, ice, continue fly

  switch(map[x_bullet][y_bullet])
    case: EMPTY
        return 0;
        break;
    case: TREE
        return 0;
        break;
    case: ICE
        return 0;
        break;   
    case: ROCK
        bullet->coord.x=-1;
        bullet->coord.y=-1;
        map[x_bullet][y_bullet]=EMPTY;
        return 1;
        break;
    case:  METAL
        bullet->coord.x=-1;
        bullet->coord.y=-1;
        return 1;
        break;
    case: BASE//Ne pomny cto eto
        return 0;
        break;
    default:
        if(Get_Map_From_Pix(bullet->coord.x)==Get_Map_From_Pix(tanks->coord.x)&&Get_Map_From_Pix(bullet->coord.y)==Get_Map_From_Pix(tanks->coord.y)){
          bullet->coord.x=-1;
          bullet->coord.y=-1;
          tanks->health=tanks->health-1;
          return 1;
        }
  
    //remove after writing func
    //if material blocking as metal, "kill" bullet (set coord -1 -1)
    //if material destructable as rock, set EMPTY
    //check tanks, does one of them should be killed?
}
