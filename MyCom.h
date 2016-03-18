/*
 * MyCom.h
 *
 *  Created on: 18.03.2016
 *      Author: enrico
 */

#ifndef MYCOM_H_
#define MYCOM_H_

#include "rec/robotino/api2/all.h"
#include <stdlib.h>
#include <iostream>

using namespace rec::robotino::api2;
using namespace std;

namespace pickandplace {



class MyCom: public Com {
public:
	MyCom();

	void errorEvent(const char* errorString);

	void connectedEvent();

	void connectionClosedEvent();

	void logEvent(const char* message, int level);
};

} /* namespace pickandplace */

#endif /* MYCOM_H_ */
