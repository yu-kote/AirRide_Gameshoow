#pragma once
#include "cinder/app/AppNative.h"


enum Window {
	WIDTH = 1024,
	HEIGHT = 1024
};


bool sphereToSphere(ci::Vec3f pos1_, float radius1_, ci::Vec3f pos2_, float radius2_);