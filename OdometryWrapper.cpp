/*
 * OdometryWrapper.cpp
 *
 *  Created on: 15.03.2016
 *      Author: enrico
 */

#include "OdometryWrapper.h"

using namespace std;

namespace pickandplace {

OdometryWrapper::OdometryWrapper(){
	x_position = 0.0;
	y_position = 0.0;
	phi = 0.0;
	vx = 0.0;
	vy = 0.0;
	omega = 0.0;
	sequence = 0;
}

OdometryWrapper::~OdometryWrapper() {
}

void OdometryWrapper::readingsEvent(double x, double y, double phi, float vx, float vy, float omega, unsigned int sequence){
	x_position = x;
	y_position = y;
	this->phi = phi;
	this->vx = vx;
	this->vy = vy;
	this->omega = omega;
	this->sequence = sequence;

	if(x_position == 0.0 || y_position == 0.0 || phi == 0.0) return;

	notify();

//	// Test routine for event handling
//	printValues();
//
//	if(x_position < 0.2)
//	{
//		drive.setVelocity(0.2,0.0,0.0);
//		cout << "-move" << endl;
//	}
//	else
//	{
//		drive.setVelocity(0.0,0.0,0.0);
//		cout << "-stop" << endl;
//	}
}

void OdometryWrapper::reset(){
	set(0.0,0.0,0.0,true);
}

void OdometryWrapper::printValues(){
	cout << "#:  " << sequence << endl;
	cout << "X:  " << x_position << endl;
	cout << "Y:  " << y_position << endl;
	cout << "P:  " << phi << endl;
	cout << "Vx: " << vx << endl;
	cout << "Vy: " << vy << endl;
	cout << "Vp: " << omega << endl;
}



double OdometryWrapper::getX() {
	return x_position;
}
double OdometryWrapper::getY() {
	return y_position;
}
double OdometryWrapper::getPhi() {
	return phi;
}


} /* namespace pickandplace */
