#pragma once

#include "pluginterfaces/gui/iplugview.h"
#include "base/source/fobject.h"

namespace Steinberg {

	class BypasserIPlugView : public FObject, public IPlugView
	{
	public:
		BypasserIPlugView();
		BypasserIPlugView(const ViewRect* _rect);

		// From IPlugView
		tresult PLUGIN_API isPlatformTypeSupported(FIDString type) SMTG_OVERRIDE;
		tresult PLUGIN_API attached(void* parent, FIDString type) SMTG_OVERRIDE;
		tresult PLUGIN_API removed() SMTG_OVERRIDE;

		tresult PLUGIN_API onWheel(float /*distance*/) SMTG_OVERRIDE { return kResultFalse; }
		tresult PLUGIN_API onKeyDown(char16 /*key*/, int16 /*keyMsg*/, int16 /*modifiers*/) SMTG_OVERRIDE { return kResultFalse; }
		tresult PLUGIN_API onKeyUp(char16 /*key*/, int16 /*keyMsg*/, int16 /*modifiers*/) SMTG_OVERRIDE { return kResultFalse; }
		tresult PLUGIN_API getSize(ViewRect* size) SMTG_OVERRIDE;
		tresult PLUGIN_API onSize(ViewRect* newSize) SMTG_OVERRIDE;

		tresult PLUGIN_API onFocus(TBool /*state*/) SMTG_OVERRIDE { return kResultFalse; }
		tresult PLUGIN_API setFrame(IPlugFrame* frame) SMTG_OVERRIDE { /*plugFrame = frame;*/ return kResultTrue; }

		tresult PLUGIN_API canResize() SMTG_OVERRIDE { return kResultFalse; }
		tresult PLUGIN_API checkSizeConstraint(ViewRect* /*rect*/) SMTG_OVERRIDE { return kResultFalse; }

		// Define interface
		OBJ_METHODS(BypasserIPlugView, FObject)
			DEFINE_INTERFACES
			DEF_INTERFACE(IPlugView)
			END_DEFINE_INTERFACES(FObject)
			REFCOUNT_METHODS(FObject)

	protected:
		ViewRect rect;
		void* systemWindow;
		IPlugFrame* plugFrame;
	};

} // namepsace Steinberg