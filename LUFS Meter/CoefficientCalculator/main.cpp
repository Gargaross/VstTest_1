
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "converter.h"

using namespace std;

const double HS_48k_a1 = -1.69065929318241;
const double HS_48k_a2 = 0.73248077421585;
const double HS_48k_b0 = 1.53512485958697;
const double HS_48k_b1 = -2.69169618940638;
const double HS_48k_b2 = 1.198329281085285;

const double HPF_48k_a1 = -1.99004745483398;
const double HPF_48k_a2 = 0.99007225036621;
const double HPF_48k_b0 = 1.0;
const double HPF_48k_b1 = -2.0;
const double HPF_48k_b2 = 1.0;

const string fileName = "Coefficients.txt";

void PrintToFile(const string& str, const double& sampleRate, const SampleRateConverter& highPassFilter)
{
	ofstream file;
	file.open(fileName, fstream::in | fstream::out | fstream::app);

	if (file.is_open()) {
		file << "Type: " << str << endl;
		file << "Sample Rate: " << sampleRate << endl;

		file.precision(15);
		file << "a1: " << highPassFilter.GetA1() << endl; 
		file << "a2: " << highPassFilter.GetA2() << endl;
		file << "b0: " << highPassFilter.GetB0() << endl;
		file << "b1: " << highPassFilter.GetB1() << endl;
		file << "b2: " << highPassFilter.GetB2() << endl;

		file << endl;
	}
}


int main()
{
	vector<double> sampleRates = { 22050, 24000, 44100, 48000, 88200, 96000, 176400, 192000 };

	SampleRateConverter highShelfFilter(
		HS_48k_a1,
		HS_48k_a2,
		HS_48k_b0,
		HS_48k_b1,
		HS_48k_b2);
	SampleRateConverter highPassFilter(
		HPF_48k_a1,
		HPF_48k_a2,
		HPF_48k_b0,
		HPF_48k_b1,
		HPF_48k_b2);

	remove(fileName.c_str());

	for (double sampleRate : sampleRates) {
		highShelfFilter.ConvertTo(sampleRate);
		highPassFilter.ConvertTo(sampleRate);

		PrintToFile("High Shelf filter", sampleRate, highShelfFilter);
		PrintToFile("High Pass filter", sampleRate, highPassFilter);
	}

	return 0;
}