#pragma once

#include "pluginterfaces/base/fplatform.h"
#include <string>

namespace Steinberg {
namespace Vst {

#if PLATFORM_X64
#if NDEBUG
static const FUID LUFSMeterProcessorUID(0xBA255AA4, 0x126B11E8, 0x9F421E9B, 0x194601C1);
static const FUID LUFSMeterControllerUID(0xD4AA4E2A, 0x126B11E8, 0xBC48B59B, 0x194601C1);
#else
static const FUID LUFSMeterProcessorUID(0xE504479E, 0x126B11E8, 0xB27CD49B, 0x194601C1);
static const FUID LUFSMeterControllerUID(0xF637E78C, 0x126B11E8, 0x95D7E39B, 0x194601C1);
#endif
#else
#if NDEBUG
static const FUID LUFSMeterProcessorUID(0x05971ACC, 0x126C11E8, 0x8C5BEE9B, 0x194601C1);
static const FUID LUFSMeterControllerUID(0x1422035E, 0x126C11E8, 0x8AEC419C, 0x194601C1);
#else
static const FUID LUFSMeterProcessorUID(0x2228642A, 0x126C11E8, 0x92BC4E9C, 0x194601C1);
static const FUID LUFSMeterControllerUID(0x371B0202, 0x126C11E8, 0xBAB06D9C, 0x194601C1);
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

#define NAME_STR "LUFS Meter " PLATFORM_STR " " CONFIG_STR
