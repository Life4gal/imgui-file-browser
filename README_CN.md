# IMFB（ImGui 文件浏览器）

[![License](https://img.shields.io/github/license/Life4gal/imgui-file-browser)](LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/Life4gal/imgui-file-browser)](https://github.com/Life4gal/imgui-file-browser)

## 项目简介

IMFB 是一个基于 [Dear ImGui](https://github.com/ocornut/imgui) 的跨平台现代 C++ 文件浏览器控件，适用于桌面应用程序，易于集成和定制。

## 主要特性

- 支持 Windows、Linux、macOS
- 现代 C++（C++23）
- 支持多选、目录选择、文件过滤
- 可自定义标志和界面
- 提供 SFML3 示例工程

## 快速开始

### 依赖环境

- CMake >= 3.25
- 支持 C++23 的编译器（MSVC、Clang、GCC、AppleClang）
- [Dear ImGui](https://github.com/ocornut/imgui)
- （可选）[SFML3](https://github.com/SFML/SFML) 用于示例

### 构建方法

```sh
git clone https://github.com/Life4gal/imgui-file-browser.git 
cd imgui-file-browser

# 使用 CMake 配置
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="C:/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake" cmake --build build
```

### 使用方法

包含头文件并链接库：
```cpp
#include <imgui-file_browser.hpp>

auto main() noexcept -> int
{
	ImGui::FileBrowser file_browser{"FileBrowser"}; 

	file_browser.set_flags(
			// ImGui::FileBrowserFlags::NO_MODAL,
			ImGui::FileBrowserFlags::CLOSE_ON_ESCAPE,
			ImGui::FileBrowserFlags::CONFIRM_ON_ENTER,
			ImGui::FileBrowserFlags::MULTIPLE_SELECTION,
			ImGui::FileBrowserFlags::PATH_EDITABLE
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
完整集成示例请参考 `example/SFML3/main.cpp`。

## 许可证

本项目采用 ISC 许可证。

## 相关链接

- [主页](https://github.com/Life4gal/imgui-file-browser)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [SFML](https://github.com/SFML/SFML)
