/*
 * Controller.h
 *
 *  Created on: 15.04.2016
 *      Author: enrico
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace pickandplace {

class Controller {
public:
	Controller();
	virtual ~Controller();

	void mainSequence();

	void driveFromInitialToLeftPlatform();
	void driveFromLeftToRightPlatform();
	void driveFromRightToLeftPlatform();
	void targetStacker(int stackerNumber);
	void scanStackerStates();

private:
	void executionLoop(int timeOutSeconds, bool executableJob);
};

} /* namespace pickandplace */

#endif /* CONTROLLER_H_ */
