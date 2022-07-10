#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "EndingMenu.h"
#include "HighScore.h"
#include "WinningMenu.h"
#include "Instruction.h"
#include "Settings.h"
using namespace std;
enum CurrentGameState 
{ 
	Start = 0, 
	CoreGame, 
	Ending, 
	LevelUp, 
	HighScoreMenu, 
	Tutorial, 
	SettingsMenu };
class GameState
{
private:
	//intro bgm
	sf::Music intro;
	//core game bgm
	sf::Music coreGame;
	//levelup bgm
	sf::Music levelup;
	//gameover bgm
	sf::Music gameOver;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event gameEvent;
	sf::Image windowIcon;
	Menu menu;
	Game game;
	HighScore highScore;
	EndingMenu endingMenu;
	WinningMenu winningMenu;
	Instruction instruction;
	Settings settings;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	int gameState;
	int audioState;
	int currentBGMVolume;
	int playerHighScore;
	void InitWindow();
	void InitAudio();
	void InitTexture();
	void InitVariables();
public:
	GameState();
	~GameState();
	void Start();
	void CoreGame();
	void Ending();
	void LevelUp();
	void HighScoreMenu();
	void Tutorial();
	void SettingsMenu();
	void SetVolume();
	void StartGame();
	void CheckGameState();
	void SetGameStatus(int currentGameStatus);
	int GetGameStatus();
};

