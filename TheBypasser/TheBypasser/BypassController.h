#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
	namespace Vst {

		enum {
			kBypassId = 100
		};

		class BypassController : public EditController
		{
		public:
			static FUnknown* createInstance(void*) { return (IEditController*)new BypassController(); }

			//---from IPluginBase--------
			tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;

			tresult PLUGIN_API setComponentState(IBStream* state) SMTG_OVERRIDE;

			IPlugView* PLUGIN_API createView(FIDString str) SMTG_OVERRIDE;

			//---Interface---------
			/*
			OBJ_METHODS(BypassController, EditController)
				DEFINE_INTERFACES
				//DEF_INTERFACE(IBypassTestController)
				END_DEFINE_INTERFACES(EditController)
				REFCOUNT_METHODS(EditController)
				*/
		};

	} // namespace Vst
} // namespace Steinberg
