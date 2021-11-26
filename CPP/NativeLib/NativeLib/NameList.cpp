#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
static vector<string> family_name_list = {};
static vector<string> man_name_list = {};
static vector<string> woman_name_list = {};
const string file_path = "data/name_ansi.txt";

static void load_name_data2() {
	string f_name_data = "�̽��ϰ��� �긮Ÿ ��������� ����ũ���� ���� ��� ���������� �����Ϻ��� �����Ϲ߶� ��� �󵵰� ���� ��帮�� ��� ��� �� �� ���� �� �� �� ���� ���� ī���� ����Ŀ ���Ϸ� �з� �Ǽ� �ٱ׳� ���̽� ��ī ���̾� ��ī ��ī ���� ���� ����ī ��Ƽ�� �ٳ׾� ��ī ����ī ����ī ���϶� �θ�ī �θ��� �����ī ����Ǿ� ���ī ���� ��ϳ� ���ī ���� ���ī ���γ� ����ī ��ī ������ �ƹ�ī �ƺ��� ������ �ƺ�ī �̶�� ��ī ���̻� �ֻ� �ֳ� ü��� üī ī���� ī�λ� ī�γ� ī��� ī�̳� īí ĭī�� ����ī ������ �ڿ��� ����� �ݵ�� ��Ű�� ��ī ��� ����� ĳ�� Ű��� Ű�ֻ� ų��� ų��ī ŸŸ�� ����Ÿ �丶ī �丶�� ���� ���� ���ī Ʃ��ī �ĺ�ī �ĺ�� �Ĺ� ����ī �Ǹ��� �Ǹ��� �ǿ����� �ǿ���ī ����� ����ī �丮�� �丮ī �Ϲ��� �Ϻ�ī ��ī �쵥�� ���� ���� ��ī ��ġ�� �׸����� ����� ���̳� ���ľ� �پ�ī ����ī ���ʻ� ��� ��Ƽī ��Ƽ�� ���̾ƻ� ���϶�� �纣�� �ε�� ��ī ������ ��Ǫ�� �ޱ�ī �ޱ�� ���ϻ� ����ī ���� �̾ƻ�";
	string m_name_data = "���� ���� ���� ���� �� �ֵ� �׸��� ���� ���� ���� ���� ���� ���̾� ���� ���� ���� ���� ���� ���̿� ������ ���� ������ ���� ���� ��� �� ���̵� ���̾� ����Ʈ ���� ���̳ε� �ι� �纥 �ε� �κ� �κ� ��ī ���� ��� ��ƽ� ���̳� ���� ���� ����Ʈ ���� ��Ǫ �� ��ũ ���� ���� �ָ� �޷� �޷� �� ��� �� ���� ���� ���� ��Ʈ �ٳ� �ٷ� �ٺ� ���� ���� ���� �� �θ� ����� ��� ��� ��콺 ���� ���� ��ũ ���� ���� ���� ���� ���̺� ���� �ֶ� �ƺ� ���� ������ ���� ��ī ���� ���õ� �̶��� �̺� ��ũ ���� �� ���̽� �ֽ� �� ü�� üũ ��� ī�� ī�� ī�� ī�� ī�� ī�� īġ ĭĭ ������ ���� ���� ���� �ڿ� ���� �ݵ� ��Ű �� ���� ĳ�� Ű�� Ű�� ų�� Ÿ���� ŸŸ ����Ʈ �丶 ��� ��� Ʃ�� �ĺ� ���� ���� �Ǹ� �ǿ� ���� ���� �丮 �Ϲ� �Ϻ� �Թٱ� ��ũ �쵧 ��� ���� � � ���� ȭ��Ʈ ��ũ ��Ǫ ��ġ";
	string w_name_data = "�׸��� ���� ���� ���� ���� ���̾� ���� ���� ���̿� ������ ���� ���� ��� ��Ÿ ���̾� ���϶� �纥 �ε� �κ� �κ� ����� ��ī ��� ��� ���� ��Ǫ ���� ���� ���� ���� ��ī ��ũ ���� �ָ� �ޱ� �޷� �޷� �޵�� ��� ���� ����� ���� ���� ���Ƴ� ���� ���� ��ġ ��Ʈ ��Ƽ�� �ٳ� �ٳ� �ٳ� �ٴϿ� �ٴ� �ٴҸ� �ٷ� �ٹٷξ� �ٹݳ� �ٺ� ���̵� �θ� ��� �� ��� ���� ���� ���ī ���� ��� ���̶� ��Ű�� ���� ���� ���� ��ũ ��Ǫ ���� ���� ���̺� ���� �ֶ� ���䳪 �ø��� ���� ���� ��ī �̶��� �̺� �̾� ���� ���̹� �ֽ� �� ü�̻� üŰ�� ī�� ī���� ī�� ī�̻� ī�� īƼ�� īǪ�� ���� ���� ��Ű �ڳ� �ڸ� ���ڳ� �ݶ� ���� ĳ�� Ű�� Ű�� ŸŸ ����Ʈ �丶 �ĺ� ���� ���� ������ ���� ���� Ǫ�� ������ �÷ζ� �÷θ� �Ǹ� �ǿ� ���� �ʸ��� �ϴ��� ��ũ ȭ��Ʈ ��ũ ��Ǫ ��ġ";

	string f_name_eng = "estern abc das banana cake";

	string word_buffer;

	std::stringstream family_line(f_name_eng);

	while (getline(family_line, word_buffer, ' ')) {
		family_name_list.push_back(word_buffer);
	}

	std::stringstream m_name_line(f_name_eng);
	while (getline(m_name_line, word_buffer, ' ')) {
		man_name_list.push_back(word_buffer);
	}

	std::stringstream f_name_line(f_name_eng);
	while (getline(f_name_line, word_buffer, ' ')) {
		woman_name_list.push_back(word_buffer);
	}

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