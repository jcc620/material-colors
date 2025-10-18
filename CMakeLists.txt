cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

add_executable(material-colors src/main.cc)

target_link_libraries(material-colors PUBLIC material_color_utilities_lib)

set_property(TARGET material-colors PROPERTY CXX_STANDARD 17)
set_property(TARGET material-colors PROPERTY CXX_STANDARD_REQUIRED ON)

add_library(material_color_utilities_lib STATIC
    third_party/material-color-utilities/cpp/cam/hct.cc
    third_party/material-color-utilities/cpp/cam/hct_solver.cc
    third_party/material-color-utilities/cpp/cam/cam.cc
    third_party/material-color-utilities/cpp/cam/viewing_conditions.cc
    third_party/material-color-utilities/cpp/utils/utils.cc
)

target_include_directories(material-colors PRIVATE
    third_party/material-color-utilities
    third_party
)

target_include_directories(material_color_utilities_lib PRIVATE
    third_party/material-color-utilities
)


add_subdirectory(third_party/abseil-cpp)
target_link_libraries(material_color_utilities_lib PUBLIC absl::strings)