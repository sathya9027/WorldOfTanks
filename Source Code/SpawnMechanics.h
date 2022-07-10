#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemies.h"
class SpawnMechanics
{
private:
public:
	SpawnMechanics();
	~SpawnMechanics();
	void SpawnEnemies();
	void SpawnPlayer();
	void SpawnProjectiles();
	void SpawnHealthPickups();
	void SpawnShieldPickups();
	void Render(sf::RenderTarget* target);
};

