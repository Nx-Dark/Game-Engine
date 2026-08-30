#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifdef DARK_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include <iostream>
#include <functional>
#include <utility>
#include <algorithm>
#include <memory>
#include <chrono>
#include <filesystem>

#include "Dark/Core/Log.h"
#include "Dark/Core/Core.h"

#include "Dark/Debug/InstrumentationProfiler.h"

#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdint>