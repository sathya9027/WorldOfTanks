#include "Instruction.h"
Instruction::Instruction() {
	this->InitVariables();
	this->InitText();
	this->InitFont();
	this->InitTexture();
	this->InitRect();
	this->InitAudio();
}
Instruction::~Instruction() {

}
void Instruction::InitAudio() {
	this->button.setBuffer(buttonBuffer);
	if (!buttonBuffer.loadFromFile("Audio\\click.wav")) {
		return;
	}
}
void Instruction::InitVariables() {
	currentIndex = 0;
	temp = 0;
	this->isButtonPressed = false;
}
void Instruction::InitText() {
	iconText.setString("player                 enemy               health   shield");
	iconText.setPosition(sf::Vector2f(80, 350));
	iconText.setFillColor(sf::Color::Green);
	iconText.setCharacterSize(15);
	text.setPosition(460, 550);
	text.setString("Back");
	text.setFillColor(sf::Color::Red);
	stringstream istream;
	istream << "\Press  'W/D/S/A'  to  move  \nthe  player" << endl;
	istream << "\ " << endl;
	istream << "\Press  'Space'  to  \nselect  options" << endl;
	istream << "\ " << endl;
	istream << "\Press  'Left  Mouse  Button'  \nto  shoot  shells" << endl;
	istream << "\ " << endl;
	istream << "\Press  'Esc'  to  \nexit  the  game" << endl;
	istream << "\ " << endl;
	this->instructionText.setFillColor(sf::Color::Green);
	this->instructionText.setCharacterSize(17.5);
	this->instructionText.setString(istream.str());
	this->instructionText.setPosition(20, 0);
}
void Instruction::InitFont() {
	font.loadFromFile("Absolute Xero.otf");
	text.setFont(font);
	this->instructionText.setFont(font);
	this->iconText.setFont(font);
}
void Instruction::InitTexture() {
	iconTexture[0].loadFromFile("Image\\Tank_Big_Yellow.png");
	iconTexture[1].loadFromFile("Image\\Tank_Brown.png");
	iconTexture[2].loadFromFile("Image\\MilitaryTruck.png");
	iconTexture[3].loadFromFile("Image\\heart-Element.png");
	iconTexture[4].loadFromFile("Image\\Rect-element.png");
}
void Instruction::InitRect() {
	icons[0].setSize(sf::Vector2f(64, 97));
	icons[1].setSize(sf::Vector2f(67, 108));
	icons[2].setSize(sf::Vector2f(73.0f, 137.0f));
	icons[3].setSize(sf::Vector2f(100, 100));
	icons[4].setSize(sf::Vector2f(100, 100));
	for (int i = 0; i < maxTextItem; i++)
	{
		temp += 100;
		icons[i].setPosition(temp, 400);
	}
	for (int i = 0; i < maxTextItem; i++)
	{
		icons[i].setTexture(&iconTexture[i]);
	}
}
int Instruction::getPressedItem() {
	return currentIndex;
}
bool Instruction::IsButtonPressed() {
	return isButtonPressed;
}
void Instruction::GetBool(bool isPlayIsPressed) {
	this->isButtonPressed = isPlayIsPressed;
}
void Instruction::Draw(sf::RenderTarget* target)
{
	for (int i = 0; i < maxTextItem; i++)
	{
		target->draw(icons[i]);
	}
	target->draw(iconText);
	target->draw(text);
	target->draw(instructionText);
}
void Instruction::Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event) {
	this->EventInput(window, event);
	this->RenderWindow(target);
}
void Instruction::RenderWindow(sf::RenderTarget* target) {
	this->Draw(target);
}
void Instruction::EventInput(sf::RenderWindow& window, sf::Event event) {
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::Space:
				this->button.play();
				switch (getPressedItem())
				{
				case 0:
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

void Instruction::TextButtonPressed(sf::RenderWindow& window, sf::Event event) {
	if (text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
		string buttonName = this->text.getString();
		cout << buttonName << " is pressed" << endl;
		this->button.play();
		this->currentIndex = 0;
		this->isButtonPressed = true;
	}
}