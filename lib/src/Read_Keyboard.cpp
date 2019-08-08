#include <cursedtanks.h>

void Read_Keyboard(tank_c *tank, float time)
{
		int x = 0, y = 0, value = 0;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			--x;
			++value;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			++x;
			++value;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
			--y;
			++value;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
			++y;
			++value;

		}
		if (( value == 1 )) {
			tank -> sprite.move(x * tank->Get_Speed() * time, y * tank->Get_Speed() * time);
			if (x == 0) {
				if (y > 0)
					tank -> Set_Dir(DOWN);
				else
					tank -> Set_Dir(UP);
			}
			else {
				if (x > 0)
					tank -> Set_Dir(RIGHT);
				else
					tank -> Set_Dir(LEFT);
			}
		}
}
