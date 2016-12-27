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

#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstdarg>
#include <map>
#include <thread>

// tales classes
#include "core/object.h"
#include "core/array.h"
#include "core/map.h"
#include "core/string.h"

#include "net/socket.h"

