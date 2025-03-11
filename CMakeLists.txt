cmake_minimum_required(VERSION 3.24)
set(PROG_NAME "Imgui Vulkan App")
set(PRODUCT_NAME imguivulkanapp)
set(SUB_PRODUCT_NAME imguivulkanappexample)
set(COMPANY_NAME MyCompany)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
project(imgui_vulkan_example_app C CXX)

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

# For Notifications
if (WIN32)
  option(WINTOASTLIB_BUILD_EXAMPLES "Build WinToast examples" OFF)
  add_subdirectory(libs/WinToast EXCLUDE_FROM_ALL)
endif ()
# include_directories(libs/ImGuiNotify)

# For System File Dialog
add_subdirectory(libs/nativefiledialog-extended)

# For CmakeHelpers
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/libs/CMakeHelpers")
include(generate_product_version)
generate_product_version(ProductVersionFiles
    NAME ${PROG_NAME}
    VERSION_MAJOR ${VERSION_MAJOR}
    VERSION_MINOR ${VERSION_MINOR}
    VERSION_PATCH ${VERSION_PATCH}
    VERSION_REVISION 0
    COMPANY_NAME ${COMPANY_NAME})

#file(GLOB sources *.cpp)

set(SOURCES
  main.cpp
  src/GUI.cpp
)

set(IMGUI_SOURCES
  ${IMGUI_DIR}/misc/freetype/imgui_freetype.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMPLOT_DIR}/implot_demo.cpp
  ${IMPLOT_DIR}/implot_items.cpp
  ${IMPLOT_DIR}/implot.cpp
)

set(BACKEND_SOURCES
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES} ${BACKEND_SOURCES} ${target-files} ${ProductVersionFiles})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_link_libraries(${PROJECT_NAME} freetype nfd)
target_link_libraries(${PROJECT_NAME} WinToast)

# target_link_libraries(${PROJECT_NAME} harfbuzz ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DImTextureID=ImU64)

if (PROG_NAME)
    message(STATUS "Setting PROG_NAME to ${PROG_NAME}")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PROGI_NAME=${PROG_NAME})
    target_compile_definitions(${PROJECT_NAME} PRIVATE PRODUCT_NAME=${PRODUCT_NAME})
    target_compile_definitions(${PROJECT_NAME} PRIVATE SUB_PRODUCT_NAME=${SUB_PRODUCT_NAME})
    target_compile_definitions(${PROJECT_NAME} PRIVATE COMPANY_NAME=${COMPANY_NAME})
    target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_MAJOR=${VERSION_MAJOR})
    target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_MINOR=${VERSION_MINOR})
    target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_PATCH=${VERSION_PATCH})
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()