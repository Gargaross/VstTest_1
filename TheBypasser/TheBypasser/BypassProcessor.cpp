
#include "BypassProcessor.h"
#include "BypassController.h"
#include "TheBypasser.h"
//#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

namespace Steinberg {
namespace Vst {
	BypassProcessor::BypassProcessor() : mBypass(false)
	{
		setControllerClass(BypassControllerUID);
	}


	tresult PLUGIN_API BypassProcessor::initialize(FUnknown* context)
	{
		tresult result = AudioEffect::initialize(context);
		if (result == kResultTrue)
		{
			addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
			addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
		}

		return result;
	}


	tresult PLUGIN_API BypassProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
	{
		// we only support one in and output bus and these buses must have the same number of channels
		if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
			return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
		return kResultFalse;
	}


	tresult PLUGIN_API BypassProcessor::setActive(TBool state)
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


	tresult PLUGIN_API BypassProcessor::process(ProcessData& data)
	{
		if (data.inputParameterChanges)
		{
			int32 numParams = data.inputParameterChanges->getParameterCount();
			for (int32 index = 0; index < numParams; index++) {
				IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
				if (paramQueue) {
					ParamValue value;
					int32 sampleOffset;
					int32 numPoints = paramQueue->getPointCount();
					
					uint32 id = paramQueue->getParameterId();

					if (id == kBypassId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
							mBypass = (value > 0.5f);
						}
					}
				}
			}
		}

		if (data.numSamples > 0)
		{
			// Both FL Studio 12 and VST Host tester uses 32 bit samples

			SpeakerArrangement arr;
			getBusArrangement(kOutput, 0, arr);
			int32 numChannels = SpeakerArr::getChannelCount(arr);

			for (int32 channel = 0; channel < numChannels; channel++) {
				float* outputChannel = data.outputs[0].channelBuffers32[channel];
				float* inputChannel = data.inputs[0].channelBuffers32[channel];

				for (int32 sample = 0; sample < data.numSamples; sample++) {
					if (mBypass)
						outputChannel[sample] = inputChannel[sample];
					else
						outputChannel[sample] = 0;
				}
			}
		}
		return kResultTrue;
	}


	tresult PLUGIN_API BypassProcessor::setState(IBStream* state)
	{
		if (!state)
			return kResultFalse;

		// called when we load a preset, the model has to be reloaded

		int32 savedBypass = 0;
		if (state->read(&savedBypass, sizeof(int32)) != kResultOk)
		{
			// could be an old version, continue
		}

#if BYTEORDER == kBigEndian
			SWAP_32(savedBypass)
#endif

		mBypass = savedBypass > 0;

		return kResultTrue;
	}

	/*
	tresult PLUGIN_API BypassProcessor::getState(IBStream* state)
	{
		
		// here we need to save the model

		float toSaveDelay = mDelay;
		int32 toSaveBypass = mBypass ? 1 : 0;

#if BYTEORDER == kBigEndian
		SWAP_32(toSaveDelay)
			SWAP_32(toSaveBypass)
#endif

			state->write(&toSaveDelay, sizeof(float));
		state->write(&toSaveBypass, sizeof(int32));

		return kResultOk;
	}
	*/

} // namespace Vst
} // nmamespace Steinberg