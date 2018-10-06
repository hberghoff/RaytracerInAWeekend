#include "..\inc\PPMFile.h"
#include <fstream>

static const int maxColor = 255;
static const std::string extention = ".ppm";
static const std::string ASCII_MAGIC_NUMBER = "P3";

PPMFile::PPMFile(const std::size_t width, const std::size_t height) : _currentElement(0), _pixels(width * height * 3, 0), _width(width), _height(height), _dim(width * height)
{
}

void PPMFile::AddNewPixel(const float r, const float g, const float b)
{
	if (_currentElement < _dim)
	{
		const std::size_t pixelOffset = _currentElement * 3;
		_currentElement++;
		_pixels[pixelOffset + 0] = static_cast<int>(255.99 * r);
		_pixels[pixelOffset + 1] = static_cast<int>(255.99 * g);
		_pixels[pixelOffset + 2] = static_cast<int>(255.99 * b);
	}
}

void PPMFile::Write(const std::string & filename)
{
	std::ofstream write(filename + extention);
	// header information about the file
	write << ASCII_MAGIC_NUMBER << "\n" << _width << " " << _height << '\n' << maxColor << std::endl;
	// pixel information
	const std::size_t size = _pixels.size();
	for (std::size_t i = 0; i < size; i += 3)
	{
		write << _pixels[i + 0] << " " << _pixels[i + 1] << " " << _pixels[i + 2] << std::endl;
	}
}

// Todo
void PPMFile::WriteBinary(const std::string & filename)
{
	std::ofstream write(filename + extention, std::ios::out | std::ios::binary);
	// header information about the file
	//write << ASCII_MAGIC_NUMBER << "\n" << _width << " " << _height << '\n' << maxColor << std::endl;
	// pixel information
	/*const std::size_t size = _pixels.size();
	for (std::size_t i = 0; i < size; i += 3)
	{
		write << _pixels[i + 0] << " " << _pixels[i + 1] << " " << _pixels[i + 2] << std::endl;
	}*/
}
