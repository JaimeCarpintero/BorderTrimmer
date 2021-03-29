/*
* BorderRemovalCommandParser.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef BORDER_REMOVAL_COMMAND_PARSER_H
#define BORDER_REMOVAL_COMMAND_PARSER_H

//C++ libraries
#include <string>

//Local libraries
#include "ImageUtils/ImageUtils.h"

/// \brif  BorderRemovalCommandParser serves a simple command line parser of the BorderTrimmer application
class BorderRemovalCommandParser
{
public:
	/// \brief BorderRemovalCommandParsingStatus defines a status of the parse command process
	enum BorderRemovalCommandParsingStatus
	{
		BRCPS_INVALID = 0,
		BRCPS_VALID
	};

	/// \brief BorderRemovalParsedData wraps the necessary elements that the application needs to run accordingly
	struct BorderRemovalParsedData
	{
		BorderRemovalParsedData()
			: inputPath(),
			  borderR(0),
			  borderG(0),
			  borderB(0),
			  outputPath(),
			  parsingStatus(BorderRemovalCommandParsingStatus::BRCPS_VALID),
			  fileType(ImageExtensions::IFT_UNSUPORTED)
		{
		}

		std::string inputPath;
		unsigned char borderR;
		unsigned char borderG;
		unsigned char borderB;
		std::string outputPath;
		BorderRemovalCommandParsingStatus parsingStatus;
		ImageExtensions::ImageFileType fileType;
	};

	///constructor
	BorderRemovalCommandParser();

	///
	/// \brief parseCommand parses the supplied commands, ensuring they comply with the application's requierements
	/// \param numberOfArguments an int that defines the number of arguments supplied to the application
	/// \param arguments a \ref char *[] that holds the values of each supplied argument 
	/// \returns a BorderRemovalParsedData with the validated data
	/// \returns a BorderRemovalParsedData with parsingStatus BRCPS_INVALID if one or more commands did not comply with the application's requirements
	///
	BorderRemovalParsedData parseCommand(int numberOfArguments, char *arguments[]);
};


#endif // BORDER_REMOVAL_COMMAND_PARSER_H