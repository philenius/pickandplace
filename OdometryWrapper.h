/*
 * OdometryWrapper.h
 *
 *  Created on: 15.03.2016
 *      Author: enrico
 */

#ifndef ODOMETRYWRAPPER_H_
#define ODOMETRYWRAPPER_H_

#include "rec/robotino/api2/all.h"
#include "Subject.h"
#include <iostream>

using namespace rec::robotino::api2;

namespace pickandplace {

class OdometryWrapper : Odometry, public Subject {
public:
	OdometryWrapper();
	virtual ~OdometryWrapper();

	void readingsEvent( double x, double y, double phi, float vx, float vy, float omega, unsigned int sequence );
	void printValues();
	void reset();

	double getX();
	double getY();
	double getPhi();

private:
	double x_position;
	double y_position;
	double phi;
	float vx;
	float vy;
	float omega;
	unsigned int sequence;

	rec::robotino::api2::OmniDrive drive;
};

} /* namespace pickandplace */

#endif /* ODOMETRYWRAPPER_H_ */
