// Copyright 2024 Rody Browser
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Brand-specific types and constants for Rody Browser.

#ifndef CHROME_INSTALL_STATIC_RODY_INSTALL_MODES_H_
#define CHROME_INSTALL_STATIC_RODY_INSTALL_MODES_H_

#include <array>

#include "chrome/app/chrome_dll_resource.h"
#include "chrome/common/chrome_icon_resources_win.h"
#include "chrome/install_static/install_constants.h"

namespace install_static {

// Note: This list of indices must be kept in sync with the brand-specific
// resource strings in chrome/installer/util/prebuild/create_string_rc.
enum InstallConstantIndex {
  RODY_INDEX,
  NUM_INSTALL_MODES,
};

inline constexpr auto kInstallModes = std::to_array<InstallConstants>({
    // The primary (and only) install mode for Rody Browser.
    {
        .size = sizeof(InstallConstants),
        .index = RODY_INDEX,  // The one and only mode for Rody.
        .install_switch =
            "",  // No install switch for the primary install mode.
        .install_suffix =
            L"",  // Empty install_suffix for the primary install mode.
        .logo_suffix = L"",  // No logo suffix for the primary install mode.
        .app_guid =
            L"",  // Empty app_guid since no integration with Google Update.
        .base_app_name = L"Rody",              // A distinct base_app_name.
        .base_app_id = L"Rody",                // A distinct base_app_id.
        .browser_prog_id_prefix = L"RodyHTM",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Rody HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "rody",
        .pdf_prog_id_prefix = L"RodyPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Rody PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{8A3C5E2F-B197-4685-9E8D-C7889F23A1BD}",  // Active Setup GUID.
        .legacy_command_execute_clsid =
            L"{B3E06F8A-C32B-55A9-9B0A-9C8E85G30271}",  // CommandExecuteImpl
                                                        // CLSID.
        .toast_activator_clsid = {0x746FFA70,
                                  0x19E7,
                                  0x5ECA,
                                  {0xCE, 0x25, 0x9B, 0x10, 0xEF, 0x98, 0x62,
                                   0x6A}},  // Toast Activator CLSID.
        .elevator_clsid = {0xE244C231,
                           0x7EC5,
                           0x5E7C,
                           {0x9C, 0xFF, 0x94, 0xC0, 0x9D, 0xB2, 0xC2,
                            0xC1}},  // Elevator CLSID.
        .elevator_iid = {0xcc29b0f6,
                         0x0d7,
                         0x5077,
                         {0xa5, 0xc3, 0x6b, 0xff, 0xd7, 0xff, 0xea,
                          0x4b}},  // IElevator IID and TypeLib
        // {CC29B0F6-00D7-5077-A5C3-6BFFD7FFEA4B}.
        .tracing_service_clsid = {0x94f7a478,
                                  0x553e,
                                  0x558f,
                                  {0x9c, 0xdd, 0x1f, 0x4f, 0xa8, 0xcf, 0xad,
                                   0xf3}},  // SystemTraceSession CLSID.
        .tracing_service_iid = {0xb4fe691b,
                                0xffe5,
                                0x5186,
                                {0xa2, 0x85, 0x86, 0xe1, 0xc2, 0xaa, 0xe4,
                                 0xdc}},  // ISystemTraceSessionRody IID and
                                          // TypeLib
        .default_channel_name =
            L"",  // Empty default channel name since no update integration.
        .channel_strategy = ChannelStrategy::UNSUPPORTED,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_MAINFRAME,  // App icon resource id.
        .html_doc_icon_resource_index =
            icon_resources::kHtmlDocIndex,  // HTML doc icon resource index.
        .pdf_doc_icon_resource_index =
            icon_resources::kPDFDocIndex,  // PDF doc icon resource index.
        .sandbox_sid_prefix =
            L"S-1-15-2-4362648266-2095557066-3042369810-952584806-"
            L"2049664496-"
            L"1035123259-",  // App container sid prefix for sandbox.
    },
});

}  // namespace install_static

#endif  // CHROME_INSTALL_STATIC_RODY_INSTALL_MODES_H_
