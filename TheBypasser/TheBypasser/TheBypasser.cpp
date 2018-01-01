
#include "public.sdk/source/main/pluginfactoryvst3.h"
#include "TheBypasser.h"
#include "BypassProcessor.h"

BEGIN_FACTORY_DEF("Gargaross Technologies",
	"http://www.testing.com",
	"mailto:info@testing.com")

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::BypassProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		"The Bypasser",
		Vst::kDistributable,
		"Fx|Other",
		"1.0",		// Plug-in version
		kVstVersionString,
		Steinberg::Vst::BypassProcessor::createInstance)

END_FACTORY

bool InitModule() { return true; }
bool DeinitModule() { return true; }

