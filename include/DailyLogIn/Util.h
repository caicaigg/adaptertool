#pragma once

#include <fstream>
#include <unordered_map>
#include <iostream>



class Util
{
public:
	Util(std::string FilePath);
	~Util();

	std::ofstream& Stream();
	std::ofstream& operator<<(std::string str);
private:

	std::ofstream *_stream;
	std::unordered_map<std::string, std::ofstream> _hashStream;
	std::string _filePath;
};

