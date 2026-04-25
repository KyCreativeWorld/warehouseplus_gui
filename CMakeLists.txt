cmake_minimum_required(VERSION 3.10) # Modernized version
set(PROJECT WarehouseUI)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 17) # Ensures you can use modern C++ features

# 1. Properly find GLFW installed via Homebrew
find_package(glfw3 REQUIRED)

# 2. Updated Source List (Assuming you moved files to an /imgui folder)
set(SOURCES
    main.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp # Added this for the renderer
)

# 3. Create the executable
add_executable(${PROJECT} ${SOURCES})

# 4. Tell the compiler where the .h files are
target_include_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# 5. Link everything (The Mac-specific way)
if(APPLE)
    target_link_libraries(${PROJECT} PRIVATE 
        glfw 
        "-framework OpenGL" 
        "-framework Cocoa" 
        "-framework IOKit" 
        "-framework CoreVideo"
    )
endif()