#include "BypasserCPlugView.h"

namespace Steinberg {

	BypasserPlugView::BypasserPlugView()
	{

	}

	/** Calls when this view will be attached to its parent view. */
	
	void BypasserPlugView::attachedToParent()
	{
		
	}
	

	/** Calls when this view will be removed from its parent view. */
	void BypasserPlugView::removedFromParent()
	{

	}
	

	
	tresult PLUGIN_API BypasserPlugView::isPlatformTypeSupported(FIDString type)
	{
		if (strcmp(type, kPlatformTypeHWND) == 0)
			return kResultTrue;

		return kNotImplemented;
	}
	
	/*
	tresult PLUGIN_API attached(void* parent, FIDString type)
	{
		return 0;
	}

	tresult PLUGIN_API removed()
	{
		return 0;
	}

	tresult PLUGIN_API onWheel(float distance)
	{
		return 0;
	}

	tresult PLUGIN_API onKeyDown(char16 key, int16 keyCode, int16 modifiers)
	{
		return 0;
	}

	tresult PLUGIN_API onKeyUp(char16 key, int16 keyCode, int16 modifiers)
	{
		return 0;
	}

	tresult PLUGIN_API getSize(ViewRect* size)
	{
		return 0;
	}

	tresult PLUGIN_API onSize(ViewRect* newSize)
	{
		return 0;
	}

	tresult PLUGIN_API onFocus(TBool state)
	{
		return 0;
	}

	tresult PLUGIN_API setFrame(IPlugFrame* frame)
	{
		return 0;
	}

	tresult PLUGIN_API canResize()
	{
		return 0;
	}

	tresult PLUGIN_API checkSizeConstraint(ViewRect* rect)
	{
		return 0;
	}
	*/

} // namespace Steinberg