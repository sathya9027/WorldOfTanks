#include "Player.h"
Player::Player() {
	this->InitVariables();
}
Player::~Player() {

}
sf::RectangleShape Player::getRect() {
	return this->playerRect;
}
sf::RectangleShape Player::getProjectile() {
	this->playerCenter = sf::Vector2f(playerRect.getPosition().x + playerRect.getSize().x / 2 - 6.7,
		playerRect.getPosition().y + 10);
	this->projectile.setPosition(this->playerCenter);
	return this->projectile;
}
sf::RectangleShape Player::getHealthPickup(sf::RenderWindow& window) {
	this->health.setPosition(sf::Vector2f(rand() % int(window.getSize().x - health.getSize().x),
		rand() % int(window.getSize().y - health.getSize().y)));
	return health;
}
sf::Vector2f Player::getCenter() {
	return this->playerCenter;
}
int Player::GetHealthPoint() {
	return this->healthPoint;
}
int Player::MaxHealthPoint() {
	return this->maxHealthPoint;
}
void Player::TakeDamage(int damage) {
	if (this->healthPoint > 0) {
		this->healthPoint -= damage;
	}
	if (this->healthPoint < 0) {
		this->healthPoint = 0;
	}
}
void Player::GainHealth(int health) {
	if (this->healthPoint < this->maxHealthPoint) {
		this->healthPoint += health;
	}
	if (this->healthPoint > this->maxHealthPoint) {
		this->healthPoint = this->maxHealthPoint;
	}
}
void Player::InitRect() {
	this->playerRect.setPosition(sf::Vector2f(300.0f, 500.0f));
	this->playerRect.setSize(sf::Vector2f(64, 97));
}
void Player::InitVariables() {
	this->speed = 5.0f;
	this->maxHealthPoint = 100;
	this->healthPoint = this->maxHealthPoint;
	this->projectile.setSize(sf::Vector2f(11.91, 34.91));
	this->health.setSize(sf::Vector2f(100, 100));
}
void Player::InitTexture() {
	this->playerTexture.loadFromFile("Image\\Tank_Big_Yellow.png");
	this->playerRect.setTexture(&playerTexture);
	this->projectileTexture.loadFromFile("Image\\shell.png");
	this->projectile.setTexture(&projectileTexture);
	this->healthTexture.loadFromFile("Image\\heart-Element.png");
	this->health.setTexture(&healthTexture);
}
void Player::UpdateInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->playerRect.move(-this->speed, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->playerRect.move(this->speed, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->playerRect.move(0.0f, -this->speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->playerRect.move(0.0f, this->speed);
	}
}
void Player::ResetStats() {
	this->InitTexture();
	this->InitRect();
	this->InitVariables();
}
void Player::UpdateBoundCollision(sf::RenderTarget* target) {
	//left bound
	if (this->playerRect.getGlobalBounds().left <= 0.0f) {
		this->playerRect.setPosition(sf::Vector2f(0.0f, this->playerRect.getGlobalBounds().top));
	}
	//right bound
	if (this->playerRect.getGlobalBounds().left +
		this->playerRect.getGlobalBounds().width >= target->getSize().x) {
		this->playerRect.setPosition(sf::Vector2f(target->getSize().x - this->playerRect.getGlobalBounds().width,
			this->playerRect.getGlobalBounds().top));
	}
	//top bound
	if (this->playerRect.getGlobalBounds().top <= 0.0f) {
		this->playerRect.setPosition(sf::Vector2f(this->playerRect.getGlobalBounds().left, 0.0f));
	}
	//bottom bound
	if (this->playerRect.getGlobalBounds().top +
		this->playerRect.getGlobalBounds().height >= target->getSize().y) {
		this->playerRect.setPosition(sf::Vector2f(this->playerRect.getGlobalBounds().left,
			target->getSize().y - this->playerRect.getGlobalBounds().height));
	}
}
void Player::UpdatePlayer(sf::RenderTarget* target) {
	this->UpdateInput();
	this->UpdateBoundCollision(target);
}
void Player::RenderPlayer(sf::RenderTarget* target) {
	target->draw(this->playerRect);
}