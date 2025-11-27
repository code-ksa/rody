// Copyright 2024 Rody Browser
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Brand-specific installer behaviors for Rody Browser.

#include "chrome/installer/setup/brand_behaviors.h"

#include <windows.h>

#include <shellapi.h>

#include <memory>
#include <string_view>

#include "base/files/file_path.h"
#include "base/json/json_file_value_serializer.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "base/strings/strcat_win.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "base/values.h"
#include "base/version.h"
#include "base/win/registry.h"
#include "base/win/windows_version.h"
#include "chrome/common/chrome_paths_internal.h"
#include "chrome/install_static/install_util.h"
#include "components/metrics/metrics_pref_names.h"
#include "third_party/crashpad/crashpad/client/crash_report_database.h"
#include "third_party/crashpad/crashpad/client/settings.h"
#include "third_party/crashpad/crashpad/util/misc/uuid.h"

namespace installer {

namespace {

// Rody Browser support URL for uninstall feedback.
constexpr std::wstring_view kUninstallSurveyUrl(
    L"https://rodybrowser.com/uninstall-feedback");

// Launches the url directly with the user's default handler for |url|.
bool NavigateToUrlWithDefaultBrowser(const std::wstring& url) {
  SHELLEXECUTEINFO info = {sizeof(info)};
  info.fMask = SEE_MASK_NOASYNC;
  info.lpVerb = L"open";
  info.lpFile = url.c_str();
  info.nShow = SW_SHOWNORMAL;
  if (::ShellExecuteEx(&info))
    return true;
  PLOG(ERROR) << "Failed to launch default browser for uninstall survey";
  return false;
}

// Returns true if the prefs dictionary located at |local_data_path| contains
// an enabled metrics pref.
bool IsMetricsEnabled(const base::FilePath& file_path) {
  JSONFileValueDeserializer json_deserializer(file_path);

  std::unique_ptr<base::Value> root =
      json_deserializer.Deserialize(nullptr, nullptr);
  // Preferences should always have a dictionary root.
  if (!root || !root->is_dict())
    return false;

  const std::optional<bool> value = root->GetDict().FindBoolByDottedPath(
      metrics::prefs::kMetricsReportingEnabled);

  return value.value_or(false);
}

}  // namespace

// Rody Browser doesn't use Google Update, so this is a no-op.
void UpdateInstallStatus() {}

// Returns distribution data for telemetry purposes.
// For Rody Browser, we only collect crash client id if metrics are enabled.
std::wstring GetDistributionData() {
  std::wstring result;

  // Crash client id - only collected if user has opted in to metrics.
  base::FilePath crash_dir;
  if (chrome::GetDefaultUserDataDirectory(&crash_dir)) {
    crash_dir = crash_dir.Append(FILE_PATH_LITERAL("Crashpad"));
    crashpad::UUID client_id;
    std::unique_ptr<crashpad::CrashReportDatabase> database(
        crashpad::CrashReportDatabase::InitializeWithoutCreating(crash_dir));
    if (database && database->GetSettings()->GetClientID(&client_id)) {
      result.append(L"crash_client_id=").append(client_id.ToWString());
    }
  }

  return result;
}

// Performs brand-specific operations following uninstallation of the browser.
// Opens the uninstall survey page with version and OS information.
void DoPostUninstallOperations(const base::Version& version,
                               const base::FilePath& local_data_path,
                               const std::wstring& distribution_data) {
  // Get OS version information.
  const base::win::OSInfo* os_info = base::win::OSInfo::GetInstance();
  base::win::OSInfo::VersionNumber version_number = os_info->version_number();
  std::wstring os_version =
      base::StrCat({base::NumberToWString(version_number.major), L".",
                    base::NumberToWString(version_number.minor), L".",
                    base::NumberToWString(version_number.build)});

  // Build the survey URL with query parameters.
  std::wstring url = std::wstring(kUninstallSurveyUrl);
  url += L"?crversion=";
  url += base::ASCIIToWide(version.GetString());
  url += L"&os=";
  url += os_version;

  // Include distribution data only if metrics are enabled.
  if (!distribution_data.empty() && IsMetricsEnabled(local_data_path)) {
    url += L"&";
    url += distribution_data;
  }

  // Open the survey in the user's default browser.
  NavigateToUrlWithDefaultBrowser(url);
}

}  // namespace installer
