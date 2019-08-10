#ifndef __LOGIC_H__
#define __LOGIC_H__

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

#include <SFML/Graphics.hpp>

enum direct_e { UP, LEFT, DOWN, RIGHT };

struct coord_s {
    short x;
    short y;
};

struct tank_s {
    struct coord_s coord;
    enum direct_e direct;
    short health;
};

struct bullet_s {
    struct coord_s coord;
    enum direct_e direct;
};

class object_c {

	public:
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		object_c() {
		}
		~object_c() {
		}
		virtual void update() {
		}
};

class tank_c : public object_c {

	private:
		int place;
		float speed = 0;
		enum direct_e direct;
		short health;
	public:
		tank_c(sf::String file,
	   	       int x,
		       int y,
		       short color,
		       enum direct_e dir) {
			direct = dir;
			//sf::Image image;
			image.loadFromFile(file);
			image.createMaskFromColor(sf::Color(0,0,0,255), 0);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			place = color;
//			sprite.setTextureRect(sf::IntRect((color/2)*128+dir*32, (color%2)*128, 15, 15));
			sprite.setPosition(x, y);
		}

		enum direct_e Get_Dir() {
			return direct;
		}

		void Set_Dir(enum direct_e direct_) {
			direct = direct_;
			sprite.setTextureRect(sf::IntRect(place/2*128+direct*32, (place%2)*128, 15, 15));
		}

		sf::Vector2i Get_Map_Position(float x_, float y_) {
			sf::Vector2i coord_;
			coord_.x = (sprite.getPosition().x + x_) / SIZE_TILE;
			coord_.y = (sprite.getPosition().y + y_) / SIZE_TILE;
			return coord_;
		}

		void Set_Speed(float speed_) {
			speed = speed_;
		}

		float Get_Speed() {
			return speed;
		}

		short Get_Health() {
			return health;
		}

		void Set_Health(short health_) {
			health = health_;
		}

		tank_s Get_Structure() {
			tank_s tank;
			tank.coord.x = sprite.getPosition().x;
			tank.coord.y = sprite.getPosition().y;
			tank.direct = direct;
			tank.health = health;
			return tank;
		}
};

class bullet_c : public object_c {
	private:
		int place;
		float speed = 0;
		enum direct_e direct;
	public:
		bullet_c(sf::String file,
		     int x,
		     int y,
		     enum direct_e dir) {
			direct = dir;
			//sf::Image image;
			image.loadFromFile(file);
			image.createMaskFromColor(sf::Color(0,0,0,255), 0);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(dir*8+320, 100, 8, 8));
			sprite.setPosition(x, y + 4);
		}

		enum direct_e Get_Dir() {
            return direct;
        }

        void Set_Dir(enum direct_e direct_) {
            direct = direct_;
            sprite.setTextureRect(sf::IntRect(direct*8+320, 100, 8, 8));
        }

        struct coord_s Get_Map_Position() {
            struct coord_s coord_;
            coord_.x = sprite.getPosition().x/SIZE_TILE;
            coord_.y = sprite.getPosition().y/SIZE_TILE;
            return coord_;
        }

        void Set_Speed(float speed_) {
            speed = speed_;
        }

        float Get_Speed() {
            return speed;
        }

        bullet_s Get_Structure() {
            bullet_s bullet;
            bullet.coord.x = sprite.getPosition().x;
            bullet.coord.y = sprite.getPosition().y;
            bullet.direct = direct;
            return bullet;
        }


};


int Get_Map_From_Pix (short x);

int Validate_Tank (char **map,                  //double-ptr to map
                   tank_c *tank);        //ptr to tank

int Validate_Bullet (char **map,                //double-ptr to map
                     bullet_c *bullet,   //ptr to bullet
                     tank_c *tanks);     //all tanks

#endif // !__LOGIC_H__
