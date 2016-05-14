/*
 * RotateJob.cpp
 *
 *  Created on: 14.05.2016
 *      Author: enrico
 */

#include "RotateJob.h"

using namespace std;
using namespace rec::robotino::api2;

namespace pickandplace {

RotateJob::RotateJob(OdometryWrapper * odometry, OmniDrive * drive, double deltaPhi) {
	this->deltaPhi = deltaPhi;
	this->odometry = odometry;
	this->drive = drive;

	Subject * subject = odometry;
	subject->subscribe(this);

	rotated = 0.0;
	lastPhi = 0.0;
	actualPhi = 0.0;
	omega = 20.0;
}

RotateJob::~RotateJob() {
	Subject * subject = odometry;
	subject->unsubscribe(this);
}

void RotateJob::start() {
	actualPhi = this->odometry->getPhi();
	lastPhi = this->odometry->getPhi();
	Job::state = working;
}

void RotateJob::recalculate() {
	actualPhi = this->odometry->getPhi();
	cout << "Phi:" << actualPhi << endl;

	if( actualPhi - lastPhi > M_PI ) {
		lastPhi += 2 * M_PI;
	}
	else if( lastPhi - actualPhi > M_PI )	{
		lastPhi -= 2 * M_PI;
	}

	rotated += actualPhi - lastPhi;
	lastPhi = actualPhi;


	float movePhi = 0.0;
	double differencePhi = deltaPhi - rec::robotino::api2::rad2deg( (float)rotated );

	if( fabs( differencePhi ) > 1.0  ) {
		if( fabs(differencePhi) > 5.0 ) {
			if( differencePhi > 0.0 ) {
				movePhi = 1.0;
			}
			else {
				movePhi = -1.0;
			}
		}
		else {
			movePhi = differencePhi / 5.0;
		}
	}

	if( movePhi != 0.0 ) {
		cout << "Working phi:" << rad2deg( (float)rotated ) << "/" << deltaPhi << endl;

		drive->setVelocity( 0.0, 0.0, deg2rad( omega ) * movePhi );
	}
	else {
		cout << "Finished phi:" << rad2deg( (float)rotated ) << "/" << deltaPhi << endl;
		drive->setVelocity( 0.0, 0.0, 0.0 );
		this->state = finished;
	}


}

} /* namespace pickandplace */
