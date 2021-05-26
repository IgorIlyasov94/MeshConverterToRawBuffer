#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <shobjidl.h>

#include <wrl/client.h>
#include <DirectXMath.h>

#include <vector>
#include <array>
#include <set>
#include <exception>
#include <utility>
#include <algorithm>
#include <memory>
#include <iterator>
#include <any>
#include <random>

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include <locale>
#include <codecvt>

using namespace Microsoft::WRL;
using namespace DirectX;
