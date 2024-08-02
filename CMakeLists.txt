cmake_minimum_required(VERSION 3.24)
project(imgui_example_glfw_vulkan C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # testing

# GLFW
set(GLFW_DIR libs/glfw) # Set this to point to an up-to-date GLFW repo
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
option(GLEW_STATIC "static glew" ON)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)

# Freetype
set(FREETYPE_DIRECTORY "libs/freetype")
add_subdirectory(${FREETYPE_DIRECTORY})
# include_directories(${FREETYPE_DIRECTORY}/include)

# Dear ImGui
include_directories(BEFORE Resources)
set(IMGUI_DIR libs/imgui)
set(IMPLOT_DIR libs/implot)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ${IMPLOT_DIR} ..)
include_directories(${IMGUI_DIR}/misc/freetype)
add_compile_definitions(IMGUI_ENABLE_FREETYPE)
add_compile_definitions(IMGUI_USE_WCHAR32)

# Libraries
find_package(Vulkan REQUIRED)
#find_library(VULKAN_LIBRARY
  #NAMES vulkan vulkan-1)
#set(LIBRARIES "glfw;${VULKAN_LIBRARY}")
set(LIBRARIES "glfw;Vulkan::Vulkan")

# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

# For FontAwesome Icons
include_directories(libs/IconFontCppHeaders)

include_directories(libs/ImGuiNotify)

#file(GLOB sources *.cpp)

add_executable(${PROJECT_NAME} main.cpp src/GUI.cpp ${IMGUI_DIR}/misc/freetype/imgui_freetype.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMPLOT_DIR}/implot_demo.cpp ${IMPLOT_DIR}/implot_items.cpp ${IMPLOT_DIR}/implot.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_link_libraries(${PROJECT_NAME} freetype)

# target_link_libraries(${PROJECT_NAME} harfbuzz ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DImTextureID=ImU64)

# if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
#   set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
# endif()