/*
 * Controller.cpp
 *
 *  Created on: 15.04.2016
 *      Author: enrico
 */

#include "Controller.h"

namespace pickandplace {

Controller::Controller() {
	isInitialized = false;
	initSequence();
}

Controller::~Controller() {
	com.disconnectFromServer();
}

void Controller::initSequence() {
	// Connect
	string hostname = "172.26.1.1";

	try {
		cout << "Connecting...";
		com.setAddress(hostname.c_str());

		com.connectToServer(true);

		if (false == com.isConnected()) {
			cout << endl << "Could not connect to " << com.address()
					<< endl;

			shutdown();
			exit(1);
		} else {
			cout << "success" << endl;
			isInitialized = true;

			executionLoop(1,0);

		}
	} catch (const RobotinoException& e) {
		cerr << "Robotino Error: " << e.what() << endl;
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	} catch (...) {
		cerr << "Unknow Error" << endl;
	}
}

void Controller::executionLoop(int timeOutSeconds, Job * executableJob) {
	if(isInitialized == false) return;
	time_t t = time(0);
	struct tm * startTime = localtime(&t);

	while((executableJob == 0 || executableJob->getState() != Job::finished) && com.isConnected()) {
		com.processEvents();
		time_t t2 = time(0);
		struct tm * now = localtime(&t2);
		if(difftime(t2, t) > (double)timeOutSeconds) {
			break;
		}
	}

	cout << "Press any key to exit..." << endl;
	waitForKey();
}


void Controller::driveTest() {
	cout << "starting drive test" << endl;
	DriveJob * driveJob = new DriveJob(&odometry, &drive, 1.0, 4.71238);
	this->executionLoop(100, driveJob);
	cout << "execution finished" << endl;
}

void Controller::positioningTest() {
	RelativeRobotPosition position;
	PositioningJob * positioningJob = new PositioningJob(&camera, &position, &drive);
	this->executionLoop(1000, positioningJob);
}

void Controller::rotationTest() {
	cout << "starting rotation test" << endl;
	RotateJob * rotateJob = new RotateJob(&odometry, &drive, 360.0);
	this->executionLoop(1000, rotateJob);
}

} /* namespace pickandplace */
