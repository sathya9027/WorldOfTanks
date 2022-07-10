#include "Settings.h"
Settings::Settings() {
	this->InitVariables();
	this->InitAudio();
	this->InitText();
	this->InitTexture();
}
Settings::~Settings() {

}
void Settings::InitTexture() {
	this->rightArrowTexture.loadFromFile("Image\\right arrow.png");
	this->leftArrowTexture.loadFromFile("Image\\left arrow.png");
	for (int i = 0; i < maxVolumeText; i++)
	{
		this->rightArrow[i].setTexture(&rightArrowTexture);
		this->leftArrow[i].setTexture(&leftArrowTexture);
		this->rightArrow[i].setPosition(510, temp);
		this->leftArrow[i].setPosition(400, temp);
		temp += 100;
		this->rightArrow[i].setSize(sf::Vector2f(50, 50));
		this->leftArrow[i].setSize(sf::Vector2f(50, 50));
	}
	this->rightArrow[0].setFillColor(sf::Color::Magenta);
	this->rightArrow[1].setFillColor(sf::Color::Magenta);
	this->leftArrow[0].setFillColor(sf::Color::Red);
	this->leftArrow[1].setFillColor(sf::Color::Red);
}
void Settings::InitText() {
	font.loadFromFile("Absolute Xero.otf");
	for (int i = 0; i < maxTextItem; i++)
	{
		text[i].setFont(font);
	}
	settingsText.setFont(font);
	settingsText.setPosition(200, 75);
	text[0].setPosition(75, 190);
	text[1].setPosition(75, 290);
	text[2].setPosition(75, 390);
	text[3].setPosition(75, 490);
	settingsText.setString("Settings");
	settingsText.setFillColor(sf::Color::Green);
	text[0].setString("BGM Volume");
	text[0].setFillColor(sf::Color::Red);
	text[1].setString("SFX Volume");
	text[1].setFillColor(sf::Color::Magenta);
	text[2].setString("Restore Default");
	text[2].setFillColor(sf::Color::Magenta);
	text[3].setString("Back");
	text[3].setFillColor(sf::Color::Magenta);
	this->volumeText[0].setFont(font);
	this->volumeText[0].setPosition(450, 190);
	this->volumeText[1].setFont(font);
	this->volumeText[1].setPosition(450, 290);
}
void Settings::InitAudio() {
	this->button.setBuffer(buttonBuffer);
	if (!buttonBuffer.loadFromFile("Audio\\click.wav")) {
		return;
	}
}
void Settings::InitVariables() {
	currentBGMVolume = 0;
	currentSFXVolume = 0;
	currentIndex = 0;
	temp = 145 + 40;
	this->isButtonPressed = false;
}
int Settings::getPressedItem() {
	return currentIndex;
}
bool Settings::IsButtonPressed() {
	return isButtonPressed;
}
void Settings::GetBool(bool isPlayIsPressed) {
	this->isButtonPressed = isPlayIsPressed;
}
void Settings::MoveDown() {
	if (currentIndex > 0) {
		this->button.play();
		currentIndex--;
		text[currentIndex + 1].setFillColor(sf::Color::Magenta);
		text[currentIndex].setFillColor(sf::Color::Red);
	}
}
void Settings::MoveUp() {
	if (currentIndex + 1 < maxTextItem) {
		currentIndex++;
		this->button.play();
		text[currentIndex - 1].setFillColor(sf::Color::Magenta);
		text[currentIndex].setFillColor(sf::Color::Red);
	}
}
void Settings::GetVolume() {
	ifstream readFile;
	ifstream readLevelFile;
	readFile.open("BGMVolume.txt");
	readLevelFile.open("SFXVolume.txt");
	if (readFile.is_open() && readLevelFile.is_open()) {
		while (!readFile.eof() && !readLevelFile.eof())
		{
			readFile >> currentBGMVolume;
			readLevelFile >> currentSFXVolume;
			this->VolumeText(currentBGMVolume, currentSFXVolume);
		}
	}
	readFile.close();
	readLevelFile.close();
}
void Settings::SetVolume() {
	ofstream writeFile("BGMVolume.txt");
	ofstream writeLevelFile("SFXVolume.txt");
	if (writeFile.is_open() && writeLevelFile.is_open()) {
		writeFile << currentBGMVolume;
		writeLevelFile << currentSFXVolume;
	}
	writeFile.close();
	writeLevelFile.close();
}
void Settings::ResetVolume() {
	ofstream writeFile("BGMVolume.txt");
	ofstream writeLevelFile("SFXVolume.txt");
	if (writeFile.is_open() && writeLevelFile.is_open()) {
		writeFile << 15;
		writeLevelFile << 50;
	}
	writeFile.close();
	writeLevelFile.close();
}
void Settings::Draw(sf::RenderTarget* target)
{
	for (int i = 0; i < maxTextItem; i++)
	{
		target->draw(text[i]);
	}
	for (int i = 0; i < maxVolumeText; i++)
	{
		target->draw(volumeText[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		target->draw(this->rightArrow[i]);
		target->draw(this->leftArrow[i]);
	}
	target->draw(settingsText);
}
void Settings::VolumeText(int bgmVolume, int sfxVolume) {
	this->volumeText[0].setFillColor(sf::Color::Green);
	this->volumeText[0].setString(to_string(bgmVolume));
	this->volumeText[1].setFillColor(sf::Color::Green);
	this->volumeText[1].setString(to_string(sfxVolume));
}
void Settings::Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event) {
	this->EventInput(window, event);
	this->GetVolume();
	this->RenderWindow(target);
}
void Settings::RenderWindow(sf::RenderTarget* target) {
	this->Draw(target);
}
void Settings::IncreaseVolume() {
	if (getPressedItem() == 0) {
		if (currentBGMVolume < 100) {
			currentBGMVolume += 5;
			this->button.play();
		}
		this->rightArrow[0].setFillColor(sf::Color::Red);
		this->leftArrow[0].setFillColor(sf::Color::Magenta);
	}
	else if (getPressedItem() == 1) {
		if (currentSFXVolume < 100) {
			currentSFXVolume += 5;
			this->button.play();
		}
		this->rightArrow[1].setFillColor(sf::Color::Red);
		this->leftArrow[1].setFillColor(sf::Color::Magenta);
	}
	this->SetVolume();
}
void Settings::DecreaseVolume() {
	if (getPressedItem() == 0) {
		if (currentBGMVolume > 0) {
			currentBGMVolume -= 5;
			this->button.play();
		}
		this->rightArrow[0].setFillColor(sf::Color::Magenta);
		this->leftArrow[0].setFillColor(sf::Color::Red);
	}
	else if (getPressedItem() == 1) {
		if (currentSFXVolume >= 0) {
			currentSFXVolume -= 5;
			this->button.play();
		}
		this->rightArrow[1].setFillColor(sf::Color::Magenta);
		this->leftArrow[1].setFillColor(sf::Color::Red);
	}
	this->SetVolume();
}
void Settings::TextButtonPressed(sf::RenderWindow& window, sf::Event event) {
	for (int i = 0; i < maxTextItem; i++)
	{
		if (text[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
			string buttonName = this->text[i].getString();
			cout << buttonName << " is pressed" << endl;
			this->button.play();
			this->currentIndex = i;
			cout << currentIndex << endl;
			if (i == 2) {
				this->ResetVolume();
			}
			this->isButtonPressed = true;
		}
	}
	for (int i = 0; i < maxVolumeText; i++)
	{
		if (leftArrow[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
			this->button.play();
			this->currentIndex = i;
			DecreaseVolume();
		}
	}
	for (int i = 0; i < maxVolumeText; i++)
	{
		if (rightArrow[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
			this->button.play();
			this->currentIndex = i;
			this->IncreaseVolume();
		}
	}
}
void Settings::EventInput(sf::RenderWindow& window, sf::Event event) {
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::W:
				MoveDown();
				break;
			case sf::Keyboard::S:
				MoveUp();
				break;
			case sf::Keyboard::A:
				DecreaseVolume();
				break;
			case sf::Keyboard::D:
				IncreaseVolume();
				break;
			case sf::Keyboard::Space:
				this->button.play();
				switch (getPressedItem())
				{
				case 2:
					this->ResetVolume();
					break;
				case 3:
					this->isButtonPressed = true;
					break;
				}
				break;
			}
			break;
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				this->TextButtonPressed(window, event);
				break;
			}
			break;
		}
	}
}