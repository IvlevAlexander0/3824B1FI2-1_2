#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class Film {
public:
    string title;
    string director;
    string screenwriter;
    string composer;
    int day;
    int month;
    int year;
    long long earnings;

    Film(string t, string d, string s, string c, int dy, int mn, int yr, long long e)
        : title(t), director(d), screenwriter(s), composer(c), day(dy), month(mn), year(yr), earnings(e) {}

    //Для упорядочивания фильмов
    bool operator<(const Film& other) const {
        if (title == other.title) return year < other.year;
        return title < other.title;
    }
    //Для поиска в массиве
    bool operator==(const Film& other) const {
        return title == other.title && year == other.year;
    }
};

class FilmLibrary {
private:
    vector<Film> films;

    //Для упорядочивания
    void insertFilmSorted(const Film& film) {
        auto it = lower_bound(films.begin(), films.end(), film);
        films.insert(it, film);
    }
    //Далее lower bound используется для упрощения поиска в упорядоченном массиве

public:
    //1 -Добавить фильм
    void addFilm(const Film& film) {
        insertFilmSorted(film);
    }

    //2 - Изменить фильм
    void updateFilm(const string& title, int year, const Film& newFilm) {
        auto it = lower_bound(films.begin(), films.end(), Film(title, "", "", "", 0, 0, year, 0));
        if (it != films.end() && *it == Film(title, "", "", "", 0, 0, year, 0)) {
            *it = newFilm;
            insertFilmSorted(newFilm); // Сортировка по новой, если она нужна
        }
    }

    //3 - Поиск фильма
    Film* findFilm(const string& title, int year) {
        auto it = lower_bound(films.begin(), films.end(), Film(title, "", "", "", 0, 0, year, 0));
        if (it != films.end() && *it == Film(title, "", "", "", 0, 0, year, 0)) {
            return &(*it);
        }
        return nullptr;
    }

    //4 - фильмы по режиссеру 
    vector<Film> getFilmsByDirector(const string& director) {
        vector<Film> result;
        for (const auto& film : films) {
            if (film.director == director) {
                result.push_back(film);
            }
        }
        return result;
    }

    //5- Фильмы по году
    vector<Film> getFilmsByYear(int year) {
        vector<Film> result;
        for (const auto& film : films) {
            if (film.year == year) {
                result.push_back(film);
            }
        }
        return result;
    }

    //6- Максимальные сборы
    vector<Film> getTopEarnings(int count) {
        vector<Film> sortedFilms = films;
        sort(sortedFilms.begin(), sortedFilms.end(), [](const Film& a, const Film& b) {
            return a.earnings > b.earnings;
            });
        if (count > sortedFilms.size()) count = sortedFilms.size();
        return vector<Film>(sortedFilms.begin(), sortedFilms.begin() + count);
    }

    //7 - Максимальные сборы по году
    vector<Film> getTopEarningsByYear(int year, int count) {
        vector<Film> filteredFilms;
        for (const auto& film : films) {
            if (film.year == year) {
                filteredFilms.push_back(film);
            }
        }
        sort(filteredFilms.begin(), filteredFilms.end(), [](const Film& a, const Film& b) {
            return a.earnings > b.earnings;
            });
        if (count > filteredFilms.size()) count = filteredFilms.size();
        return vector<Film>(filteredFilms.begin(), filteredFilms.begin() + count);
    }


    //8 - Число фильмов в фильмотеке
    int getFilmCount() {
        return films.size();
    }

    //9 - Удаление фильма
    void deleteFilm(const string& title, int year) {
        auto it = lower_bound(films.begin(), films.end(), Film(title, "", "", "", 0, 0, year, 0));
        if (it != films.end() && *it == Film(title, "", "", "", 0, 0, year, 0)) {
            films.erase(it);
        }
    }

    //10 - Добавить в файл
    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& film : films) {
            file << film.title << "," << film.director << "," << film.screenwriter << ","
                << film.composer << "," << film.day << "," << film.month << "," << film.year << ","
                << film.earnings << "\n";
        }
    }

    //11 - Извлечь из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, director, screenwriter, composer;
            int day, month, year;
            long long earnings;
            getline(ss, title, ',');
            getline(ss, director, ',');
            getline(ss, screenwriter, ',');
            getline(ss, composer, ',');
            ss >> day;
            ss.ignore();
            ss >> month;
            ss.ignore();
            ss >> year;
            ss.ignore();
            ss >> earnings;
            addFilm(Film(title, director, screenwriter, composer, day, month, year, earnings));
        }
        file.close();
    }
};
int main() {
    FilmLibrary library;
    FilmLibrary library1; // Для загрузки из файла

    library.addFilm(Film("The Lord of the Rings: The Fellowship of the Ring", "Peter Jackson", "Peter Jackson", "Howard Shore", 19, 12, 2003, 871530324));
    library.addFilm(Film("Oppenheimer", "Christopher Nolan", "Christopher Nolan", "Ludwig Göransson", 12, 07, 2023, 975673120));
    library.addFilm(Film("Menu", "Adam McKay", "Set Raisse", "Colin Stetson", 3, 01, 2023, 76245120));

    library.saveToFile("films.txt");
    library1.loadFromFile("films.txt");

    //Был выпущен в 2001
    const Film K("The Lord of the Rings: The Fellowship of the Ring", "Peter Jackson", "Peter Jackson", "Howard Shore", 19, 12, 2001, 871530324);
    library.updateFilm("The Lord of the Rings: The Fellowship of the Ring", 2003, K);


    library1.addFilm(Film("Inglourious Basterds", "Quentin Tarantino", "Quentin Tarantino", "Ennio Morricone", 19, 8, 2009, 321455689));

    cout << "Film count first library: " << library.getFilmCount() << endl;
    cout << "Film count second library: " << library1.getFilmCount() << endl;

    Film* film = library.findFilm("Oppenheimer", 2023);
    if (film) {
        cout << "Found film: " << film->title << endl;
    }
    else {
        cout << "Film not found" << endl;
    }

    Film* film1 = library.findFilm("Inglourious Basterds", 2009);
    if (film1) {
        cout << "Found film: " << film1->title << endl;
    }
    else {
        cout << "Film not found" << endl;
    }

    Film* film2 = library1.findFilm("Inglourious Basterds", 2009);
    if (film2) {
        cout << "Found film: " << film2->title << endl;
    }
    else {
        cout << "Film not found" << endl;
    }

    vector<Film> ByYear = library.getFilmsByYear(2023);
    cout << "Films of 2023 are:" << endl;
    for (const auto& l : ByYear) {
        cout << l.title << endl;
    }

    vector<Film> topEarnings = library1.getTopEarnings(2);
    cout << "Top earnings:" << endl;
    for (const auto& f : topEarnings) {
        cout << f.title << " - " << f.earnings << endl;
    }


    Film* film_ = library1.findFilm("The Lord of the Rings: The Fellowship of the Ring", 2003);
    if (film_) {
        cout << "Found film: " << film_->title << endl;
    }
    else {
        cout << "Film not found" << endl;
    }

    library.deleteFilm("The Lord of the Rings: The Fellowship of the Ring", 2001);
    library1.deleteFilm("Inglourious Basterds", 2009);

    //Не удаляется, поскольку в файле(и в library1 соответственно) записан с другим годом выпуска:
    library1.deleteFilm("The Lord of the Rings: The Fellowship of the Ring", 2001);
    cout << "Film count after deletion: " << library.getFilmCount() << endl;
    cout << "Film count after deletion: " << library1.getFilmCount() << endl;

    return 0;
}
