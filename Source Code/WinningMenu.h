#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
#define maxItem 2
class WinningMenu
{
private:
	sf::Sound button;
	sf::SoundBuffer buttonBuffer;
	sf::Font font;
	sf::Text text[maxItem];
	sf::Text levelCompletedText;
	float temp;
	int currentIndex;
	bool isButtonPressed;
	void InitVariables();
	void InitFont();
	void InitText();
	void InitAudio();
public:
	WinningMenu();
	~WinningMenu();
	bool IsButtonPressed();
	void SetButtonPressed(bool isButtonPressed);
	int GetIndex();
	void EventInput(sf::RenderWindow& window, sf::Event event);
	void TextButtonPressed(sf::RenderWindow& window, sf::Event event);
	void Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event);
	void MoveDown();
	void MoveUp();
	void Draw(sf::RenderTarget* target);
	void RenderWindow(sf::RenderTarget* target);
};