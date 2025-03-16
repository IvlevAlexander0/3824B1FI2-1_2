#include <string>
#include<iostream>
#include <fstream>
#include <set>
#include <vector>
#include "Date.h"
#pragma once

using std::string;
using std::ostream;
using std::set;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::endl;

class SongWriter;
class Song;
ostream& operator << (ostream& out, Song sw);

class Song {
	string name;
	string author;
	string singer;
	Date date;
public:
	Song(string name_="", string author_="", string singer_="", Date date_=Date()) :
		name{name_}, author{author_}, singer{singer_}, date{date_} {}
	 bool operator < (const Song& s2) const {
		if (name != s2.name) {
			return name < s2.name;
		}
		if (author != s2.author) {
			return author < s2.author;
		}
		if (singer != s2.singer) {
			return singer < s2.singer;
		}
		return date < s2.date;
	}
	friend SongWriter;
	friend ostream& operator << (ostream& out, Song s);
};
ostream& operator << (ostream& out, Song s) {
	out << "name: " << s.name << "\tauthor: " << s.author << "\tsinger: " << s.singer << "\tdate: " << s.date;
	return out;
}
class SongWriter {
	set<Song> songs = set<Song>();
public:
	SongWriter() {};
	SongWriter(size_t count, Song* songs_) {
		songs = set<Song>();
		for (size_t i = 0; i < count; i++) {
			songs.insert(songs_[i]);
		}
	}
	void add_song(Song song) {
		songs.insert(song);
	}
	void change_song(Song old_song, Song new_song) {
		songs.erase(old_song);
		songs.insert(new_song);
	}
	Song find_song(string name, string singer) {
		for (Song s : songs) {
			if (s.name == name && s.singer == singer) {
				return s;
			}
		}
		return Song();
	}
	vector<Song> get_by_author(string author) {
		vector<Song> result = vector<Song>();
		for (Song s : songs) {
			if(s.author == author) result.push_back(s);
		}
		return result;
	}
	vector<Song> get_by_singer(string singer) {
		vector<Song> result = vector<Song>();
		for (Song s : songs) {
			if (s.singer == singer) {
				result.push_back(s);
			}
		}
		return result;
	}
	size_t get_size() {
		return songs.size();
	}
	void delete_song(Song song) {
		songs.erase(song);
	}
	void save_to_file(string path) {
		ofstream file;
		file.open(path);
		if (file.is_open()) {
			file << '[' << endl;
			for (Song s : songs) {
				file << '[' << endl;
				file << s.name << endl;
				file << s.author << endl;
				file << s.singer << endl;
				file << s.date.to_file() << endl;
				file << ']' << endl;
			}
			file << ']' << endl;
		}
		file.close();

	}
	SongWriter(string path) {
		ifstream file;
		file.open(path);
		if (file.is_open()) {
			bool flag_songwriter = false, flag_song=false;
			string line;
			string massive[4] = { "", "", "", "" };
			size_t i = 0;
			while (std::getline(file, line)) {
				size_t j = 0;
				while ((line[j] == '\t' || line[j] == ' ') && j < line.size())j++;
				if (j == line.size()) continue;
				if ('[' == line[j] && j == line.size() - 1) {
					if (flag_songwriter)flag_song = true; else flag_songwriter = true;
					continue;
				}
				if (']' == line[j] && j == line.size() - 1) {
					if (flag_song) { 
						songs.insert(Song(massive[0], massive[1], massive[2], Date(massive[3])));
						flag_song = false;
						massive[0] = "";
						massive[1] = "";
						massive[2] = "";
						massive[3] = "";
						i = 0;

					}
					else flag_songwriter = false;
					continue;
				}
				massive[i] = line;
				if(i < 3) i++;

			}
		}
	}
	friend ostream& operator << (ostream& out, SongWriter sw);
};

ostream& operator << (ostream& out, SongWriter sw) {
	for (Song s : sw.songs) {
		out << s <<endl;
	}
	return out;
}