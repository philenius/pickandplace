/*
 * CameraExtender.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Phil
 */

#include "CameraExtender.h"

namespace pickandplace {

CameraExtender::CameraExtender() {
}

CameraExtender::~CameraExtender() {
}

void CameraExtender::settingsChangedEvent(unsigned int width,
		unsigned int height, const char * format) {
	cout << LINE << endl;
	cout << "Image width: " << width << endl;
	cout << "Image height: " << height << endl;
	cout << LINE << endl;
}

void CameraExtender::capabilitiesChangedEvent(
		const CameraCapabilities & capibilites) {
	cout << LINE << endl;
	cout << "The connected camera supports the following settings:" << endl;

	cout << TAB << "auto white balance: " << capibilites.autoWhiteBalance
			<< endl;
	cout << TAB << "auto exposure: " << capibilites.autoExposure << endl;
	cout << TAB << "auto focus: " << capibilites.autoFocus << endl;

	cout << TAB << "backlight compensation: "
			<< capibilites.backlightCompensation << endl;
	cout << TAB << "brightness: " << capibilites.brightness << endl;
	cout << TAB << "contrast: " << capibilites.contrast << endl;
	cout << TAB << "exposure: " << capibilites.exposure << endl;
	cout << TAB << "focus: " << capibilites.focus << endl;
	cout << TAB << "gain: " << capibilites.gain << endl;
	cout << TAB << "saturation: " << capibilites.saturation << endl;
	cout << TAB << "sharpness: " << capibilites.sharpness << endl;
	cout << TAB << "white balance temperature: "
			<< capibilites.whiteBalanceTemperature << endl;
	cout << LINE << endl;
}

void CameraExtender::imageReceivedEvent(const unsigned char* data,
		unsigned int dataSize, unsigned int width, unsigned int height,
		unsigned int step) {

//	// Counter for the stored images. Gets reseted every time when the value of fps is reached.
//	static unsigned int sequence = 0;
//	// Counts the amount of calls of this method.
//	static unsigned long countCalls = 0;
//	// Stores the start time of this program
//	static const clock_t beginTime = clock();
//	static unsigned int fps;
//
//	countCalls < ULONG_MAX ? countCalls++ : countCalls = 0;
//
//	// Calculate frames per second
//	float elapsedTime = (clock() - beginTime) / 1000000;
//	fps = countCalls / elapsedTime;
//
//	// Only save the image once per second
//	if (sequence < fps) {
//		sequence++;
//		return;
//	}
//
//	sequence = 0;

	ostringstream outputStream;
	outputStream << "cameraImage" << ".ppm";

	FILE* fp = fopen(outputStream.str().c_str(), "w");
	if (fp == NULL) {
		cerr << "Error: Cannot open file " << outputStream.str() << endl;
	} else {
		fprintf(fp, "P6 %d %d 255\n", width, height);
		fwrite(data, width * height * 3, 1, fp);
		fclose(fp);
	}
}
}
