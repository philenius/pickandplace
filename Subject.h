/*
 * Subject.h
 *
 *  Created on: 15.04.2016
 *      Author: enrico
 */

#ifndef SUBJECT_H_
#define SUBJECT_H_

#include "Observer.h"
#include <list>

namespace pickandplace {

class Subject {
public:
	Subject();
	virtual ~Subject();

	void subscribe(Observer *obs);
	void unsubscribe(Observer *obs);

	void notify();

private:
	std::list<Observer *> observers;
};

} /* namespace pickandplace */

#endif /* SUBJECT_H_ */
