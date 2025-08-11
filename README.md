# IMFB (ImGui File Browser)

[![License](https://img.shields.io/github/license/Life4gal/imgui-file-browser)](LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/Life4gal/imgui-file-browser)](https://github.com/Life4gal/imgui-file-browser)

## Overview

IMFB is a cross-platform, modern C++ file browser widget for [Dear ImGui](https://github.com/ocornut/imgui). It provides a customizable, efficient, and easy-to-integrate file selection dialog for desktop applications.

## Features

- Cross-platform: Windows, Linux, macOS
- Modern C++ (C++23)
- Multiple selection, directory selection, filter support
- Customizable flags and appearance
- Example integration with SFML3

## Getting Started

### Prerequisites

- CMake >= 3.25
- C++23 compatible compiler (MSVC, Clang, GCC, AppleClang)
- [Dear ImGui](https://github.com/ocornut/imgui)
- (Optional) [SFML3](https://github.com/SFML/SFML) for example

### Build Instructions

```sh
git clone https://github.com/Life4gal/imgui-file-browser.git 
cd imgui-file-browser

# Configure with CMake
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="C:/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake" cmake --build build
```

### Usage

Include the header and link the library:
```cpp
#include <imgui-file_browser.hpp>

ImGui::FileBrowser browser{"Open File"}; 

browser.set_flags(
		// ImGui::FileBrowserFlags::NO_MODAL,
		ImGui::FileBrowserFlags::CLOSE_ON_ESCAPE,
		ImGui::FileBrowserFlags::CONFIRM_ON_ENTER,
		ImGui::FileBrowserFlags::MULTIPLE_SELECTION,
		ImGui::FileBrowserFlags::PATH_EDITABLE
	);
browser.set_filter({".hpp", ".cpp", ".dll"});

if (main_loop())
{
	if (button("open fb"))
	{
		browser.open(); 
	}

	browser.show(); 

	if (browser.has_selected()) 
	{ 
		auto selected = browser.get_selected(); 
		// Use selected file 
	}
}
```
See `example/SFML3/main.cpp` for a full integration example.

## License

This project is licensed under the ISC License.

## Links

- [Homepage](https://github.com/Life4gal/imgui-file-browser)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [SFML](https://github.com/SFML/SFML)
