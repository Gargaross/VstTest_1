
#include "BypassProcessor.h"

namespace Steinberg {
namespace Vst {
	BypassProcessor::BypassProcessor()
	{

	}


	tresult BypassProcessor::initialize(FUnknown* context)
	{
		return 0;
	}


	tresult BypassProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
	{
		return 0;
	}


	tresult BypassProcessor::setActive(TBool state)
	{
		return 0;
	}


	tresult BypassProcessor::process(ProcessData& data)
	{
		return 0;
	}


	tresult BypassProcessor::setState(IBStream* state)
	{
		return 0;
	}


	tresult BypassProcessor::getState(IBStream* state)
	{
		return 0;
	}
} // namespace Vst
} // nmamespace Steinberg