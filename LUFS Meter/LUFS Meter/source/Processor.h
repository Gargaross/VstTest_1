#pragma once

#include "public.sdk\source\vst\vstaudioeffect.h"
#include "Filter.h"

namespace Steinberg {
namespace Vst {

	class GatedBlock {
	public:
		GatedBlock();

		void SetMaxSamples(int maxSamples);
		void AddSample(double sample);
		bool IsFull() { return mBlockFull; }
		double GetMeanSquare();
		void Reset();

	private:
		bool mBlockFull;
		
		double mMeanSquare;
		int mSamplesProcessed;
		int mMaxNumSamples;
		double mSampleSum;
	};

class Processor : public AudioEffect
{
public:
	Processor();

	tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts) SMTG_OVERRIDE;

	tresult PLUGIN_API setActive(TBool state) SMTG_OVERRIDE;
	tresult PLUGIN_API setupProcessing(ProcessSetup& newSetup) SMTG_OVERRIDE;
	tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE;

	//------------------------------------------------------------------------
	tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE;

	static FUnknown* createInstance(void*) { return (IAudioProcessor*)new Processor(); }

protected:
	void CalculateBlockMeanSquare(GatedBlock& block);

	void SetFilterConstants(SampleRate sampleRate);

	// Filter constants
	bool mBypass;
	float mGain;

	double mMS;
	float mLUFS;
	float mBlockLUFS;

	unsigned int mSamplesProcessed;

	unsigned int mBlocksProcessed;
	double mBlockTotalMeanSquare;
	GatedBlock mBlock1;
	GatedBlock mBlock2;
	GatedBlock mBlock3;
	GatedBlock mBlock4;

	Filter highShelfFilter;
	Filter highPassFilter;
};

} // namespace Vst
} // namespace Steinberg
