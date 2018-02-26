#pragma once

#include "pluginterfaces\base\ftypes.h"

enum FilterChannel {
	Left,
	Right
};

class Filter {
public:
	Filter();

	void Process(float* data, Steinberg::int32 numOfSamples, FilterChannel channel);
	void SetConstants(const double& b0_in,
		const double& b1_in,
		const double& b2_in,
		const double& a1_in,
		const double& a2_in);

private:
	double mZ1[2];
	double mZ2[2];
	double b0, b1, b2, a1, a2;
};