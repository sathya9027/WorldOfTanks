#include "GameState.h"
GameState::GameState() {
	this->InitVariables();
	this->InitWindow();
	this->InitTexture();
	this->InitAudio();
	this->intro.play();
}
GameState::~GameState() {

}
void GameState::InitAudio() {
	//intro
	if (!this->intro.openFromFile("Audio\\introMusic.wav")) {
		return;
	}

	//core game
	if (!this->coreGame.openFromFile("Audio\\coreGameMusic.wav")) {
		return;
	}

	//level up
	if (!this->levelup.openFromFile("Audio\\levelup.wav")) {
		return;
	}

	//gameover
	if (!this->gameOver.openFromFile("Audio\\gameOver.wav")) {
		return;
	}
}
void GameState::InitTexture() {
	backgroundTexture.loadFromFile("Image\\BG.png");
	background.setTexture(&backgroundTexture);
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}
void GameState::InitVariables() {
	this->gameState = 0;
}
void GameState::InitWindow() {
	this->videoMode = sf::VideoMode(600, 600);
	this->window = new sf::RenderWindow(this->videoMode, "World Of Tanks", sf::Style::Default);
	this->window->setFramerateLimit(60);
	this->windowIcon.loadFromFile("Image\\Tank_Big_Yellow.png");
	this->window->setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
}
void GameState::SetVolume() {
	ifstream readFile;
	readFile.open("BGMVolume.txt");
	if (readFile.is_open()) {
		while (!readFile.eof())
		{
			readFile >> currentBGMVolume;
			this->intro.setVolume(currentBGMVolume);
			this->coreGame.setVolume(currentBGMVolume);
			this->levelup.setVolume(currentBGMVolume);
			this->gameOver.setVolume(currentBGMVolume);
		}
	}
	readFile.close();
}
void GameState::StartGame() {
	this->CheckGameState();
}
void GameState::CheckGameState() {
	while (this->window->isOpen())
	{
		this->SetVolume();
		this->window->clear(sf::Color::Black);
		this->window->draw(background);
		switch (this->gameState)
		{
		case CurrentGameState::Start:
			this->Start();
			break;
		case CurrentGameState::CoreGame:
			this->CoreGame();
			break;
		case CurrentGameState::Ending:
			this->Ending();
			break;
		case CurrentGameState::HighScoreMenu:
			this->HighScoreMenu();
			break;
		case CurrentGameState::LevelUp:
			this->LevelUp();
			break;
		case CurrentGameState::Tutorial:
			this->Tutorial();
			break;
		case CurrentGameState::SettingsMenu:
			this->SettingsMenu();
			break;
		}
		this->window->display();
	}
}
void GameState::Start() {
	this->intro.setLoop(true);
	if (this->menu.getPressedItem() == 0 && this->menu.IsButtonPressed()) {
		this->intro.stop();
		this->gameState = CurrentGameState::CoreGame;
		this->game.Reset();
		this->menu.GetBool(false);
	}
	else if (this->menu.getPressedItem() == 1 && this->menu.IsButtonPressed()) {
		this->gameState = CurrentGameState::Tutorial;
		this->menu.GetBool(false);
	}
	else if (this->menu.getPressedItem() == 2 && this->menu.IsButtonPressed()) {
		this->gameState = CurrentGameState::HighScoreMenu;
		this->menu.GetBool(false);
	}
	else if (this->menu.getPressedItem() == 3 && this->menu.IsButtonPressed()) {
		this->gameState = CurrentGameState::SettingsMenu;
		this->menu.GetBool(false);
	}
	else if (this->menu.getPressedItem() == 4 && this->menu.IsButtonPressed()) {
		this->window->close();
	}
	else {
		this->menu.Update(window, *window, gameEvent);
	}
}
void GameState::CoreGame() {
	if (!this->coreGame.getStatus()) {
		this->coreGame.play();
	}
	if (this->game.IsGameOver()) {
		this->gameState = CurrentGameState::Ending;
		this->gameOver.play();
		this->coreGame.stop();
		this->game.SetGameState(false);
	}
	else if (this->game.CheckLevelAchived()) {
		this->gameState = CurrentGameState::LevelUp;
		this->levelup.play();
		this->coreGame.stop();
		this->game.SetTargetCheck(false);
	}
	else {
		this->game.Update(window, *window);
	}
}
void GameState::Ending() {
	if (this->endingMenu.GetIndex() == 0 && this->endingMenu.IsButtonPressed()) {
		this->game.Reset();
		this->gameState = CurrentGameState::CoreGame;
		this->gameOver.stop();
		this->endingMenu.SetButtonPressed(false);
	}
	else if (this->endingMenu.GetIndex() == 1 && this->endingMenu.IsButtonPressed()) {
		this->gameState = CurrentGameState::Start;
		this->gameOver.stop();
		this->game.Reset();
		this->endingMenu.SetButtonPressed(false);
	}
	else {
		this->endingMenu.Update(window, *window, gameEvent);
	}
}
void GameState::HighScoreMenu() {
	if (this->highScore.getPressedItem() == 1 && this->highScore.IsButtonPressed()) {
		this->gameState = CurrentGameState::Start;
		this->highScore.GetBool(false);
	}
	else {
		this->highScore.Update(window, *window, gameEvent);
	}
}
void GameState::LevelUp() {
	if (this->winningMenu.GetIndex() == 0 && this->winningMenu.IsButtonPressed()) {
		this->gameState = CurrentGameState::CoreGame;
		this->levelup.stop();
		this->game.NextLevel();
		this->winningMenu.SetButtonPressed(false);
	}
	else if (this->winningMenu.GetIndex() == 1 && this->winningMenu.IsButtonPressed()) {
		this->gameState = CurrentGameState::Start;
		this->levelup.stop();
		this->game.Reset();
		this->winningMenu.SetButtonPressed(false);
	}
	else {
		this->winningMenu.Update(window, *window, gameEvent);
	}
}
void GameState::Tutorial() {
	if (this->instruction.getPressedItem() == 0 && this->instruction.IsButtonPressed()) {
		this->gameState = CurrentGameState::Start;
		this->instruction.GetBool(false);
	}
	else {
		this->instruction.Update(window, *window, gameEvent);
	}
}
void GameState::SettingsMenu() {
	if (this->settings.getPressedItem() == 3 && this->settings.IsButtonPressed()) {
		this->gameState = CurrentGameState::Start;
		this->settings.GetBool(false);
	}
	else {
		this->settings.Update(window, *window, gameEvent);
	}
}
void GameState::SetGameStatus(int currentGameStatus) {
	this->gameState = currentGameStatus;
}
int GameState::GetGameStatus() {
	return gameState;
}