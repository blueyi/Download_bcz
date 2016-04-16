/*
 * words_list.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>

//接受两个参数，第一个参数为总单词表，第二个参数为单词id表
int main(int argc, char **argv)
{
    std::map<unsigned, std::string> words_list_all;
    std::vector<unsigned> words_list_id;
    std::vector<std::string> words_list_word;
    std::string word_list_file = argv[1];
    std::string word_id_file = argv[2];
    std::ifstream ifs_a(word_list_file);
    std::ifstream ifs_i(word_id_file);
    std::string ofname = word_id_file.substr(0, word_id_file.find("id")) + "word";
    std::ofstream ofs(ofname + ".txt");
    if (!ifs_a)
        throw std::runtime_error("input words_list_all file error");
    if (!ifs_i)
        throw std::runtime_error("input word_id_file file error");
    if (!ofs)
        throw std::runtime_error("output file error");
    std::string str;
    while (getline(ifs_a, str)) {
        while (str.empty()) {
            getline(ifs_a, str);
        }
        std::istringstream istr(str);
        unsigned id;
        std::string word;
        istr >> id >> word;
        words_list_all.emplace(id, word);
    }
    unsigned id;
    while (ifs_i >> id) {
        words_list_id.push_back(id);
    }
    for (auto i : words_list_id) {
        std::string words = words_list_all[i];
        ofs << words << std::endl;
    }
    ifs_a.close();
    ifs_i.close();
    ofs.close();

    return 0;
}


