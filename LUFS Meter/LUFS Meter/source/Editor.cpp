#include "Editor.h"
#include "Controller.h"
#include "Common.h"

bool normalizedToDb(float value, std::string& result, CParamDisplay* display)
{
	float dbReduction = 10 * log10(value);
	result = std::to_string(dbReduction);

	return true;
}

/*
bool FilterTypeToString(float value, std::string& result, CParamDisplay* display)
{
	if (value == 0.0) {
		result = "Low Pass";
	}
	else {
		result = "High Pass";
	}

	return true;
}


bool CenterFreqToString(float value, std::string& result, CParamDisplay* display)
{
	double freq = NormalizedFrequencyToFrequency(value);
	result = std::to_string(freq);

	return true;
}


bool QToString(float value, std::string& result, CParamDisplay* display)
{
	double q = NormalizedQToQ(value);
	result = std::to_string(q);

	return true;
}


bool GainToString(float value, std::string& result, CParamDisplay* display)
{
	result = "TODO";
	return true;
}
*/


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

			CRect displayRect(0, 0, 80, 40);
			displayRect.offset(0, 100);
			mLUFSDisplay = new CParamDisplay(displayRect);
			mLUFSDisplay->setValueToStringFunction2(normalizedToDb);

			frame->addView(mLUFSDisplay);

			Parameter* luParam = controller->getParameterObject(kLUFSId);
			if (luParam) {
				luParam->addRef();
				luParam->addDependent(this);
			}

			CRect buttonRect(0, 0, 100, 20);
			buttonRect.offset(10, 50);
			CTextButton* resetButton = new CTextButton(buttonRect, this, kResetId, "Reset");

			frame->addView(resetButton);

			/*
			CRect buttonRect(0, 0, 100, 20);

			buttonRect.offset(10, 50);
			CTextButton* textButton = new CTextButton(buttonRect, this, kLowPassId, "Low pass");

			buttonRect.offset(0, 20);
			CTextButton* textButton2 = new CTextButton(buttonRect, this, kHighPassId, "High pass");

			// center freq knob
			CBitmap* knobImg = new CBitmap("knob.png");
			CRect r(0, 0, knobImg->getWidth(), 42);

			r.offset(121, 50);
			mCenterFreqKnob = new CAnimKnob(r, this, kCenterFreqId, 80, 42, knobImg, CPoint(0, 0));

			// q knob
			r.offset(42, 0);
			mQKnob = new CAnimKnob(r, this, kQId, 80, 42, knobImg, CPoint(0, 0));

			// gain knob
			r.offset(42, 0);
			mGainKnob = new CAnimKnob(r, this, kGainId, 80, 42, knobImg, CPoint(0, 0));

			CRect displayRect(0, 0, 80, 40);
			displayRect.offset(0, 100);
			mFilterTypeNormDisplay = new CParamDisplay(displayRect);
			displayRect.offset(0, 40);
			mFilterTypeDisplay = new CParamDisplay(displayRect);

			displayRect.offset(85, -40);
			mCenterFreqNormDisplay = new CParamDisplay(displayRect);
			displayRect.offset(0, 40);
			mCenterFreqDisplay = new CParamDisplay(displayRect);

			displayRect.offset(85, -40);
			mQNormDisplay = new CParamDisplay(displayRect);
			displayRect.offset(0, 40);
			mQDisplay = new CParamDisplay(displayRect);

			displayRect.offset(85, -40);
			mGainNormDisplay = new CParamDisplay(displayRect);
			displayRect.offset(0, 40);
			mGainDisplay = new CParamDisplay(displayRect);

			mFilterTypeDisplay->setValueToStringFunction2(FilterTypeToString);
			mCenterFreqDisplay->setValueToStringFunction2(CenterFreqToString);
			mQDisplay->setValueToStringFunction2(QToString);
			mGainDisplay->setValueToStringFunction2(GainToString);


			// Labels
			CRect labelRect(0, 0, 80, 20);
			labelRect.offset(0, 180);
			CTextLabel* filterTypeLabel = new CTextLabel(labelRect, "Filter Type");

			labelRect.offset(85, 0);
			CTextLabel* centerFreqLabel = new CTextLabel(labelRect, "Frequency");

			labelRect.offset(85, 0);
			CTextLabel* QLabel = new CTextLabel(labelRect, "Q");

			labelRect.offset(85, 0);
			CTextLabel* gainLabel = new CTextLabel(labelRect, "Gain");

			knobImg->forget();

			frame->addView(textButton);
			frame->addView(textButton2);
			frame->addView(mCenterFreqKnob);
			frame->addView(mQKnob);
			frame->addView(mGainKnob);
			frame->addView(mFilterTypeNormDisplay);
			frame->addView(mCenterFreqNormDisplay);
			frame->addView(mQNormDisplay);
			frame->addView(mGainNormDisplay);
			frame->addView(mFilterTypeDisplay);
			frame->addView(mCenterFreqDisplay);
			frame->addView(mQDisplay);
			frame->addView(mGainDisplay);
			frame->addView(filterTypeLabel);
			frame->addView(centerFreqLabel);
			frame->addView(QLabel);
			frame->addView(gainLabel);

			Parameter* centerFreqParam = controller->getParameterObject(kCenterFreqId);
			Parameter* qParam = controller->getParameterObject(kQId);
			Parameter* gainParam = controller->getParameterObject(kGainId);

			if (centerFreqParam) {
				centerFreqParam->addRef();
				centerFreqParam->addDependent(this);
			}
			if (qParam) {
				qParam->addRef();
				qParam->addDependent(this);
			}
			if (gainParam) {
				gainParam->addRef();
				gainParam->addDependent(this);
			}
			*/

			//CBitmap* background = new CBitmap("background.png");
			//CView* backgroundView = new CView(CRect(0, 0, background->getWidth(), background->getHeight()));
			//backgroundView->setBackground(background);

			/*
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
			*/

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
				controller->endEdit(tag);
			}
			if (tag == kLUFSId) {
				controller->beginEdit(tag);
				float value = pControl->getValueNormalized();
				controller->performEdit(tag, pControl->getValueNormalized());
				controller->endEdit(tag);
			}
			if (tag == kResetId) {
				controller->beginEdit(tag);
				controller->performEdit(tag, 1.0);
				controller->endEdit(tag);
			}

			/*
			if (tag == kLowPassId) {
				controller->beginEdit(kFilterTypeId);
				controller->performEdit(kFilterTypeId, 0.0);
				mFilterTypeNormDisplay->setValueNormalized(0.0);
				mFilterTypeDisplay->setValueNormalized(0.0);
				controller->endEdit(kFilterTypeId);
			}
			if (tag == kHighPassId) {
				controller->beginEdit(kFilterTypeId);
				controller->performEdit(kFilterTypeId, 1.0);
				mFilterTypeNormDisplay->setValueNormalized(1.0);
				mFilterTypeDisplay->setValueNormalized(1.0);
				controller->endEdit(kFilterTypeId);
			}
			if (tag == kCenterFreqId) {
				controller->beginEdit(tag);
				controller->performEdit(tag, pControl->getValueNormalized());
				mCenterFreqNormDisplay->setValueNormalized(pControl->getValueNormalized());
				mCenterFreqDisplay->setValueNormalized(pControl->getValueNormalized());
				controller->endEdit(tag);
			}
			if (tag == kQId) {
				controller->beginEdit(tag);
				controller->performEdit(tag, pControl->getValueNormalized());
				mQNormDisplay->setValueNormalized(pControl->getValueNormalized());
				mQDisplay->setValueNormalized(pControl->getValueNormalized());
				controller->endEdit(tag);
			}
			if (tag == kGainId) {
				controller->beginEdit(tag);
				controller->performEdit(tag, pControl->getValueNormalized());
				mGainNormDisplay->setValueNormalized(pControl->getValueNormalized());
				mGainDisplay->setValueNormalized(pControl->getValueNormalized());
				controller->endEdit(tag);
			}
			*/
		}

		void PLUGIN_API Editor::update(FUnknown* changedUnknown, Steinberg::int32 message)
		{
			if (message == IDependent::kChanged)
			{
				if (Parameter* p = dynamic_cast<Parameter*>(changedUnknown)) {
					mLUFSDisplay->setValueNormalized(controller->getParamNormalized(kLUFSId));
				}
			}
		}

	} // namespace Vst
} // namespace Steinberg