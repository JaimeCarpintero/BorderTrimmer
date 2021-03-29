/*
* ImageUtils.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

//C++ libraries
#include <memory>
#include <string>

//Local libraries
#include "ImageUtils/ImageData.h"

namespace ImageExtensions
{
	enum ImageFileType
	{
		IFT_UNSUPORTED,
		IFT_PNG,
		IFT_JPEG
	};
}

namespace ImageUtils
{
	namespace Loader
	{
		/// \brief ImageLoader a wrapper class that uses the stb library to load JPEG/PNG images
		class ImageLoader
		{
		public:
			/// \brief loadImage loads and image and places its data into an ImageData entity
			/// \param imagePath an std::string that holds the filepath of the image to be loaded
			/// \returns a \ref std::shared_ptr<ImageData<unsigned char>> that points to ImageData entity see class description for an in depth description
			///
			static std::shared_ptr<ImageData<unsigned char>> loadImage(std::string &imagePath);
		};		
	}
	
	namespace Writer
	{
		///\brief ImageWriter  a wrapper class that uses the stb library to write JPEG/PNG images
		class ImageWriter
		{
		public:
			/// \brief writeImage writes the contents of an image in the desired filepath
			/// \param an std::string that holds the filepath of the image to be written
			/// \param an ImageData<unsigned char> pointer that points to an entity that holds the data to be written
			/// \param ImageExtensions::ImageFileType the file type in which the image will be saved
			/// returns a bool that indicates if the image was saved sucessfully or if an error was encontured
			///
			static bool writeImage(std::string &imagePath,
								   ImageData<unsigned char> *imageData,
								   ImageExtensions::ImageFileType filetype);
		};
	}
}

#endif // !IMAGE_UTILS_H