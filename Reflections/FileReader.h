#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace reflections {

	//Simple file reader class which handles opening and closing of files using a string path.
	class FileReader {
	private:
		std::ifstream file;
		std::string path;
		std::string currentLine;
		bool eof;
	public:
		FileReader(std::string path);
		bool open();
		bool close();
		bool nextLine();
		std::string getCurrentLine();
		std::ifstream & getFile();

		//Set location in the file stream
		void rewind();
		int getPos();
		void setPos(int pos);
	};
}