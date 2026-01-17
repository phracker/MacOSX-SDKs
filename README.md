# MacOSX-SDKs

---

## Overview

This repository is a comprehensive collection of macOS SDKs (Software Development Kits) from Xcode 2.0 (macOS 10.1.5) to modern releases (macOS 16.x in 2025-2026). These SDKs are compiled from various releases of Xcode and Command Line Tools.

**If you need individual SDK releases rather than the entire repository**, download them from the [GitHub Releases page](https://github.com/phracker/MacOSX-SDKs/releases).

## Repository Contents

| SDK Version | Compatible macOS | Xcode Version | Size |
|-------------|------------------|---------------|------|
| **Legacy SDKs (Unpacked)** | | | |
| MacOSX10.1.5.sdk | macOS 10.1.5 | Xcode 2.0 | 44M |
| MacOSX10.2.8.sdk | macOS 10.2.8 | Xcode 2.5 | 59M |
| MacOSX10.3.0.sdk | macOS 10.3.0 | Xcode 1.5 | 86M |
| MacOSX10.3.9.sdk | macOS 10.3.9 | Xcode 2.1 | 135M |
| MacOSX10.4u.sdk | macOS 10.4 (Universal) | Xcode 2.4.1 | 156M |
| MacOSX10.5.sdk | macOS 10.5 | Xcode 3.1 | 237M |
| MacOSX10.6.sdk | macOS 10.6 | Xcode 4.0 | 248M |
| MacOSX10.7.sdk | macOS 10.7 | Xcode 4.6 | 177M |
| MacOSX10.8.sdk | macOS 10.8 | Xcode 4.6 | 152M |
| MacOSX10.9.sdk | macOS 10.9 | Xcode 5.0 | 328M |
| MacOSX10.10.sdk | macOS 10.10 | Xcode 6.1 | 330M |
| MacOSX10.11.sdk | macOS 10.11 | Xcode 7.3 | 333M |
| MacOSX10.12.sdk | macOS 10.12 | Xcode 8.1 | 337M |
| MacOSX10.13.sdk | macOS 10.13 | Xcode 9.0 | 229M |
| MacOSX10.14.sdk | macOS 10.14 | Xcode 10.0 | 289M |
| MacOSX10.15.sdk | macOS 10.15 | Xcode 11.0 | 395M |
| MacOSX11.0.sdk | macOS 11.0 (Big Sur) | Xcode 12.0 | 565M |
| MacOSX11.1.sdk | macOS 11.1 | Xcode 12.2 | 555M |
| MacOSX11.3.sdk | macOS 11.3 | Xcode 12.5 | 574M |
| **Modern SDKs (Packed as .tar.xz)** | | | |
| MacOSX12.0.sdk | macOS 12.0 (Monterey) | Xcode 13.0 | 52M |
| MacOSX12.1.sdk | macOS 12.1 | Xcode 13.2 | 52M |
| MacOSX12.3.sdk | macOS 12.3 | Xcode 13.3 | 51M |
| MacOSX13.0.sdk | macOS 13.0 (Ventura) | Xcode 14.0 | 56M |
| MacOSX13.3.sdk | macOS 13.3 | Xcode 14.3 | 56M |
| MacOSX14.0.sdk | macOS 14.0 (Sonoma) | Xcode 15.0 | 64M |
| MacOSX14.2.sdk | macOS 14.2 | Xcode 15.2 | 62M |
| MacOSX14.4.sdk | macOS 14.4 | Xcode 15.4 | 65M |
| MacOSX14.5.sdk | macOS 14.5 | Xcode 15.4 | 65M |
| MacOSX15.0.sdk | macOS 15.0 (Sequoia) | Xcode 16.0 | 65M |
| MacOSX15.1.sdk | macOS 15.1 | Xcode 16.1 | 65M |
| MacOSX15.2.sdk | macOS 15.2 | Xcode 16.2 | 65M |
| MacOSX15.5.sdk | macOS 15.5 | Xcode 16.5 | 75M |
| MacOSX26.0.sdk | macOS 16.0 | Xcode 17.0 | 83M |
| MacOSX26.1.sdk | macOS 16.1 | Xcode 17.1 | 84M |
| MacOSX26.2.sdk | macOS 16.2 | Xcode 17.2 | 295M |

> **Note:** For outdated/legacy versions, the altenrate download links are provided in the older version of this README file.

## Getting Xcode SDKs (2025-2026)

There are several methods to obtain macOS SDKs for modern development:

### 1. **Xcode via App Store (Recommended)**
   ```bash
   # Install Xcode from the Mac App Store
   # All SDKs are bundled with Xcode
   # SDK location: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/
   ```

### 2. **Command Line Tools for Xcode (CLT)**
   ```bash
   # For development without the full Xcode IDE
   sudo xcode-select --install

   # Check your active SDK path
   xcrun --show-sdk-path

   # SDKs are located at:
   # /Library/Developer/CommandLineTools/SDKs/
   ```

### 3. **Apple Developer Downloads Portal**
   - **URL:** [developer.apple.com/download/all](https://developer.apple.com/download/all)
   - **Requirements:** Apple Developer account (free account available)
   - **What's available:** Full Xcode versions, Command Line Tools, additional SDKs
   - **Tip:** Older Xcode versions (including beta builds) may be available

### 4. **Xcode Beta & Archive**
   - Beta versions include latest SDKs
   - Helps test upcoming macOS features
   - Access via [developer.apple.com/xcode](https://developer.apple.com/xcode)

### 5. **Homebrew Cask**
   ```bash
   # Install Xcode Command Line Tools
   brew install --cask xcode

   # Or install specific Xcode version (check available versions first)
   ```

## Installation & Usage

### 1. **Extracting SDK from Archive**
   For SDKs delivered as `.tar.xz` archives:
   ```bash
   # Download the SDK tarball
   # Extract
   xz -d MacOSX<version>.sdk.tar.xz
   tar xvf MacOSX<version>.sdk.tar

   # For newer SDKs (macOS 12+), the archive format is simpler
   tar -xJf MacOSX*.sdk.tar.xz
   ```

### 2. **Placing SDK in Xcode Directory**
   ```bash
   # Xcode 15+ (recommended location)
   sudo cp -r MacOSX<version>.sdk /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/

   # OR: Command Line Tools installation
   sudo cp -r MacOSX<version>.sdk /Library/Developer/CommandLineTools/SDKs/

   # Verify the SDK is recognized
   xcrun --sdk macosx --show-sdk-path
   ```

### 3. **Removing SIP Quarantine Flags**
   If you encounter issues with older SDKs on modern macOS:
   ```bash
   sudo xattr -d -r com.apple.quarantine /path/to/sdk/MacOSX*.sdk
   ```

### 4. **Using the SDK in Builds**

#### Setting Environment Variables
```bash
export SDKROOT=/path/to/your/sdk
```

#### Specifying Compiler Paths
If your build system doesn't automatically find the compiler:
```bash
export CC="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
export CXX="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
```

#### CMake Projects
```bash
cmake -G Ninja -S project-root-dir -B build-output-dir
cmake --build build-output-dir
```

#### Autotools Projects
```bash
./configure --prefix=/usr/local/your-package --host=x86_64-apple-darwin
```

#### Manual Compilation
```bash
clang --target=x86_64-apple-darwin23 -isysroot /path/to/sdk -o program program.c
```

### 5. **Working with Make Projects**
```bash
export SDKROOT=/path/to/your/sdk
export MACOSX_DEPLOYMENT_TARGET=<version>
make
```

## Legal & Compatibility Notes

### Important Compatibility Considerations
- **Apple Silicon (M1/M2/M3)**: Ensure the SDK you're using provides ARM64 (`arm64`) binaries
- **Intel Macs**: Use `x86_64` architecture SDKs
- **Universal Binaries**: SDKs 10.4u and later support multiple architectures

### SIP (System Integrity Protection)
- Modern macOS versions (10.14+) enforce SIP by default
- Location-Independent SDKs may require SIP adjustments
- Consider using `xattr -d` to remove quarantine flags on extracted SDKs

### Development for Legacy Systems
- Older SDKs (10.1-10.10) may require older Xcode for proper compilation
- Cross-compilation from newer macOS versions using older SDKs is possible but requires careful configuration
- Test your build with your target SDK before deployment

## Troubleshooting

### Issue: "Unable to find SDK"
- **Solution:** Verify location with `xcrun --show-sdk-path`
- **Check permissions:** `sudo chmod -R 755 /path/to/sdk`

### Issue: "Compilation errors with old SDK"
- **Solution:** Some older SDKs may have missing libraries or incompatibilities
- **Consider:** Using a newer SDK matching your build target

### Issue: "xattr: command not found"
- **Solution:** `xattr` is included on macOS. Ensure your shell can access system utilities.

### Issue: "Permission denied" during SDK installation
- **Solution:** Use `sudo` when copying SDKs, but consider:
  ```bash
  sudo chown -R $(whoami) /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/
  ```

## Contributing

### Adding New SDKs
1. Download the new SDK from Apple Developer Portal
2. Verify SDK compatibility and structure
3. Run the `make_tarballs.sh` script to create distribution tarballs
4. Update this README with the new SDK entry

### Building Distribution Archives
```bash
chmod +x make_tarballs.sh
./make_tarballs.sh
```

## Additional Resources

- **Apple Developer Documentation:** [developer.apple.com/documentation](https://developer.apple.com/documentation)
- **Xcode Release Notes:** [developer.apple.com/xcode/release-notes](https://developer.apple.com/xcode/release-notes)
- **Homebrew for macOS Development:** [brew.sh](https://brew.sh)
- **LLVM/Clang Documentation:** [llvm.org](https://llvm.org)

## License

This repository is a collection of SDKs from various Xcode releases. Each Xcode version and its SDKs are subject to Apple's licensing terms. Please review Apple's terms before use.

---

**Last Updated:** 2025-01-17
**Xcode Compatibility:** 2.0 - 17.2+
**macOS Range:** 10.1.5 - 16.2
