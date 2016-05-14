/*
 * RotateJob.h
 *
 *  Created on: 14.05.2016
 *      Author: enrico
 */

#ifndef ROTATEJOB_H_
#define ROTATEJOB_H_

#include "Job.h"
#include "OdometryWrapper.h"
#include "rec/robotino/api2/all.h"
#include <math.h>
#include <iostream>

namespace pickandplace {

class RotateJob: public Job {
public:
	RotateJob(OdometryWrapper * odometry, OmniDrive * drive, double deltaPhi);
	virtual ~RotateJob();

	void start();
	void recalculate();

private:
	OdometryWrapper * odometry;
	OmniDrive * drive;

	double deltaPhi;
	double lastPhi;
	double rotated;
	double omega;
	double actualPhi;

};

} /* namespace pickandplace */

#endif /* ROTATEJOB_H_ */
