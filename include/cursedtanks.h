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
		object_c()
		{
		}
		virtual void update()
		{
		}
};

class tank_c : public object_c {
	private:
		tank_s tank_;
		int place;
	public:
		tank_c(sf::String file,
	   	       int x,
		       int y,
		       short color,
		       enum direct_e dir)
		{
			tank_.coord.x = x;
			tank_.coord.y = y;
			tank_.direct = dir;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			place = color;
			sprite.setTextureRect(sf::IntRect((color/2)*128+dir*32, (color%2)*128, 16, 16));
			sprite.setPosition(x, y);
		}
		void update()
		{
			sprite.setPosition(Get_X(), Get_Y());
			sprite.setTextureRect(sf::IntRect(place/2*128+tank_.direct*32, (place%2)*128, 16, 16));
		}
		int Get_X()
		{
			return tank_.coord.x;
		}
		int Get_Y()
		{
			return tank_.coord.y;
		}
		enum direct_e Get_Dir()
		{
			return tank_.direct;
		}
		void Set_X(int x)
		{
			tank_.coord.x = x;
			update();
		}
		void Set_Y(int y)
		{
			tank_.coord.y = y;
			update();
		}
		void Set_Dir(enum direct_e direct)
		{
			tank_.direct = direct;
			update();
		}
		struct coord_s Get_Coord()
		{
			return tank_.coord;
		}
		void Set_Coord(struct coord_s coord_)
		{
			tank_.coord.x = coord_.x;
			tank_.coord.y = coord_.y;
		}
		struct coord_s Get_Map_Position()
		{
			struct coord_s coord_;
			coord_.x = tank_.coord.x/SIZE_TILE;
			coord_.y = tank_.coord.y/SIZE_TILE;
			return coord_;
		}
};

class bullet_c : public object_c {
	private:
		bullet_s bullet_;
	public:
		bullet_c(sf::String file,
		     int x,
		     int y,
		     enum direct_e dir)
		{
			bullet_.coord.x = x;
			bullet_.coord.y = y;
			bullet_.direct = dir;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(dir*8+320, 100, 8, 8));
			sprite.setPosition(x, y + 4);
		}
		void update()
		{
			sprite.setPosition(Get_X(), Get_Y());
			sprite.setTextureRect(sf::IntRect(bullet_.direct*8+320, 100, 8, 8));

		}
		int Get_X()
		{
			return bullet_.coord.x;
		}
		int Get_Y()
		{
			return bullet_.coord.y - 4;
		}
		enum direct_e Get_Dir()
		{
			return bullet_.direct;
		}
		void Set_X(int x)
		{
			bullet_.coord.x = x + 4;
			update();
		}
		void Set_Y(int y)
		{
			bullet_.coord.y = y + 4;
			update();
		}
		void Set_Dir(enum direct_e direct)
		{
			bullet_.direct = direct;
			update();
		}
		struct coord_s Get_Coord()
                {
                        return bullet_.coord;
                }
                void Set_Coord(struct coord_s coord_)
                {
                        bullet_.coord.x = coord_.x;
                        bullet_.coord.y = coord_.y;
                }
                struct coord_s Get_Map_Position()
                {
                        struct coord_s coord_;
                        coord_.x = bullet_.coord.x/SIZE_TILE;
                        coord_.y = bullet_.coord.y/SIZE_TILE;
                        return coord_;
                }

};

#endif //__CURSED_TANKS_H__
