/*
* ParseUtils.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

//C++ libraries
#include <string>
#include <vector>

/// \brief ParseUitls provides string manipulation helper methods
class ParseUitls
{
public:

	///
	/// \brief stringToNumber parses an input string number representation and retrieves its numeric data form
	/// \param input an std::string that holds the number represented by a sequence of characters
	/// \param number a long long that will hold the numeric representation held by the input parameter
	/// \returns a boolean indicating true if the conversion taking places was sucessful, false otherwise
	///
	static bool stringToNumber(const std::string &input, long long &number)
	{
		const int inputSize = static_cast<int>(input.size());
		long long negative = 1;
		long long factor = 1;
		long long currentNumber = 0;
		for(int index = inputSize - 1; index >= 0; --index)
		{
			const char currentDigit = input[index];
			if(currentDigit == '-' && negative == 1)
			{
				negative = -1;
				continue;
			}
			else if(currentDigit == '-' && negative != -1)
			{
				//we cannot accespt two negative numbers
				return false;
			}


			const int numberToAdd = (currentDigit - '0');
			if(numberToAdd < 0 || numberToAdd > 9)
			{
				return false;
			}
			
			currentNumber += (numberToAdd * factor);
			factor *= 10;
		}
		number = (currentNumber * negative);
		return true;
	}


	///
	/// \brief retrieves the path extension from a supplied filepath
	/// \param an std::string that holds the filepath to be processed
	/// \returns an std::string with the extension found, empty string if no extension was found
	///
	static std::string getPathExtension(std::string filePath)
	{
		std::string extension;
		static const std::string delimiter = ".";
		if(filePath.size() > 0)
		{
			std::vector<std::string> splitStrings;
			size_t position = 0;
			std::string currentSubstring;
			while((position = filePath.find(delimiter)) != std::string::npos)
			{
				currentSubstring = filePath.substr(0, position);
				filePath.erase(0, position + delimiter.size());
				splitStrings.push_back(currentSubstring);
			}
			if(!filePath.empty())
			{
				splitStrings.push_back(filePath);
			}
			if(splitStrings.size() > 0)
			{
				extension = splitStrings.back();
			}
		}
		return extension;
	}
};


#endif // PARSE_UTILS_H