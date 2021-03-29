/*
* Main.cpp
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

//C++ libraries
#include <iostream>

//Local libraries+
#include "BorderRemoval/LineScanBorderTrimmer.h"
#include "ImageUtils/ImageUtils.h"
#include "BorderRemovalCommandParser/BorderRemovalCommandParser.h"

int main(int argc, char* argv[])
{
	BorderRemovalCommandParser commandParser;
	BorderRemovalCommandParser::BorderRemovalParsedData parsedData = commandParser.parseCommand(argc, argv);
	if(parsedData.parsingStatus == BorderRemovalCommandParser::BorderRemovalCommandParsingStatus::BRCPS_INVALID)
	{
		std::cout << "Unable to parse command, one or more commands were supplied wrongly" << std::endl;
		std::cout << "Valid command should comply with the form: inputPath rBorderCode(0~255) gBorderCode(0~255) bBorderCode(0~255) outputPath" << std::endl;
		std::cout << "example: D:\\myFolder\\mySampleWithBorders.png 190 180 170 D:\\myFolder\\myTrimmedSample.png" << std::endl;
		std::cout << "Supported bitdepth for images is 8bpp for the moment" << std::endl;
		std::cout << "Supported image extensions are PNG and JPG" << std::endl;
		std::cout << "Aborting" << std::endl;
		return 0;
	}

	//Reading image
	std::shared_ptr<ImageUtils::ImageData<unsigned char>> image = ImageUtils::Loader::ImageLoader::loadImage(parsedData.inputPath);

	if(!image.get())
	{
		std::cout << "Image file couldn't be loaded check that image exists or compiles with the format PNG or JPEG" << std::endl;
		std::cout << "Aborting" << std::endl;
		return 0;
	}

	//Border Trimming
	std::cout << "Starting border trimming process .." << std::endl;
	LineScanBorderTimmerParameters<unsigned char> parameters;
	parameters.borderR = parsedData.borderR;
	parameters.borderG = parsedData.borderG;
	parameters.borderB = parsedData.borderB;
	parameters.originalImageWidth = image->width();
	parameters.originalImageHeight = image->height();
	parameters.imageChannels = image->channels();

	LineScanBorderTrimmer borderTrimmer;
	std::shared_ptr<unsigned char> trimmedImage = borderTrimmer.run(image->data(), &parameters);
	std::cout << "Finishing border trimming process .." << std::endl;
	//End of border trimming

	if(!trimmedImage.get())
	{
		std::cout << "Image couldn't be trimmed check that that the entire image is not the same color as the border" << "Aborting" << std::endl;
		return 0;
	}

	std::shared_ptr<ImageUtils::ImageData<unsigned char>> outputImage(new ImageUtils::ImageData<unsigned char>(trimmedImage.get(),
																	  parameters.trimmedImageWidth,
																	  parameters.trimmedImageHeight,
																	  parameters.imageChannels));

	//Saving image
	const bool wasImageWritten = ImageUtils::Writer::ImageWriter::writeImage(parsedData.outputPath, outputImage.get(), parsedData.fileType);

	if(!wasImageWritten)
	{
		std::cout << "Couldn't save image, check that the image complies with the system's format" << "Aborting" << std::endl;
		return 0;
	}

	std::cout << "Finishing application... please wait";

	return 0;
}