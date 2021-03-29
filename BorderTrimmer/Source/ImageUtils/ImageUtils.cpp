/*
* ImageUtils.cpp
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#include "ImageUtils/ImageUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::shared_ptr<ImageUtils::ImageData<unsigned char>> ImageUtils::Loader::ImageLoader::loadImage(std::string& imagePath)
{
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char *inputImage = stbi_load(imagePath.c_str(), &width, &height, &channels, STBI_rgb);

	//Image has been loaded correctly
	if(width == 0 || height == 0 || channels == 0 || !inputImage)
	{
		return nullptr;
	}
	//force channels to be 3, when stb reads image, it places the real number of channels, but it is being forced to STBI_rgb aka 3
	channels = STBI_rgb;
	std::shared_ptr<ImageData<unsigned char>> image(new ImageData<unsigned char>(inputImage, width, height, channels));
	////Free reserved Image
	stbi_image_free(inputImage);
	return image;
}

bool ImageUtils::Writer::ImageWriter::writeImage(std::string& imagePath,
												 ImageData<unsigned char>* image,
												 ImageExtensions::ImageFileType filetype)
{
	int result = -1;
	switch(filetype)
	{
		case ImageExtensions::ImageFileType::IFT_PNG:
			result = stbi_write_png(imagePath.c_str(),
									image->width(),
									image->height(),
									image->channels(),
									image->data(),
									image->width() * sizeof(unsigned char) * image->channels());
		break;

		case ImageExtensions::ImageFileType::IFT_JPEG:
			result = stbi_write_jpg(imagePath.c_str(),
									image->width(),
									image->height(),
									image->channels(),
									image->data(),
									image->width() * sizeof(unsigned char) * image->channels());
		break;

		default:
		break;
	}
	return (result != 0);
}
