#ifndef _CURSED_TANKS_
#define _CURSED_TANKS_

#include "IO.h"
#include "logic.h"
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
	public:
		tank_c(sf::String file,
		     int x,
		     int y,
		     sf::Color color)
		{
			tank_.coord.x = x;
			tank_.coord.y = y;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
			sprite.setPosition(x, y);
			sprite.setColor(color);
		}
		void update()
		{
			sprite.setPosition(Get_X(), Get_Y());
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
};

class bullet_c : public object_c {
	private:
		bullet_s bullet_;
	public:
		bullet_c(sf::String file,
		     int x,
		     int y,
		     sf::Color color)
		{
			bullet_.coord.x = x;
			bullet_.coord.y = y;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 6, 6));
			sprite.setPosition(x, y);
			sprite.setColor(color);
		}
		void update()
		{
			sprite.setPosition(Get_X(), Get_Y());
		}
		int Get_X()
		{
			return bullet_.coord.x;
		}
		int Get_Y()
		{
			return bullet_.coord.y;
		}
		enum direct_e Get_Dir()
		{
			return bullet_.direct;
		}
		void Set_X(int x)
		{
			bullet_.coord.x = x;
			update();
		}
		void Set_Y(int y)
		{
			bullet_.coord.y = y;
			update();
		}
		void Set_Dir(enum direct_e direct)
		{
			bullet_.direct = direct;
			update();
		}
};
#endif //_CURSED_TANKS_
