#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
#define maxTextItem 2
class HighScore
{
private:
	sf::Sound button;
	sf::SoundBuffer buttonBuffer;
	sf::Font font;
	sf::Text text[maxTextItem];
	sf::Text highScore;
	float temp;
	int currentIndex;
	int currentHighScore;
	int currentHighestLevel;
	bool isButtonPressed;
	void InitVariables();
	void InitText();
	void InitAudio();
public:
	HighScore();
	~HighScore();
	int getPressedItem();
	bool IsButtonPressed();
	void GetBool(bool isPlayIsPressed);
	void MoveLeft();
	void MoveRight();
	void GetHighScore();
	void ResetHighScore();
	void Draw(sf::RenderTarget* target);
	void HighScoreText(int playerHighScore, int highestLevel);
	void Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event);
	void RenderWindow(sf::RenderTarget* target);
	void EventInput(sf::RenderWindow& window, sf::Event event);
	void TextButtonPressed(sf::RenderWindow& window, sf::Event event);
};

