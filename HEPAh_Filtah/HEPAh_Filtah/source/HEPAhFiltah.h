#pragma once

#include "pluginterfaces/base/fplatform.h"
#include <string>

namespace Steinberg {
namespace Vst {

#if PLATFORM_X64
#if NDEBUG
static const FUID HEPAhFiltahProcessorUID(0x3B739E28, 0xFEE311E7, 0xACBF614B, 0x3154759D);
static const FUID HEPAhFiltahControllerUID(0x48A2812C, 0xFEE311E7, 0x9611664B, 0x3154759D);
#else
static const FUID HEPAhFiltahProcessorUID(0x5546A688, 0xFEE311E7, 0x8834734B, 0x3154759D);
static const FUID HEPAhFiltahControllerUID(0x6086624A, 0xFEE311E7, 0xB44D794B, 0x3154759D);
#endif
#else
#if NDEBUG
static const FUID HEPAhFiltahProcessorUID(0x6B03BD30, 0xFEE311E7, 0xAB8D7D4B, 0x3154759D);
static const FUID HEPAhFiltahControllerUID(0x76AA2DEA, 0xFEE311E7, 0x86CACA4B, 0x3154759D);
#else
static const FUID HEPAhFiltahProcessorUID(0x81BD0AC2, 0xFEE311E7, 0xB46A124C, 0x3154759D);
static const FUID HEPAhFiltahControllerUID(0x8D778BA8, 0xFEE311E7, 0x8E0C164C, 0x3154759D);
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

#define NAME_STR "HEPAh Filtah " PLATFORM_STR " " CONFIG_STR
