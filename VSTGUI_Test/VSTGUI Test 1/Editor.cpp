
#include "Editor.h"

namespace Steinberg {
	namespace Vst {

		TestEditor::TestEditor(void* controller, ViewRect* size)
			: VSTGUIEditor(controller, size)
		{
			
		}

		bool PLUGIN_API TestEditor::open(void* parent, const PlatformType& platformType)
		{
			CRect frameSize(0, 0, 400, 400);
			frame = new CFrame(frameSize, this);
			frame->open(parent);
			
			CBitmap* background = new CBitmap("KnobBackground.png");
			CBitmap* handle = new CBitmap("KnobHandle.png");
			CRect r(0, 0, background->getWidth(), background->getHeight());
			CKnob* knob = new CKnob(r, this, 0, background, handle, CPoint(0, 0));
			r.offset(200, 0);
			CKnob* knob2 = new CKnob(r, this, 1, background, handle, CPoint(0, 0));

			background->forget();
			handle->forget();

			frame->addView(knob);
			frame->addView(knob2);

			return true;
		}

		void PLUGIN_API TestEditor::close()
		{
			
		}

		void TestEditor::valueChanged(CControl* ptr)
		{
			int32_t tag = ptr->getTag();
			if (tag == 0) {

			}
			else if (tag == 1) {

			}
		}

	} // namespace Vst
} // namespace Steinberg