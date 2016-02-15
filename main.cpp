//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "rec/robotino/api2/all.h"

using namespace rec::robotino::api2;

class MyCom : public Com
{
public:
	MyCom()
		: Com( "example_circle" )
	{
	}

	void errorEvent( const char* errorString )
	{
		std::cerr << "Error: " << errorString << std::endl;
	}

	void connectedEvent()
	{
		std::cout << "Connected." << std::endl;
	}

	void connectionClosedEvent()
	{
		std::cout << "Connection closed." << std::endl;
	}

	void logEvent( const char* message, int level )
	{
		std::cout << message << std::endl;
	}
};

MyCom com;
OmniDrive omniDrive;
Bumper bumper;
AnalogInput analogInput;
DigitalInput digitalInput[4];
ElectricalGripper electricalGripper;
float fe; //Regelabweichung
float fDrehung; //omegawert f�r omnidrive
float fesum = 0; //f�r I-Regler
float fealt = 6; // f�r D-Regler

void init( const std::string& hostname )
{
	// Initialize the actors

	// Connect
	std::cout << "Connecting...";
	com.setAddress( hostname.c_str() );

	com.connectToServer( true );

	if( false == com.isConnected() )
	{
		std::cout << std::endl << "Could not connect to " << com.address() << std::endl;

		rec::robotino::api2::shutdown();
		exit(1);
	}
	else
	{
		std::cout << "success" << std::endl;
	}
}

void fahreLinie(){
		fe = analogInput.value() - 6;
//		std::cout << fesum << std::endl;
		fesum = fesum + fe;
/*		if (fe<0){
			fesum=0;
		}*/
		if (fesum > 100){
			fesum=100;
			}
		fDrehung = 3*fe+5*0.05*fesum+0.1*(fe-fealt)/0.05; //PID-Regler
		fealt = fe;
		omniDrive.setVelocity(0.07,0,fDrehung/57.3);//Werte in m/s und rad statt deg!
		usleep(50000);
}

void drive()
{
	analogInput.setInputNumber(0); //induktiver Sensor
	digitalInput[0].setInputNumber(0); //Lichtschranke Greifer
	digitalInput[1].setInputNumber(1); //Schieber Greifer
	digitalInput[2].setInputNumber(2); //Lichtsensor links
	digitalInput[3].setInputNumber(3); //Lichtsensor rechts
	bool sensorState = bumper.value();

	while( com.isConnected() && false == sensorState )
	{		
		while (digitalInput[2].value() == false){
			fahreLinie();
		}
		electricalGripper.open();
		sleep(5);
		electricalGripper.close();
	}
}

void destroy()
{
	com.disconnectFromServer();
}

int main( int argc, char **argv )
{
	std::string hostname = "172.26.1.1";
	if( argc > 1 )
	{
		hostname = argv[1];
	}

	try
	{
		init( hostname );
		drive();
		destroy();
	}
	catch( const rec::robotino::api2::RobotinoException& e )
	{
		std::cerr << "Robotino Error: " << e.what() << std::endl;
	}
	catch( const std::exception& e )
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch( ... )
	{
		std::cerr << "Unknow Error" << std::endl;
	}

	//std::cout << "Press any key to exit..." << std::endl;
	//rec::core_lt::waitForKey();
}
