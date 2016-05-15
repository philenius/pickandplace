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
#include "CylinderDetection.h"
#include "rec/robotino/api2/all.h"

#include "DriveJob.h"
#include "PositioningJob.h"
#include "RotateJob.h"
#include "FollowLineJob.h"

namespace pickandplace {

class Controller {
public:
	Controller();
	~Controller();

	void mainSequence();

	void driveFromInitialToLeftPlatform();
	void driveFromLeftToRightPlatform();
	void driveFromRightToLeftPlatform();
	void searchCylinder(int startDepotPosition);
	void targetStacker(int stackerNumber);
	void scanStackerStates();
	void driveDistance(double distance, double phi);
	void driveToDepot();
	void rotate(double deltaPhi);
	void followLine();

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
