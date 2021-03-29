/*
* IBorderTrimmer.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef IBORDER_TRIMMER_H
#define IBORDER_TRIMMER_H

//C++ libraries
#include <memory>

//Local Libraries
#include "BorderRemoval/AbstractBorderTimmerParameters.h"

/// brief IBorderTrimmer interface that provides a baseline to apply a border trimmer algorithm
class IBorderTrimmer
{
public:
	///
	/// \brief run performs the border trimming of a supplied image
	/// \param imageRgbData an unsigned char pointer that points to an 8bpp image data in the r, g, b format, where 
	/// imageRgbData[0] = R, imageRgbData[1] = G and imageRgbData[2] = B. imageRgbData[3] = Alpha if applicable
	/// \param a \ref AbstractBorderTrimmerParameters that define the needed parameters for the algorithm 
	/// \return a \ref std::shared_ptr<unsigned char> that points to the borderless image
	/// \return a shared_ptr with a null reference if an error was encounter during the algorithm's execution
	///
	virtual std::shared_ptr<unsigned char> run(unsigned char const * const imageRgbData,
											   AbstractBorderTimmerParameters *parameters) = 0;

	///
	/// \brief run performs the border trimming of a supplied image
	/// \param imageRgbData an unsigned short pointer that points to an 8~16bpp image data in the r, g, b format, where 
	/// imageRgbData[0] = R, imageRgbData[1] = G and imageRgbData[2] = B. imageRgbData[3] = Alpha if applicable
	/// \param a \ref AbstractBorderTrimmerParameters that define the needed parameters for the algorithm 
	/// \return a \ref std::shared_ptr<unsigned short> that points to the borderless image
	/// \return a shared_ptr with a null reference if an error was encounter during the algorithm's execution
	///
	virtual std::shared_ptr<unsigned short> run(unsigned short const * const imageRgbData,
												AbstractBorderTimmerParameters *parameters) = 0;

	///
	/// \brief run performs the border trimming of a supplied image
	/// \param imageRgbData an int pointer that points to an 8bpp~32bpp image data in the r, g, b format, where 
	/// imageRgbData[0] = R, imageRgbData[1] = G and imageRgbData[2] = B. imageRgbData[3] = Alpha if applicable
	/// \param a \ref AbstractBorderTrimmerParameters that define the needed parameters for the algorithm 
	/// \return a \ref std::shared_ptr<int> that points to the borderless image
	/// \return a shared_ptr with a null reference if an error was encounter during the algorithm's execution
	///
	virtual std::shared_ptr<unsigned int> run(unsigned int const * const imageRgbData,
											  AbstractBorderTimmerParameters *parameters) = 0;

	///
	/// \brief run performs the border trimming of a supplied image
	/// \param imageRgbData an float pointer that points to normalized image data in the r, g, b format, where 
	/// imageRgbData[0] = R, imageRgbData[1] = G and imageRgbData[2] = B. imageRgbData[3] = Alpha if applicable
	/// \param a \ref AbstractBorderTrimmerParameters that define the needed parameters for the algorithm 
	/// \return a \ref std::shared_ptr<float> that points to the borderless image
	/// \return a shared_ptr with a null reference if an error was encounter during the algorithm's execution
	///
	virtual std::shared_ptr<float> run(float const * const imageRgbData,
									   AbstractBorderTimmerParameters *parameters) = 0;
};

#endif // IBORDER_TRIMMER_H