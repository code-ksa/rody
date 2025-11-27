// Copyright 2024 Rody Browser
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Brand-specific constants and install modes for Rody Browser.

#include "chrome/install_static/rody_install_modes.h"

#include <stdlib.h>

#include "chrome/install_static/install_modes.h"

namespace install_static {

const wchar_t kCompanyPathName[] = L"Rody";

const wchar_t kProductPathName[] = L"Rody";

const size_t kProductPathNameLength = _countof(kProductPathName) - 1;

const char kSafeBrowsingName[] = "rody";

}  // namespace install_static
