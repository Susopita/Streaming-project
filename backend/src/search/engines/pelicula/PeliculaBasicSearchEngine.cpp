#include <search/engines/pelicula/PeliculaBasicSearchEngine.hpp>

#include <core/pelicula/infrastructure/peliculaRepository.hpp>
#include <core/pelicula/domain/pelicula.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <optional>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

// Funciones auxiliares
string toLowerCase(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
              [](unsigned char c)
              { return tolower(c); });
    return lowerStr;
}

string removePunctuation(const string &str)
{
    string cleanStr;
    copy_if(str.begin(), str.end(), back_inserter(cleanStr),
            [](unsigned char c)
            { return !ispunct(c); });
    return cleanStr;
}

vector<string> splitIntoWords(const string &str, char delimiter = ' ')
{
    vector<string> words;
    stringstream ss(str);
    string word;
    while (getline(ss, word, delimiter))
    {
        if (!word.empty())
        {
            words.push_back(word);
        }
    }
    return words;
}

// Implementación de la función de búsqueda con pesos por campo
vector<Pelicula> PeliculaBasicSearchEngine::search(const PeliculaRepository &repository, const string &query)
{
    vector<Pelicula> peliculasFiltradas;

    // Si la consulta está vacía, retornar todas las películas
    if (query.empty())
    {
        return peliculasFiltradas;
    }

    // Normalizar y tokenizar la consulta
    string normalizedQuery = toLowerCase(query);
    normalizedQuery = removePunctuation(normalizedQuery);
    vector<string> queryWords = splitIntoWords(normalizedQuery, ' ');

    if (queryWords.empty())
    {
        return peliculasFiltradas;
    }

    // Definir pesos para cada campo
    const int TITLE_WEIGHT = 3;
    const int DESCRIPTION_WEIGHT = 1;
    const int TAGS_WEIGHT = 2;

    // Estructura para almacenar películas con sus puntuaciones
    struct PeliculaScore
    {
        Pelicula pelicula;
        int score;
    };

    vector<PeliculaScore> scoredPeliculas;

    // Iterar a través de todas las películas en el repositorio
    for (const auto &pelicula : repository.getAll())
    {
        int score = 0;

        // Procesar el título
        string title = toLowerCase(pelicula.getTitulo());
        title = removePunctuation(title);
        vector<string> titleWords = splitIntoWords(title, ' ');
        set<string> titleWordSet(titleWords.begin(), titleWords.end());

        // Procesar la descripción
        string description = toLowerCase(pelicula.getSinopsis());
        description = removePunctuation(description);
        vector<string> descriptionWords = splitIntoWords(description, ' ');
        set<string> descriptionWordSet(descriptionWords.begin(), descriptionWords.end());

        // Procesar las etiquetas
        set<string> tagsWordSet;
        for (const auto &tag : pelicula.getTags())
        {
            string normalizedTag = toLowerCase(tag);
            normalizedTag = removePunctuation(normalizedTag);
            vector<std::string> tagWords = splitIntoWords(normalizedTag, ' ');
            for (const auto &word : tagWords)
            {
                if (!word.empty())
                {
                    tagsWordSet.insert(word);
                }
            }
        }
        // Calcular la puntuación basada en las coincidencias en cada campo
        for (const auto &word : queryWords)
        {
            if (titleWordSet.find(word) != titleWordSet.end())
            {
                score += TITLE_WEIGHT;
            }
            if (descriptionWordSet.find(word) != descriptionWordSet.end())
            {
                score += DESCRIPTION_WEIGHT;
            }
            if (tagsWordSet.find(word) != tagsWordSet.end())
            {
                score += TAGS_WEIGHT;
            }
        }

        // Solo considerar películas con al menos una coincidencia
        if (score > 0)
        {
            scoredPeliculas.push_back(PeliculaScore{pelicula, score});
        }
    }

    // Ordenar las películas por puntuación descendente
    sort(scoredPeliculas.begin(), scoredPeliculas.end(),
         [](const PeliculaScore &a, const PeliculaScore &b)
         {
             return a.score > b.score;
         });

    // Añadir las películas ordenadas al vector de resultados
    for (const auto &ps : scoredPeliculas)
    {
        peliculasFiltradas.push_back(ps.pelicula);
    }

    return peliculasFiltradas;
}
