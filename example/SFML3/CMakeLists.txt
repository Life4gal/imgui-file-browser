project(IMFB_SFML3)

# ===================================================================================================
# DEPENDENCIES

# SFML3
find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Audio)
find_package(OpenGL REQUIRED)
set(IMFB_SFML_LIBRARIES "SFML::Graphics;SFML::Audio;OpenGL::GL")

add_executable(
	${PROJECT_NAME}
	
	${CMAKE_CURRENT_SOURCE_DIR}/imgui-SFML.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui-SFML.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(
	${PROJECT_NAME} 
	PUBLIC 

	${CMAKE_CURRENT_SOURCE_DIR}
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
	IMFB
)
