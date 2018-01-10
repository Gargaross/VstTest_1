#pragma once

#include "public.sdk\source\common\pluginview.h"

namespace Steinberg {

	class BypasserPlugView : public CPluginView
	{
	public:
		BypasserPlugView();

		/** Calls when this view will be attached to its parent view. */
		//void PLUGIN_API attachedToParent() SMTG_OVERRIDE {};

		/** Calls when this view will be removed from its parent view. */
		//void PLUGIN_API removedFromParent() SMTG_OVERRIDE;
		
		//tresult PLUGIN_API isPlatformTypeSupported(FIDString type);

		/** The parent window of the view has been created, the (platform) representation of the view
		should now be created as well.
		Note that the parent is owned by the caller and you are not allowed to alter it in any way
		other than adding your own views.
		Note that in this call the Plug-in could call a IPlugFrame::resizeView ()!
		\param parent : platform handle of the parent window or view
		\param type : \ref platformUIType which should be created */
		//tresult PLUGIN_API attached(void* parent, FIDString type) SMTG_OVERRIDE;

		/** The parent window of the view is about to be destroyed.
		You have to remove all your own views from the parent window or view. */
		//tresult PLUGIN_API removed() SMTG_OVERRIDE;

		/** Handling of mouse wheel. */
		//tresult PLUGIN_API onWheel(float distance) SMTG_OVERRIDE;

		/** Handling of keyboard events : Key Down.
		\param key : unicode code of key
		\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
		\param modifiers : any combination of modifiers - see \ref KeyModifier in keycodes.h
		\return kResultTrue if the key is handled, otherwise kResultFalse. \n
		<b> Please note that kResultTrue must only be returned if the key has really been
		handled. </b> Otherwise key command handling of the host might be blocked! */
		//tresult PLUGIN_API onKeyDown(char16 key, int16 keyCode, int16 modifiers) SMTG_OVERRIDE;

		/** Handling of keyboard events : Key Up.
		\param key : unicode code of key
		\param keyCode : virtual keycode for non ascii keys - see \ref VirtualKeyCodes in keycodes.h
		\param modifiers : any combination of KeyModifier - see \ref KeyModifier in keycodes.h
		\return kResultTrue if the key is handled, otherwise return kResultFalse. */
		//tresult PLUGIN_API onKeyUp(char16 key, int16 keyCode, int16 modifiers) SMTG_OVERRIDE;

		/** Returns the size of the platform representation of the view. */
		//tresult PLUGIN_API getSize(ViewRect* size) SMTG_OVERRIDE;

		/** Resizes the platform representation of the view to the given rect. Note that if the Plug-in
		*	requests a resize (IPlugFrame::resizeView ()) onSize has to be called afterward. */
		//tresult PLUGIN_API onSize(ViewRect* newSize) SMTG_OVERRIDE;

		/** Focus changed message. */
		//tresult PLUGIN_API onFocus(TBool state) SMTG_OVERRIDE;

		/** Sets IPlugFrame object to allow the Plug-in to inform the host about resizing. */
		//tresult PLUGIN_API setFrame(IPlugFrame* frame) SMTG_OVERRIDE;

		/** Is view sizable by user. */
		//tresult PLUGIN_API canResize() SMTG_OVERRIDE;

		/** On live resize this is called to check if the view can be resized to the given rect, if not
		*	adjust the rect to the allowed size. */
		//tresult PLUGIN_API checkSizeConstraint(ViewRect* rect) SMTG_OVERRIDE;
	};

} // namespace Steinberg