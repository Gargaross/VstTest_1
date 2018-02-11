#include "Common.h"

double NormalizedFrequencyToFrequency(float freqNorm)
{
	// Linear from 200 Hz to 8000 Hz
	return 200.0 + 7800*freqNorm;
}
