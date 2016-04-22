/*
 * Job.cpp
 *
 *  Created on: 16.04.2016
 *      Author: enrico
 */

#include "Job.h"

namespace pickandplace {

Job::Job() {
	Job::state = none;
}

Job::~Job() {
}

void Job::handleEvent(){
	recalculate();
}

Job::JobState Job::getState(){
	return state;
}

} /* namespace pickandplace */
