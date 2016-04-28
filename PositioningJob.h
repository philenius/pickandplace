/*
 * PositioningJob.h
 *
 *  Created on: 28.04.2016
 *      Author: enrico
 */

#ifndef POSITIONINGJOB_H_
#define POSITIONINGJOB_H_

#include "Job.h"
#include "CameraExtender.h"
#include "RelativeRobotPosition.h"

namespace pickandplace {

class PositioningJob : public Job {
public:
	PositioningJob(CameraExtender * camera, RelativeRobotPosition * position, OmniDrive * drive);
	virtual ~PositioningJob();

	void start();
	void recalculate();

private:
	CameraExtender * camera;
	RelativeRobotPosition * position;
	OmniDrive * drive;

};

} /* namespace pickandplace */

#endif /* POSITIONINGJOB_H_ */
