#pragma once

class SampleRateConverter {
public:
	SampleRateConverter(
		const double& a1_in,
		const double& a2_in,
		const double& b0_in,
		const double& b1_in,
		const double& b2_in);

	void ConvertTo(const double& sampleRate);

	double GetA1() const { return a1; }
	double GetA2() const { return a2; }
	double GetB0() const { return b0; }
	double GetB1() const { return b1; }
	double GetB2() const { return b2; }

private:
	double a1_48k;
	double a2_48k;
	double b0_48k;
	double b1_48k;
	double b2_48k;

	double a1;
	double a2;
	double b0;
	double b1;
	double b2;
};