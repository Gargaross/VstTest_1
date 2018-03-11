#include "Controller.h"
#include "Editor.h"
#include "LUFS Meter.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"
#include "vstgui\plugin-bindings\vst3editor.h"

namespace Steinberg {
namespace Vst {

		tresult PLUGIN_API Controller::initialize(FUnknown* context)
		{
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				parameters.addParameter(STR16("Bypass"), 0, 1, 0, ParameterInfo::kCanAutomate | ParameterInfo::kIsBypass, kBypassId);
				parameters.addParameter(STR16("LUFS"), 0, 0, 0, ParameterInfo::kCanAutomate, kLUFSId);
				parameters.addParameter(STR16("Gated LUFS"), 0, 0, 0, ParameterInfo::kCanAutomate, kGatedLUFSId);
				parameters.addParameter(STR16("Reset"), 0, 1, 0, ParameterInfo::kCanAutomate, kResetId);
			}
			return kResultTrue;
		}

		//------------------------------------------------------------------------
		tresult PLUGIN_API Controller::setComponentState(IBStream* state)
		{
			// we receive the current state of the component (processor part)
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

				// read the gain
				int32 gainState;
				if (state->read(&gainState, sizeof(gainState)) == kResultTrue)
				{
#if BYTEORDER == kBigEndian
					SWAP_32(gainState)
#endif
						//setParamNormalized(kGainId, gainState);

				}
			}

			return kResultOk;
		}

		tresult PLUGIN_API Controller::setState(IBStream* state)
		{
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

				// read the gain
				int32 gainState;
				if (state->read(&gainState, sizeof(gainState)) == kResultTrue)
				{
#if BYTEORDER == kBigEndian
					SWAP_32(gainState)
#endif
						//setParamNormalized(kGainId, gainState);

				}
			}

			return kResultOk;
		}

		tresult PLUGIN_API Controller::getState(IBStream* state)
		{
			int32 bypassState = getParamNormalized(kBypassId);
			//int32 gainState = getParamNormalized(kGainId);

#if BYTEORDER == kBigEndian
				SWAP_32(bypassState)
				SWAP_32(gainState)
#endif
			state->write(&bypassState, sizeof(bypassState));

			return kResultTrue;
		}

		tresult PLUGIN_API Controller::setParamNormalized(ParamID tag, ParamValue value)
		{
			Parameter* parameter = getParameterObject(tag);
			if (parameter)
			{
				parameter->setNormalized(value);
				return kResultTrue;
			}
			return kResultFalse;
		}

		IPlugView* PLUGIN_API Controller::createView(FIDString str)
		{
			// someone wants my editor
			if (str && strcmp(str, "editor") == 0)
			{
				Editor* view = new Editor(this);
				
				return view;
			}
			
			return 0;
		}

} // namespace Vst
} // namespace Steinberg
