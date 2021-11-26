#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <String.hpp>
#include <File.hpp>
#include "Common.h"

using namespace std;
static vector<string> family_name_list = {};
static vector<string> man_name_list = {};
static vector<string> woman_name_list = {};
const string file_path = "data/name_ansi.txt";
const String file_path2 = "res://data/name_ansi.txt";

static void load_name_data_godot() { 
	Ref<File> file = File::_new();
	String line_buffer;

	file->open(file_path2, File::READ);
	line_buffer = file->get_line();
	Godot::print(line_buffer);

	file->close();
}

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
	/*
	for (auto name : family_name_list) {
		cout<<name<<" ";
	}
	printf("\n\n");

	for (auto name : man_name_list) {
		cout<<name<<" ";
	}
	printf("\n\n");

	for (auto name : woman_name_list) {
		cout<<name<<" ";
	}
	printf("\n\n");
	*/
}