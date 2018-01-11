#include "BypassEditor.h"

namespace Steinberg {
	namespace Vst {

		BypassEditor::BypassEditor(void* controller, ViewRect* size)
			: VSTGUIEditor(controller, size)
		{

		}

		bool PLUGIN_API BypassEditor::open(void* parent,
			const PlatformType& platformType = kDefaultNative)
		{
			return true;
		}

		void PLUGIN_API BypassEditor::close()
		{

		}

	} // namespace Vst
} // namespace Steinberg