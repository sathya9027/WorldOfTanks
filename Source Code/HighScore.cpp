#include "HighScore.h"
HighScore::HighScore() {
	this->InitVariables();
	this->InitAudio();
	this->InitText();
}
HighScore::~HighScore() {

}
void HighScore::InitText() {
	font.loadFromFile("Absolute Xero.otf");
	for (int i = 0; i < maxTextItem; i++)
	{
		text[i].setFont(font);
	}
	text[0].setPosition(100, 350);
	text[1].setPosition(145 * 3 - 50, 350);
	text[0].setString("Reset");
	text[0].setFillColor(sf::Color::Red);
	text[1].setString("Back");
	text[1].setFillColor(sf::Color::Magenta);
	this->highScore.setFont(font);
	this->highScore.setPosition(105, 150);
}
void HighScore::InitAudio() {
	this->button.setBuffer(buttonBuffer);
	if (!buttonBuffer.loadFromFile("Audio\\click.wav")) {
		return;
	}
}
void HighScore::InitVariables() {
	currentIndex = 0;
	temp = 0;
	this->isButtonPressed = false;
}
int HighScore::getPressedItem() {
	return currentIndex;
}
bool HighScore::IsButtonPressed() {
	return isButtonPressed;
}
void HighScore::GetBool(bool isPlayIsPressed) {
	this->isButtonPressed = isPlayIsPressed;
}
void HighScore::MoveLeft() {
	if (currentIndex > 0) {
		currentIndex--;
		this->button.play();
		text[currentIndex + 1].setFillColor(sf::Color::Magenta);
		text[currentIndex].setFillColor(sf::Color::Red);
	}
}
void HighScore::MoveRight() {
	if (currentIndex + 1 < maxTextItem) {
		currentIndex++;
		this->button.play();
		text[currentIndex - 1].setFillColor(sf::Color::Magenta);
		text[currentIndex].setFillColor(sf::Color::Red);
	}
}
void HighScore::GetHighScore() {
	ifstream readFile;
	ifstream readLevelFile;
	readFile.open("HighScore.txt");
	readLevelFile.open("HighestLevel.txt");
	if (readFile.is_open() && readLevelFile.is_open()) {
		while (!readFile.eof() && !readLevelFile.eof())
		{
			readFile >> currentHighScore;
			readLevelFile >> currentHighestLevel;
			this->HighScoreText(currentHighScore, currentHighestLevel);
		}
	}
	readFile.close();
	readLevelFile.close();
}
void HighScore::ResetHighScore() {
	ofstream writeFile("HighScore.txt");
	ofstream writeLevelFile("HighestLevel.txt");
	if (writeFile.is_open() && writeLevelFile.is_open()) {
		writeFile << 0;
		writeLevelFile << 0;
	}
	writeFile.close();
	writeLevelFile.close();
}
void HighScore::Draw(sf::RenderTarget* target)
{
	for (int i = 0; i < maxTextItem; i++)
	{
		target->draw(text[i]);
	}
	target->draw(highScore);
}
void HighScore::HighScoreText(int playerHighScore, int highestLevel) {
	this->highScore.setFillColor(sf::Color::Green);
	this->highScore.setString("HighScore: " + to_string(playerHighScore) + "\nHighest Level: " + to_string(highestLevel));
}
void HighScore::Update(sf::RenderTarget* target, sf::RenderWindow& window, sf::Event event) {
	this->EventInput(window, event);
	this->GetHighScore();
	this->RenderWindow(target);
}
void HighScore::RenderWindow(sf::RenderTarget* target) {
	this->Draw(target);
}
void HighScore::TextButtonPressed(sf::RenderWindow& window, sf::Event event) {
	for (int i = 0; i < maxTextItem; i++)
	{
		if (text[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
			string buttonName = this->text[i].getString();
			cout << buttonName << " is pressed" << endl;
			this->button.play();
			this->currentIndex = i;
			cout << currentIndex << endl;
			if (i == 0) {
				this->ResetHighScore();
			}
			this->isButtonPressed = true;
		}
	}
}
void HighScore::EventInput(sf::RenderWindow& window, sf::Event event) {
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::D:
				MoveRight();
				break;
			case sf::Keyboard::A:
				MoveLeft();
				break;
			case sf::Keyboard::Space:
				this->button.play();
				switch (getPressedItem())
				{
				case 0:
					this->ResetHighScore();
					break;
				case 1:
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