
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
	FilterConstants HSF_22k = { -1.33830533606613, 0.508244558913602, 1.47980599675297, -2.17083127322591, 0.860706349703016 };
	FilterConstants HPF_22k = { -1.97839760259012, 0.978514419503251, 0.994169099216665, -1.98833819843333, 0.994169099216665 };
	FilterConstants HSF_24k = { -1.39023460519282, 0.536838481260398, 1.48788595993445, -2.24628965728315, 0.904784871829906 };
	FilterConstants HPF_24k = { -1.98014412622893, 0.980242817859277, 0.995042168936226, -1.99008433787245, 0.995042168936226 };
	FilterConstants HSF_44k = { -1.66365511325602, 0.712595428073225, 1.53084110526294, -2.65098583726841, 1.16901070304651 };
	FilterConstants HPF_44k = { -1.9891696736298, 0.989199035787039, 0.999560064542514, -1.99912012908503, 0.999560064542514 };
	FilterConstants HSF_48k = { -1.69065929318241, 0.73248077421585, 1.53512485958697, -2.69169618940638, 1.19832928108529 };
	FilterConstants HPF_48k = { -1.99004745483398, 0.99007225036621, 1, -2, 1 };
	FilterConstants HSF_88k = { -1.83091998796233, 0.844142261087853, 1.55751180924125, -2.90560302012217, 1.36129339844473 };
	FilterConstants HPF_88k = { -1.99457751545034, 0.994584875878055, 1.00227196335738, -2.00454392671476, 1.00227196335738 };
	FilterConstants HSF_96k = { -1.84460946989011, 0.855843322930641, 1.55970991060078, -2.92671577256153, 1.37822264998936 };
	FilterConstants HPF_96k = { -1.99501754472472, 0.995023759040923, 1.00249278898634, -2.00498557797269, 1.00249278898634 };
	FilterConstants HSF_176k = { -1.91532931683305, 0.918771744160007, 1.57110586616723, -3.03651153867014, 1.46884287054094 };
	FilterConstants HPF_176k = { -1.99728692242381, 0.997288765026068, 1.00363204710421, -2.00726409420843, 1.00363204710421 };
	FilterConstants HSF_192k = { -1.92220223060749, 0.925117735116826, 1.57221714877803, -3.04724956494638, 1.47794349182153 };
	FilterConstants HPF_192k = { -1.9975072228407, 0.99750877835551, 1.00374267537144, -2.00748535074287, 1.00374267537144 };


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

		mMS = 0.0;
		mLUFS = 0.0;
		mSamplesProcessed = 0;

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


	tresult PLUGIN_API Processor::setupProcessing(ProcessSetup& newSetup)
	{
		processSetup.maxSamplesPerBlock = newSetup.maxSamplesPerBlock;
		processSetup.processMode = newSetup.processMode;
		processSetup.sampleRate = newSetup.sampleRate;

		if (canProcessSampleSize(newSetup.symbolicSampleSize) != kResultTrue)
			return kResultFalse;

		processSetup.symbolicSampleSize = newSetup.symbolicSampleSize;

		// set filter constants
		SetFilterConstants(processSetup.sampleRate);

		// set settings for gate blocks
		mBlock1.SetMaxSamples(processSetup.sampleRate * 0.4);
		mBlock2.SetMaxSamples(processSetup.sampleRate * 0.4);
		mBlock3.SetMaxSamples(processSetup.sampleRate * 0.4);
		mBlock4.SetMaxSamples(processSetup.sampleRate * 0.4);

		return kResultOk;
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
					double gateSampleLimit = (processSetup.sampleRate * 0.4) / 4;

					if (mSamplesProcessed < gateSampleLimit) {
						mBlock1.AddSample(inputChannel[sample]);
					}
					else if (mSamplesProcessed < (gateSampleLimit * 2)) {
						mBlock1.AddSample(inputChannel[sample]);
						mBlock2.AddSample(inputChannel[sample]);
					}
					else if (mSamplesProcessed < (gateSampleLimit * 3)) {
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

	
	void Processor::SetFilterConstants(SampleRate sampleRate)
	{
		FilterConstants highShelfConstants;
		FilterConstants highPassConstants;

		if (sampleRate == 22050) {
			highShelfConstants = HSF_22k;
			highPassConstants = HPF_22k;
		}
		else if (sampleRate == 24000) {
			highShelfConstants = HSF_24k;
			highPassConstants = HPF_24k;
		}
		else if (sampleRate == 44100) {
			highShelfConstants = HSF_44k;
			highPassConstants = HPF_44k;
		}
		else if (sampleRate == 48000) {
			highShelfConstants = HSF_48k;
			highPassConstants = HPF_48k;
		}
		else if (sampleRate == 88200) {
			highShelfConstants = HSF_88k;
			highPassConstants = HPF_88k;
		}
		else if (sampleRate == 96000) {
			highShelfConstants = HSF_96k;
			highPassConstants = HPF_96k;
		}
		else if (sampleRate == 176400) {
			highShelfConstants = HSF_176k;
			highPassConstants = HPF_176k;
		}
		else { // sampleRate == 192000
			highShelfConstants = HSF_192k;
			highPassConstants = HPF_192k;
		}

		highShelfFilter.SetConstants(highShelfConstants);
		highPassFilter.SetConstants(highPassConstants);
	}
} // namespace Vst
} // nmamespace Steinberg