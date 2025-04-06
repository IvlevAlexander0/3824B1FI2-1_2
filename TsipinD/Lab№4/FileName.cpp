#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Song {
public:
    string title;
    string poet;
    string composer;
    string performer;
    string album;

    struct Date {
        int day;
        int month;
        int year;
    } date;

    Song(const string& title_, const string& poet_, const string& composer_, const string& performer_, const string& album_, int day_, int month_, int year_)
        : title(title_), poet(poet_), composer(composer_), performer(performer_), album(album_) {
        date.day = day_;
        date.month = month_;
        date.year = year_;
    }

    bool operator<(const Song& other) const { // сортировка по названию
        return title < other.title;
    }
};

class Songbook {
private:
    vector<Song> songs;

    string getNextData(const string& str, size_t& pos) {
        size_t start = pos;
        pos = str.find("|", start);
        string Data = str.substr(start, pos - start);
        if (pos != string::npos) {
            pos = pos + 1;
        }
        return Data;
    }

    int findIndexByTitle(const string& title) const {
        int left = 0, right = songs.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (songs[mid].title == title) {
                return mid;
            }
            else if (songs[mid].title < title) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1;
    }

    void insertSong(const Song& song) {
        int left = 0;
        int right = songs.size() - 1;
        int insertPos = songs.size();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (songs[mid].title >= song.title) {
                insertPos = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        songs.insert(songs.begin() + insertPos, song);
    }

public:
    void addSong(const string title, const string poet, const string composer, const string performer, const string album, int day, int month, int year) {
        Song song(title, poet, composer, performer, album, day, month, year);
        insertSong(song);
    }

    void modifySong(int index, const string title, const string poet, const string composer, const string performer, const string album, int day, int month, int year) {
        if (index >= 0 && index < songs.size()) {
            songs.erase(songs.begin() + index);
            Song song(title, poet, composer, performer, album, day, month, year);
            insertSong(song);
        }
    }

    Song* findSong(const string& title, const string& performer) {
        int index = findIndexByTitle(title);
        if (index != -1 && songs[index].performer == performer) {
            return &songs[index];
        }
        return nullptr;
    }

    vector<Song> getSongsByPoet(const string& poet) {
        vector<Song> result;
        for (const Song& song : songs) {
            if (song.poet == poet) {
                result.push_back(song);
            }
        }
        return result;
    }

    vector<Song> getSongsByComposer(const string& composer) {
        vector<Song> result;
        for (const Song& song : songs) {
            if (song.composer == composer) {
                result.push_back(song);
            }
        }
        return result;
    }

    vector<Song> getSongsByPerformer(const string& performer) {
        vector<Song> result;
        for (const Song& song : songs) {
            if (song.performer == performer) {
                result.push_back(song);
            }
        }
        return result;
    }

    int getNumberOfSongs() const {
        return songs.size();
    }

    void deleteSong(int index) {
        if (index >= 0 && index < songs.size()) {
            songs.erase(songs.begin() + index);
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const Song& song : songs) {
                file << song.title << "|" << song.poet << "|" << song.composer << "|" << song.performer << "|" << song.album << "|"
                    << song.date.day << "|" << song.date.month << "|" << song.date.year << "\n";
            }
        }
        else {
            cout << "File opening error!" << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (line.empty()) continue;
                string title, poet, composer, performer, album;
                int day, month, year;
                size_t pos = 0;
                title = getNextData(line, pos);
                poet = getNextData(line, pos);
                composer = getNextData(line, pos);
                performer = getNextData(line, pos);
                album = getNextData(line, pos);
                day = stoi(getNextData(line, pos));
                month = stoi(getNextData(line, pos));
                year = stoi(getNextData(line, pos));
                insertSong(Song(title, poet, composer, performer, album, day, month, year));
            }
        }
        else {
            cout << "File opening error!" << endl;
        }
    }

    void printAllSongs() const {
        cout << "Total songs: " << songs.size() << "\n\n";
        for (size_t i = 0; i < songs.size(); ++i) {
            const Song& song = songs[i];
            cout << "---------------------" << '\n';
            cout << "Song #" << i + 1 << ":\n"
                << "Title: " << song.title << "\n"
                << "Poet: " << song.poet << "\n"
                << "Composer: " << song.composer << "\n"
                << "Performer: " << song.performer << "\n"
                << "Album: " << song.album << "\n"
                << "Date: " << song.date.day << "."
                << song.date.month << "."
                << song.date.year << endl;
        }
    }
};

int main() {
    Songbook songbook;
    songbook.addSong("Song1_p1", "Poet1", "Composer1", "Performer1", "Album1", 1, 1, 2024);
    songbook.addSong("Song2_p1", "Poet1", "Composer1", "Performer1", "Album2", 2, 1, 2024);
    songbook.addSong("Song3_p1", "Poet1", "Composer1", "Performer1", "Album3", 3, 1, 2024);
    songbook.addSong("Song2", "Poet2", "Composer2", "Performer2", "Album2", 2, 2, 2025);
    songbook.modifySong(0, "Song1_Modded", "Poet1", "Composer1", "Performer1", "Album1", 1, 1, 2020);

    Song* song = songbook.findSong("Song1_Modded", "Performer1");
    if (song) {
        cout << "song " << (*song).title << " was found." << endl;
    }

    vector<Song> poetSongs = songbook.getSongsByPoet("Poet1");
    for (const Song& s : poetSongs) {
        cout << "Poet1's song: " << s.title << endl;
    }

    songbook.printAllSongs();

    cout << endl << "-------File's data added.-------" << endl << endl;
    songbook.loadFromFile("songbook.txt");
    songbook.printAllSongs();

    cout << endl;
    vector<Song> BeethovenSongs = songbook.getSongsByComposer("Beethoven");
    for (const Song& s : BeethovenSongs) {
        cout << "Beethoven's song: " << s.title << endl;
    }

    return 0;
}
