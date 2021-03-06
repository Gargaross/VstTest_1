#include "BypassEditor.h"
#include "BypassController.h"

namespace Steinberg {
	namespace Vst {

		BypassEditor::BypassEditor(void* controller, ViewRect* size)
			: VSTGUIEditor(controller, size)
		{

		}

		bool PLUGIN_API BypassEditor::open(void* parent, const PlatformType& platformType)
		{
			CRect frameSize(0, 0, 400, 400);
			frame = new CFrame(frameSize, this);
			frame->open(parent);

			frame->setBackgroundColor(kRedCColor);

			CBitmap* background = new CBitmap("background.png");
			CView* backgroundView = new CView(CRect(0, 0, background->getWidth(), background->getHeight()));
			backgroundView->setBackground(background);

			CBitmap* buttonImg = new CBitmap("buttonOnOff.png");
			CRect r(0, 0, buttonImg->getWidth(), buttonImg->getHeight() / 2);
			r.offset(100, 200);
			COnOffButton* button = new COnOffButton(r, this, kBypassId, buttonImg);
			mButton = button;
			Parameter* buttonParam = controller->getParameterObject(kBypassId);
			if (buttonParam) {
				buttonParam->addRef();
				buttonParam->addDependent(this);
			}

			background->forget();
			buttonImg->forget();

			frame->addView(backgroundView);
			frame->addView(button);

			return true;
		}

		void PLUGIN_API BypassEditor::close()
		{
			frame->forget();
		}

		void BypassEditor::valueChanged(CControl* pControl)
		{
			int tag = pControl->getTag();
			if (tag == kBypassId) {
				controller->beginEdit(tag);
				controller->performEdit(tag, pControl->getValueNormalized());
				controller->endEdit(tag);
			}
		}

		void PLUGIN_API BypassEditor::update(FUnknown* changedUnknown, Steinberg::int32 message)
		{
			if (message == IDependent::kChanged)
			{
				if (Parameter* p = dynamic_cast<Parameter*>(changedUnknown)) {
					mButton->setValueNormalized(controller->getParamNormalized(kBypassId));
				}
			}
		}

	} // namespace Vst
} // namespace Steinberg