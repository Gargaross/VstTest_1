
#include "public.sdk/source/main/pluginfactoryvst3.h"
#include "LUFS Meter.h"
#include "Processor.h"
#include "Controller.h"

// TODO
// Fix gated loudness, not working with ITU test samples, probably
// 2 channel support
// Test if OpenGL window works
// GUI change to OpenGL

// Reference material
// Specification
// https://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1770-4-201510-I!!PDF-E.pdf
// reference files
// https://www.itu.int/dms_pub/itu-r/opb/rep/R-REP-BS.2217-1-2012-PDF-E.pdf



BEGIN_FACTORY_DEF("Gargaross Technologies",
	"http://www.testing.com",
	"mailto:info@testing.com")

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::LUFSMeterProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		NAME_STR,
		Vst::kDistributable,
		"Fx|Other",
		"1.0",		// Plug-in version
		kVstVersionString,
		Steinberg::Vst::Processor::createInstance)

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::LUFSMeterControllerUID),
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
