/*
* LineScanBorderTrimmer.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef LINE_SCAN_BORDER_TRIMMER_H
#define LINE_SCAN_BORDER_TRIMMER_H

//Local libraries
#include "BorderRemoval/IBorderTrimmer.h"
#include "BorderRemoval/LineScanBorderTrimmerParameters.h"

///
/// \brief LineScanBorderTrimmer serves as a wrapper class for a line scan based border removal algorithm
///
class LineScanBorderTrimmer final : public IBorderTrimmer
{
public:
	///LineScanBorderTrimmer constructor
	LineScanBorderTrimmer();
	//LineScanBorderTrimmer destructor 
	virtual ~LineScanBorderTrimmer();

	///See IBorderTrimmer class documentation for an in depth explanation
	virtual std::shared_ptr<unsigned char> run(unsigned char const * const imageRgbData,
											   AbstractBorderTimmerParameters *parameters) override;

	///See IBorderTrimmer class documentation for an in depth explanation
	virtual std::shared_ptr<unsigned short> run(unsigned short const * const imageRgbData,
												AbstractBorderTimmerParameters *parameters) override;

	///See IBorderTrimmer class documentation for an in depth explanation
	virtual std::shared_ptr<unsigned int> run(unsigned int const * const imageRgbData,
											  AbstractBorderTimmerParameters *parameters) override;

	///See IBorderTrimmer class documentation for an in depth explanation
	virtual std::shared_ptr<float> run(float const * const imageRgbData,
									   AbstractBorderTimmerParameters *parameters) override;

private:
	///
	/// \brief execute method provides an implementation for a line scan based border removal algorithm that supports unsigned char/unsigned short/int/float data types
	/// \param a T pointer that holds the image's data to be processed
	/// \param a LineScanBorderTimmerParameters that holds the necessary parameters that the algorithm implementation needs in order to work properly
	/// \return a \ref std::shared_ptr<T> that points to the borderless image
	/// \return a shared_ptr with a null reference if an error was encounter during the algorithm's execution
	///
	template<typename T>
	std::shared_ptr<T> execute(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> *parameters);

	///
	/// \brief getBottomUpWidth retrieves the width of the bottom-up horizontal border in a image.
	/// \param a T pointer that holds the image's data to be processed
	/// \param a LineScanBorderTimmerParameters that holds the necessary parameters that the process needs in order to work properly
	/// \returns an int that defines the width of the border found, -1 if the entire image scaned was composed by border based pixels
	///
	template<typename T>
	int getBottomUpWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters);

	///
	/// \brief getTopDownWidth retrieves the width of the top-down horizontal border in a image.
	/// \param a T pointer that holds the image's data to be processed
	/// \param a LineScanBorderTimmerParameters that holds the necessary parameters that the process needs in order to work properly
	/// \returns an int that defines the width of the border found, -1 if the entire image scaned was composed by border based pixels
	///
	template<typename T>
	int getTopDownWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters);

	///
	/// \brief getLeftRightWidth retrieves the width of the left-right vertical border in a image.
	/// \param a T pointer that holds the image's data to be processed
	/// \param a LineScanBorderTimmerParameters that holds the necessary parameters that the process needs in order to work properly
	/// \returns an int that defines the width of the border found, -1 if the entire image scaned was composed by border based pixels
	///
	template<typename T>
	int getLeftRightWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters);

	///
	/// \brief getRightLeftWidth retrieves the width of the right-left vertical border in a image.
	/// \param a T pointer that holds the image's data to be processed
	/// \param a LineScanBorderTimmerParameters that holds the necessary parameters that the process needs in order to work properly
	/// \returns an int that defines the width of the border found, -1 if the entire image scaned was composed by border based pixels
	///
	template<typename T>
	int getRightLeftWidth(T const* const ImageRgbData, LineScanBorderTimmerParameters<T>& parameters);
};

#endif // LINE_SCAN_BORDER_TRIMMER_H
