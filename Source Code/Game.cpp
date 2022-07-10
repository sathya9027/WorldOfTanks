#include "Game.h"
Game::Game() {
	this->InitVariables();
	this->InitFonts();
	this->InitTexture();
	this->InitAudio();
}
Game::~Game() {
	this->enemiesTank.clear();
	this->enemiesTruck.clear();
	this->projectiles.clear();
	this->healthPickups.clear();
	this->baseShields.clear();
}
void Game::InitAudio() {
	//enemy destroy
	this->enemyHit.setBuffer(this->enemyHitBuffer);
	if (!this->enemyHitBuffer.loadFromFile("Audio\\explosion.wav")) {
		return;
	}

	//player shoot
	this->playerShoot.setBuffer(this->playerShootBuffer);
	if (!this->playerShootBuffer.loadFromFile("Audio\\tank_shoot.wav")) {
		return;
	}

	//player damage
	this->playerHit.setBuffer(this->playerHitBuffer);
	if (!this->playerHitBuffer.loadFromFile("Audio\\hitHurt.wav")) {
		return;
	}

	//pickup
	this->pickup.setBuffer(this->pickupBuffer);
	if (!this->pickupBuffer.loadFromFile("Audio\\pickup.wav")) {
		return;
	}
}
void Game::InitFonts() {
	if (!this->font.loadFromFile("Absolute Xero.otf")) {
		cout << "font file not found!!!";
	}
}
void Game::InitText(sf::RenderWindow& window) {
	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(sf::Color::Green);
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::Green);
}
void Game::InitBaseShield() {
	this->baseShieldTexture.loadFromFile("Image\\Rect-element.png");
	this->baseShield.setTexture(&this->baseShieldTexture);
	this->baseShield.setSize(sf::Vector2f(100, 100));
}
void Game::InitTexture() {
	this->explosion.setSize(sf::Vector2f(150, 150));
	this->explosionTexture.loadFromFile("Image\\Explo.png");
	this->explosion.setTexture(&this->explosionTexture);

}
void Game::InitVariables() {
	this->totalScore = 0;
	this->isLevelFinished = false;
	this->currentlevel = 1;
	this->currentTarget = 60;
	this->changeInTarget = 20 + (rand() % 20);
	this->changeInSpeed = 0.005;
	this->baseHealth = 100;
	this->changeInSpawnRate = rand() % 10;
	this->shootTimer = 0;
	this->isGameOver = false;
	this->maxEnemiesTank = 10;
	this->maxEnemiesTruck = 3;
	this->maxHealthPickups = 3;
	this->score = 0;
	this->maxShieldSpawnTimer = 20.0f;
	this->shieldSpawnTimer = this->maxShieldSpawnTimer;
	this->maxBaseShieldPickup = 4;
	this->spawnTankTimerMax = 20.0f;
	this->spawnTruckTimerMax = 100.0f;
	this->maxHealthSpawnTimer = 200.0f;
	this->healthSpawnTimer = this->maxHealthSpawnTimer;
	this->enemySpeed = 1.5f;
	this->spawnTankTimer = this->spawnTankTimerMax;
	this->spawnTruckTimer = this->spawnTruckTimerMax;
}
bool Game::IsGameOver() {
	return this->isGameOver;
}
void Game::SetGameState(bool gameOver) {
	this->isGameOver = gameOver;
}
int Game::RandomEnemyType() {
	int type;
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80) {
		type = EnemyTypes::HEALTH;
	}
	else if (randValue > 80) {
		type = EnemyTypes::DAMAGE;
	}
	else {
		type = EnemyTypes::DEFAULT;
	}
	return type;
}
void Game::SetVolume() {
	ifstream readFile;
	readFile.open("SFXVolume.txt");
	if (readFile.is_open()) {
		while (!readFile.eof())
		{
			readFile >> this->currentSFXVolume;
			this->enemyHit.setVolume(this->currentSFXVolume);
			this->playerShoot.setVolume(this->currentSFXVolume);
			this->playerHit.setVolume(this->currentSFXVolume);
			this->pickup.setVolume(this->currentSFXVolume);
		}
	}
	readFile.close();
}
void Game::Update(sf::RenderTarget* target, sf::RenderWindow& window) {
	this->SetVolume();
	this->InitText(window);
	this->PollEvents(window);
	if (this->isGameOver == false || this->isLevelFinished == false) {
		this->CheckTargetAchived();
		this->UpdatePlay(target);
		this->Shoot();
		this->SpawnHealthPickup(window);
		this->SpawnBaseShields(window);
		this->SpawnEnemies(window);
		this->UpdateCollision(window);
		this->UpdateText();
		this->GetHighScore();
		this->SetHighScore();
		this->GetHighestLevel();
		this->SetHighestLevel();
		this->Render(target, window);
	}
}
void Game::NextLevel() {
	this->baseHealth = 100;
	this->currentlevel++;
	this->currentTarget += changeInTarget;
	this->spawnTankTimerMax += changeInSpawnRate;
	this->spawnTruckTimerMax += changeInSpawnRate;
	this->player.ResetStats();
	this->score = 0;
	this->isLevelFinished = false;
	this->projectiles.clear();
	this->enemiesTank.clear();
	this->enemiesTruck.clear();
	this->healthPickups.clear();
	this->baseShields.clear();
}
void Game::CheckTargetAchived() {
	if (this->score >= this->currentTarget) {
		this->isLevelFinished = true;
	}
}
bool Game::CheckLevelAchived() {
	return this->isLevelFinished;
}
void Game::SetTargetCheck(bool targetCheck) {
	this->isLevelFinished = targetCheck;
}
void Game::UpdatePlay(sf::RenderTarget* target) {
	this->player.UpdatePlayer(target);
}
void Game::SpawnHealthPickup(sf::RenderWindow& window) {
	if (this->player.GetHealthPoint() <= 80) {
		if (this->healthSpawnTimer < this->maxHealthSpawnTimer) {
			this->healthSpawnTimer += 1.0f;
		}
		else {
			if (this->healthPickups.size() < this->maxHealthPickups) {
				cout << "health spawned" << endl;
				this->healthPickups.push_back(this->player.getHealthPickup(window));
			}
			this->healthSpawnTimer = 0.0f;
		}
	}
}
void Game::SpawnBaseShields(sf::RenderWindow& window) {
	if (this->baseHealth <= 70) {
		if (this->shieldSpawnTimer < this->maxShieldSpawnTimer) {
			this->shieldSpawnTimer += 1.0f;
		}
		else {
			if (this->baseShields.size() < this->maxBaseShieldPickup) {
				cout << "shield spawned" << endl;
				this->baseShield.setPosition(sf::Vector2f(rand() % int(window.getSize().x - this->baseShield.getSize().x),
					rand() % int(window.getSize().y - this->baseShield.getSize().y)));
				this->baseShields.push_back(this->baseShield);
			}
			this->shieldSpawnTimer = 0.0f;
		}
	}
}
void Game::SpawnEnemies(sf::RenderWindow& window) {
	//tank
	if (this->spawnTankTimer < this->spawnTankTimerMax) {
		this->spawnTankTimer += 0.5f + this->changeInSpeed;
	}
	else {
		if (this->enemiesTank.size() < this->maxEnemiesTank) {
			this->enemiesTank.push_back(this->enemy.getEnemyTank(window));
		}
		if (this->enemiesTruck.size() < this->maxEnemiesTruck) {
			this->enemiesTruck.push_back(this->enemy.getEnemyTruck(window));
		}
		this->spawnTankTimer = 0.0f;
	}
	//truck
	if (this->spawnTruckTimer < this->spawnTruckTimerMax) {
		this->spawnTruckTimer += 0.1f + this->changeInSpeed;
	}
	else {
		if (this->enemiesTruck.size() < this->maxEnemiesTruck) {
			this->enemiesTruck.push_back(this->enemy.getEnemyTruck(window));
		}
		this->spawnTruckTimer = 0.0f;
	}
}
void Game::Shoot() {
	if (this->shootTimer < 20) {
		this->shootTimer++;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shootTimer >= 20)	//shoot
	{
		this->projectiles.push_back(this->player.getProjectile());
		this->playerShoot.play();
		this->shootTimer = 0;
	}

	for (size_t i = 0; i < this->projectiles.size(); i++)
	{
		this->projectiles[i].move(0.0f, -10.0f);

		if (this->projectiles[i].getPosition().y <= 0) {
			this->projectiles.erase(this->projectiles.begin() + i);
		}
	}
}
void Game::UpdateCollision(sf::RenderWindow& window) {
	//tank
	for (size_t i = 0; i < this->enemiesTank.size(); i++) {
		this->enemiesTank[i].move(0.0f, this->enemySpeed);

		if (this->enemiesTank[i].getPosition().y > 500) {
			this->explosion.setPosition(this->enemiesTank[i].getPosition());
			window.draw(this->explosion);
			this->enemyHit.play();
			this->enemiesTank.erase(this->enemiesTank.begin() + i);
			this->baseHealth -= 15;
		}
		if (this->player.getRect().getGlobalBounds().intersects(this->enemiesTank[i].getGlobalBounds())) {
			this->player.TakeDamage(20);
			if (this->player.GetHealthPoint() <= 0) {
				this->explosion.setPosition(this->player.getRect().getPosition());
				window.draw(this->explosion);
				this->playerHit.play();
			}
			this->explosion.setPosition(this->enemiesTank[i].getPosition());
			window.draw(this->explosion);
			this->enemyHit.play();
			this->playerHit.play();
			this->enemiesTank.erase(this->enemiesTank.begin() + i);
		}
	}

	//truck
	for (size_t i = 0; i < this->enemiesTruck.size(); i++)
	{
		this->enemiesTruck[i].move(0.0f, this->enemySpeed + 1.0f);

		if (this->enemiesTruck[i].getPosition().y > 500) {
			this->explosion.setPosition(this->enemiesTruck[i].getPosition());
			window.draw(this->explosion);
			this->enemyHit.play();
			this->enemiesTruck.erase(this->enemiesTruck.begin() + i);
			this->baseHealth -= 25;
		}
		if (this->player.getRect().getGlobalBounds().intersects(this->enemiesTruck[i].getGlobalBounds())) {
			this->player.TakeDamage(30);
			if (this->player.GetHealthPoint() <= 0) {
				this->explosion.setPosition(this->player.getRect().getPosition());
				window.draw(this->explosion);
				this->playerHit.play();
			}
			this->explosion.setPosition(this->enemiesTruck[i].getPosition());
			window.draw(this->explosion);
			this->enemyHit.play();
			this->playerHit.play();
			this->enemiesTruck.erase(this->enemiesTruck.begin() + i);
		}
	}

	//health
	for (size_t i = 0; i < this->healthPickups.size(); i++)
	{
		if (this->player.getRect().getGlobalBounds().intersects(this->healthPickups[i].getGlobalBounds())) {
			this->player.GainHealth(10);
			this->pickup.play();
			this->healthPickups.erase(this->healthPickups.begin() + i);
		}
	}

	//baseshield
	for (size_t i = 0; i < this->baseShields.size(); i++)
	{
		if (this->player.getRect().getGlobalBounds().intersects(this->baseShields[i].getGlobalBounds())) {
			this->baseHealth += 10;
			this->pickup.play();
			this->baseShields.erase(this->baseShields.begin() + i);
		}
	}

	//projectile
	for (size_t i = 0; i < this->projectiles.size(); i++)
	{
		for (size_t k = 0; k < this->enemiesTank.size(); k++)
		{
			if (this->projectiles[i].getGlobalBounds().intersects(enemiesTank[k].getGlobalBounds()))
			{
				this->explosion.setPosition(enemiesTank[k].getPosition());
				window.draw(this->explosion);
				this->enemyHit.play();
				this->projectiles.erase(this->projectiles.begin() + i);
				this->enemiesTank.erase(this->enemiesTank.begin() + k);
				this->score++;
				this->totalScore++;
				break;
			}
		}
	}
	
	for (size_t i = 0; i < this->projectiles.size(); i++)
	{
		for (size_t k = 0; k < this->enemiesTruck.size(); k++)
		{
			if (this->projectiles[i].getGlobalBounds().intersects(this->enemiesTruck[k].getGlobalBounds()))
			{
				this->explosion.setPosition(this->enemiesTruck[k].getPosition());
				window.draw(this->explosion);
				this->enemyHit.play();
				this->projectiles.erase(this->projectiles.begin() + i);
				this->enemiesTruck.erase(this->enemiesTruck.begin() + k);
				this->score+=2;
				this->totalScore+=2;
				break;
			}
		}
	}
}
void Game::PollEvents(sf::RenderWindow& window) {
	while (window.pollEvent(this->gameEvent))
	{
		switch (this->gameEvent.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			break;
		}
	}
}
void Game::UpdateText() {
	stringstream istream;
	stringstream ostream;
	istream << "\Level: " << this->currentlevel << endl;
	istream << "\Score: " << this->score << endl;
	ostream << "        " << this->baseHealth << " :Base" << endl;
	ostream << this->player.GetHealthPoint() << " :Player" << endl;
	this->text.setCharacterSize(25);
	this->text.setString(ostream.str());
	this->text.setPosition(370, 0);
	this->scoreText.setCharacterSize(25);
	this->scoreText.setString(istream.str());

}
void Game::Reset() {
	this->InitBaseShield();
	this->player.ResetStats();
	this->InitVariables();
	this->projectiles.clear();
	this->enemiesTank.clear();
	this->enemiesTruck.clear();
	this->healthPickups.clear();
	this->baseShields.clear();
}
void Game::GetHighScore() {
	ifstream readFile;
	readFile.open("HighScore.txt");
	if (readFile.is_open()) {
		while (!readFile.eof())
		{
			readFile >> this->currentHighScore;
		}
	}
	readFile.close();
}
void Game::SetHighScore() {
	ofstream writeFile("HighScore.txt");
	if (writeFile.is_open()) {
		if (this->totalScore > this->currentHighScore) {
			this->currentHighScore = this->totalScore;
			writeFile << this->currentHighScore;
		}
		else {
			writeFile << this->currentHighScore;
		}
	}
	writeFile.close();
}
void Game::GetHighestLevel() {
	ifstream readFile;
	readFile.open("HighestLevel.txt");
	if (readFile.is_open()) {
		while (!readFile.eof())
		{
			readFile >> this->currentHighestLevel;
		}
	}
	readFile.close();
}
void Game::SetHighestLevel() {
	ofstream writeFile("HighestLevel.txt");
	if (writeFile.is_open()) {
		if (currentlevel >= currentHighestLevel) {
			currentHighestLevel = currentlevel;
			writeFile << currentHighestLevel;
		}
		else {
			writeFile << currentHighestLevel;
		}
	}
	writeFile.close();
}
void Game::Render(sf::RenderTarget* target, sf::RenderWindow& window) {
	for (int i = 0; i < projectiles.size(); i++)
	{
		window.draw(projectiles[i]);
	}
	for (size_t i = 0; i < healthPickups.size(); i++)
	{
		window.draw(healthPickups[i]);
	}
	for (size_t i = 0; i < baseShields.size(); i++)
	{
		window.draw(baseShields[i]);
	}
	for (size_t i = 0; i < enemiesTank.size(); i++)
	{
		window.draw(enemiesTank[i]);
	}
	for (size_t i = 0; i < enemiesTruck.size(); i++)
	{
		window.draw(enemiesTruck[i]);
	}
	this->player.RenderPlayer(target);
	this->RenderText(target);
}
void Game::RenderText(sf::RenderTarget* target) {
	target->draw(this->scoreText);
	target->draw(this->text);
	if (this->player.GetHealthPoint() <= 0) {
		this->isGameOver = true;
	}
	else if (this->baseHealth <= 0) {
		this->isGameOver = true;
	}
}