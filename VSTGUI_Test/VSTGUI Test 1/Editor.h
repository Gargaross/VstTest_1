#pragma once

#include "public.sdk\source\vst\vstguieditor.h"

namespace Steinberg {
	namespace Vst {

		class TestEditor : public VSTGUIEditor, 
						   public IControlListener
		{
		public:
			TestEditor(void* controller, ViewRect* size = nullptr);

			// from VSTGUIEditor
			virtual bool PLUGIN_API open(void* parent, const PlatformType& platformType = kDefaultNative);
			virtual void PLUGIN_API close();

			// from IControlListener
			void valueChanged(CControl* pControl);
		};

	} // namespace Vst
} // namespace Steinberg

