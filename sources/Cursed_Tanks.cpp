#include <SFML/Graphics.hpp>
#include <map.h>
#include <cursedtanks.h>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(500, 500), "CursedTanks");
	View view(FloatRect(0,0,100,100));
	window.setView(view);
//	CircleShape shape(100.f);
//	shape.setFillColor(Color::Green);
	Color color(255,255,255);
	tank_c tank("textures/tank.png", 1, 1, color);
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
