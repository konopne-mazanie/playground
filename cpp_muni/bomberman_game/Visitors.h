#pragma once

// A collection of useful visitors.
#include "ObjectVisitorSkeleton.h"

struct DeadPlayerDetector : ConstObjectVisitorSkeleton {
	bool detected = false;
	void operator()(Player const  &player) override { detected = detected || player.isDead(); }
};
