#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

#define FileReader_H
#ifdef FileReader_H
struct FileReader {
public:
	FileReader(std::string fileName);
	int sizeOfTriangles();
	int sizeOfFile();
	int sizeOfPoints();
	sf::Vector3f getPoint(int triNum, int triPointNum);
	sf::Vector3f getPoint(int index);
private:
	std::vector<std::string> _vecOfStrings;
	std::vector<sf::Vector3f> _vecOfPoints;
	std::vector<sf::Vector3i> _vecOfFaces;
	void _ConvertToFloat();
	void ReadToStringVector(std::string fileName, std::vector<std::string>& vecOfStrs);

};
#endif