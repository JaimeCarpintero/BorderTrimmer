/*
* AbstractBorderTimmerParameters.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef ABSTRACT_BORDER_TRIMMER_PARAMETERS_H
#define ABSTRACT_BORDER_TRIMMER_PARAMETERS_H

///
/// \brief AbstractBorderTimmerParameters wraps the essential parameters needed by a border trimmer algorithm
struct AbstractBorderTimmerParameters
{
public:
	///~AbstractBorderTimmerParameters pure virtual destructor in order to perform polymophsim
	virtual ~AbstractBorderTimmerParameters() = 0;

	int originalImageWidth;
	int originalImageHeight;
	int imageChannels;

	int trimmedImageWidth;
	int trimmedImageHeight;
};

inline AbstractBorderTimmerParameters::~AbstractBorderTimmerParameters() = default;

#endif // ABSTRACT_BORDER_TRIMMER_PARAMETERS_H