# frontend/CMakeLists.txt

# Archivos Fuentes
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Frontend ejecutable
add_executable(
        Streaming_client
        ${SOURCES}
)

find_package(Threads REQUIRED)

# Archivos de cabecera
target_include_directories(Streaming_client PRIVATE 
        ${CMAKE_SOURCE_DIR}/frontend/include
)

# Enlazar Bibliotecas necesarias
target_link_libraries(Streaming_client PRIVATE
        nlohmann_json::nlohmann_json
        Threads::Threads
)

# Si usas bibliotecas externas para la UI (Qt, wxWidgets, etc.)
# find_package(Qt5 REQUIRED)
# target_link_libraries(frontend Qt5::Widgets)
