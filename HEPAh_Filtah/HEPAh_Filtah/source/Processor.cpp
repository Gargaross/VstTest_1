
#include "Processor.h"
#include "Controller.h"
#include "HEPAhFiltah.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "vstgui4\vstgui\lib\vstguidebug.h"

namespace Steinberg {
namespace Vst {
	Processor::Processor() : 
		mBypass(false),
		fGain(0.0),
		z1L(0),
		z2L(0),
		z1R(0),
		z2R(0)
	{
		a0 = 0.0012074046354035072;
		a1 = 0.0024148092708070144;
		a2 = 0.0012074046354035072;
		b1 = -1.8993325472756315;
		b2 = 0.9041621658172454;

		for (int i = 0; i < 2; i++) {
			z1[i] = 0;
			z2[i] = 0;
		}

		setControllerClass(HEPAhFiltahControllerUID);
	}


	tresult PLUGIN_API Processor::initialize(FUnknown* context)
	{
		tresult result = AudioEffect::initialize(context);
		if (result == kResultTrue)
		{
			addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
			addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
		}

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
					/*if (id == kGainId) {
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
							fGain = value;
						}
					}*/
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
					// TODO implement LPF here
					// y[n] = a0*x[n] + a1*x[n-1] + a2*x[n-2] – b1*y[n-1] – b2*y[n-2]
					// y[n] = outputChannel

					// Transposed direct form 2
					// y[n] = a0*x[n] + z1
					// z1 = a1 * x[n] + z2 - b1 * y[n]
					// z2 = a2 * x[n] - b2 * y[n]

					double in = inputChannel[sample];

					outputChannel[sample] = a0 * in + z1[channel];
					z1[channel] = a1 * in + z2[channel] - b1 * outputChannel[sample];
					z2[channel] = a2 * in - b2 * outputChannel[sample];

				}
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
		fGain = savedGain;

		return kResultTrue;
	}

	
	tresult PLUGIN_API Processor::getState(IBStream* state)
	{
		
		// here we need to save the model

		int32 toSaveBypass = mBypass ? 1 : 0;
		int32 toSavedGain = fGain;

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