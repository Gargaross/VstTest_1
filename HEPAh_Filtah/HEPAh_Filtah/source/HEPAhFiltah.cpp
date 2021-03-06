
#include "public.sdk/source/main/pluginfactoryvst3.h"
#include "HEPAhFiltah.h"
#include "Processor.h"
#include "Controller.h"



BEGIN_FACTORY_DEF("Gargaross Technologies",
	"http://www.testing.com",
	"mailto:info@testing.com")

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::HEPAhFiltahProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		NAME_STR,
		Vst::kDistributable,
		"Fx|Other",
		"1.0",		// Plug-in version
		kVstVersionString,
		Steinberg::Vst::Processor::createInstance)

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::HEPAhFiltahControllerUID),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass,
		NAME_STR "Controller",	// controller name (could be the same than component name)
		0,						// not used here
		"",						// not used here
		"1.0",		// Plug-in version (to be changed)
		kVstVersionString,
		Steinberg::Vst::Controller::createInstance)

END_FACTORY

bool InitModule() { return true; }
bool DeinitModule() { return true; }
