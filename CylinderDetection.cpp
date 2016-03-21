/*
 * CylinderDetection.cpp
 *
 *  Created on: 08.03.2016
 *      Author: Phil
 */

#include "CylinderDetection.h"

namespace pickandplace {

string cameraImage;

CylinderDetection::CylinderDetection(string cameraImage) {
	this->cameraImage = cameraImage;
}

CylinderDetection::~CylinderDetection() {
}

/**
 * This method detects whether a red cylinder is visible on the camer image or not. It converts the image into HSV
 * and applies threshold on it.
 *
 * @return Returns true, if a cylinder was detected; returns otherwise false
 */
bool CylinderDetection::IsCylinderPresent() {
	Mat src, hsv, dst;

	src = imread(this->cameraImage, CV_LOAD_IMAGE_COLOR);
	if (src.empty()) {
		cout << "Error! The image cannot be read" << endl;
		return -1;
	}

	// Convert to HSV
	cvtColor(src, hsv, CV_BGR2HSV);

	// Applies a binary threshold filtering for red colors with heavy variant saturation and brightness / value
	Scalar lowerBoundary(0, 100, 188);
	Scalar upperBoundary(13, 255, 255);
	inRange(hsv, lowerBoundary, upperBoundary, dst);

	// Count non-zero pixels
	int pixels = countNonZero(dst);

	// Investigations showed: Cylinder present -> 6761 pixels; Cylinder absent -> 0 pixels
	if (pixels >= 2000) {
		return true;
	}
	return false;
}

} /* namespace pickandplace */
