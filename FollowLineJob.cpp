/*
 * FollowLineJob.cpp
 *
 *  Created on: 14.05.2016
 *      Author: enrico
 */

#include "FollowLineJob.h"

namespace pickandplace {

FollowLineJob::FollowLineJob(CameraExtender * camera,
		RelativeRobotPosition * position, OmniDrive * drive) {
	this->position = position;
	this->camera = camera;
	this->drive = drive;
	this->driveCount = 0;

	Subject * subject = camera;
	subject->subscribe(this);
}

FollowLineJob::~FollowLineJob() {
	this->driveCount = 0;
	Subject * subject = camera;
	subject->subscribe(this);
}

void FollowLineJob::start() {
	cout << "Job started" << endl;
	Job::state = working;
}

void FollowLineJob::recalculate() {

	int pixelDiff;
	float leftPercentage;
	float rightPercentage;
	int totalPixelCount;

	cout << "get position" << endl;
	position->getPositionForBlackLine(&pixelDiff, &leftPercentage,&rightPercentage, &totalPixelCount);
	cout << "Job recalculating" << endl;

	cout << "Diff:   " << pixelDiff;
	cout << "   Left:  " << leftPercentage;
	cout << "   Right: " << rightPercentage << endl;

	if (leftPercentage > 0.30 && rightPercentage > 0.30) {
		cout << "Drive through" << endl;
		drive->setVelocity(0.08, 0.0, 0.0);
		driveCount++;
	} else {
		if (rightPercentage > leftPercentage) {
			cout << "Drive left" << endl;
			drive->setVelocity(0.0, -0.01, -0.1);
		}
		if (leftPercentage > rightPercentage) {
			cout << "Drive right" << endl;
			drive->setVelocity(0.0, 0.01, 0.1);
		}
		driveCount++;
	}

	if (totalPixelCount <= 0 && driveCount > 100) {
		cout << "Drive count: " << driveCount << endl;
		cout << "Finished follow line job" << endl;
		this->state = finished;
	}
}

} /* namespace pickandplace */
