/*
 * MyCom.cpp
 *
 *  Created on: 18.03.2016
 *      Author: enrico
 */

#include "MyCom.h"

namespace pickandplace {

MyCom::MyCom() : Com("pickandplace") {
}

void MyCom::errorEvent(const char* errorString) {
	cerr << "Error: " << errorString << endl;
}

void MyCom::connectedEvent() {
	cout << "Connected." << endl;
}

void MyCom::connectionClosedEvent() {
	cout << "Connection closed." << endl;
}

void MyCom::logEvent(const char* message, int level) {
	cout << message << endl;
}

} /* namespace pickandplace */
