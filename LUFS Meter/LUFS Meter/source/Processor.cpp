
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

	GatedBlock::GatedBlock() 
	{
		mBlockFull = false;
		mMaxNumSamples = 0;
		mSampleSum = 0.0;
	}


	void GatedBlock::SetMaxSamples(int maxNumSamples)
	{
		mBlockFull = false;
		mMaxNumSamples = maxNumSamples;
		mSampleSum = 0.0;
	}


	void GatedBlock::AddSample(double sample)
	{
		if (!mBlockFull) {
			mSampleSum += sample * sample;
			mSamplesProcessed++;
		}
		
		if (mSamplesProcessed == mMaxNumSamples) {
			mBlockFull = true;
		}
	}


	void GatedBlock::Reset()
	{
		mMeanSquare = 0.0;
		mBlockFull = false;
		mSampleSum = 0.0;
		mSamplesProcessed = 0;
	}


	double GatedBlock::GetMeanSquare()
	{
		return mSampleSum / mMaxNumSamples;
	}


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

		mMS = 0.0;
		mLUFS = 0.0;
		mSamplesProcessed = 0;

		// Should be set to samplerate * 0.4
		// Now set for 48kHz
		mBlock1.SetMaxSamples(19200);
		mBlock2.SetMaxSamples(19200);
		mBlock3.SetMaxSamples(19200);
		mBlock4.SetMaxSamples(19200);

		mBlockTotalMeanSquare = 0.0;
		mBlocksProcessed = 0;

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

					if (id == kResetId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
							if (value > 0.5f) {
								// Reset
								mMS = 0.0;
								mLUFS = 0.0;
								mSamplesProcessed = 0;
								
								mBlockTotalMeanSquare = 0.0;
								mBlocksProcessed = 0;
								mBlock1.Reset();
								mBlock2.Reset();
								mBlock3.Reset();
								mBlock4.Reset();
							}
							else {
								
							}
						}
					}

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

			double sampleSum = 0.0;

			for (int32 channel = 0; channel < numChannels; channel++) {
				float* outputChannel = data.outputs[0].channelBuffers32[channel];
				float* inputChannel = data.inputs[0].channelBuffers32[channel];

				highShelfFilter.Process(inputChannel, data.numSamples, (channel == 0) ? FilterChannel::Left : FilterChannel::Right);

				highPassFilter.Process(inputChannel, data.numSamples, (channel == 0) ? FilterChannel::Left : FilterChannel::Right);

				// one channel at 48kHz is the only one working currently
				// Something wrong with 2 channel calculations
				if (channel == 1)
					continue;

				for (int32 sample = 0; sample < data.numSamples; sample++) {
					// Send filtered signal to output
					outputChannel[sample] = inputChannel[sample];

					// Old metering
					sampleSum += inputChannel[sample] * inputChannel[sample];

					// Only add samples to some blocks after a while
					if (mSamplesProcessed < 4800) {
						mBlock1.AddSample(inputChannel[sample]);
					}
					else if (mSamplesProcessed < 9600) {
						mBlock1.AddSample(inputChannel[sample]);
						mBlock2.AddSample(inputChannel[sample]);
					}
					else if (mSamplesProcessed < 14400) {
						mBlock1.AddSample(inputChannel[sample]);
						mBlock2.AddSample(inputChannel[sample]);
						mBlock3.AddSample(inputChannel[sample]);
					}
					else {
						mBlock1.AddSample(inputChannel[sample]);
						mBlock2.AddSample(inputChannel[sample]);
						mBlock3.AddSample(inputChannel[sample]);
						mBlock4.AddSample(inputChannel[sample]);
					}

					CalculateBlockMeanSquare(mBlock1);
					CalculateBlockMeanSquare(mBlock2);
					CalculateBlockMeanSquare(mBlock3);
					CalculateBlockMeanSquare(mBlock4);

					mSamplesProcessed++;
				}
			}

			if (mMS > 0.0) {
				mMS = ((mSamplesProcessed - data.numSamples)*mMS + sampleSum) / mSamplesProcessed;
			}
			else {
				mMS = sampleSum / mSamplesProcessed;
			}

			mLUFS = -0.691 + 10. * log10(mMS);
			mBlockLUFS = -0.691 + 10. * log10(mBlockTotalMeanSquare);
		}

		IParameterChanges* outParamChanges = data.outputParameterChanges;
		if (outParamChanges) {
			int32 index = 0;
			IParamValueQueue* paramQueue = outParamChanges->addParameterData(kLUFSId, index);
			if (paramQueue) {
				int32 index2 = 0;
				paramQueue->addPoint(0, pow(10, mLUFS/10), index2);
				index++;
			}

			paramQueue = outParamChanges->addParameterData(kGatedLUFSId, index);
			if (paramQueue) {
				int32 index2 = 0;
				paramQueue->addPoint(0, pow(10, mBlockLUFS / 10), index2);
				index++;
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
	

	void Processor::CalculateBlockMeanSquare(GatedBlock& block)
	{
		if (!block.IsFull())
			return;

		// Absolute threshold, -70 LUFS for the block
		double blockLoudness = -0.691 + 10. * log10(block.GetMeanSquare());
		if (blockLoudness <= -70.0) {
			block.Reset();
			return;
		}

		// Relative treshold
		double currentLoudness = -0.691 + 10. * log10(mBlockTotalMeanSquare);
		if (blockLoudness <= (currentLoudness - 10.)) {
			block.Reset();
			return;
		}

		// Calculate new total mean square
		if (mBlockTotalMeanSquare > 0.0) {
			mBlockTotalMeanSquare = (mBlocksProcessed*mBlockTotalMeanSquare + block.GetMeanSquare()) / (mBlocksProcessed + 1);
		}
		else {
			mBlockTotalMeanSquare = block.GetMeanSquare();
		}

		// reset gated block
		block.Reset();

		mBlocksProcessed++;
	}

} // namespace Vst
} // nmamespace Steinberg