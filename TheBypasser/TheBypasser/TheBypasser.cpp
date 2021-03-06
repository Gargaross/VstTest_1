
#include "public.sdk/source/main/pluginfactoryvst3.h"
#include "TheBypasser.h"
#include "BypassProcessor.h"
#include "BypassController.h"



BEGIN_FACTORY_DEF("Gargaross Technologies",
	"http://www.testing.com",
	"mailto:info@testing.com")

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::BypassProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		NAME_STR,
		Vst::kDistributable,
		"Fx|Other",
		"1.0",		// Plug-in version
		kVstVersionString,
		Steinberg::Vst::BypassProcessor::createInstance)

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::BypassControllerUID),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass,
		NAME_STR "Controller",	// controller name (could be the same than component name)
		0,						// not used here
		"",						// not used here
		"1.0",		// Plug-in version (to be changed)
		kVstVersionString,
		Steinberg::Vst::BypassController::createInstance)

END_FACTORY

bool InitModule() { return true; }
bool DeinitModule() { return true; }

void DbgOut(std::string str)
{
	char buffer[400];
	sprintf_s(buffer, str.c_str());
	//OutputDebugStringA(buffer);
	//OutputDebugString(L"\n");
}