#include <SFML/Graphics.hpp>
#include <map.h>
#include <cursedtanks.h>
using namespace sf;

void Draw_Map(RenderWindow *window, String *mass_tile)
{
	
}

int main()
{
	RenderWindow window(VideoMode(500, 500), "CursedTanks");
	View view(FloatRect(0,0,100,100));
	window.setView(view);
	Color color(255,255,255);
	tank_c tank("textures/tank1.png", 1, 1, color, LEFT);
	//if (Macro_To_Micro(macro_tile, micro_tile))
		//printf("Macro_map can't be read");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			window.close();
	        }
		window.clear();
		window.draw(tank.sprite);
		window.display();
	}

	return 0;
}
