cmake_minimum_required(VERSION 3.25)

# C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\vcpkg
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "Vcpkg toolchain file")
set(VCPKG_ROOT "C:/workspace/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "Vcpkg toolchain file")

set(IMFB_MAJOR_VERSION 1 CACHE STRING "IMFB major version")
set(IMFB_MINOR_VERSION 0 CACHE STRING "IMFB minor version")
set(IMFB_PATCH_VERSION 0 CACHE STRING "IMFB patch version")
set(IMFB_VERSION "${IMFB_MAJOR_VERSION}.${IMFB_MINOR_VERSION}.${IMFB_PATCH_VERSION}" CACHE STRING "IMFB version")

project(
	IMFB
	VERSION ${IMFB_VERSION}
	DESCRIPTION "IMFB"
	HOMEPAGE_URL "https://github.com/Life4gal/imgui-file-browser"
	LANGUAGES CXX
)

# ===================================================================================================
# PLATFORM

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(IMFB_PLATFORM_WINDOWS ON)
	set(IMFB_PLATFORM_NAME IMFB_PLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(IMFB_PLATFORM_LINUX ON)
	set(IMFB_PLATFORM_NAME IMFB_PLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(IMFB_PLATFORM_DARWIN ON)
	set(IMFB_PLATFORM_NAME IMFB_PLATFORM_DARWIN)
else ()
	message(FATAL_ERROR "[IMFB] Unknown Platform: ${CMAKE_SYSTEM_NAME}")
endif (CMAKE_SYSTEM_NAME STREQUAL "Windows")

# ===================================================================================================
# COMPILER

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(IMFB_COMPILER_MSVC ON)
	set(IMFB_COMPILER_NAME "MSVC")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	if (CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
		set(IMFB_COMPILER_CLANG_CL ON)
		set(IMFB_COMPILER_NAME "ClangCL")
	else ()
		set(IMFB_COMPILER_CLANG ON)
		set(IMFB_COMPILER_NAME "Clang")
	endif (CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(IMFB_COMPILER_GNU ON)
	set(IMFB_COMPILER_NAME "GNU")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
	set(IMFB_COMPILER_CLANG_APPLE ON)
	set(IMFB_COMPILER_NAME "AppleClang")
else ()
	message(FATAL_ERROR "[IMFB] Unknown compiler: ${CMAKE_CXX_COMPILER}")
endif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

# ===================================================================================================
# COMPILE FLAGS

if (IMFB_COMPILER_MSVC)
	set(IMFB_COMPILE_FLAGS "/D_CRT_SECURE_NO_WARNINGS;/DNOMINMAX;/utf-8;/W3;/WX;/Zc:preprocessor")
elseif (IMFB_COMPILER_CLANG_CL)
	set(IMFB_COMPILE_FLAGS "/D_CRT_SECURE_NO_WARNINGS;/DNOMINMAX;/utf-8;/W3;/WX")
elseif (IMFB_COMPILER_CLANG)
	set(IMFB_COMPILE_FLAGS "-Wall;-Wextra;-Wpedantic;-Werror")
elseif (IMFB_COMPILER_GNU)
	set(IMFB_COMPILE_FLAGS "-Wall;-Wextra;-Wpedantic;-Werror")
elseif (IMFB_COMPILER_CLANG_APPLE)
	set(IMFB_COMPILE_FLAGS "-Wall;-Wextra;-Wpedantic;-Werror")
endif (IMFB_COMPILER_MSVC)

# ===================================================================================================
# OUTPUT INFO

message(STATUS "[IMFB] CMAKE VERSION: ${CMAKE_VERSION}. Platform: ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}.")
message(STATUS "[IMFB] ${PROJECT_NAME}-${IMFB_VERSION} (${CMAKE_BUILD_TYPE})")

# ===================================================================================================
# DEPENDENCIES

# IMGUI
find_package(imgui CONFIG REQUIRED)

add_library(
	${PROJECT_NAME}
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/imgui-file_browser.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/imgui-file_browser.cpp
)

target_include_directories(
	${PROJECT_NAME} 
	PUBLIC 

	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(
	${PROJECT_NAME}
	PUBLIC

	${IMFB_COMPILE_FLAGS}
)

target_compile_definitions(
	${PROJECT_NAME}
	PUBLIC

	IMFB_MAJOR_VERSION=${IMFB_MAJOR_VERSION}
	IMFB_MINOR_VERSION=${IMFB_MINOR_VERSION}
	IMFB_PATCH_VERSION=${IMFB_PATCH_VERSION}
	IMFB_VERSION="${IMFB_VERSION}"

	IMFB_PROJECT_NAME="${PROJECT_NAME}"
	IMFB_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
	IMFB_GIT_COMMIT_INFO="${IMFB_GIT_COMMIT_INFO}"

	${IMFB_PLATFORM_NAME}

	# msvc
	$<$<CXX_COMPILER_ID:MSVC>:IMFB_COMPILER_MSVC>
	# g++
	$<$<CXX_COMPILER_ID:GNU>:IMFB_COMPILER_GNU>
	# clang-cl
	$<$<AND:$<CXX_COMPILER_ID:Clang>,$<STREQUAL:"${CMAKE_CXX_SIMULATE_ID}","MSVC">>:IMFB_COMPILER_CLANG_CL>
	# clang
	$<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<STREQUAL:"${CMAKE_CXX_SIMULATE_ID}","MSVC">>>:IMFB_COMPILER_CLANG>
	# apple clang
	$<$<CXX_COMPILER_ID:AppleClang>:IMFB_COMPILER_APPLE_CLANG>
)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
	cxx_std_23
)

target_link_libraries(
	${PROJECT_NAME} 
	PRIVATE 

	${IMFB_SFML_LIBRARIES}
	imgui::imgui
)
