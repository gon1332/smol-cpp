#if defined(USE_SMOL_STRING_VIEW)
#include "smol/string_view.h"
#define STD_OR_SMOL smol
#else
#include <string_view>
#define STD_OR_SMOL std
#endif
