#define CAMERAIMAGE "/home/enrico/examples/src/c++/pickandplace/cameraImage.ppm"

#include <iostream>
#include <stdlib.h>
#include "rec/robotino/api2/all.h"
//#include "MyCom.h"
//#include "CameraExtender.h"
//#include "CylinderDetection.h"
//#include "RelativeRobotPosition.h"
#include "Controller.h"

using namespace rec::robotino::api2;
using namespace pickandplace;
using namespace std;

//MyCom com;
//CameraExtender camera;

//void init(const string& hostname) {
//	// Connect
//	cout << "Connecting...";
//	com.setAddress(hostname.c_str());
//
//	com.connectToServer(true);
//
//	if (false == com.isConnected()) {
//		cout << endl << "Could not connect to " << com.address()
//				<< endl;
//
//		shutdown();
//		exit(1);
//	} else {
//		cout << "success" << endl;
//	}
//}
//
//void destroy() {
//	com.disconnectFromServer();
//}

int main(int argc, char **argv) {
	int depotNumber;

	Controller * controller = new Controller();
	controller->followLine();
	controller->rotate(42.0);
	controller->driveDistance(0.25, 0.0);
	controller->searchCylinder(1);

//	string hostname = "172.26.1.1";
//	if (argc > 1) {
//		hostname = argv[1];
//	}
//
//	try {
//		init(hostname);
//
//		int pixelDif;
//		float leftPercentage;
//		float rightPercentage;
//		RelativeRobotPosition position;
//
//		while (com.isConnected()) {
//			com.processEvents();
//			position.getPosition(&pixelDif, &leftPercentage, &rightPercentage);
//		}
//
//		destroy();
//		waitForKey();
//	} catch (const RobotinoException& e) {
//		cerr << "Robotino Error: " << e.what() << endl;
//	} catch (const exception& e) {
//		cerr << "Error: " << e.what() << endl;
//	} catch (...) {
//		cerr << "Unknow Error" << endl;
//	}
//
//	cout << "Press any key to exit..." << endl;
//	waitForKey();
}
