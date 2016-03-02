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

/**
 * This method handles the COM events and stores the received images on the hard disk.
 * The frames per second (fps) are counted and once per second the image is saved. The old image will be overwritten.
 * The image is saved above the "target" folder as "cameraImage.ppm".
 *
 * @param data
 * @param dataSize
 * @param width
 * @param height
 * @param step
 */
void CameraExtender::imageReceivedEvent(const unsigned char* data,
		unsigned int dataSize, unsigned int width, unsigned int height,
		unsigned int step) {

	// Counter for the stored images. Gets reseted every time when the value of fps is reached.
	static unsigned int sequence = 0;
	// Counts the amount of calls of this method.
	static unsigned long countCalls = 0;
	// Stores the start time of this program
	static const clock_t beginTime = clock();
	static unsigned int fps;

	countCalls < sizeof(unsigned long) ? countCalls++ : countCalls = 0;

	// Calculate frames per second
	float elapsedTime = (clock() - beginTime) / 1000000;
	fps = countCalls / elapsedTime;

	// Only save the image once per second
	if (sequence < fps) {
		sequence++;
		return;
	}

	sequence = 0;

	ostringstream outputStream;
	outputStream << "cameraImage" << ".ppm";

	FILE* fp = fopen(outputStream.str().c_str(), "w");
	if (fp == NULL) {
		cerr << "Error: Cannot open file " << outputStream.str() << std::endl;
	} else {
		cout << "wrote image to file " << outputStream.str() << endl;
		fprintf(fp, "P6 %d %d 255\n", width, height);
		fwrite(data, width * height * 3, 1, fp);
	}
}
}
