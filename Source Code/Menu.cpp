#include "Menu.h"
Menu::Menu()
{
	this->InitVariables();
	this->InitFont();
	this->InitText();
	this->InitAudio();
}
Menu::~Menu()
{

}
void Menu::InitAudio() {
	this->button.setBuffer(buttonBuffer);
	if (!buttonBuffer.loadFromFile("Audio\\click.wav")) {
		return;
	}
}
void Menu::InitVariables() {
	this->currentIndex = 0;
	this->temp = 0;
	this->isButtonPressed = false;
}
void Menu::InitFont() {
	font.loadFromFile("Absolute Xero.otf");
	for (int i = 0; i < maxItems; i++)
	{
		buttonText[i].setFont(font);
	}
	titleText.setFont(font);
}
void Menu::InitText() {
	buttonText[0].setPosition(255, 175);
	buttonText[1].setPosition(170, 250);
	buttonText[2].setPosition(185, 325);
	buttonText[3].setPosition(205, 400);
	buttonText[4].setPosition(260, 475);
	titleText.setPosition(10, 75);
	titleText.setCharacterSize(45);
	titleText.setFillColor(sf::Color::Green);
	buttonText[0].setString("Play");
	buttonText[0].setFillColor(sf::Color::Red);
	buttonText[1].setFillColor(sf::Color::Magenta);
	buttonText[2].setFillColor(sf::Color::Magenta);
	buttonText[3].setFillColor(sf::Color::Magenta);
	buttonText[4].setFillColor(sf::Color::Magenta);
	buttonText[1].setString("Instruction");
	buttonText[2].setString("HighScore");
	buttonText[3].setString("Settings");
	buttonText[4].setString("Exit");
	titleText.setString("World Of Tanks");
}
int Menu::getPressedItem() {
	return currentIndex;
}
bool Menu::IsButtonPressed() {
	return isButtonPressed;
}
void Menu::GetBool(bool isPlayIsPressed) {
	this->isButtonPressed = isPlayIsPressed;
}
void Menu::Draw(sf::RenderTarget* target)
{
	target->draw(titleText);
	for (int i = 0; i < maxItems; i++)
	{
		target->draw(buttonText[i]);
	}
}
void Menu::Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event) {
	this->EventInput(window, event);
	this->RenderWindow(target);
}
void Menu::RenderWindow(sf::RenderTarget* target) {
	this->Draw(target);
}
void Menu::MoveDown() {
	if (currentIndex + 1 < maxItems) {
		currentIndex++;
		this->button.play();
		buttonText[currentIndex - 1].setFillColor(sf::Color::Magenta);
		buttonText[currentIndex].setFillColor(sf::Color::Red);
	}
}
void Menu::MoveUp() {
	if (currentIndex > 0) {
		this->button.play();
		currentIndex--;
		buttonText[currentIndex + 1].setFillColor(sf::Color::Magenta);
		buttonText[currentIndex].setFillColor(sf::Color::Red);
	}
}
void Menu::EventInput(sf::RenderWindow& window, sf::Event event) {
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::S:
				MoveDown();
				break;
			case sf::Keyboard::W:
				MoveUp();
				break;
			case sf::Keyboard::Space:
				this->button.play();
				switch (getPressedItem())
				{
				case 0:
					this->StartTheGame();
					break;
				case 1:
					this->isButtonPressed = true;
					cout << "Instruction" << endl;
					break;
				case 2:
					this->isButtonPressed = true;
					cout << "HighScore" << endl;
					break;
				case 3:
					this->isButtonPressed = true;
					cout << "Settings" << endl;
					break;
				case 4:
					window.close();
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
void Menu::TextButtonPressed(sf::RenderWindow& window, sf::Event event) {
	for (int i = 0; i < maxItems; i++)
	{
		if (buttonText[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
			string buttonName = this->buttonText[i].getString();
			cout << buttonName << " is pressed" << endl;
			this->button.play();
			this->currentIndex = i;
			cout << currentIndex << endl;
			this->isButtonPressed = true;
		}
	}
}
void Menu::StartTheGame() {
	this->isButtonPressed = true;
	cout << "Play" << endl;
}