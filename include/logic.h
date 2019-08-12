#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <string.h>
#include <IO.h>
#include <SFML/Graphics.hpp>

#define EMPTY   '0'
#define BRICK   '1'
#define TREE    '2'
#define METAL   '3'
#define WATER   '4'
#define ICE     '5'
#define BASE    '6'
#define NONE    '7'

#define MAP_SIDE 80

#define SMALL_SQUARE 4

#define SIZE_TILE 4
#define SIZE_BASE_TILE 16

#define SIZE_MICRO_TILE 	4
#define SIZE_MICRO_MAP_X 	88
#define SIZE_MICRO_MAP_Y 	88
#define SIZE_MACRO_TILE 	16
#define SIZE_MACRO_MAP_X 	20
#define SIZE_MACRO_MAP_Y 	20

#define SIZE_MAP SIZE_MICRO_MAP_X * SIZE_MICRO_MAP_Y
#define SIZE_TANK sizeof(struct tank_s)
#define SIZE_TANKS SIZE_TANK * NUM_CLIENTS 
#define SIZE_BULLET sizeof(struct bullet_s)
#define SIZE_BULLETS SIZE_BULLET * NUM_CLIENTS
#define SIZE_CLI_NUM 1

#define NUM_CLIENTS 2

enum direct_e { UP, LEFT, DOWN, RIGHT };

struct coord_s {
    int x;
    int y;
};

struct tank_s {
    struct coord_s coord;
    enum direct_e direct;
    short health;
};

struct bullet_s {
    struct coord_s coord;
    enum direct_e direct;
    char act;
};

struct info_to_server_s {
    char map[SIZE_MICRO_MAP_Y][SIZE_MICRO_MAP_X];
    struct tank_s tank;
    struct bullet_s bullet;
    char cli_num;
};

struct info_to_player_s {
    char map[SIZE_MICRO_MAP_Y][SIZE_MICRO_MAP_X];
    struct tank_s tanks[NUM_CLIENTS];
    struct bullet_s bullets[NUM_CLIENTS];
};

class object_c {

    protected:
        char active;
        enum direct_e direct;
        float speed;
    public:
        sf::Texture texture;
        sf::Sprite sprite;

        object_c() {
            active = 0;
        }

        ~object_c() {
        }

        virtual void Init(){
        }

        virtual void update() {
        }

        char Is_Active()
        {
            return active;
        }

        void Set_Active(char active_)
        {
            active = active_;
        }

        enum direct_e Get_Dir() {
            return direct;
        }

        virtual void Set_Dir(enum direct_e direct_) {
            direct = direct_;
        }

        void Set_Speed(float speed_) {
            speed = speed_;
        }

        float Get_Speed() {
            return speed;
        }

        sf::Vector2i Get_Map_Position(float x_, float y_) {
            sf::Vector2i coord_;
            coord_.x = (sprite.getPosition().x + x_) / SIZE_TILE;
            coord_.y = (sprite.getPosition().y + y_) / SIZE_TILE;
            return coord_;
        }

};

class tank_c : public object_c {

    private:
        int place;
        short health;
    public:
        tank_c()
        {
            active = 0;
        }
        tank_c(sf::String file,
                  int x,
               int y,
               short color,
               enum direct_e dir) {
            active = 1;
            direct = dir;
            texture.loadFromFile(file);
            sprite.setTexture(texture);
            place = color;
            sprite.setTextureRect(sf::IntRect((color/2)*128+dir*32, (color%2)*128, 15, 15));
            sprite.setPosition(x, y);
        }
        void Init(sf::String file,
                  int x,
               int y,
               short color,
               enum direct_e dir) {
            active = 1;
            direct = dir;
            texture.loadFromFile(file);
            sprite.setTexture(texture);
            place = color;
            sprite.setTextureRect(sf::IntRect((color/2)*128+dir*32, (color%2)*128, 15, 15));
            sprite.setPosition(x, y);
        }

        void Set_Dir(enum direct_e direct_) {
            direct = direct_;
            sprite.setTextureRect(sf::IntRect(place/2*128+direct*32, (place%2)*128, 15, 15));
        }

        short Get_Health() {
            return health;
        }

        void Set_Health(short health_) {
            health = health_;
        }

        tank_s Get_Structure(tank_s *tank) {
            tank->coord.x = sprite.getPosition().x;
            tank->coord.y = sprite.getPosition().y;
            tank->direct = direct;
            tank->health = health;
            return *tank;
        }
        
        void Set_Structure(tank_s tank)
        {
            sprite.setPosition(tank.coord.x, tank.coord.y);
            direct = tank.direct;
            health = tank.health; 
            sprite.setTextureRect(sf::IntRect(place/2*128+direct*32, (place%2)*128, 15, 15));
        }
};

class bullet_c : public object_c {
    private:
        int place;
    public:
        bullet_c()
        {
            active = 0;
        }
        bullet_c(sf::String file,
             int x,
             int y,
             enum direct_e dir) {
            active = 1;
            direct = dir;
            texture.loadFromFile(file);
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(dir*8+322, 102, 4, 4));
            sprite.setPosition(x, y);
        }

        void Init(sf::String file,
             int x,
             int y,
             enum direct_e dir) {
            active = 1;
            direct = dir;
            texture.loadFromFile(file);
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(dir*8+322, 102, 4, 4));
            sprite.setPosition(x, y);
        }

        void Set_Dir(enum direct_e direct_) {
            direct = direct_;
            sprite.setTextureRect(sf::IntRect(direct*8+322, 102, 4, 4));
        }

        bullet_s Get_Structure(bullet_s *bullet) {
            bullet->coord.x = sprite.getPosition().x;
            bullet->coord.y = sprite.getPosition().y;
            bullet->direct = direct;
            bullet->act = active;
            return *bullet;
        }
        void Set_Structure(bullet_s bullet)
        {
            sprite.setPosition(bullet.coord.x, bullet.coord.y);
            direct = bullet.direct;
            sprite.setTextureRect(sf::IntRect(direct * 8 + 322, 102, 4, 4));
            active = bullet.act;
        }

};

int Get_Map_From_Pix (short x);

int Validate_Tank (char **map,           //double-ptr to map
                   tank_c *tank);        //ptr to tank

int Validate_Bullet(char **map,         //double-ptr to map
                    bullet_c *bullets,  //ptr to bullet
                    tank_c *tanks,      //ptr to tanks
                    short num_arrays,   //all tanks
                    char number);       //number of clients

int Handling_Bullet (bullet_c *bullet,
                      float time);

void Update_Info (struct info_to_player_s *server_info,  //ptr to server info
                  struct info_to_server_s *player_info); //ptr to player info
#endif // !__LOGIC_H__
