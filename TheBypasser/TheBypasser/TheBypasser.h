#pragma once

#include "pluginterfaces/base/fplatform.h"


namespace Steinberg {
namespace Vst {

#if PLATFORM_X64
#if NDEBUG
static const FUID BypassProcessorUID(0x5278A87C, 0xEF1911E7, 0xB35DFF3C, 0x61172F1A);
static const FUID BypassControllerUID(0xE8205EAC, 0xF3C811E7, 0xBAD7E590, 0x7105BEE2);
#else
static const FUID BypassProcessorUID(0x84F2634C, 0xEF1911E7, 0x8FA2843D, 0x61172F1A);
static const FUID BypassControllerUID(0x10F3D264, 0xF3C911E7, 0x8FC7FD90, 0x7105BEE2);
#endif
#else
#if NDEBUG
static const FUID BypassProcessorUID(0x9C15CAF0, 0xEF1911E7, 0xAF6F943D, 0x61172F1A);
static const FUID BypassControllerUID(0x154C3522, 0xF3C911E7, 0xB3C70091, 0x7105BEE2);
#else
static const FUID BypassProcessorUID(0xAFF7A84A, 0xEF1911E7, 0xA129D83D, 0x61172F1A);
static const FUID BypassControllerUID(0x1BEB320C, 0xF3C911E7, 0x83E00191, 0x7105BEE2);
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

#define NAME_STR "The Bypasser " PLATFORM_STR " " CONFIG_STR
