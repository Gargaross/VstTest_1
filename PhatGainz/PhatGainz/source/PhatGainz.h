#pragma once

#include "pluginterfaces/base/fplatform.h"
#include <string>

namespace Steinberg {
namespace Vst {

#if PLATFORM_X64
#if NDEBUG
static const FUID PhatGainzProcessorUID(0x8BFF203A, 0xFE1411E7, 0x8C7744C9, 0x3054759D);
static const FUID PhatGainzControllerUID(0x9FF77C54, 0xFE1411E7, 0x987848C9, 0x3054759D);
#else
static const FUID PhatGainzProcessorUID(0xAF4B8B14, 0xFE1411E7, 0x848587C9, 0x3054759D);
static const FUID PhatGainzControllerUID(0xBB95E48C, 0xFE1411E7, 0xA90690C9, 0x3054759D);
#endif
#else
#if NDEBUG
static const FUID PhatGainzProcessorUID(0xC76A8920, 0xFE1411E7, 0xB64894C9, 0x3054759D);
static const FUID PhatGainzControllerUID(0xD245CBA2, 0xFE1411E7, 0x889ABEC9, 0x3054759D);
#else
static const FUID PhatGainzProcessorUID(0xDE38E67E, 0xFE1411E7, 0xAFCBC6C9, 0x3054759D);
static const FUID PhatGainzControllerUID(0xEB34A692, 0xFE1411E7, 0x953CCCC9, 0x3054759D);
#endif
#endif

} // Vst
} // Steinberg


#if PLATFORM_64
#define PLATFORM_STR "x64"
#else
#define PLATFORM_STR "x86"
#endif

#if NDEBUG
#define CONFIG_STR "Rel"
#else
#define CONFIG_STR "Dbg"
#endif

#define NAME_STR "Phat Gainz " PLATFORM_STR " " CONFIG_STR
