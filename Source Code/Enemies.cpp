#include "Enemies.h"
Enemies::Enemies() {
	this->InitTexture();
}
Enemies::~Enemies() {

}
sf::RectangleShape Enemies::getEnemyTank(sf::RenderWindow& window) {
	this->enemy.setPosition(sf::Vector2f(rand() % int(window.getSize().x - enemy.getSize().x), -100));
	return this->enemy;
}
sf::RectangleShape Enemies::getEnemyTruck(sf::RenderWindow& window) {
	this->enemyTruck.setPosition(sf::Vector2f(rand() % int(window.getSize().x - enemyTruck.getSize().x), -600));
	return this->enemyTruck;
}
void Enemies::InitTexture() {
	enemyTexture.loadFromFile("Image\\Tank_Brown.png");
	this->enemy.setTexture(&enemyTexture);
	enemy.setSize(Vector2f(67.0f, 108.0f));
	enemyTruckTexture.loadFromFile("Image\\MilitaryTruck.png");
	enemyTruck.setTexture(&enemyTruckTexture);
	enemyTruck.setSize(Vector2f(73.0f, 137.0f));
}
void Enemies::RenderEnemy(sf::RenderTarget* target) {
	target->draw(this->enemy);
}