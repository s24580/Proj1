#include <iostream>
#include <time.h>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/Drawable.hpp"
 //em skopiowane z biblioteki sfml bo próbuje zrozumieć mouse button
 #define SFML_MOUSE_HPP
 
    // Headers
   #include <SFML/Window/Export.hpp>
   #include <SFML/System/Vector2.hpp>

int main () 
{
	std::srand (time(0)); //losowansko/git
	
	sf::RenderWindow app(sf::VideoMode(600,600), "Sweep"); //render okna działa
	
	
	 int w=32;
	int grid [12][12];
	int sgrid [12][12]; //wymiary
	
	sf::Texture txt;
	txt.loadFromFile("kafle/tiles.jpg"); //wczyt jpg dla tekstur kafli
	sf::Sprite s(txt);
	
	sf::Clock zegar;			// kurde nie da sie renderowac czasu do okna
	sf::Time czas = zegar.getElapsedTime();
	float i = czas.asSeconds();
	
	
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

	while (app.isOpen())	//wczytwyanie mysz/warning tylko
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
					//nie działa biała plansza jest przezroczysta//naprawione
	for (int i=1;i<=10;i++)		
		for (int j=1;j<=10;j++)
		{
		if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
           	s.setTextureRect(sf::IntRect(sgrid[i][j]*w,0,w,w));
           	s.setPosition(i*w, j*w);
           	app.draw(s);
           	/*else 
           	#define _pelne_pol(wlas,i,j):
           	tile = wlas.(sf::IntRect(grid[i][j])) 
           	wlas._show_tile(pos.tile)
           		if (tile.texture == s.[0]):
           			neighbors = wlas._get_tile_neighbors(pos.tile)
           				for i in neighbors:
           					if (wlas.grid[i[0]][i[1]].ishidden):
           						wlas._pelne_pol(i[0],i[1])*/
           	
		}
	
	sf::Event quit;//quit pod esc
	while (app.pollEvent(quit))
	{
	if (quit.type == sf::Event::KeyPressed)
		{	
		if (quit.key.code == sf::Keyboard::Escape)
			{
			app.close();
			}
		}
	}
	
	/*app.draw(i);
	if( i >= 1 )
	{
	zegar.restart();
	}*/

	app.display(); //pokazywanie
	}
	
		
	return 0;
}


//errory:
//Setting vertical sync not supported
//Segmentation fault (core dumped)
