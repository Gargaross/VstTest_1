#pragma once

#include <vector>

#include "pluginterfaces\base\ftypes.h"

typedef std::vector<double> FilterConstants;

enum FilterChannel {
	Left,
	Right
};

// Make it possible to use arbitrary amount of channels

class Filter {
public:
	Filter();

	void Process(float* data, Steinberg::int32 numOfSamples, FilterChannel channel);
	void SetConstants(const double& a1_in,
		const double& a2_in,
		const double& b0_in,
		const double& b1_in,
		const double& b2_in);
	void SetConstants(FilterConstants constants);

private:
	double mZ1[2];
	double mZ2[2];
	double* z1;
	double* z2;
	double a1, a2, b0, b1, b2;
	int channelCount;
};