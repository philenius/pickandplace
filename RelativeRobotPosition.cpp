/*
 * CenterRobot.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Phil
 */

#include "RelativeRobotPosition.h"

namespace pickandplace {

RelativeRobotPosition::RelativeRobotPosition() {
	namedWindow("debug info");
}

RelativeRobotPosition::~RelativeRobotPosition() {
}

void RelativeRobotPosition::getPosition(float* differenceOfPixels,
		float* leftPixelPercentage, float* rightPixelPercentage) {
	Mat src;

	src = ExtractColoredBox();

	if (!src.data) {
		cout << "Extracted image could not be loaded!" << endl;
		throw "Extracted image could not be loaded!";
	}

	// The left mask covers the left half of the image (vertical cut).
	Mat leftMask(src.rows, src.cols, CV_8U, Scalar(0, 0, 0));
	rectangle(leftMask, Point(0, 0), Point(src.cols / 2, src.rows),
			Scalar(255, 255, 255), -1);

	// The right mask covers the right half of the image (vertical cut).
	Mat rightMask(src.rows, src.cols, CV_8U, Scalar(0, 0, 0));
	rectangle(rightMask, Point(src.cols / 2, 0), Point(src.cols, src.rows),
			Scalar(255, 255, 255), -1);

	// Applies mask to the image
	Mat leftHalfOfImage, rightHalfOfImage;
	bitwise_and(src, leftMask, leftHalfOfImage);
	bitwise_and(src, rightMask, rightHalfOfImage);

	int leftPixelCount = countNonZero(leftHalfOfImage);
	int rightPixelCount = countNonZero(rightHalfOfImage);

	// negative means: too much on the left side; positive means: too much in the right side
	float resultValue = rightPixelCount - leftPixelCount;
	cout << "result: " << resultValue << endl;

	int totalPixels = leftPixelCount + rightPixelCount;
	float leftSideRatioValue = (float) leftPixelCount / totalPixels;
	float rightSideRatioValue = (float) rightPixelCount / totalPixels;

	differenceOfPixels = &resultValue;
	leftPixelPercentage = &leftSideRatioValue;
	rightPixelPercentage = &rightSideRatioValue;

	// Only write debug info if there enough yellow pixels detected
	if ((leftPixelCount + rightPixelCount) > 300) {
		WriteDebugInfo(leftSideRatioValue, rightSideRatioValue,
				leftPixelCount + rightPixelCount);
	} else {
		Size size(320, 240);
		Mat empty(size, CV_8UC3, Scalar(0, 0, 0));
		putText(empty, "< 300 pixels detected", Point(55, 120), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
		imshow("debug info", empty);
	}
}

void RelativeRobotPosition::WriteDebugInfo(float leftSidePercentage,
		float rightSidePercentage, int nonZeroPixels) {
	Mat src;

	src = imread(CAMERAIMAGE, CV_LOAD_IMAGE_COLOR);

	if (!src.data) {
		return;
	}

	string strLeft = convertFloatToString((int) (100 * leftSidePercentage));
	string strRight = convertFloatToString((int) (100 * rightSidePercentage));
	string strNonZero = convertFloatToString(nonZeroPixels);

	string text1 = "left: ";
	text1.append(strLeft);
	text1.append(" %");

	string text2 = "right: ";
	text2.append(strRight);
	text2.append(" %");

	string text3 = "total px: ";
	text3.append(strNonZero);

	// If the robot is nearly in the middle of the yellow cardboard, then the text "centered" is displayed.
	if (leftSidePercentage >= 0.35 && rightSidePercentage >= 0.35) {
		putText(src, "centered", Point(160, 20), CV_FONT_NORMAL, 0.9,
				Scalar(255, 255, 255));
		putText(src, text3, Point(25, 20), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
	} else {
		putText(src, text1, Point(25, 20), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
		putText(src, text2, Point(25, 50), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
		putText(src, text3, Point(25, 80), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
	}

	// If the robot is about to center, then the color of the vertical line changes from white to green.
	Scalar lineColor(255, 255, 255);
	if (leftSidePercentage >= 0.15 && rightSidePercentage >= 0.15) {
		lineColor = Scalar(0, 255, 0);
	}
	line(src, Point(src.cols / 2, 0), Point(src.cols / 2, src.rows), lineColor,
			2, 8);

	// Shows image
	imshow("debug info", src);
	waitKey(2);
}

Mat RelativeRobotPosition::ExtractColoredBox() {

	Mat src, hsv, dst;

	src = imread(CAMERAIMAGE, CV_LOAD_IMAGE_COLOR);

	if (!src.data) {
		cout << "Camera image could not be loaded!" << endl;
		throw "Camera image could not be loaded!";
	}

	// Converts image to HSV
	cvtColor(src, hsv, CV_BGR2HSV);

	// Applies a binary threshold filtering for yellow colors
	Scalar lowerBoundary(19, 56.1, 147.9);
	Scalar upperBoundary(33.5, 168.3, 255);
	inRange(hsv, lowerBoundary, upperBoundary, dst);

	// Shows image
	imshow("binary threshold", dst);
	waitKey(2);

	return dst;
}

string RelativeRobotPosition::convertFloatToString(float value) {
	ostringstream stream;
	stream << value;
	string str = stream.str();
	return str;
}

} /* namespace pickandplace */