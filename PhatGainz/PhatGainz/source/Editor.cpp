#include "Editor.h"
#include "Controller.h"

bool DbReductionFunction(float value, std::string& result, CParamDisplay* display)
{
	float dbReduction = 10 * std::log10(pow(value, 2));
	result = std::to_string(dbReduction);

	return true;
}

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

			CBitmap* gainKnobImg = new CBitmap("knob_big.png");
			CRect r(0, 0, gainKnobImg->getWidth(), 84);
			r.offset(100, 200);
			mGainKnob = new CAnimKnob(r, this, kGainId, 80, 84, gainKnobImg, CPoint(0, 0));

			CRect gainDisplayRect(0, 0, 80, 40);
			gainDisplayRect.offset(200, 220);
			mGainDisplay = new CParamDisplay(gainDisplayRect);

			CRect gainReductionDisplayRect(0, 0, 80, 40);
			gainReductionDisplayRect.offset(200, 260);
			mGainReductionDisplay = new CParamDisplay(gainReductionDisplayRect);

			mGainReductionDisplay->setValueToStringFunction2(DbReductionFunction);

			gainKnobImg->forget();

			frame->addView(mGainKnob);
			frame->addView(mGainDisplay);
			frame->addView(mGainReductionDisplay);

			Parameter* gainParam = controller->getParameterObject(kGainId);
			if (gainParam) {
				gainParam->addRef();
				gainParam->addDependent(this);
			}

			return true;
		}

		void PLUGIN_API Editor::close()
		{
			frame->forget();
		}

		void Editor::valueChanged(CControl* pControl)
		{
			int tag = pControl->getTag();
			if (tag == kBypassId) {
				controller->beginEdit(tag);
				controller->performEdit(tag, pControl->getValueNormalized());
				//DebugPrint(pControl->getValueNormalized());
				controller->endEdit(tag);
			}
			if (tag == kGainId) {
				float valueNorm = pControl->getValueNormalized();

				controller->beginEdit(tag);
				controller->performEdit(tag, valueNorm);
				mGainDisplay->setValueNormalized(valueNorm);
				mGainReductionDisplay->setValueNormalized(valueNorm);
				controller->endEdit(tag);
			}
		}

		void PLUGIN_API Editor::update(FUnknown* changedUnknown, Steinberg::int32 message)
		{
			if (message == IDependent::kChanged)
			{
				if (Parameter* p = dynamic_cast<Parameter*>(changedUnknown)) {
					mGainKnob->setValueNormalized(controller->getParamNormalized(kGainId));
					mGainDisplay->setValueNormalized(controller->getParamNormalized(kGainId));
				}
			}
		}

	} // namespace Vst
} // namespace Steinberg