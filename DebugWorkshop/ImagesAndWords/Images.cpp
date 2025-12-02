#include <iostream>
#include <fstream>
#include <stdint.h>

#include <stdlib.h>		// srand, rand
#include <time.h>

struct ImageHeader
{
	char signature[4];
	uint16_t width;
	uint16_t height;
	unsigned short mode;
};

struct Image
{
	ImageHeader header;
	char* data;
};

bool WriteImage(Image* img, const char* filename)
{
	std::ofstream os(filename, std::ifstream::binary);
	if (!os)
		return false;

	// write header first
	os.write((char*)&img->header, sizeof(ImageHeader));

	// calculate image size
	uint16_t imgsize = img->header.width * img->header.height;

	// write image content
	os.write(img->data, imgsize);

	return true;
}

// i changed this func
Image* ReadImage(const char* filename)
{
	std::ifstream is(filename, std::ifstream::binary);
	if (!is)
	{
		return nullptr;
	}
		

	Image* img = new Image();
	is.read((char*)&img->header, sizeof(ImageHeader));

	size_t w = img->header.width;
	size_t h = img->header.height;

	if (w == 0 || h == 0)
	{
		delete img;
		return nullptr;
	}

	if (w > 10000 || h > 10000)
	{
		delete img;
		return nullptr;
	}

	if (h != 0 && w > SIZE_MAX / h)
	{
		delete img;
		return nullptr;
	}

	size_t imgsize = w * h;
	img->data = new char[imgsize];

	is.read(img->data, imgsize);
	if (!is)
	{
		delete[] img->data;
		delete img;
		return nullptr;
	}

	return img;
}


void FreeImage(Image* img)
{
	delete img;
}

Image *GenerateDummyImage(uint16_t width, uint16_t height)
{
	Image* img = new Image();

	// create image header
	memcpy(img->header.signature, "MAGI", 4);
	img->header.width = width;
	img->header.height = height;
	img->header.mode = 1;

	// calculate image size
	uint16_t imgsize = img->header.width * img->header.height;
	img->data = new char[imgsize];

	// generate dummy content
	srand((unsigned int)time(0));
	char* pos = img->data;
	for (int i = 0; i < imgsize; i++)
		*pos++ = rand() % 255;

	return img;
}


int main()
{
	Image *im = ReadImage("img1.magi");
	FreeImage(im);

	return 0;
}
