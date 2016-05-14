/*
 * FollowLineJob.h
 *
 *  Created on: 14.05.2016
 *      Author: enrico
 */

#ifndef FOLLOWLINEJOB_H_
#define FOLLOWLINEJOB_H_

#include "Job.h"
#include "CameraExtender.h"
#include "RelativeRobotPosition.h"

namespace pickandplace {

class FollowLineJob: public Job {
public:
	FollowLineJob(CameraExtender * camera, RelativeRobotPosition * position,
			OmniDrive * drive);
	virtual ~FollowLineJob();

	void start();
	void recalculate();

private:
	CameraExtender * camera;
	RelativeRobotPosition * position;
	OmniDrive * drive;
	int driveCount;
};

} /* namespace pickandplace */

#endif /* FOLLOWLINEJOB_H_ */
