/*
 * GripperWrapper.h
 *
 *  Created on: 23.02.2016
 *      Author: Philipp
 */

#ifndef GripperWrapper_H_
#define GripperWrapper_H_

#include "rec/robotino/api2/all.h"

using namespace rec::robotino::api2;

namespace pickandplace {

class GripperWrapper {

private:
	ElectricalGripper gripper;

public:
	GripperWrapper();
	virtual ~GripperWrapper();

	void close();
	void open();
	bool isClosed();
	bool isOpened();
};

} /* namespace pickandplace */

#endif /* GripperWrapper_H_ */
