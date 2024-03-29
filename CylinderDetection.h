/*
 * CylinderDetection.h
 *
 *  Created on: 08.03.2016
 *      Author: enrico
 */

#ifndef CYLINDERDETECTION_H_
#define CYLINDERDETECTION_H_

#include <opencv2/opencv.hpp>
#include "Env.h"

using namespace std;
using namespace cv;

namespace pickandplace {

class CylinderDetection {
public:
	CylinderDetection();
	virtual ~CylinderDetection();
	bool IsCylinderPresent();

private:
	string cameraImage;
};

} /* namespace pickandplace */

#endif /* CYLINDERDETECTION_H_ */
