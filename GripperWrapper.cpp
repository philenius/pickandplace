/*
 * GripperWrapper.cpp
 *
 *  Created on: 23.02.2016
 *      Author: Philipp
 */

#include "GripperWrapper.h"

using namespace rec::robotino::api2;

namespace pickandplace {

ElectricalGripper gripper;

GripperWrapper::GripperWrapper() {
}

GripperWrapper::~GripperWrapper() {
}

bool GripperWrapper::isOpened() {
	return gripper.isOpened();
}

bool GripperWrapper::isClosed() {
	return gripper.isClosed();
}

void GripperWrapper::close() {
//	if (isOpened()) {
		gripper.close();
//	}
}

void GripperWrapper::open() {
//	if (!isOpened()) {
	gripper.open();
//	}
}

}/* namespace pickandplace */
