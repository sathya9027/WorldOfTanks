#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
enum EnemyTypes { DEFAULT = 0, DAMAGE, HEALTH };
using namespace std;
using namespace sf;
class Enemies
{
private:
	sf::RectangleShape enemy;
	sf::RectangleShape enemyTruck;
	sf::Color color;
	Texture enemyTexture;
	Texture enemyTruckTexture;
	void InitTexture();
public:
	Enemies();
	~Enemies();
	sf::RectangleShape getEnemyTank(sf::RenderWindow& window);
	sf::RectangleShape getEnemyTruck(sf::RenderWindow& window);
	void RenderEnemy(sf::RenderTarget* target);
};