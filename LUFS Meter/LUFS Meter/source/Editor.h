#pragma once

#include "public.sdk\source\vst\vstguieditor.h"

namespace Steinberg {
	namespace Vst {

		class DbReductionDisplay : public CParamDisplay
		{

		};

		class Editor : public VSTGUIEditor,
						public IControlListener
		{
		public:
			Editor(void* controller, ViewRect* size = nullptr);

			bool PLUGIN_API open(void* parent, const PlatformType& platformType) SMTG_OVERRIDE;
			void PLUGIN_API close() SMTG_OVERRIDE;

			void valueChanged(CControl* pControl);
			void controlBeginEdit(CControl* pControl) {}

			void PLUGIN_API update(FUnknown* sender, int32 value) SMTG_OVERRIDE;

		private:
			//CAnimKnob* mCenterFreqKnob;
			//CAnimKnob* mQKnob;
			//CAnimKnob* mGainKnob;
			//CParamDisplay* mFilterTypeNormDisplay;
			//CParamDisplay* mCenterFreqNormDisplay;
			//CParamDisplay* mQNormDisplay;
			//CParamDisplay* mGainNormDisplay;
			//CParamDisplay* mFilterTypeDisplay;
			//CParamDisplay* mCenterFreqDisplay;
			//CParamDisplay* mQDisplay;
			//CParamDisplay* mGainDisplay;

			CParamDisplay* mLUFSDisplay;
			CParamDisplay* mGatedLUFSDisplay;
		};

	} // namespace Vst
} // namespace Steinberg