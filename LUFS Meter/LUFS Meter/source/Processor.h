#pragma once

#include "public.sdk\source\vst\vstaudioeffect.h"
#include "Filter.h"

namespace Steinberg {
namespace Vst {

class Processor : public AudioEffect
{
public:
	Processor();

	tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts) SMTG_OVERRIDE;

	tresult PLUGIN_API setActive(TBool state) SMTG_OVERRIDE;
	tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE;

	//------------------------------------------------------------------------
	tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE;

	static FUnknown* createInstance(void*) { return (IAudioProcessor*)new Processor(); }

protected:
	// Filter constants
	bool mBypass;
	float mGain;

	float mLUFS;

	double b0, b1, b2, a1, a2;
	double z1[2];
	double z2[2];

	Filter highShelfFilter;
	Filter highPassFilter;
};

} // namespace Vst
} // namespace Steinberg
