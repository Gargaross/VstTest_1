#include "BypassController.h"
#include "BypasserCPlugView.h"
#include "BypasserIPlugView.h"
#include "TheBypasser.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"

namespace Steinberg {
namespace Vst {

		//DEF_CLASS_IID(IBypassTestController)

		//-----------------------------------------------------------------------------
		tresult PLUGIN_API BypassController::initialize(FUnknown* context)
		{
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				parameters.addParameter(STR16("Bypass"), 0, 1, 0, ParameterInfo::kCanAutomate | ParameterInfo::kIsBypass, kBypassId);

				//parameters.addParameter(STR16("Delay"), STR16("sec"), 0, 1, ParameterInfo::kCanAutomate, kDelayId);
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
				/*
				float savedDelay = 0.f;
				if (state->read(&savedDelay, sizeof(float)) != kResultOk)
				{
					return kResultFalse;
				}

#if BYTEORDER == kBigEndian
				SWAP_32(savedDelay)
#endif
					setParamNormalized(kDelayId, savedDelay);

				*/

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

		
		/*
		//------------------------------------------------------------------------
		bool PLUGIN_API BypassController::doTest()
		{
			// this is called when running thru the validator
			// we can now run our own test cases
			return true;
		}
		*/

		IPlugView* PLUGIN_API BypassController::createView(FIDString str)
		{
			return new Steinberg::BypasserPlugView();
		}
		

		//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
