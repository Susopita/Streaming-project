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
    std::cout << "2. Buscar películas\n";
    std::cout << "3. Ver mi \"Ver más tarde\"\n";
    std::cout << "4. Ver mis \"Me gusta\"\n";
    std::cout << "5. Testear servidor (Hello World)\n";
    std::cout << "Seleccione una opción: ";
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
            std::cout << "Ingrese el término de búsqueda: ";
            std::string query;
            std::getline(std::cin, query);

            if (query.empty())
            {
                std::cout << "El término de búsqueda no puede estar vacío.\n";
                continue;
            }

            std::cout << "\nBuscando películas para: \"" << query << "\"\n";

            std::vector<Pelicula> peliculas = client.search_peliculas(query);

            if (peliculas.empty())
            {
                std::cout << "No se encontraron películas.\n";
            }
            else
            {
                std::cout << "\nResultados encontrados:\n";
                for (const auto &pelicula : peliculas)
                {
                    std::cout << "-----------------------------\n";
                    std::cout << "ID: " << pelicula.id << "\n";
                    std::cout << "Título: " << pelicula.titulo << "\n";
                    std::cout << "Sinopsis: " << pelicula.sinopsis << "\n";
                    std::cout << "Tags: ";
                    for (const auto &tag : pelicula.tags)
                    {
                        std::cout << tag << " ";
                    }
                    std::cout << "\n";
                }
                std::cout << "-----------------------------\n";
                std::cout << "Total de películas encontradas: " << peliculas.size() << "\n";
            }
        }
        else if (option == 3)
        {
            // Ver mi "Ver más tarde" - sección en blanco
            std::cout << "Sección 'Ver más tarde' en desarrollo.\n";
        }
        else if (option == 4)
        {
            // Ver mis "Me gusta" - sección en blanco
            std::cout << "Sección 'Me gusta' en desarrollo.\n";
        }
        else if (option == 5)
        {
            std::cout << "Testear servidor (Hello World):\n";
            std::string response = client.test_server();
            std::cout << "Respuesta del servidor: " << response << "\n";
        }
        else
        {
            std::cout << "Opción no válida. Por favor, intente de nuevo.\n";
            // Limpiar la entrada estándar en caso de que el usuario haya ingresado un valor no numérico
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "\n"; // Añadir una línea en blanco antes de mostrar el menú nuevamente
    }

    return 0;
}
