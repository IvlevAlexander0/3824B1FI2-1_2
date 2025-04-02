#include <string>
#include<iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Date.h"
#pragma once

using std::string;
using std::ostream;
using std::sort;
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
	string composer;
	string singer;
	string album;
	Date date;
public:
	Song(string name_="", string author_="", string composer_ = "", string singer_="", string album_="", Date date_ = Date()) :
		name{ name_ }, author{ author_ }, composer{ composer_ }, singer{ singer_ }, 
		album{ album_ },
		date {date_} {
		if (composer == "") {
			composer = author;
		}
		if (singer == "") {
			singer = author;
		}
	}
	bool operator < (const Song& s2) const {
		if (name != s2.name) {
			return name < s2.name;
		}
		if (author != s2.author) {
			return author < s2.author;
		}
		if (composer != s2.composer) {
			return composer < s2.composer;
		}
		if (singer != s2.singer) {
			return singer < s2.singer;
		}
		if (album != s2.album) {
			return album < s2.album;
		}
		return date < s2.date;
	}
	bool operator == (const Song& s2) const {
		return name == s2.name && author == s2.author && s2.singer == singer && date == s2.date;
	}
	friend SongWriter;
	friend ostream& operator << (ostream& out, Song s);
};
ostream& operator << (ostream& out, Song s) {
	out << "name: " << s.name << "\tauthor: " << s.author <<"\tcomposer: " << s.composer << "\tsinger: " << s.singer <<"\talbum: " << s.album << "\tdate: " << s.date;
	return out;
}

class SongWriter {
	vector<Song> songs = vector<Song>();
public:
	SongWriter() {};
	SongWriter(size_t count, Song* songs_) {
		songs = vector<Song>();
		for (size_t i = 0; i < count; i++) {
			songs.push_back(songs_[i]);
		}
		sort(songs.begin(), songs.end());
	}


	bool binary_search(Song song) {
		int r = songs.size() - 1;
		int l = 0;
		int t = (l + r) / 2;
		while (l <= r) {
			if (songs[t] < song) {
				l = t + 1;
			}
			else if (song < songs[t]) {
				r = t - 1;
			}
			else {
				return true;
			}
			t = (l + r) / 2;
		}
		return songs[t] == song;
	}
	int lower_bound(Song song) {//возвращает наибольший индекс песни, которая стоит раньше	
		int r = songs.size()-1;
		int l = 0;
		int t = (l + r) / 2;
		while (l <= r) {
			if (songs[t] < song) {
				l =  t + 1;
			}
			else if(song < songs[t]) {
				r = t - 1;
			}
			else {
				return t;
			}
			t = (l + r) / 2;
		}
		return t;
	}
	void add_song(Song song) {
		if (songs.size() == 0) {
			songs.push_back(song);
			return;
		}
		songs.insert(songs.begin()+lower_bound(song), song);
	}
	void change_song(Song old_song, Song new_song) {

		if (binary_search(old_song)) {
			if (songs.size() == 1) {
				songs[0] = new_song;
				return;
			}
			songs.erase(songs.begin() + lower_bound(old_song));
			songs.insert(songs.begin() + lower_bound(new_song), new_song);
		}
	}
	Song find_song(string name, string singer) {
		size_t r = songs.size() - 1;
		size_t l = 0;
		size_t t = (l + r) / 2;
		while (l < r) {
			t = (l + r) / 2;
			if ((songs[t].name < name) || ((songs[t].name != name) && (songs[t].singer < singer))) {
				l = (l + r) / 2 + 1;
			}
			else if ((songs[t].name > name) || ((songs[t].name != name) && (songs[t].singer > singer))) {
				r = (l + r) / 2 - 1;
			}
			else {
				break;
			}
		}
		if (songs[t].name == name && songs[t].singer == singer) {
			return songs[t];
		}
		return Song("", "", "", "", "", Date());
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
		if (binary_search(song)) {
			if (songs.size() == 1) {
				songs.erase(songs.begin());
				return;
			}
			songs.erase(songs.begin() + lower_bound(song));
		}
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
				file << s.composer << endl;
				file << s.singer << endl;
				file << s.album << endl;
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
			string massive[6] = { "", "", "", "", "", ""};
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
						songs.push_back(Song(massive[0], massive[1], massive[2], massive[3], massive[4], Date(massive[5])));
						flag_song = false;
						massive[0] = "";
						massive[1] = "";
						massive[2] = "";
						massive[3] = "";
						massive[4] = "";
						massive[5] = "";
						i = 0;

					}
					else flag_songwriter = false;
					continue;
				}
				massive[i] = line;
				if(i < 5) i++;

			}
		}
		sort(songs.begin(), songs.end());
	}
	friend ostream& operator << (ostream& out, SongWriter sw);
};

ostream& operator << (ostream& out, SongWriter sw) {
	for (Song s : sw.songs) {
		out << s <<endl;
	}
	return out;
}