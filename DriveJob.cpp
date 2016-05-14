/*
 * DriveJob.cpp
 *
 *  Created on: 26.04.2016
 *      Author: enrico
 */

#include "DriveJob.h"

using namespace std;

namespace pickandplace {

DriveJob::DriveJob(OdometryWrapper * odometry, OmniDrive * drive, double distance, double phi) {
	this->phi = phi;
	this->distance = distance;
	this->odometry = odometry;
	this->drive = drive;

	Subject * subject = odometry;
	subject->subscribe(this);

	init_x = this->odometry->getX();
	init_y = this->odometry->getY();

	target_x = 0.0;
	target_y = 0.0;

	actual_x = 2.0;
	actual_y = 2.0;
}

DriveJob::~DriveJob() {
	Subject * subject = odometry;
	subject->unsubscribe(this);
}

void DriveJob::start() {
	cout << "Start" << endl;
	init_x = this->odometry->getX();
	cout << "Init_X: " << init_x << endl;
	init_y = this->odometry->getY();
	cout << "Init_Y: " << init_y << endl;
	target_x = init_x + cos(phi) * distance;
	cout << "Target_X: " << target_x << endl;
	target_y = init_y + sin(phi) * distance;
	cout << "Target_Y: " << target_y << endl;
	Job::state = working;
}

void DriveJob::recalculate() {
	actual_x = this->odometry->getX();
	actual_y = this->odometry->getY();
	cout << "X: " << actual_x << endl;
	cout << "Y: " << actual_y << endl;
	double actualDistance = sqrt(pow((actual_x - init_x),2) + pow((actual_y - init_y),2));
	cout << "ActualDistance: " << actualDistance << endl;
	double speed = 0;
	if((distance - actualDistance) > 0.1) {
		cout << "DRIVE!" << endl;
		speed = 0.1;
		drive->setVelocity(cos(phi) * speed, sin(phi) * speed, 0.0);
	}
	else {
		this->state = finished;
	}
}

} /* namespace pickandplace */
