/*
* ImageData.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

//C++ libraries
#include <cassert>

namespace ImageUtils
{
	/// \brief ImageData serves as a wrapper class for Image data acess/manipulation
	template <typename T>
	class ImageData
	{
	public:
		ImageData(T* data, const int width, const int height, const int channels)
			: mData(nullptr),
			  mWidth(width),
			  mHeight(height),
			  mChannels(channels)
		{
			assert(data);
			const size_t imageSize = static_cast<size_t>(width * height * channels);
			mData = new T[imageSize]();
			for(size_t index = 0; index < imageSize; ++index)
			{
				mData[index] = data[index];
			}
		}

		~ImageData()
		{
			if(mData)
			{
				delete[] mData;
				mData = nullptr;
			}
		}

		/// \brief retrieves the image's width
		int width() const
		{
			return mWidth;
		}

		/// \brief retrieves the image's height
		int height() const
		{
			return mHeight;
		}

		/// \brief retrieves the image's channels
		int channels() const
		{
			return mChannels;
		}

		/// \brief retrieves the image's data
		const T* data()
		{
			return mData;
		}

	private:
		T *mData;
		int mWidth;
		int mHeight;
		int mChannels;
	};
}

#endif //IMAGE_DATA_H