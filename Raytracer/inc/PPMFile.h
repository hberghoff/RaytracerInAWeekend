#pragma once
#include <vector>
#include <string>

class PPMFile
{
public:
	PPMFile(const std::size_t width, const std::size_t height);
	void AddNewPixel(const float r, const float g, const float b);
	void Write(const std::string& filename);
	void WriteBinary(const std::string& filename);
private:
	std::vector<int> _pixels;
	std::size_t _currentElement;
	const std::size_t _width, _height, _dim;
};