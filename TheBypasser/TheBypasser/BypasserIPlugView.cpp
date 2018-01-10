#include "BypasserIPlugView.h"

namespace Steinberg {
	BypasserIPlugView::BypasserIPlugView()
	{

	}


	BypasserIPlugView::BypasserIPlugView(const ViewRect* _rect)
		: rect(0, 0, 0, 0), systemWindow(nullptr), plugFrame(nullptr)
	{
		if (_rect)
			rect = *_rect;
	}

	
	//------------------------------------------------------------------------
	tresult PLUGIN_API BypasserIPlugView::isPlatformTypeSupported(FIDString /*type*/)
	{
		return kNotImplemented;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API BypasserIPlugView::attached(void* parent, FIDString /*type*/)
	{
		systemWindow = parent;

		//attachedToParent();
		return kResultOk;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API BypasserIPlugView::removed()
	{
		systemWindow = nullptr;

		//removedFromParent();
		return kResultOk;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API BypasserIPlugView::onSize(ViewRect* newSize)
	{
		if (newSize)
			rect = *newSize;
		return kResultTrue;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API BypasserIPlugView::getSize(ViewRect* size)
	{
		if (size)
		{
			*size = rect;
			return kResultTrue;
		}
		return kInvalidArgument;
	}

} // namespace Steinberg