#pragma once

#ifdef WIN32
#define TALES_WIN32
#endif

#ifdef TALES_WIN32
#include "platform/win32/platform.h"
#endif

#include <cassert>
#define tassert assert

#include <cstring>
#include <memory>

// tales classes
#include "core/object.h"
#include "core/string.h"

