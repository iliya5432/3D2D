#include "FileReader.h"

FileReader::FileReader(std::string fileName)
{
    ReadToStringVector(fileName, _vecOfStrings);
    _ConvertToFloat();
}

sf::Vector3f FileReader::getPoint(int triNum, int triPointNum) 
{
    switch (triPointNum)
    {
    case 0:
        return _vecOfPoints[_vecOfFaces[triNum].x - 1];
        break;
    case 1:
        return _vecOfPoints[_vecOfFaces[triNum].y - 1];
        break;
    case 2:
        return _vecOfPoints[_vecOfFaces[triNum].z - 1];
        break;
    }
}

sf::Vector3f FileReader::getPoint(int index) {
    return _vecOfPoints[index];
}

void FileReader::_ConvertToFloat() {
    for (int i = 0; i < _vecOfStrings.size(); i++) //Foreach line in string vector
    {
        std::string line = _vecOfStrings[i];
        char c;
        int p, j, k;
        float x, y, z;
        std::string sp, sj, sk;
        if (line.find_first_of("vVfF") == std::string::npos) continue;
        std::istringstream ss(line);
        ss >> c;
        switch (c)
        {
        case 'v':
        case 'V':
            ss >> x >> y >> z;
            _vecOfPoints.push_back({ x, y, z });
            break;
        case 'f':
        case 'F':
            ss >> sp >> sj >> sk;
            p = std::stof(sp); j = std::stof(sj); k = std::stof(sk);
            _vecOfFaces.push_back({ p, j, k });
            break;
        }
       
    }
}

void FileReader::ReadToStringVector(std::string fileName, std::vector<std::string>& vecOfStrs)
{
    std::ifstream in(fileName.c_str());

    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();
}

int FileReader:: sizeOfTriangles() {
    return _vecOfFaces.size();
}

int FileReader::sizeOfFile() {
    return _vecOfStrings.size();
}
int FileReader::sizeOfPoints() {
    return _vecOfPoints.size();
}