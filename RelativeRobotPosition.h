/*
 * CenterRobot.h
 *
 *  Created on: 05.04.2016
 *      Author: Phil
 */

#ifndef RELATIVEROBOTPOSITION_H_
#define RELATIVEROBOTPOSITION_H_

#include <iostream>
#include <stdlib.h>
#include "Env.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace pickandplace {

class RelativeRobotPosition {
public:
	RelativeRobotPosition();
	virtual ~RelativeRobotPosition();

	/**
	 * Calculates the relative position of the robot compared to the yellow cardboard. The yellow cardboard has to be directly in the middle of the platform.
	 * The size of the cardboard doesn't matter, only it has to be visible for the camera. All bright and dark tones of yellow cardboard will be detected.
	 * This method divides the camera image in two halves (vertical cut). Then the amount of detected yellow pixels is counted.
	 * @param differenceOfPixels	The difference of right pixels to left pixels (right - left). If this value is negative, then the robots need to be moved
	 * 								more to the left. If this value is positive, then the robots needs to be moved more to the right.
	 * @param leftPixelPercentage	The amount of yellow pixels in percent (of all pixels) residing on the left half of the camera image.
	 * @param rightPixelPercentage	The amount of yellow pixels in percent (of all pixels) residing on the right half of the camera image.
	 */
	void getPosition(float* differenceOfPixels, float* leftPixelPercentage,
			float* rightPixelPercentage);

private:

	/**
	 * Applies a binary threshold on the image filtering for yellow colors. This method is specified to extract a yellow piece of cardboard.
	 * This method detects even very dark or bright tones of yellow.
	 * @return Returns the image with the applied binary threshold.
	 */
	Mat ExtractColoredBox();

	/**
	 * Displays debug information such as the ratio of pixels on the left compared to pixels on the right side. Debug infos are written onto the
	 * original camera image.
	 * @param leftSidePercentage	The amount of yellow pixels in percent on the left half of the camera image.
	 * @param rightPixelPercentage	The amount of yellow pixels in percent on the right half of the camera image.
	 */
	void WriteDebugInfo(float leftSidePercentage, float rightSidePercentage, int noneZeroPixels);

	/**
	 * Converts a given float to a string.
	 * @param value	The float value which shall be converted.
	 * @return		The float represented by a string.
	 */
	string convertFloatToString(float value);
};

} /* namespace pickandplace */

#endif /* RELATIVEROBOTPOSITION_H_ */
