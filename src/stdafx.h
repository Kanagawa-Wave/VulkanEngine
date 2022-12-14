//
// Created by Yuqi_Lu on 2022/12/13.
//

#ifndef VULKANENGINE_STDAFX_H
#define VULKANENGINE_STDAFX_H

#include <exception>
#include <algorithm>
#include <set>
#include <vector>
#include <memory>
#include <optional>
#include <iostream>

#ifndef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

#endif //VULKANENGINE_STDAFX_H
