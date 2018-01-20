#include "TextEntity.h"
#include "World.h"

using namespace reflections;

reflections::TextEntity::TextEntity(World & world) : Entity(0, 0, world, TEXT, 1, 0, 0){
	
}


TextEntity * reflections::TextEntity::addText(std::string str, int r, int g, int b) {
	Text * text = Text::create(str, r, g, b);
	this->text.push_back(text);
	return this;
}

Text * reflections::TextEntity::getText(int index) {
	if (text.size() > index) {
		return text.at(index);
	}
	return nullptr;
}


void reflections::TextEntity::removeText(int index) {
	if (this->text.size() < index) {
		Text * removed = text[index];
		removed->destroy();
		this->text.erase(this->text.begin() + index);
	}
}


std::vector<Text*>& reflections::TextEntity::getText() {
	return text;
}

reflections::TextEntity::~TextEntity() {
	for (Text* & line : text) {
		line->destroy();
	}
	text.clear();
}
