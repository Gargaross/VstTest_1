#include "Filter.h"

Filter::Filter()
{
	b0 = 0;
	b1 = 0;
	b2 = 0;
	a1 = 0;
	a2 = 0;
}


void Filter::Process(float* data, Steinberg::int32 numOfSamples, FilterChannel channel)
{
	int channelIndex;

	if (channel == FilterChannel::Left) {
		channelIndex = 0;
	}
	else {
		channelIndex = 1;
	}

	for (int sample = 0; sample < numOfSamples; sample++) {
		double in = data[sample];
		double factorForB0 = in - a1 * mZ1[channelIndex] - a2 * mZ2[channelIndex];

		double out = b0 * factorForB0 + b1 * mZ1[channelIndex] + b2 * mZ2[channelIndex];
		
		mZ2[channelIndex] = mZ1[channelIndex];
		mZ1[channelIndex] = factorForB0;

		if (!(data[sample] < -1.0e-8 || data[sample] > 1.0e-8)) {
			data[sample] = 0.0;
		}

		data[sample] = (float)out;
	}
}


void Filter::SetConstants(
	const double& b0_in,
	const double& b1_in, 
	const double& b2_in,
	const double& a1_in,
	const double& a2_in)
{
	b0 = b0_in;
	b1 = b1_in;
	b2 = b2_in;
	a1 = a1_in;
	a2 = a2_in;
}
