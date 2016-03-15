/*
 * DistanceWrapper.cpp
 *
 *  Created on: 07.03.2016
 *      Author: enrico
 */

#include "DistanceWrapper.h"

#include <iostream>

namespace pickandplace {

DistanceWrapper::DistanceWrapper() {
	memset(actualValues, 0, sizeof(actualValues));
}

DistanceWrapper::~DistanceWrapper() {
	// TODO Auto-generated destructor stub
}


//float DistanceWrapper::GetAverage(int sensorNumber)
//{
//	float calculatedValue = 0.0;
//	for(int i = 0; i < SIZE_OF_VALUE_HISTORY; i++)
//	{
//		calculatedValue += valueArray[i][sensorNumber];
//	}
//	return calculatedValue / (float)SIZE_OF_VALUE_HISTORY;
//}

// Returns the last value of a specific distance sensor
float DistanceWrapper::GetActual(int sensorNumber)
{
	if(sensorNumber > 9 || sensorNumber < 0)
		return 0;
	return actualValues[sensorNumber];
}

// Returns the minimal distance value
float DistanceWrapper::GetMinimal()
{
	float minimal = actualValues[0];
	for(int i = 1; i < 9; i++)
	{
		if(actualValues[i] < minimal)
			minimal = actualValues[i];
	}
	return minimal;
}

void DistanceWrapper::distancesChangedEvent( const float* distances, unsigned int size )
{
	// Save the actualized values
	for(int i = 0; i < size; i++)
	{
		actualValues[i] = distances[i];
	}



//	// Test routine for event handling
//	if(GetMinimal() < 0.08)
//	{
//		std::cout << "true" << std::endl; // Print 'true' if near object detected.
//	}
//	else
//	{
//		std::cout << "false" << std::endl; // Print 'false' if far object detected.
//	}

}

} /* namespace pickandplace */
