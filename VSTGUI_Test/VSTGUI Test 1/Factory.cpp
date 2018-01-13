

#include "public.sdk/source/main/pluginfactoryvst3.h"
#include "Factory.h"
#include "Processor.h"
#include "Controller.h"

BEGIN_FACTORY_DEF("Gargaross Technologies",
	"http://www.testing.com",
	"mailto:info@testing.com")

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::TestProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		"VSTGUI Test 1",
		Vst::kDistributable,
		"Fx",
		"1.0",		// Plug-in version
		kVstVersionString,
		Steinberg::Vst::TestProcessor::createInstance)
	
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::TestControllerUID),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass,
		"VSTGUI Test 1 Controller",	// controller name (could be the same than component name)
		0,						// not used here
		"",						// not used here
		"1.0",		// Plug-in version (to be changed)
		kVstVersionString,
		Steinberg::Vst::TestController::createInstance)
		

END_FACTORY


bool InitModule()
{
	return true;
}

bool DeinitModule()
{
	return true;
}
