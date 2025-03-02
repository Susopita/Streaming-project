# backend/CMakeList.txt

# Archivos Fuentes
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Backend ejecutable
add_executable(
        Streaming_server 
        ${SOURCES}
)

# Dependencias del backend
find_package(Crow CONFIG REQUIRED)
find_package(Threads REQUIRED)

# Archivos de encabezado
target_include_directories(Streaming_server PRIVATE
        ${CMAKE_SOURCE_DIR}/backend/include # Crow ya esta incluido aqui como crow_all.h
        ${asio_SOURCE_DIR}/asio/include
)

# Enlazar bibliotecas necesarias
target_link_libraries(Streaming_server PRIVATE
        Crow::Crow
        nlohmann_json::nlohmann_json
        Threads::Threads        
        ${CMAKE_THREAD_LIBS_INIT}
)

if (WIN32)
       # target_compile_definitions(Streaming_server PRIVATE -DWIN32)
      #  target_link_libraries(Streaming_server PRIVATE 
      #          ws2_32
      #  )
       # link_directories("C:/msys64/mingw64/lib")
endif()

# Haabilitar testing
enable_testing()

# Agregar pruebas
#add_test(NAME test COMMAND Streaming_server)