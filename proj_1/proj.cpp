#include <iostream>
#include <time.h>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics/Color.hpp"

 //em skopiowane z biblioteki sfml bo próbuje zrozumieć mouse button
 #define SFML_MOUSE_HPP
    // Headers
   #include <SFML/Window/Export.hpp>
   #include <SFML/System/Vector2.hpp>

int main () 
{
	std::srand (time(0)); //losowansko

	sf::RenderWindow app(sf::VideoMode(400,400), "Sweep"); //render okna działa
	
	 int w=32;
	int grid [12][12];
	int sgrid [12][12]; //wymiary
	
	sf::Texture txt;
	txt.loadFromFile("kafle/tiles.jpg"); //wczyt jpg dla tekstur kafli
	sf::Sprite s(txt);


	for (int i=1;i<=10;i++)			//odswierzanie i tabelka
		for (int j=1;j<=10;j++)
			{
			sgrid[i][j]=10; 		
			if (rand()%5==0)  grid[i][j]=9;
			else grid[i][j]=0;			
			}
	for (int i=1;i<=10;i++)
	for (int j=1;j<=10;j++)
	{
	int n=0;
	if (grid[i][j]==9) continue;
        if (grid[i+1][j]==9) n++;
        if (grid[i][j+1]==9) n++;
        if (grid[i-1][j]==9) n++;
        if (grid[i][j-1]==9) n++;
        if (grid[i+1][j+1]==9) n++;
        if (grid[i-1][j-1]==9) n++;
        if (grid[i-1][j+1]==9) n++;
        if (grid[i+1][j-1]==9) n++;
        grid[i][j]=n;				
	}

	while (app.isOpen())	//wczytwyanie mysz
	{
	sf::Vector2i pos = sf::Mouse::getPosition(app);	
	int x = pos.x/w;
	int y = pos.y/w;

	sf::Event e; 	//czytalem o eventach i nie rozumiem do konca. w miare dziala
	while (app.pollEvent(e))
		{
		if (e.type == sf::Event::Closed)
			app.close();
		if (e.type == sf::Event::MouseButtonPressed)
			if (e.key.code == sf::Mouse::Left) sgrid[x][y]=grid[x][y]; // edit:: 4h pisania tego i nie działa bind na lewy i prawy na mysz.
			else if (e.key.code == sf::Mouse::Right) sgrid [x][y]=11;		
		}	
	
	app.clear(sf::Color::White);
					//nie działa biała plansza jest przezroczysta
	for (int i=1;i<=10;i++)		
		for (int j=1;j<=10;j++)
		{
		if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
           	s.setTextureRect(sf::IntRect(sgrid[i][j]*w,0,w,w));
           	s.setPosition(i*w, j*w);
           	app.draw(s);
		}
		
	app.display(); //pokazywanie
	}
	sf::Event quit;
	while (window.pollEvent(quit))
	{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
	window.close();
	}
		
	return 0;
}


//errory:
//Setting vertical sync not supported
//Segmentation fault (core dumped)
