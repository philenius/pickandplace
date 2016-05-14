/*
 * Controller.h
 *
 *  Created on: 15.04.2016
 *      Author: enrico
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Job.h"
#include "MyCom.h"
#include <ctime>
#include "OdometryWrapper.h"
#include "CameraExtender.h"
#include "rec/robotino/api2/all.h"

#include "DriveJob.h"
#include "PositioningJob.h"
#include "RotateJob.h"

namespace pickandplace {

class Controller {
public:
	Controller();
	~Controller();

	void mainSequence();

	void driveFromInitialToLeftPlatform();
	void driveFromLeftToRightPlatform();
	void driveFromRightToLeftPlatform();
	void targetStacker(int stackerNumber);
	void scanStackerStates();
	void driveTest();
	void positioningTest();
	void rotationTest();

private:
	bool isInitialized;
	void initSequence();
	void executionLoop(int timeOutSeconds, Job * executableJob);

	MyCom com;
	OmniDrive drive;
	OdometryWrapper odometry;
	CameraExtender camera;
};

} /* namespace pickandplace */

#endif /* CONTROLLER_H_ */
