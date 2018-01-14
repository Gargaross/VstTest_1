#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
	namespace Vst {

		enum {
			kBypassId = 100
		};

		/*
		//------------------------------------------------------------------------
		class IBypassTestController : public FUnknown
		{
		public:
			virtual bool PLUGIN_API doTest() = 0;
			//------------------------------------------------------------------------
			static const FUID iid;
		};
		*/

		//DECLARE_CLASS_IID(IBypassTestController, 0x5AC98F39, 0x27234512, 0x84FBC4AD, 0x618A14FD)

		//-----------------------------------------------------------------------------
		class BypassController : public EditController/*, public IBypassTestController*/
		{
		public:
			//------------------------------------------------------------------------
			// create function required for Plug-in factory,
			// it will be called to create new instances of this controller
			//------------------------------------------------------------------------
			static FUnknown* createInstance(void*) { return (IEditController*)new BypassController(); }

			//---from IPluginBase--------
			tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;

			tresult PLUGIN_API setComponentState(IBStream* state) SMTG_OVERRIDE;

			IPlugView* PLUGIN_API createView(FIDString str) SMTG_OVERRIDE;

			//bool PLUGIN_API doTest() SMTG_OVERRIDE;

			//---Interface---------
			/*
			OBJ_METHODS(BypassController, EditController)
				DEFINE_INTERFACES
				//DEF_INTERFACE(IBypassTestController)
				END_DEFINE_INTERFACES(EditController)
				REFCOUNT_METHODS(EditController)
				*/
		};

		//------------------------------------------------------------------------
	} // namespace Vst
} // namespace Steinberg
