#ifndef __CURSED_TANKS_H__
#define __CURSED_TANKS_H__

#include <IO.h>
#include <logic.h>
#include <map_func.h>
#include <SFML/Graphics.hpp>

class object_c {

	public:
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
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			place = color;
			sprite.setTextureRect(sf::IntRect((color/2)*128+dir*32, (color%2)*128, 16, 16));
			sprite.setPosition(x, y);
		}

		enum direct_e Get_Dir() {
			return direct;
		}

		void Set_Dir(enum direct_e direct_) {
			direct = direct_;
			sprite.setTextureRect(sf::IntRect(place/2*128+direct*32, (place%2)*128, 16, 16));
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
			texture.loadFromFile(file);
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

void Read_Keyboard (tank_c *tank,
                    float time);

#endif //__CURSED_TANKS_H__
