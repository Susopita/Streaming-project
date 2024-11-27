# CMakeLists.txt en el frontend
add_executable(frontend
    src/main.cpp
    src/ui/UI.cpp
)

# Archivos de cabecera
target_include_directories(frontend PRIVATE ${CMAKE_SOURCE_DIR}/frontend/include)

# Si usas bibliotecas externas para la UI (Qt, wxWidgets, etc.)
# find_package(Qt5 REQUIRED)
# target_link_libraries(frontend Qt5::Widgets)
