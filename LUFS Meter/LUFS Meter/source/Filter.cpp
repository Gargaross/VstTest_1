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
	double z1, z2;

	if (channel == FilterChannel::Left) {
		z1 = mZ1[0];
		z2 = mZ2[0];
	}
	else {
		z2 = mZ1[1];
		z2 = mZ2[1];
	}

	for (int sample = 0; sample < numOfSamples; sample++) {
		double in = data[sample];
		double factorForB0 = in - a1 * z1 - a2 * z2;

		data[sample] = b0 * factorForB0 + b1 * z1 + b2 * z2;
		
		z2 = z1;
		z1 = factorForB0;
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
