/*
 * DriveJob.h
 *
 *  Created on: 26.04.2016
 *      Author: enrico
 */

#ifndef DRIVEJOB_H_
#define DRIVEJOB_H_

#include "OdometryWrapper.h"
#include "Job.h"
#include "rec/robotino/api2/all.h"
#include <math.h>
#include <iostream>

namespace pickandplace {

class DriveJob : public Job {
public:
	DriveJob(OdometryWrapper * odometry, OmniDrive * drive, double distance, double phi);
	~DriveJob();

	void start();
	void recalculate();

private:
	OdometryWrapper * odometry;
	OmniDrive * drive;
	double distance;
	double phi;

	double init_x;
	double init_y;

	double target_x;
	double target_y;

	double actual_x;
	double actual_y;
};

} /* namespace pickandplace */

#endif /* JOBS_DRIVEJOB_H_ */
