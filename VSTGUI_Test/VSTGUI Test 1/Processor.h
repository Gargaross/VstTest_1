#pragma once

#include "public.sdk\source\vst\vstaudioeffect.h"

namespace Steinberg {
	namespace Vst {

		class TestProcessor : public AudioEffect {
		public:
			TestProcessor();
			void TestFunction();

			tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
			//tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE { return kResultTrue; }

			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new TestProcessor(); }
		};

	} // namespace Vst
} // namespace Steinberg

