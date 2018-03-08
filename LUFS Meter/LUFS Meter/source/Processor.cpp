
#include "Processor.h"
#include "Controller.h"
#include "LUFS Meter.h"
#include "Common.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "vstgui4\vstgui\lib\vstguidebug.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Steinberg {
namespace Vst {
	Processor::Processor() : 
		mBypass(false)
	{
		

		setControllerClass(LUFSMeterControllerUID);
	}


	tresult PLUGIN_API Processor::initialize(FUnknown* context)
	{
		tresult result = AudioEffect::initialize(context);
		if (result == kResultTrue)
		{
			addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
			addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
		}

		for (int i = 0; i < 2; i++) {
			z1[i] = 0;
			z2[i] = 0;
		}

		highShelfFilter.SetConstants(
			1.53512485958697,
			-2.69169618940638,
			1.19839281085285,
			-1.69065929318241,
			0.73248077421585);

		highPassFilter.SetConstants(
			1.0,
			-2.0,
			1.0,
			-1.99004745483398,
			0.99007225036621);

		mSampleBuffersProccessed = 0;

		return result;
	}


	tresult PLUGIN_API Processor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
	{
		// we only support one in and output bus and these buses must have the same number of channels
		if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
			return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
		return kResultFalse;
	}


	tresult PLUGIN_API Processor::setActive(TBool state)
	{
		SpeakerArrangement arr;
		if (getBusArrangement(kOutput, 0, arr) != kResultTrue)
			return kResultFalse;
		int32 numChannels = SpeakerArr::getChannelCount(arr);
		if (numChannels == 0)
			return kResultFalse;

		if (state)
		{
			// allocate memory
		}
		else
		{
			// free memory
		}
		return AudioEffect::setActive(state);
	}


	tresult PLUGIN_API Processor::process(ProcessData& data)
	{
		if (data.inputParameterChanges)
		{
			//bool recalcFilterConstants = false;

			int32 numParams = data.inputParameterChanges->getParameterCount();
			for (int32 index = 0; index < numParams; index++) {
				IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
				if (paramQueue) {
					ParamValue value;
					int32 sampleOffset;
					int32 numPoints = paramQueue->getPointCount();
					
					uint32 id = paramQueue->getParameterId();

					/*
					if (id == kFilterTypeId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value)) {
							if (value < 0.5f)
								mFilterType = 0.0; // LPF
							else
								mFilterType = 1.0; // HPF

							recalcFilterConstants = true;
						}
					}
					if (id == kCenterFreqId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
							mFrequencyNormalized = value;
							mFrequency = NormalizedFrequencyToFrequency(mFrequencyNormalized);

							recalcFilterConstants = true;
						}
					}
					if (id == kQId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
							mQValueNormalized = value;
							mQValue = NormalizedQToQ(mQValueNormalized);

							recalcFilterConstants = true;
						}
					}
					if (id == kGainId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value)) {
							mGain = value;

							recalcFilterConstants = true;
						}
					}
					*/
				}
			}

			/*
			if (recalcFilterConstants) {
				// Recalc filter constants here
				// TODO support more than one sample rate frequency
				// TODO This is the LPF calculations
				double K = tan(M_PI * mFrequency / 44100.0);
				double norm = 1 / (1 + K / mQValue + K * K);
				b0 = K * K * norm;
				b1 = 2 * b0;
				b2 = b0;
				a1 = 2 * (K * K - 1) * norm;
				a2 = (1 - K / mQValue + K * K) * norm;

				// Maybe reset Z values?
			}
			*/
		}

		if (data.numSamples > 0)
		{
			// Both FL Studio 12 and VST Host tester uses 32 bit samples

			SpeakerArrangement arr;
			getBusArrangement(kOutput, 0, arr);
			int32 numChannels = SpeakerArr::getChannelCount(arr);

			double meanSquare = mLUFS;

			for (int32 channel = 0; channel < numChannels; channel++) {
				float* outputChannel = data.outputs[0].channelBuffers32[channel];
				float* inputChannel = data.inputs[0].channelBuffers32[channel];

				highShelfFilter.Process(inputChannel, data.numSamples, (channel == 0) ? FilterChannel::Left : FilterChannel::Right);

				highPassFilter.Process(inputChannel, data.numSamples, (channel == 0) ? FilterChannel::Left : FilterChannel::Right);

				double sampleSum = 0.0;

				for (int32 sample = 0; sample < data.numSamples; sample++) {
					//mLUFS = inputChannel[sample];
					
					// Bypass
					outputChannel[sample] = inputChannel[sample];

					sampleSum += inputChannel[sample];
					
					/*
					double factorForB0 = inputChannel[sample] - a1 * z1[channel] - a2 * z2[channel];
					outputChannel[sample] = b0 * factorForB0 + b1 * z1[channel] + b2 * z2[channel];

					z2[channel] = z1[channel];
					z1[channel] = factorForB0;
					*/

					/*
					if (mBypass) {
						outputChannel[sample] = inputChannel[sample];
					}
					else {
					*/

					/*
					double in = inputChannel[sample];
					
					outputChannel[sample] = b0 * in + z1[channel];
					z1[channel] = b1 * in + z2[channel] - a1 * outputChannel[sample];
					z2[channel] = b2 * in - a2 * outputChannel[sample];
					*/
				}

				if (meanSquare > 0.0) {
					double sampleSumMean = pow(sampleSum, 2) / data.numSamples;
					meanSquare = (meanSquare + sampleSumMean) / 2; // needs to be divided 
					// mSampleBuffersProccessed might solve this?
				}
				else {
					meanSquare = pow(sampleSum, 2) / data.numSamples;
				}

				mLUFS = meanSquare;
				mSampleBuffersProccessed++;
			}
		}

		IParameterChanges* outParamChanges = data.outputParameterChanges;
		if (outParamChanges) {
			int32 index = 0;
			IParamValueQueue* paramQueue = outParamChanges->addParameterData(kLUFSId, index);
			if (paramQueue) {
				int32 index2 = 0;
				paramQueue->addPoint(0, mLUFS, index2);
			}
		}

		return kResultTrue;
	}


	tresult PLUGIN_API Processor::setState(IBStream* state)
	{
		if (!state)
			return kResultFalse;

		// called when we load a preset, the model has to be reloaded

		int32 savedBypass = 0;
		if (state->read(&savedBypass, sizeof(int32)) != kResultOk)
		{
			// could be an old version, continue
		}

		int32 savedGain = 0;
		if (state->read(&savedGain, sizeof(int32)) != kResultOk) {

		}

#if BYTEORDER == kBigEndian
			SWAP_32(savedBypass)
			SWAP_32(savedGain)
#endif

		mBypass = savedBypass > 0;
		mGain = savedGain;

		return kResultTrue;
	}

	
	tresult PLUGIN_API Processor::getState(IBStream* state)
	{
		
		// here we need to save the model

		int32 toSaveBypass = mBypass ? 1 : 0;
		int32 toSavedGain = mGain;

#if BYTEORDER == kBigEndian
			SWAP_32(toSaveBypass)
			SWAP_32(toSavedGain)
#endif

		state->write(&toSaveBypass, sizeof(int32));
		state->write(&toSavedGain, sizeof(int32));

		return kResultOk;
	}
	

} // namespace Vst
} // nmamespace Steinberg