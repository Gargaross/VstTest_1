#pragma once

#include "public.sdk\source\vst\vstguieditor.h"

namespace Steinberg {
	namespace Vst {
		class BypassEditor : public Steinberg::Vst::VSTGUIEditor
		{
		public:
			BypassEditor(void* controller, ViewRect* size);

			bool PLUGIN_API open(void* parent,
				const PlatformType& platformType) SMTG_OVERRIDE;

			void PLUGIN_API close() SMTG_OVERRIDE;
		};

	} // namespace Vst
} // namespace Steinberg