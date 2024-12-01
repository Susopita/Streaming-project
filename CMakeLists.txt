# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.29)
project(Streaming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR})

# Incluir bibliotecas
include(FetchContent)

# JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Incluir cabeceras
#include_directories(${nlohmann_json_SOURCE_DIR}/single_include)

# Subcarpetas del proyecto
add_subdirectory(backend)
add_subdirectory(frontend)

# Añadir un comando personalizado para ejecutar ambos
# Si existe una session de tmux, eliminar con "tmux kill-session -t run_streaming"
#
# Comandos Compilacion:
# > cmake --build build
# > cmake --build build --target Streaming_server
# > cmake --build build --target Streaming_client
#
# Comandos Compilacion y ejecucion:
# > cmake --build build --target run
# > cmake --build build --target run_backend
# > cmake --build build --target run_frontend
add_custom_target(run
    COMMAND tmux new-session -d -s run_streaming
    COMMAND tmux split-window -h
    COMMAND tmux send-keys -t run_streaming:0.0 "./backend/Streaming_server" C-m
    COMMAND tmux send-keys -t run_streaming:0.1 "while ! nc -z localhost 8080\; do sleep 1\; done\; clear\; ./frontend/Streaming_client" C-m
    COMMAND tmux attach-session -t run_streaming
    COMMENT "Ejecutando servidor y cliente en tmux"
)

add_custom_target(run_backend
    COMMAND tmux new-session -d -s run_streaming
    COMMAND tmux split-window -h
    COMMAND tmux send-keys -t run_streaming:0.0 "./backend/Streaming_server" C-m
    COMMAND tmux attach-session -t run_streaming
    DEPENDS Streaming_server
    COMMENT "Ejecutando el servidor en tmux"
)

add_custom_target(run_frontend
    COMMAND tmux new-session -d -s run_streaming
    COMMAND tmux split-window -h
    COMMAND tmux send-keys -t run_streaming:0.1 "while ! nc -z localhost 8080\; do sleep 1\; done\; clear\; ./frontend/Streaming_client" C-m
    COMMAND tmux attach-session -t run_streaming
    DEPENDS Streaming_client
    COMMENT "Ejecutando el cliente en tmux"
)

