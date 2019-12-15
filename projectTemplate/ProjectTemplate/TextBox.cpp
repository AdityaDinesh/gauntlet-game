#include "GameCore.h"
#include "TextBox.h"

// Make sure font is passed by reference:
void Textbox::setFont(sf::Font& fonts) {
	textbox.setFont(fonts);
}

void Textbox::setPosition(sf::Vector2f point) {
	textbox.setPosition(point);
}

// Set char limits:
void Textbox::setLimit(bool ToF) {
	hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim) {
	hasLimit = ToF;
	limit = lim - 1;
}

std::string Textbox::getText() {
	return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window) {
	window.draw(textbox);
}

