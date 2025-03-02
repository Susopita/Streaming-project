// src/main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <services/client.hpp>
#include <models/pelicula.hpp>

using namespace std;

// Función para mostrar el menú principal
void display_menu()
{
    std::cout << "=====================================\n";
    std::cout << "          Streaming CLI\n";
    std::cout << "     Una plataforma de streaming\n";
    std::cout << "=====================================\n";
    std::cout << "1. Salir\n";
    std::cout << "2. Buscar peliculas\n";
    std::cout << "3. Ver mi \"Ver mas tarde\"\n";
    std::cout << "4. Ver mis \"Me gusta\"\n";
    std::cout << "5. Testear servidor (Hello World)\n";
    std::cout << "Seleccione una opcion: ";
}

int main()
{
    Client client;
    int option = 0;

    while (true)
    {
        display_menu();
        std::cin >> option;
        std::cin.ignore(); // Ignorar el carácter de nueva línea después de ingresar un número

        if (option == 1)
        {
            std::cout << "Saliendo del programa. ¡Hasta luego!\n";
            break;
        }
        else if (option == 2)
        {
            std::cout << "Ingrese el termino de busqueda: ";
            std::string query;
            std::getline(std::cin, query);

            if (query.empty())
            {
                std::cout << "El termino de busqueda no puede estar vacio.\n";
                continue;
            }

            std::cout << "\nBuscando peliculas para: \"" << query << "\"\n";

            std::vector<Pelicula> peliculas = client.search_peliculas(query);

            if (peliculas.empty())
            {
                std::cout << "No se encontraron peliculas.\n";
            }
            else
            {
                std::cout << "\nResultados encontrados:\n";
                for (const auto &pelicula : peliculas)
                {
                    std::cout << "-----------------------------\n";
                    std::cout << "ID: " << pelicula.id << "\n";
                    std::cout << "Titulo: " << pelicula.titulo << "\n";
                    // std::cout << "Sinopsis: " << pelicula.sinopsis << "\n"; // Muy grande, por ahora solo la evitamos
                    std::cout << "Tags: ";
                    for (const auto &tag : pelicula.tags)
                    {
                        std::cout << tag << " ";
                    }
                    std::cout << "\n";
                }
                std::cout << "-----------------------------\n";
                std::cout << "Total de peliculas encontradas: " << peliculas.size() << "\n";
            }
        }
        else if (option == 3)
        {
            // Ver mi "Ver más tarde" - sección en blanco
            std::cout << "Seccion 'Ver mas tarde' en desarrollo.\n";
        }
        else if (option == 4)
        {
            // Ver mis "Me gusta" - sección en blanco
            std::cout << "Seccion 'Me gusta' en desarrollo.\n";
        }
        else if (option == 5)
        {
            std::cout << "Testear servidor (Hello World):\n";
            std::string response = client.test_server();
            std::cout << "Respuesta del servidor: " << response << "\n";
        }
        else
        {
            std::cout << "Opcion no valida. Por favor, intente de nuevo.\n";
            // Limpiar la entrada estándar en caso de que el usuario haya ingresado un valor no numérico
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "\n"; // Añadir una línea en blanco antes de mostrar el menú nuevamente
    }

    return 0;
}
