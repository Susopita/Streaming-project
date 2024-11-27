# Archivos Fuentes
file(GLOB_RECURSE SOURCES "backend/src/*.cpp")

include_directories(include)

# CMakeLists.txt en el backend
add_executable(
        Streaming_backend
        ${SOURCES}
)

# Archivos de cabecera
target_include_directories(backend PRIVATE ${CMAKE_SOURCE_DIR}/backend/include)