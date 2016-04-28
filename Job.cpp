/*
 * Job.cpp
 *
 *  Created on: 16.04.2016
 *      Author: enrico
 */

#include "Job.h"

using namespace std;

namespace pickandplace {

Job::Job() {
	Job::state = none;
}

Job::~Job() {
}

void Job::handleEvent(){
	if(Job::getState() == none) {
		start();
	}
	else if(Job::getState() == working) {
		recalculate();
	}
}

Job::JobState Job::getState(){
	return state;
}

} /* namespace pickandplace */
