#pragma once
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
#define maxTextItem 5
class Instruction
{
private:
	sf::Sound button;
	sf::SoundBuffer buttonBuffer;
	sf::Font font;
	sf::Text text;
	sf::Text iconText;
	sf::Text instructionText;
	sf::RectangleShape icons[maxTextItem];
	sf::Texture iconTexture[maxTextItem];
	float temp;
	int currentIndex;
	bool isButtonPressed;
	void InitVariables();
	void InitText();
	void InitFont();
	void InitRect();
	void InitTexture();
	void InitAudio();
public:
	Instruction();
	~Instruction();
	int getPressedItem();
	bool IsButtonPressed();
	void GetBool(bool isPlayIsPressed);
	void Draw(sf::RenderTarget* target);
	void Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event);
	void RenderWindow(sf::RenderTarget* target);
	void EventInput(sf::RenderWindow& window, sf::Event event);
	void TextButtonPressed(sf::RenderWindow& window, sf::Event event);
};

