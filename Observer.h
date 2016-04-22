/*
 * Observer.h
 *
 *  Created on: 15.04.2016
 *      Author: enrico
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

namespace pickandplace {

class Observer {
public:
	Observer();
	virtual ~Observer();

	virtual void handleEvent()=0;
};

} /* namespace pickandplace */

#endif /* OBSERVER_H_ */
