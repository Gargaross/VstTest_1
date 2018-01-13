#include "Processor.h"
#include "Factory.h"

namespace Steinberg {
	namespace Vst {

		TestProcessor::TestProcessor()
		{
			setControllerClass(TestControllerUID);
		}

		void TestProcessor::TestFunction()
		{

		}

		tresult PLUGIN_API TestProcessor::initialize(FUnknown* context)
		{
			tresult result = AudioEffect::initialize(context);
			if (result == kResultTrue)
			{
				addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
				addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
			}
			return result;
		}

	} // namespace Vst
} // namespace Steinberg

