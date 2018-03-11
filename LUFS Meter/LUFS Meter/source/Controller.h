#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
	namespace Vst {

		enum {
			kBypassId = 100,
			kFilterTypeId,
			kCenterFreqId,
			kQId,
			kGainId,
			kLowPassId,
			kHighPassId,

			kLUFSId,
			kGatedLUFSId,
			kResetId
		};

		class Controller : public EditController
		{
		public:
			static FUnknown* createInstance(void*) { return (IEditController*)new Controller(); }

			//---from IPluginBase--------
			tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;

			tresult PLUGIN_API setComponentState(IBStream* state) SMTG_OVERRIDE;
			tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE;
			tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE;
			tresult PLUGIN_API setParamNormalized(ParamID tag, ParamValue value) SMTG_OVERRIDE;

			IPlugView* PLUGIN_API createView(FIDString str) SMTG_OVERRIDE;
		};

	} // namespace Vst
} // namespace Steinberg
