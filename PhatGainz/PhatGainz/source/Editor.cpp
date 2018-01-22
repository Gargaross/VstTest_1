#include "Editor.h"
#include "Controller.h"

namespace Steinberg {
	namespace Vst {

		Editor::Editor(void* controller, ViewRect* size)
			: VSTGUIEditor(controller, size)
		{

		}

		bool PLUGIN_API Editor::open(void* parent, const PlatformType& platformType)
		{
			CRect frameSize(0, 0, 400, 400);
			frame = new CFrame(frameSize, this);
			frame->open(parent);

			frame->setBackgroundColor(kWhiteCColor);

			//CBitmap* background = new CBitmap("background.png");
			//CView* backgroundView = new CView(CRect(0, 0, background->getWidth(), background->getHeight()));
			//backgroundView->setBackground(background);

			/*
			CBitmap* buttonImg = new CBitmap("buttonOnOff.png");
			CRect r(0, 0, buttonImg->getWidth(), buttonImg->getHeight() / 2);
			r.offset(100, 200);
			mBypassKnob = new COnOffButton(r, this, kBypassId, buttonImg);
			if (Parameter* buttonParam = controller->getParameterObject(kBypassId)) {
				buttonParam->addRef();
				buttonParam->addDependent(this);
			}
			*/

			CBitmap* gainKnobImg = new CBitmap("knob_big.png");
			CRect r(0, 0, gainKnobImg->getWidth(), 82);
			r.offset(100, 200);
			mGainKnob = new CAnimKnob(r, this, kGainId, 80, 84, gainKnobImg, CPoint(0, 0));

			//background->forget();
			//buttonImg->forget();

			//frame->addView(backgroundView);
			frame->addView(mGainKnob);

			return true;
		}

		void PLUGIN_API Editor::close()
		{
			frame->forget();
		}

		void Editor::valueChanged(CControl* pControl)
		{
			int tag = pControl->getTag();
			if ((tag == kBypassId) || (tag == kGainId)) {
				controller->beginEdit(tag);
				controller->performEdit(tag, pControl->getValueNormalized());
				//DebugPrint(pControl->getValueNormalized());
				controller->endEdit(tag);
			}
		}

		void PLUGIN_API Editor::update(FUnknown* changedUnknown, Steinberg::int32 message)
		{
			if (message == IDependent::kChanged)
			{
				if (Parameter* p = dynamic_cast<Parameter*>(changedUnknown)) {
					mBypassKnob->setValueNormalized(controller->getParamNormalized(kBypassId));
				}
			}
		}

	} // namespace Vst
} // namespace Steinberg