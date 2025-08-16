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

auto main() noexcept -> int
{
	ImGui::FileBrowser file_browser{"FileBrowser"}; 

	file_browser.set_flags(
		// ImGui::FileBrowserFlags::NO_MODAL,
		// ImGui::FileBrowserFlags::SELECT_DIRECTORY,
		ImGui::FileBrowserFlags::MULTIPLE_SELECTION,
		ImGui::FileBrowserFlags::CONFIRM_ON_ENTER,
		ImGui::FileBrowserFlags::CLOSE_ON_ESCAPE,
		ImGui::FileBrowserFlags::ALLOW_SET_WORKING_DIRECTORY,
		ImGui::FileBrowserFlags::ALLOW_CREATE,
		ImGui::FileBrowserFlags::ALLOW_RENAME,
		ImGui::FileBrowserFlags::ALLOW_DELETE
	);
	file_browser.set_filter({".hpp", ".cpp", ".dll"});

	while (main_loop())
	{
		// Process event
		// ...

		// Update
		// ...

		ImGui::Begin("IMFB");
		{
			if (ImGui::Button("Open FileBrowser"))
			{
				file_browser.open();
			}
		}
		ImGui::End();

		file_browser.show(); 

		if (file_browser.has_selected()) 
		{ 
			auto selected = file_browser.get_selected(); 
			// Use selected file 
			// ...
		}

		// Render
		// ...
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
