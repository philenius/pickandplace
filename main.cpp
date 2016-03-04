#include <iostream>
#include <stdlib.h>
#include "rec/robotino/api2/all.h"
#include "CameraExtender.h"

using namespace rec::robotino::api2;
using namespace pickandplace;
using namespace std;

class MyCom: public Com {
public:
	MyCom() :
			Com("pickandplace") {
	}

	void errorEvent(const char* errorString) {
		cerr << "Error: " << errorString << endl;
	}

	void connectedEvent() {
		cout << "Connected." << endl;
	}

	void connectionClosedEvent() {
		cout << "Connection closed." << endl;
	}

	void logEvent(const char* message, int level) {
		cout << message << endl;
	}
};

MyCom com;
CameraExtender camera;

void init(const string& hostname) {
	// Connect
	cout << "Connecting...";
	com.setAddress(hostname.c_str());

	com.connectToServer(true);

	if (false == com.isConnected()) {
		cout << endl << "Could not connect to " << com.address()
				<< endl;

		shutdown();
		exit(1);
	} else {
		cout << "success" << endl;
	}
}

void destroy() {
	com.disconnectFromServer();
}

int main(int argc, char **argv) {

	string hostname = "172.26.1.1";
	if (argc > 1) {
		hostname = argv[1];
	}

	try {
		init(hostname);

		while (com.isConnected()) {
			com.processEvents();
		}

		destroy();
	} catch (const RobotinoException& e) {
		cerr << "Robotino Error: " << e.what() << endl;
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	} catch (...) {
		cerr << "Unknow Error" << endl;
	}

	cout << "Press any key to exit..." << endl;
	waitForKey();
}
