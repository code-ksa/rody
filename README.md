# ![Logo](chrome/app/theme/rody/product_logo_64.png) Rody Browser

Rody Browser is a fast, secure, and user-friendly web browser built on the
Chromium open-source project. It provides enhanced privacy, security, and
performance features for all users.

## Features

- **Fast Browsing**: Lightning-fast page loads and smooth navigation
- **Security**: Built-in protection against malware and phishing
- **Privacy**: Enhanced privacy controls and tracking protection
- **Installer**: Full Windows installer (install.exe) support
- **Cross-Platform**: Available for Windows, macOS, and Linux

## Building from Source

### Prerequisites

Follow the standard Chromium build prerequisites for your platform.

### Build with Rody Branding

To build Rody Browser with full branding:

```bash
gn gen out/Default --args='is_rody_branded=true'
autoninja -C out/Default chrome
```

### Build Installer (Windows)

To build the Windows installer:

```bash
gn gen out/Default --args='is_rody_branded=true is_official_build=true'
autoninja -C out/Default mini_installer
```

The installer will be available at `out/Default/mini_installer.exe`.

## Documentation

Documentation in the source is rooted in [docs/README.md](docs/README.md).

## Contributing

We welcome contributions! Please see our contributing guidelines for more
information.

## License

Rody Browser is open source and available under the same license as Chromium.
See the [LICENSE](LICENSE) file for details.

---

*Rody Browser is based on the [Chromium](https://www.chromium.org) open-source project.*
