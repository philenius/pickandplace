/*
 * Gripper.h
 *
 *  Created on: 23.02.2016
 *      Author: Philipp
 */

#ifndef GRIPPER_H_
#define GRIPPER_H_

#include "rec/robotino/api2/all.h"

namespace pickandplace {

class Gripper {

public:
	Gripper();
	virtual ~Gripper();

	void close();
	void open();
	bool isOpened();
};

} /* namespace pickandplace */

#endif /* GRIPPER_H_ */
