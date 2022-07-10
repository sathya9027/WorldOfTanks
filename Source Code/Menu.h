#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#define maxItems 5
class Menu
{
private:
	sf::Sound button;
	sf::SoundBuffer buttonBuffer;
	sf::Font font;
	sf::Text buttonText[maxItems];
	sf::Text titleText;
	float temp;
	int currentIndex;
	bool isButtonPressed;
	void InitVariables();
	void InitFont();
	void InitText();
	void InitAudio();
public:
	Menu();
	~Menu();
	int getPressedItem();
	bool IsButtonPressed();
	void GetBool(bool isPlayIsPressed);
	void Draw(sf::RenderTarget* target);
	void Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event);
	void RenderWindow(sf::RenderTarget* target);
	void EventInput(sf::RenderWindow& window, sf::Event event);
	void StartTheGame();
	void MoveDown();
	void MoveUp();
	void TextButtonPressed(sf::RenderWindow& window, sf::Event event);
};