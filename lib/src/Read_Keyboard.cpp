#include <cursedtanks.h>

void Read_Keyboard(tank_c *tank, float time)
{
		short x = 0, y = 0;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
			y = -1;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
			y = 1;

		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			x = -1;
			y = 0;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			x = 1;
			y = 0;
		}

		if (x == -1) {
			if (tank -> Get_Dir() != LEFT) {
				tank->sprite.setPosition(tank->sprite.getPosition().x, (int)((tank->sprite.getPosition().y+4)/8)*8);
				tank->Set_Dir(LEFT);
			}
		}
		else if (x == 1) {
			if (tank -> Get_Dir() != RIGHT) {
				tank->sprite.setPosition(tank->sprite.getPosition().x, (int)((tank->sprite.getPosition().y+4)/8)*8);
				tank -> Set_Dir(RIGHT);
			}
		}

		else if (y == -1) {
			if (tank -> Get_Dir() != UP) {
				tank->sprite.setPosition(((int)(tank->sprite.getPosition().x+4)/8)*8, tank->sprite.getPosition().y);
				tank -> Set_Dir(UP);
			}
		}
		else if (y == 1) {
			if (tank -> Get_Dir() != DOWN) {
				tank->sprite.setPosition(((int)(tank->sprite.getPosition().x+4)/8)*8, tank->sprite.getPosition().y);
				tank -> Set_Dir(DOWN);
			}
		}

		tank -> sprite.move(x * tank->Get_Speed() * time, y * tank->Get_Speed() * time);
}
