#pragma once

#include "public.sdk\source\vst\vsteditcontroller.h"

namespace Steinberg {
	namespace Vst {

		class TestController : public EditController {
		public:

			void TestFunction();

			IPlugView* PLUGIN_API createView(FIDString /*name*/) SMTG_OVERRIDE;

			static FUnknown* createInstance(void*) { return (IEditController*)new TestController(); }

		};

	} // namespace Vst
} // namespace Steinberg