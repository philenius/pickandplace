/*
 * OdometryWrapper.cpp
 *
 *  Created on: 15.03.2016
 *      Author: enrico
 */

#include "OdometryWrapper.h"

#include <iostream>

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

	notify();

//	// Test routine for event handling
//	printValues();
//
//	if(x_position < 0.2)
//	{
//		drive.setVelocity(0.2,0.0,0.0);
//		std::cout << "-move" << std::endl;
//	}
//	else
//	{
//		drive.setVelocity(0.0,0.0,0.0);
//		std::cout << "-stop" << std::endl;
//	}
}

void OdometryWrapper::reset(){
	set(0.0,0.0,0.0,true);
}

void OdometryWrapper::printValues(){
	std::cout << "#:  " << sequence << std::endl;
	std::cout << "X:  " << x_position << std::endl;
	std::cout << "Y:  " << y_position << std::endl;
	std::cout << "P:  " << phi << std::endl;
	std::cout << "Vx: " << vx << std::endl;
	std::cout << "Vy: " << vy << std::endl;
	std::cout << "Vp: " << omega << std::endl;
}


} /* namespace pickandplace */
