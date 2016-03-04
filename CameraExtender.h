/*
 * CameraExtender.h
 *
 *  Created on: 29.02.2016
 *      Author: Phil
 */

#ifndef CAMERAEXTENDER_H_
#define CAMERAEXTENDER_H_

#include <sstream>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include "rec/robotino/api2/all.h"

using namespace rec::robotino::api2;
using namespace std;

namespace pickandplace {

class CameraExtender: Camera {

public:
	CameraExtender();
	virtual ~CameraExtender();
private:
	void imageReceivedEvent(const unsigned char* data, unsigned int dataSize,
			unsigned int width, unsigned int height, unsigned int step);

};

}

#endif /* CAMERAEXTENDER_H_ */
