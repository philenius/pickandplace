/*
 * Subject.cpp
 *
 *  Created on: 15.04.2016
 *      Author: enrico
 */

#include "Subject.h"

namespace pickandplace {

Subject::Subject() {
}

Subject::~Subject() {
}

void Subject::subscribe(Observer *obs) {
	observers.push_back(obs);
}

void Subject::unsubscribe(Observer *obs) {
	observers.remove(obs);
}

void Subject::notify() {
	if(observers.empty()) {
		return;
	}
	for(std::list<Observer *>::iterator it = observers.begin(); it != observers.end(); it++) {
		(*it)->handleEvent();
	}
}

} /* namespace pickandplace */
