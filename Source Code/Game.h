#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemies.h"
#define maxItems 4
using namespace std;
class Game
{
private:
	//enemy destroy sfx
	sf::Sound enemyHit;
	sf::SoundBuffer enemyHitBuffer;
	//player shoot sfx
	sf::Sound playerShoot;
	sf::SoundBuffer playerShootBuffer;
	//player hit sfx
	sf::Sound playerHit;
	sf::SoundBuffer playerHitBuffer;
	//pickup sfx
	sf::Sound pickup;
	sf::SoundBuffer pickupBuffer;
	sf::Event gameEvent;
	sf::Font font;
	sf::Text scoreText;
	sf::Text text;
	sf::Text IconText[maxItems];
	Player player;
	Enemies enemy;
	sf::Texture baseShieldTexture;
	sf::Texture explosionTexture;
	sf::RectangleShape baseShield;
	sf::RectangleShape explosion;
	vector<sf::RectangleShape> enemiesTank;
	vector<sf::RectangleShape> enemiesTruck;
	vector<sf::RectangleShape> projectiles;
	vector<sf::RectangleShape> healthPickups;
	vector<sf::RectangleShape> baseShields;
	int currentlevel;
	int currentTarget;
	int currentSFXVolume;
	int changeInSpawnRate;
	int changeInTarget;
	int maxEnemiesTank;
	int maxEnemiesTruck;
	int maxHealthPickups;
	int baseHealth;
	int maxBaseShieldPickup;
	int score;
	int totalScore;
	int currentHighScore;
	int currentHighestLevel;
	int shootTimer;
	int shootCount;
	float changeInSpeed;
	float enemySpeed;
	float spawnTankTimer;
	float spawnTankTimerMax;
	float spawnTruckTimer;
	float spawnTruckTimerMax;
	float healthSpawnTimer;
	float maxHealthSpawnTimer;
	float shieldSpawnTimer;
	float maxShieldSpawnTimer;
	bool isLevelFinished;
	bool isGameOver;
	void InitVariables();
	void InitFonts();
	void InitText(sf::RenderWindow& window);
	void InitBaseShield();
	void InitTexture();
	void InitAudio();
public:
	Game();
	~Game();
	bool IsGameOver();
	int RandomEnemyType();
	void SetVolume();
	void Update(sf::RenderTarget* target, sf::RenderWindow& window);
	void SetGameState(bool gameOver);
	void UpdatePlay(sf::RenderTarget* target);
	void SpawnEnemies(sf::RenderWindow& window);
	void SpawnHealthPickup(sf::RenderWindow& window);
	void SpawnBaseShields(sf::RenderWindow& window);
	void Shoot();
	void UpdateCollision(sf::RenderWindow& window);
	void PollEvents(sf::RenderWindow& window);
	void UpdateText();
	void Reset();
	void GetHighScore();
	void SetHighScore();
	void GetHighestLevel();
	void SetHighestLevel();
	void Render(sf::RenderTarget* target, sf::RenderWindow& window);
	void RenderText(sf::RenderTarget* target);
	void NextLevel();
	void CheckTargetAchived();
	bool CheckLevelAchived();
	void SetTargetCheck(bool targetCheck);
};