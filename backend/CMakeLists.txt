# backend/CMakeList.txt

# Archivos Fuentes
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Backend ejecutable
add_executable(
        Streaming_server 
        ${SOURCES}
)

# Dependencias del backend
include_directories("/usr/local/opt/asio/include")
find_package(Crow REQUIRED)
find_package(Threads REQUIRED)

# Archivos de encabezado
target_include_directories(Streaming_server PRIVATE
        ${CMAKE_SOURCE_DIR}/backend/include # Crow ya esta incluido aqui como crow_all.h
)

# Enlazar bibliotecas necesarias
target_link_libraries(Streaming_server PRIVATE
        nlohmann_json::nlohmann_json
        Threads::Threads
        ${CMAKE_THREAD_LIBS_INIT}
)

# Haabilitar testing
enable_testing()

# Agregar pruebas
#add_test(NAME test COMMAND Streaming_server)