/*
 * PositioningJob.cpp
 *
 *  Created on: 28.04.2016
 *      Author: enrico
 */

#include "PositioningJob.h"

namespace pickandplace {

PositioningJob::PositioningJob(CameraExtender * camera, RelativeRobotPosition * position, OmniDrive * drive) {
	this->position = position;
	this->camera = camera;
	this->drive = drive;

	Subject * subject = camera;
	camera->subscribe(this);
}

PositioningJob::~PositioningJob() {
	Subject * subject = camera;
	subject->unsubscribe(this);
}

void PositioningJob::start() {
	cout << "Job started" << endl;
	Job::state = working;
}

void PositioningJob::recalculate() {
	int pixelDif;
	float leftPercentage;
	float rightPercentage;

	pixelDif = 99;
	position->getPosition(&pixelDif, &leftPercentage, &rightPercentage);
	cout << "Job recalculating" << endl;


	cout << "Dif:   " << pixelDif << endl;
	cout << "Left:  " << leftPercentage << endl;
	cout << "Right: " << rightPercentage << endl;


	if(leftPercentage > 0.40 && rightPercentage > 0.40) {
		if(position->isYellowBoxInCenter(50)) {
			cout << "Job finished" << endl;
			Job::state = finished;
		}
		else {
			drive->setVelocity(0.0, 0.05, 0.0);
			cout << "Drive fast right" << endl;
		}
	}
	else {
		if(rightPercentage > leftPercentage) {
			cout << "Drive right" << endl;
			drive->setVelocity(0.0, -0.02, 0.0);
		}
		if(leftPercentage > rightPercentage) {
			cout << "Drive left" << endl;
			drive->setVelocity(0.0, 0.02, 0.0);
		}
	}
}

} /* namespace pickandplace */
