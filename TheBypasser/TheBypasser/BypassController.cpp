#include "BypassController.h"
#include "BypassEditor.h"
#include "TheBypasser.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"
#include "vstgui\plugin-bindings\vst3editor.h"

namespace Steinberg {
namespace Vst {

		tresult PLUGIN_API BypassController::initialize(FUnknown* context)
		{
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				parameters.addParameter(STR16("Bypass"), 0, 1, 0, ParameterInfo::kCanAutomate | ParameterInfo::kIsBypass, kBypassId);
			}
			return kResultTrue;
		}

		//------------------------------------------------------------------------
		tresult PLUGIN_API BypassController::setComponentState(IBStream* state)
		{
			// we receive the current state of the component (processor part)
			// we read only the gain and bypass value...
			if (state)
			{
				// read the bypass
				int32 bypassState;
				if (state->read(&bypassState, sizeof(bypassState)) == kResultTrue)
				{
#if BYTEORDER == kBigEndian
					SWAP_32(bypassState)
#endif
						setParamNormalized(kBypassId, bypassState ? 1 : 0);
				}
			}

			return kResultOk;
		}

		tresult PLUGIN_API BypassController::setState(IBStream* state)
		{
			// we receive the current state of the component (processor part)
			// we read only the gain and bypass value...
			if (state)
			{
				// read the bypass
				int32 bypassState;
				if (state->read(&bypassState, sizeof(bypassState)) == kResultTrue)
				{
#if BYTEORDER == kBigEndian
					SWAP_32(bypassState)
#endif
					setParamNormalized(kBypassId, bypassState ? 1 : 0);
				}
			}

			return kResultOk;
		}

		tresult PLUGIN_API BypassController::getState(IBStream* state)
		{
			int32 bypassState = getParamNormalized(kBypassId);

#if BYTEORDER == kBigEndian
				SWAP_32(bypassState)
#endif
			state->write(&bypassState, sizeof(bypassState));

				return kResultTrue;
		}

		tresult PLUGIN_API BypassController::setParamNormalized(ParamID tag, ParamValue value)
		{
			Parameter* parameter = getParameterObject(tag);
			if (parameter)
			{
				parameter->setNormalized(value);
				return kResultTrue;
			}
			return kResultFalse;
		}

		IPlugView* PLUGIN_API BypassController::createView(FIDString str)
		{
			// someone wants my editor
			if (str && strcmp(str, "editor") == 0)
			{
				BypassEditor* view = new BypassEditor(this);
				
				return view;
			}
			
			return 0;
		}

} // namespace Vst
} // namespace Steinberg
