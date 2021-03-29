/*
* LineScanBorderTimmerParameters.h
* (c)2021 Jaime Carpintero Carrillo
* jaime.carpintero.carrillo@gmail.com
* jaime.carpintero@uabc.edu.mx
* This code is licensed under MIT license(see LICENSE.txt for details)
*/

#ifndef LINE_SCAN_BORDER_TRIMMER_PARAMETERS_H
#define LINE_SCAN_BORDER_TRIMMER_PARAMETERS_H

#include "BorderRemoval/AbstractBorderTimmerParameters.h"

/// \brief LineScanBorderTimmerParameters defines the necessary parameters needed by a line scan based border removal algorithm
template <typename T>
struct LineScanBorderTimmerParameters final : public AbstractBorderTimmerParameters
{
	LineScanBorderTimmerParameters()
		: AbstractBorderTimmerParameters()
	{
	}

	T borderR;
	T borderG;
	T borderB;
};

#endif // LINE_SCAN_BORDER_TRIMMER_PARAMETERS_H