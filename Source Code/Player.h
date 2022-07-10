#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
class Player
{
private:
	sf::RectangleShape playerRect;
	sf::Texture playerTexture;
	sf::RectangleShape projectile;
	sf::Texture projectileTexture;
	sf::RectangleShape health;
	sf::Texture healthTexture;
	sf::Vector2f playerCenter;
	float speed;
	int healthPoint;
	int maxHealthPoint;
	void InitRect();
	void InitVariables();
	void InitTexture();
public:
	Player();
	~Player();
	sf::RectangleShape getRect();
	sf::RectangleShape getHealthPickup(sf::RenderWindow& window);
	sf::RectangleShape getProjectile();
	sf::Vector2f getCenter();
	int GetHealthPoint();
	int MaxHealthPoint();
	void TakeDamage(int damage);
	void GainHealth(int health);
	void UpdateInput();
	void ResetStats();
	void UpdateBoundCollision(sf::RenderTarget* target);
	void UpdatePlayer(sf::RenderTarget* target);
	void RenderPlayer(sf::RenderTarget* target);
};