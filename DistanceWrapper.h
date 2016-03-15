/*
 * DistanceWrapper.h
 *
 *  Created on: 07.03.2016
 *      Author: enrico
 */

#ifndef DISTANCEWRAPPER_H_
#define DISTANCEWRAPPER_H_

#include "rec/robotino/api2/all.h"

using namespace rec::robotino::api2;

namespace pickandplace {

class DistanceWrapper : rec::robotino::api2::DistanceSensorArray {
public:
	DistanceWrapper();
	virtual ~DistanceWrapper();

	void Actualize();
	void MeasureAverage(int numberOfRepeats);
	void ResetAverage();

	float GetAverage(int sensorNumber);
	float GetActual(int sensorNumber);
	float GetMinimal();

	void distancesChangedEvent( const float* distances, unsigned int size );

private:
	static const int NUMBER_OF_SENSORS = 9;
	static const int SIZE_OF_VALUE_HISTORY = 10;
	float actualValues[NUMBER_OF_SENSORS];
	float valueArray[SIZE_OF_VALUE_HISTORY][NUMBER_OF_SENSORS];
};

} /* namespace pickandplace */

#endif /* DISTANCEWRAPPER_H_ */
