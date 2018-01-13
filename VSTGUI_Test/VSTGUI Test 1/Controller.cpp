
#include "Controller.h"
#include "Editor.h"

namespace Steinberg {
	namespace Vst {

		void TestController::TestFunction()
		{
			
		}

		IPlugView* PLUGIN_API TestController::createView(FIDString name)
		{
			if (strcmp(name, ViewType::kEditor) == 0)
			{
				return new TestEditor(this);
			}
			return 0;
		}

	} // namespace Vst
} // namespace Steinberg