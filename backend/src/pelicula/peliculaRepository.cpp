#include <pelicula/infrastructure/peliculaRepository.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

// Función para procesar una línea de CSV
vector<string> parseCSVLine(const string &line, char delimiter = ',', char quote = '"')
{
    vector<string> fields;
    stringstream ss(line);
    string field;
    bool insideQuote = false;
    string currentField;

    for (char c : line)
    {
        if (c == quote)
        {
            // Si estamos dentro de las comillas, cambiamos el estado
            insideQuote = !insideQuote; // Alterna entre dentro y fuera de comillas
        }
        else if (c == '\n' or !insideQuote)
        {
            fields.push_back(currentField);
            currentField.clear();
        }
        else if (c == delimiter && !insideQuote)
        {
            // Si encontramos un delimitador fuera de las comillas, agregamos el campo
            fields.push_back(currentField);
            currentField.clear();
        }
        else
        {
            currentField.push_back(c);
        }
    }
    // Agregar el último campo procesado
    if (!currentField.empty())
    {
        fields.push_back(currentField);
    }

    return fields;
}

// Función para leer un archivo CSV con saltos de línea dentro de los campos
// Para abrir archivos .csv
void PeliculaRepository::loadData(const string &dataRoute)
{
    ifstream file(dataRoute);
    string line;
    string fullContent = "";
    string headers = "";

    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    getline(file, headers);

    // Leemos el archivo completo concatenando las líneas
    while (getline(file, line))
    {
        // Si no estamos dentro de un campo de texto (dentro de comillas)
        if (line.back() == '"' && count(line.begin(), line.end(), '"') % 2 == 0)
        {
            fullContent += line + "\n";
        }
        else
        {
            // Si hay saltos de línea dentro de un campo (sin comillas cerradas), las concatenamos
            fullContent += line;
        }
    }

    file.close();

    // Ahora procesamos el contenido concatenado
    stringstream contentStream(fullContent);

    vector<string> fields;

    fields = parseCSVLine(headers);
    // Imprimir los encabezados para verificar
    cout << "Campos (Encabezados):" << endl;
    for (const auto &field : fields)
    {
        cout << "- " << field << endl;
    }
    cout << "-------------------------" << endl;

    while (getline(contentStream, line))
    {
        // Procesar solo si la línea no está vacía
        if (!line.empty())
        {
            fields = parseCSVLine(line);
            // Si ya hemos procesado los encabezados, seguimos mapeando los valores
            /*
            cout << "Campos de los datos:" << endl;
            for (const auto &field : fields)
            {
                cout << "Campo: " << field << endl;
            }*/
            models[fields[0]] = Pelicula(fields[0], fields[1], fields[2], parseCSVLine(fields[3]));
        }
    }
}