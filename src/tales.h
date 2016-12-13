#pragma once

#ifdef WIN32
#define TALES_WIN32
#endif

#ifdef TALES_WIN32
#include "platform/win32/platform.h"
#endif

#include <cassert>
#define tales_assert assert

#ifndef TALES_EXPORT
#define TALES_API //__declspec(dllimport)
#else
#define TALES_API //__declspec(dllexport)
#endif

#pragma warning(disable:4217)

#include <cstring>
#include <memory>
#include <cstdarg>
#include <ctype.h>

// tales classes
#include "core/object.h"
#include "core/string.h"

