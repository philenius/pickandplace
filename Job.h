/*
 * Job.h
 *
 *  Created on: 16.04.2016
 *      Author: enrico
 */

#ifndef JOB_H_
#define JOB_H_

#include "Observer.h"

namespace pickandplace {


class Job : public Observer {
public:
	enum JobState {none, finished, working};
	Job();
	virtual ~Job();

	void handleEvent();
	virtual void start()=0;
	virtual void recalculate()=0;

	Job::JobState getState();

private:
	Job::JobState state;
};

} /* namespace pickandplace */

#endif /* JOB_H_ */
