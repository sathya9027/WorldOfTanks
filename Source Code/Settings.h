#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
#define maxTextItem 4
#define maxVolumeText 2
class Settings
{
private:
	sf::Sound button;
	sf::SoundBuffer buttonBuffer;
	sf::Font font;
	sf::Text settingsText;
	sf::Text text[maxTextItem];
	sf::Text volumeText[maxVolumeText];
	sf::RectangleShape rightArrow[maxVolumeText];
	sf::RectangleShape leftArrow[maxVolumeText];
	sf::Texture rightArrowTexture;
	sf::Texture leftArrowTexture;
	float temp;
	int currentIndex;
	int currentBGMVolume;
	int currentSFXVolume;
	bool isButtonPressed;
	void InitVariables();
	void InitText();
	void InitAudio();
	void InitTexture();
public:
	Settings();
	~Settings();
	int getPressedItem();
	bool IsButtonPressed();
	void GetBool(bool isPlayIsPressed);
	void MoveDown();
	void MoveUp();
	void GetVolume();
	void SetVolume();
	void ResetVolume();
	void IncreaseVolume();
	void DecreaseVolume();
	void Draw(sf::RenderTarget* target);
	void VolumeText(int bgmVolume, int sfxVolume);
	void Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event);
	void RenderWindow(sf::RenderTarget* target);
	void EventInput(sf::RenderWindow& window, sf::Event event);
	void TextButtonPressed(sf::RenderWindow& window, sf::Event event);
};

