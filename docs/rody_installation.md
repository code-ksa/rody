# Rody Browser Installation Guide

This document provides comprehensive instructions for building and installing
Rody Browser across all supported platforms.

## Supported Platforms

- **Windows**: Windows 10 and later (x64, x86, arm64)
- **macOS**: macOS 10.15 (Catalina) and later (x64, arm64)
- **Linux**: Ubuntu 18.04+, Debian 10+, Fedora 32+, and compatible distributions
- **Android**: Android 8.0 (API 26) and later
- **iOS**: iOS 15.0 and later (limited builds)

## Building Installers

### Prerequisites

Follow the standard Chromium build prerequisites for your platform:
- [Windows Build Instructions](windows_build_instructions.md)
- [macOS Build Instructions](mac_build_instructions.md)
- [Linux Build Instructions](linux/build_instructions.md)
- [Android Build Instructions](android_build_instructions.md)
- [iOS Build Instructions](ios_build_instructions.md)

### Windows Installer

The Windows installer (`mini_installer.exe`) is built using the GN build system.

#### Build Commands

```bash
# Generate build files with Rody branding
gn gen out/Default --args='is_rody_branded=true is_official_build=true'

# Build the mini installer
autoninja -C out/Default mini_installer
```

The installer will be available at `out/Default/mini_installer.exe`.

#### Installation Options

```bash
# Per-user installation (default)
mini_installer.exe

# System-level installation (requires administrator)
mini_installer.exe --system-level

# Silent installation
mini_installer.exe /silent

# Verbose logging
mini_installer.exe --verbose-logging
```

#### Log Files

- Per-user install: `%TMP%\rody_installer.log`
- System install: `%SYSTEMROOT%\SystemTemp\rody_installer.log`

### macOS Installer

The macOS installer creates a signed DMG file.

#### Build Commands

```bash
# Generate build files with Rody branding
gn gen out/Default --args='is_rody_branded=true is_official_build=true'

# Build the browser
autoninja -C out/Default chrome

# Create the DMG (after signing)
python3 chrome/installer/mac/sign_chrome.py out/Default
```

The DMG will be available in the `out/Default` directory.

#### Installation

1. Open the `.dmg` file
2. Drag Rody Browser to the Applications folder
3. Optionally, you can install from the command line:
   ```bash
   hdiutil attach RodyBrowser.dmg
   cp -R /Volumes/Rody\ Browser/Rody\ Browser.app /Applications/
   hdiutil detach /Volumes/Rody\ Browser
   ```

### Linux Installer

Linux installers are available in DEB (Debian/Ubuntu) and RPM (Fedora/RHEL)
formats.

#### Build Commands

```bash
# Generate build files with Rody branding
gn gen out/Default --args='is_rody_branded=true is_official_build=true'

# Build the Linux installers
autoninja -C out/Default linux
```

The packages will be available in `out/Default`:
- `rody-browser-stable_<version>_amd64.deb`
- `rody-browser-stable-<version>.x86_64.rpm`

#### Installation

**Debian/Ubuntu:**
```bash
sudo dpkg -i rody-browser-stable_<version>_amd64.deb
sudo apt-get install -f  # Install dependencies if needed
```

**Fedora/RHEL:**
```bash
sudo dnf install rody-browser-stable-<version>.x86_64.rpm
```

**Arch Linux (manual):**
```bash
# Extract the DEB or RPM and install manually
sudo pacman -S dependencies...
```

### Android APK

Android builds produce an APK file that can be installed on Android devices.

#### Build Commands

```bash
# Set up Android build environment
source build/android/envsetup.sh

# Generate build files for Android
gn gen out/Android --args='target_os="android" is_rody_branded=true is_official_build=true'

# Build the APK
autoninja -C out/Android chrome_public_apk
```

The APK will be available at `out/Android/apks/ChromePublic.apk`.

#### Installation

```bash
# Install via ADB
adb install out/Android/apks/ChromePublic.apk

# Or transfer the APK to your device and install manually
```

### iOS IPA

iOS builds are only available for official development purposes.

#### Build Commands

```bash
# Generate build files for iOS
gn gen out/iOS --args='target_os="ios" is_rody_branded=true is_official_build=true'

# Build the iOS app
autoninja -C out/iOS chrome_ios
```

Note: iOS builds require a valid Apple Developer certificate for distribution.

## Uninstallation

### Windows

1. Open Settings > Apps > Installed Apps
2. Find "Rody Browser" and click Uninstall
3. Or run from command line: `RodyBrowser.exe --uninstall`

### macOS

1. Drag Rody Browser from Applications to Trash
2. Optional: Remove user data from `~/Library/Application Support/Rody`

### Linux

**Debian/Ubuntu:**
```bash
sudo apt remove rody-browser
```

**Fedora/RHEL:**
```bash
sudo dnf remove rody-browser
```

### Android

1. Long-press the Rody Browser icon
2. Select "Uninstall" or drag to "Uninstall"
3. Or: Settings > Apps > Rody Browser > Uninstall

## Configuration

### Installation Directory

| Platform | Per-User Location | System Location |
|----------|-------------------|-----------------|
| Windows  | `%LOCALAPPDATA%\Rody\Browser` | `%PROGRAMFILES%\Rody\Browser` |
| macOS    | - | `/Applications/Rody Browser.app` |
| Linux    | - | `/opt/rody/browser` |

### User Data Directory

| Platform | Location |
|----------|----------|
| Windows  | `%LOCALAPPDATA%\Rody\User Data` |
| macOS    | `~/Library/Application Support/Rody` |
| Linux    | `~/.config/rody` |

## Troubleshooting

### Windows

**Installation fails silently:**
- Check the installer log at `%TMP%\rody_installer.log`
- Ensure you have sufficient disk space
- Try running as Administrator for system-level installs

**"Windows protected your PC" warning:**
- This appears because the installer is not signed with an EV certificate
- Click "More info" then "Run anyway"

### macOS

**"Rody Browser is damaged and can't be opened":**
```bash
xattr -c /Applications/Rody\ Browser.app
```

**Gatekeeper blocks installation:**
- Go to System Preferences > Security & Privacy
- Click "Open Anyway"

### Linux

**Missing dependencies:**
```bash
# Debian/Ubuntu
sudo apt-get install -f

# Fedora/RHEL
sudo dnf install <missing-packages>
```

## Advanced Topics

### Enterprise Deployment

For enterprise deployments, consider:
- Using MSI installer for Windows Group Policy deployment
- Using configuration management tools (Chef, Puppet, Ansible)
- Setting up initial preferences via `initial_preferences` file

### Command Line Options

See the full list of command line options:
```bash
rody --help
```

### Building Debug Installers

For development purposes:
```bash
gn gen out/Debug --args='is_rody_branded=true is_debug=true'
autoninja -C out/Debug mini_installer
```

## Support

For installation issues and support:
- Visit: https://rodybrowser.com/help
- Report bugs: https://rodybrowser.com/report-issue
