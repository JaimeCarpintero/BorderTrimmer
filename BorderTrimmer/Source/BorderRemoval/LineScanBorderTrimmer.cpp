/*
* LineScanBorderTrimmer.cpp
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#include "BorderRemoval/LineScanBorderTrimmer.h"

//C++ libraries
#include <cassert>

LineScanBorderTrimmer::LineScanBorderTrimmer()
{
}

LineScanBorderTrimmer::~LineScanBorderTrimmer()
{
}

std::shared_ptr<unsigned char> LineScanBorderTrimmer::run(unsigned char const* const imageRgbData, AbstractBorderTimmerParameters *parameters)
{
	LineScanBorderTimmerParameters<unsigned char> *lineScanParameters = dynamic_cast<LineScanBorderTimmerParameters<unsigned char>*>(parameters);
	if(!lineScanParameters || !parameters)
	{
		return std::shared_ptr<unsigned char>();
	}
	return execute(imageRgbData, lineScanParameters);
}

std::shared_ptr<unsigned short> LineScanBorderTrimmer::run(unsigned short const* const imageRgbData, AbstractBorderTimmerParameters *parameters)
{
	LineScanBorderTimmerParameters<unsigned short> *lineScanParameters = dynamic_cast<LineScanBorderTimmerParameters<unsigned short>*>(parameters);
	if(!lineScanParameters || !parameters)
	{
		return std::shared_ptr<unsigned short>();
	}
	return execute(imageRgbData, lineScanParameters);
}

std::shared_ptr<unsigned int> LineScanBorderTrimmer::run(unsigned int const* const imageRgbData, AbstractBorderTimmerParameters *parameters)
{
	LineScanBorderTimmerParameters<unsigned int> *lineScanParameters = dynamic_cast<LineScanBorderTimmerParameters<unsigned int>*>(parameters);
	if(!lineScanParameters || !parameters)
	{
		return std::shared_ptr<unsigned int>();
	}
	return execute(imageRgbData, lineScanParameters);
}

std::shared_ptr<float> LineScanBorderTrimmer::run(float const* const imageRgbData, AbstractBorderTimmerParameters *parameters)
{
	LineScanBorderTimmerParameters<float>* lineScanParameters = dynamic_cast<LineScanBorderTimmerParameters<float>*>(parameters);
	if(!lineScanParameters || !parameters)
	{
		return std::shared_ptr<float>();
	}
	return execute(imageRgbData, lineScanParameters);
}

template <typename T>
std::shared_ptr<T> LineScanBorderTrimmer::execute(T const * const imageRgbData, LineScanBorderTimmerParameters<T> *parameters)
{
	assert(imageRgbData);
	assert(parameters);

	const int imageWidth = parameters->originalImageWidth;
	const int imageHeight = parameters->originalImageHeight;
	const int imageChannels = parameters->imageChannels;
	if(imageWidth <= 0 || imageHeight <= 0)
	{
		return std::shared_ptr<T>(nullptr);
	}

	//NOTE [Jaime]: this can be done in different threads for better performance.
	const int topDownDistance = getTopDownWidth(imageRgbData, *parameters);
	const int bottomUpDistance = getBottomUpWidth(imageRgbData, *parameters);
	const int leftRightDistance = getLeftRightWidth(imageRgbData, *parameters);
	const int rightLeftDistance = getRightLeftWidth(imageRgbData, *parameters);

	//NOTE: [Jaime] if the image is all border then there is nothing to trim
	if(topDownDistance < 0 || bottomUpDistance < 0 || leftRightDistance < 0 || rightLeftDistance < 0)
	{
		return std::shared_ptr<T>(nullptr);
	}

	const int trimmedImageWidth = imageWidth - leftRightDistance - rightLeftDistance;
	const int trimmedImageHeight = imageHeight - topDownDistance - bottomUpDistance;
	const size_t trimmedImageSize = static_cast<size_t>(trimmedImageWidth * trimmedImageHeight * imageChannels);

	std::shared_ptr<T> trimmedImage(new T[trimmedImageSize]());
	T* trimmedImageData = trimmedImage.get();

	for(int row = 0; row < trimmedImageHeight; ++row)
	{
		for(int col = 0; col < trimmedImageWidth; ++col)
		{
			const int indexOnTrimmedImage = (row * trimmedImageWidth + col) * imageChannels;
			const int indexOnInputImage = ((row + topDownDistance) * (imageWidth) + (col + leftRightDistance)) * imageChannels;

			for(int channelOffset = 0; channelOffset < imageChannels; ++channelOffset)
			{
				trimmedImageData[indexOnTrimmedImage + channelOffset] = imageRgbData[indexOnInputImage + channelOffset];
			}
		}
	}

	parameters->trimmedImageWidth = trimmedImageWidth;
	parameters->trimmedImageHeight = trimmedImageHeight;
	return trimmedImage;

}

template<typename T>
int LineScanBorderTrimmer::getBottomUpWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters)
{
	const int imageWidth = parameters.originalImageWidth;
	const int imageHeight = parameters.originalImageHeight;
	const int imageChannels = parameters.imageChannels;

	const T borderR = parameters.borderR;
	const T borderG = parameters.borderG;
	const T borderB = parameters.borderB;

	int bottomUpDistance = -1;
	bool distanceFound = false;
	for(int row = imageHeight - 1; (row >= 0) && !distanceFound; --row)
	{
		for(int col = 0; col < imageWidth; ++col)
		{
			const int indexOnImage = (row * imageWidth + col) * imageChannels;
			const T &r = ImageRgbData[indexOnImage];
			const T &g = ImageRgbData[indexOnImage + 1];
			const T &b = ImageRgbData[indexOnImage + 2];
			//Alpha is ignored

			if(r != borderR || g != borderG || b != borderB)
			{
				bottomUpDistance = (imageHeight - 1) - row;
				distanceFound = true;
				break;
			}
		}
	}
	return bottomUpDistance;
}

template<typename T>
int LineScanBorderTrimmer::getTopDownWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters)
{
	const int imageWidth = parameters.originalImageWidth;
	const int imageHeight = parameters.originalImageHeight;
	const int imageChannels = parameters.imageChannels;

	const T borderR = parameters.borderR;
	const T borderG = parameters.borderG;
	const T borderB = parameters.borderB;

	int topDownDistance = -1;
	bool distanceFound = false;
	for(int row = 0; (row < imageHeight) && !distanceFound; ++row)
	{
		for(int col = 0; (col < imageWidth); ++col)
		{
			const int indexOnImage = (row * imageWidth + col) * imageChannels;
			const T	&r = ImageRgbData[indexOnImage];
			const T	&g = ImageRgbData[indexOnImage + 1];
			const T	&b = ImageRgbData[indexOnImage + 2];
			//Alpha is ignored

			if(r != borderR || g != borderG || b != borderB)
			{
				topDownDistance = row;
				distanceFound = true;
				break;
			}
		}
	}
	return topDownDistance;
}

template<typename T>
int LineScanBorderTrimmer::getLeftRightWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters)
{
	const int imageWidth = parameters.originalImageWidth;
	const int imageHeight = parameters.originalImageHeight;
	const int imageChannels = parameters.imageChannels;

	const T borderR = parameters.borderR;
	const T borderG = parameters.borderG;
	const T borderB = parameters.borderB;

	int leftToRightDistance = -1;
	bool distanceFound = false;

	for(int col = 0; col < imageWidth; ++col)
	{
		for(int row = 0; (row < imageHeight) && !distanceFound; ++row)
		{
			const int indexOnImage = (row * imageWidth + col) * imageChannels;
			const T &r = ImageRgbData[indexOnImage];
			const T &g = ImageRgbData[indexOnImage + 1];
			const T &b = ImageRgbData[indexOnImage + 2];
			//Alpha is ignored

			if(r != borderR || g != borderG || b != borderB)
			{
				leftToRightDistance = col;
				distanceFound = true;
				break;
			}
		}
	}
	return leftToRightDistance;
}

template<typename T>
int LineScanBorderTrimmer::getRightLeftWidth(T const * const ImageRgbData, LineScanBorderTimmerParameters<T> &parameters)
{
	const int imageWidth = parameters.originalImageWidth;
	const int imageHeight = parameters.originalImageHeight;
	const int imageChannels = parameters.imageChannels;

	const T borderR = parameters.borderR;
	const T borderG = parameters.borderG;
	const T borderB = parameters.borderB;

	int rightToLeftDistance = -1;
	bool distanceFound = false;
	for(int col = imageWidth - 1; col >= 0; --col)
	{
		for(int row = 0; (row < imageHeight) && !distanceFound; ++row)
		{
			const int indexOnImage = (row * imageWidth + col) * imageChannels;
			const T &r = ImageRgbData[indexOnImage];
			const T &g = ImageRgbData[indexOnImage + 1];
			const T &b = ImageRgbData[indexOnImage + 2];
			//Alpha is ignored

			if(r != borderR || g != borderG || b != borderB)
			{
				rightToLeftDistance = (imageWidth - 1) - col;
				distanceFound = true;
				break;
			}
		}
	}
	return rightToLeftDistance;
}
