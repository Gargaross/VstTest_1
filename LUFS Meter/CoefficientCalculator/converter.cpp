
#include "converter.h"
#include <math.h>

SampleRateConverter::SampleRateConverter(
	const double& a1_in,
	const double& a2_in,
	const double& b0_in,
	const double& b1_in,
	const double& b2_in)
{
	a1_48k = a1_in;
	a2_48k = a2_in;
	b0_48k = b0_in;
	b1_48k = b1_in;
	b2_48k = b2_in;

	a1 = 0;
	a2 = 0;
	b0 = 0;
	b1 = 0;
	b2 = 0;
}


void SampleRateConverter::ConvertTo(const double& sampleRate)
{
	double Q, arctanK, VB, VH, VL, sampleRate48k;
	sampleRate48k = 48000;

	const double KoverQ = (2. - 2. * a2_48k) / (a2_48k - a1_48k + 1.);
	const double K = sqrt((a1_48k + a2_48k + 1.) / (a2_48k - a1_48k + 1.));
	Q = K / KoverQ;
	arctanK = atan(K);
	VB = (b0_48k - b2_48k) / (1. - a2_48k);
	VH = (b0_48k - b1_48k + b2_48k) / (a2_48k - a1_48k + 1.);
	VL = (b0_48k + b1_48k + b2_48k) / (a1_48k + a2_48k + 1.);

	const double K2 = tan(arctanK * sampleRate48k / sampleRate);
	const double commonFactor = 1. / (1. + K2 / Q + K2 * K2);
	b0 = (VH + VB * K2 / Q + VL * K2*K2)*commonFactor;
	b1 = 2.*(VL*K2*K2 - VH)*commonFactor;
	b2 = (VH - VB * K2 / Q + VL * K2*K2)*commonFactor;
	a1 = 2.*(K2*K2 - 1.)*commonFactor;
	a2 = (1. - K2 / Q + K2 * K2)*commonFactor;
}