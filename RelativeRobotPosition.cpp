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

void RelativeRobotPosition::getPositionForYellowCardboard(
		int* differenceOfPixels, float* leftPixelPercentage,
		float* rightPixelPercentage, int* totalPixelCount) {
	Mat src;
	src = ExtractYellowBox();

	countLeftAndRightSidePixels(src, differenceOfPixels, leftPixelPercentage, rightPixelPercentage, totalPixelCount);
}

void RelativeRobotPosition::getPositionForBlackLine(int* differenceOfPixels,
		float* leftPixelPercentage, float* rightPixelPercentage, int* totalPixelCount) {
	Mat src;
	src = ExtractBlackLine();

	countLeftAndRightSidePixels(src, differenceOfPixels, leftPixelPercentage, rightPixelPercentage, totalPixelCount);
}

void RelativeRobotPosition::countLeftAndRightSidePixels(const Mat& src, int* differenceOfPixels,
		float* leftPixelPercentage, float* rightPixelPercentage, int* totalPixelCount) {
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
	cout << "left: " << leftPixelCount << "    right: " << rightPixelCount << endl;

	// negative means: too much on the left side; positive means: too much in the right side
	int resultValue = rightPixelCount - leftPixelCount;

	int totalPixels = leftPixelCount + rightPixelCount;
	float leftSideRatioValue = (float) (leftPixelCount) / totalPixels;
	float rightSideRatioValue = (float) (rightPixelCount) / totalPixels;

	*differenceOfPixels = resultValue;
	*leftPixelPercentage = leftSideRatioValue;
	*rightPixelPercentage = rightSideRatioValue;
	*totalPixelCount = totalPixels;

	// Only write debug info if enough pixels are detected
	if ((leftPixelCount + rightPixelCount) > 300) {
		WriteDebugInfo(leftSideRatioValue, rightSideRatioValue,
				leftPixelCount + rightPixelCount);
	} else {
		Size size(320, 240);
		Mat empty(size, CV_8UC3, Scalar(0, 0, 0));
		putText(empty, "< 300 pixels detected", Point(55, 120), CV_FONT_NORMAL,
				0.6, Scalar(255, 255, 255));
		imshow("debug info", empty);
	}
}

bool RelativeRobotPosition::isYellowBoxInCenter(int threshold) {
	Mat src = this->ExtractYellowBox();

	// The mask covers the center of the camera image with a radius of 30 pixels
	Mat mask(src.rows, src.cols, CV_8U, Scalar(0, 0, 0));
	rectangle(mask, Point(src.cols / 2 - 30, 0),
			Point(src.cols / 2 + 30, src.rows), Scalar(255, 255, 255), -1);

	// Applies mask to image and counts the non zero pixels
	Mat dst;
	bitwise_and(src, mask, dst);
	int count = countNonZero(dst);

	if (count >= threshold) {
		return true;
	}
	return false;
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
		putText(src, "centered", Point(170, 20), CV_FONT_NORMAL, 0.9,
				Scalar(255, 255, 255));
		putText(src, text3, Point(10, 20), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
	} else {
		putText(src, text1, Point(10, 20), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
		putText(src, text2, Point(10, 50), CV_FONT_NORMAL, 0.6,
				Scalar(255, 255, 255));
		putText(src, text3, Point(10, 80), CV_FONT_NORMAL, 0.6,
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

Mat RelativeRobotPosition::ExtractYellowBox() {

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

	// Applies an opening morphological operation to the image
	Mat eroded, dilated;
	Mat element = getStructuringElement(MORPH_RECT, Size(4, 4));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(12, 12));

	erode(dst, eroded, element);
	dilate(eroded, dilated, element2);

	// Shows image
	imshow("binary threshold", dilated);
	waitKey(2);

	return dilated;
}

Mat RelativeRobotPosition::ExtractBlackLine() {

	Mat src, gray, dst;

	src = imread(CAMERAIMAGE, CV_LOAD_IMAGE_COLOR);

	if (!src.data) {
		cout << "Camera image could not be loaded!" << endl;
		throw "Camera image could not be loaded!";
	}

	// Convert image into grayscale
	cvtColor(src, gray, CV_RGB2GRAY);

	// Applies a binary threshold filtering for black tones
	Scalar lowerBoundary(0, 0, 0);
	Scalar upperBoundary(100, 100, 100);
	inRange(gray, lowerBoundary, upperBoundary, dst);

	// The mask covers the upper half of the image (horizontal cut).
	Mat mask(src.rows, src.cols, CV_8U, Scalar(0, 0, 0));
	rectangle(mask, Point(0, 0), Point(src.cols, src.rows / 2),
			Scalar(255, 255, 255), -1);

	// Applies mask to the image
	Mat maskedImage;
	bitwise_and(dst, mask, maskedImage);


	// Shows image
	imshow("binary threshold", maskedImage);
	waitKey(2);

	return maskedImage;
}

string RelativeRobotPosition::convertFloatToString(float value) {
	ostringstream stream;
	stream << value;
	string str = stream.str();
	return str;
}

} /* namespace pickandplace */
