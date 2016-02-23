/*
 * Gripper.cpp
 *
 *  Created on: 23.02.2016
 *      Author: Philipp
 */

#include "Gripper.h"

using namespace rec::robotino::api2;

namespace pickandplace {

class Gripper {

private:
	ElectricalGripper gripper;

public:
	Gripper() {
		ElectricalGripper gripper;
	}

	~Gripper() {
	}

	bool isOpened() {
		return gripper.isOpened();
	}

	void close() {
		if (isOpened()) {
			gripper.close();
		}
	}

	void open() {
		if (!isOpened()) {
			gripper.open();
		}
	}

};
}/* namespace pickandplace */
