#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <pthread.h>
#include <cstring>

#include "Alalba/Core/Log.h"
#ifdef ALALBA_PLATFORM_WINDOWS
	#include<Windows.h>
#endif // ALALBA_PLATFORM_WINDOWS