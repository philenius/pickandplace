/*
 * CameraExtender.h
 *
 *  Created on: 29.02.2016
 *      Author: Phil
 */

#ifndef CAMERAEXTENDER_H_
#define CAMERAEXTENDER_H_
#define TAB "\t"
#define LINE "#############################################################"

#include <sstream>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include "Subject.h"
#include "rec/robotino/api2/all.h"

using namespace rec::robotino::api2;
using namespace std;

namespace pickandplace {

class CameraExtender: Camera, public Subject {

public:
	CameraExtender();
	virtual ~CameraExtender();
private:
	/**
	 * This method handles the COM events for incoming images and stores the received images on the hard disk.
	 * The image is saved above the "target" folder as "cameraImage.ppm".
	 *
	 * @param data
	 * @param dataSize
	 * @param width
	 * @param height
	 * @param step
	 */
	void imageReceivedEvent(const unsigned char* data, unsigned int dataSize,
			unsigned int width, unsigned int height, unsigned int step);

	/**
	 * Reacts when the camera capabilities changed. This event happens also every time once on startup of the program.
	 * Prints out the camera capabilities.
	 * @param capabilities
	 */
	void capabilitiesChangedEvent(const CameraCapabilities & capabilities);

	/**
	 * Reacts when the size of the camera image was changed and prints the new size onto the console.
	 * @param width
	 * @param height
	 * @param format
	 */
	void settingsChangedEvent(unsigned int width, unsigned int height,
			const char * format);

};

}

#endif /* CAMERAEXTENDER_H_ */
