#pragma once
#pragma execution_character_set("utf-8")
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
static vector<string> family_name_list = {};
static vector<string> man_name_list = {};
static vector<string> woman_name_list = {};
const string file_path = "data/name.txt";

static void load_name_data() {
	ifstream f(file_path);
	string line_buffer;
	string word_buffer;

	if (f.fail()) {
		cerr << "[NameList]File not found: " << file_path << endl;
		exit(100);
	}

	getline(f, line_buffer);

	std::stringstream family_line(line_buffer);

	while (getline(family_line, word_buffer, ' ')) {
		family_name_list.push_back(word_buffer);
	}

	getline(f, line_buffer);

	std::stringstream m_name_line(line_buffer);
	while (getline(m_name_line, word_buffer, ' ')) {
		man_name_list.push_back(word_buffer);
	}

	getline(f, line_buffer);

	std::stringstream f_name_line(line_buffer);
	while (getline(f_name_line, word_buffer, ' ')) {
		woman_name_list.push_back(word_buffer);
	}

	f.close();
}