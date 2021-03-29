/*
* BorderRemovalCommandParser.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#include "BorderRemovalCommandParser/BorderRemovalCommandParser.h"

//C++ libraries
#include <algorithm>

//Local Libraries
#include "ParseUtils/ParseUtils.h"

BorderRemovalCommandParser::BorderRemovalCommandParser()
{
}

BorderRemovalCommandParser::BorderRemovalParsedData BorderRemovalCommandParser::parseCommand(int numberOfArguments, char *arguments[])
{
	//Arguments should comply the following format
	//#1 input image path
	//#2 border R code 8bit (0-255)
	//#3 border G code 8bit (0-255)
	//#4 border B code 8bit (0-255)
	//#5 output image path

	//NOTE: [Jaime] input and output must comply with the same extension

	BorderRemovalParsedData parsedData;
	parsedData.parsingStatus = BRCPS_VALID;

	static const int validNumberOfArguments = 6; //first argument is always the name of the application
	if(numberOfArguments < validNumberOfArguments)
	{
		parsedData.parsingStatus = BRCPS_INVALID;
		return parsedData;
	}

	static std::vector<std::string> supportedExtensions = { "PNG", "JPG" };

	std::string inputPath = std::string(arguments[1]);
	std::string borderRed = std::string(arguments[2]);
	std::string borderGreen = std::string(arguments[3]);
	std::string borderBlue = std::string(arguments[4]);
	std::string outputPath = std::string(arguments[5]);

	std::string inputExtension = ParseUitls::getPathExtension(inputPath);
	std::transform(inputExtension.begin(), inputExtension.end(), inputExtension.begin(), ::toupper);
	std::string outputExtension = ParseUitls::getPathExtension(outputPath);
	std::transform(outputExtension.begin(), outputExtension.end(), outputExtension.begin(), ::toupper);

	if((inputExtension != outputExtension) 
		|| std::find(supportedExtensions.begin(), supportedExtensions.end(), inputExtension) == supportedExtensions.end()
		|| std::find(supportedExtensions.begin(), supportedExtensions.end(), outputExtension) == supportedExtensions.end())
	{
		parsedData.parsingStatus = BRCPS_INVALID;
		return parsedData;
	}


	long long borderRedValue = 0;
	bool rgbCodeValid = ParseUitls::stringToNumber(borderRed, borderRedValue);
	long long borderGreenValue = 0;
	rgbCodeValid |= ParseUitls::stringToNumber(borderGreen, borderGreenValue);
	long long borderBlueValue = 0;
	rgbCodeValid |= ParseUitls::stringToNumber(borderBlue, borderBlueValue);

	if(!rgbCodeValid 
		|| (borderRedValue < 0 || borderRedValue > 255)
		|| (borderGreenValue < 0 || borderGreenValue > 255)
		|| (borderBlueValue < 0 || borderBlueValue > 255))
	{
		parsedData.parsingStatus = BRCPS_INVALID;
		return parsedData;
	}

	parsedData.inputPath = inputPath;
	parsedData.outputPath = outputPath;

	if(inputExtension == std::string("PNG"))
	{
		parsedData.fileType = ImageExtensions::IFT_PNG;
	}
	else if(inputExtension == std::string("JPG"))
	{
		parsedData.fileType = ImageExtensions::IFT_JPEG;
	}

	parsedData.borderR = static_cast<unsigned char>(borderRedValue);
	parsedData.borderG = static_cast<unsigned char>(borderGreenValue);
	parsedData.borderB = static_cast<unsigned char>(borderBlueValue);

	return parsedData;
}
