#pragma once

#include "public.sdk\source\vst\vstaudioeffect.h"

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
	bool mBypass;
	float fGain;

	// LPF filter constants
	double a0;
	double a1;
	double a2;
	double b1;
	double b2;
	double z1L;
	double z2L;
	double z1R;
	double z2R;
};

} // namespace Vst
} // namespace Steinberg
