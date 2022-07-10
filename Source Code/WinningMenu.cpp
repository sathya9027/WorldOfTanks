#include "WinningMenu.h"
WinningMenu::WinningMenu() {
	this->InitVariables();
	this->InitFont();
	this->InitText();
	this->InitAudio();
}
WinningMenu::~WinningMenu() {

}
void WinningMenu::InitAudio() {
	this->button.setBuffer(buttonBuffer);
	if (!buttonBuffer.loadFromFile("Audio\\click.wav")) {
		return;
	}
}
void WinningMenu::InitVariables() {
	currentIndex = 0;
	temp = 0;
	this->isButtonPressed = false;
}
void WinningMenu::InitFont() {
	font.loadFromFile("Absolute Xero.otf");
	for (int i = 0; i < maxItem; i++)
	{
		text[i].setFont(font);
	}
	levelCompletedText.setFont(font);
}
void WinningMenu::InitText() {
	text[0].setPosition(250, 250);
	text[1].setPosition(175, 350);
	text[0].setString("Next");
	text[0].setFillColor(sf::Color::Red);
	text[1].setFillColor(sf::Color::Magenta);
	text[1].setString(" Main Menu");
	levelCompletedText.setString("Level Completed");
	levelCompletedText.setPosition(80, 100);
	levelCompletedText.setFillColor(sf::Color::Green);
}
int WinningMenu::GetIndex() {
	return currentIndex;
}
bool WinningMenu::IsButtonPressed() {
	return isButtonPressed;
}
void WinningMenu::Draw(sf::RenderTarget* target)
{
	for (int i = 0; i < maxItem; i++)
	{
		target->draw(text[i]);
	}
	target->draw(levelCompletedText);
}
void WinningMenu::RenderWindow(sf::RenderTarget* target) {
	this->Draw(target);
}
void WinningMenu::MoveDown() {
	if (currentIndex + 1 < maxItem) {
		currentIndex++;
		this->button.play();
		text[currentIndex - 1].setFillColor(sf::Color::Magenta);
		text[currentIndex].setFillColor(sf::Color::Red);
	}
}
void WinningMenu::MoveUp() {
	if (currentIndex > 0) {
		this->button.play();
		currentIndex--;
		text[currentIndex + 1].setFillColor(sf::Color::Magenta);
		text[currentIndex].setFillColor(sf::Color::Red);
	}
}
void WinningMenu::Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event) {
	this->EventInput(window, event);
	this->RenderWindow(target);
}
void WinningMenu::SetButtonPressed(bool isButtonPressed) {
	this->isButtonPressed = isButtonPressed;
}
void WinningMenu::TextButtonPressed(sf::RenderWindow& window, sf::Event event) {
	for (int i = 0; i < maxItem; i++)
	{
		if (text[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
			string buttonName = this->text[i].getString();
			cout << buttonName << " is pressed" << endl;
			this->button.play();
			this->currentIndex = i;
			cout << currentIndex << endl;
			this->isButtonPressed = true;
		}
	}
}
void WinningMenu::EventInput(sf::RenderWindow& window, sf::Event event) {
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::S:
				MoveDown();
				break;
			case sf::Keyboard::W:
				MoveUp();
				break;
			case sf::Keyboard::Space:
				this->button.play();
				switch (GetIndex())
				{
				case 0:
					this->isButtonPressed = true;
					cout << "Play Again" << endl;
					break;
				case 1:
					this->isButtonPressed = true;
					cout << "Main Menu" << endl;
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