MacOSX-SDKs
---
**10.1.5 - 11.3**

A collection of those pesky SDK folders.  Compiled from various releases of Xcode.

If you don't need this entire repository, each SDK is available [here](https://github.com/phracker/MacOSX-SDKs/releases).


<sub>Outdated versions: **[mediafire](http://www.mediafire.com/?a4g384ysgy5rg)** /  **[mega.co.nz](https://mega.co.nz/#F!H8xGhaDD!Uv5BTPr0LP7IU5pj0WGCKg)** / 
**[mediafire](http://www.mediafire.com/?abr89fy4uaz3z)** /  **[mega.co.nz](https://mega.co.nz/#F!4U4SXAxa!ZVltflL2O_5q57R0BVsPTg)**.
</sub>

**Important**

Modern versions of Xcode (7.3+) need you to edit the `MinimumSDKVersion` in this file to use older SDKs:
`/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Info.plist`

**Usage**

Set the SDKROOT environment variable:
```
export SDKROOT=path-to-old-sdk
```

If you put an old SDK in a nonstandard path, Apple's hacks in /usr/bin which redirect to calling Apple's
tools in the XCode installation may fail. If your build system fails to find the compiler, explicitly
specify its path:

```
export CC="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
export CXX="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
```

If you are building a project with CMake, using the default Unix Makefile generator may fail to
find the real `make` binary even if you put it in your $PATH before /usr/bin. To hack around this, install
[Ninja](https://ninja-build.org/) in your $PATH and use the Ninja CMake generator by running your CMake
configure step with:

```
cmake -G Ninja -S project-root-dir -B build-output-dir
```

