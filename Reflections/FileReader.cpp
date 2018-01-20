#include "FileReader.h"

reflections::FileReader::FileReader(std::string path) {
	this->path = path;
	eof = false;
}

bool reflections::FileReader::open() {
	file.open(path);
	return file.good();
}

bool reflections::FileReader::close() {
	file.close();
	return file.good();
}

//Read the next line as long as there's lines available.
//Ignore any lines that start with //
bool reflections::FileReader::nextLine() {
	while (!eof) {
		eof = std::getline(file, currentLine).eof();
		if (!currentLine.empty() && currentLine.substr(0, 2).compare("//") != 0) {
			return true;
		}
	}
	return false;
}

std::string reflections::FileReader::getCurrentLine() {
	return currentLine;
}

std::ifstream & reflections::FileReader::getFile() {
	return file;
}

//Start stream from the start again.
void reflections::FileReader::rewind() {
	file.clear();
	file.seekg(0);
	eof = false;
}

int reflections::FileReader::getPos() {
	return file.tellg();
}

void reflections::FileReader::setPos(int pos) {
	file.clear();
	file.seekg(pos);
	eof = false;
}

