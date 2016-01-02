/*
 * Copy_words.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>

const int total_bar = 65;
int get_words_list(const std::string &infile, std::vector<std::string> &words_list);

//show download progress bar
void show_progress(int cur, int total, std::string cur_file)
{
    double rate = static_cast<double>(cur) / static_cast<double>(total);
    int num_equal = rate * total_bar;
    std::cout << "***copying " << cur_file << "***" << std::endl << std::endl;
    std::string progress(num_equal, '+');
    std::cout << "Total:[" << progress << "=>" << cur << "/" << total << "]" << std::endl << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "You must input word list text file name and resource file directory!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string source_dir = argv[2];
    std::string file_name = argv[1];
    std::string dir_command = "md ";
    std::string dest_dir;
    if (file_name.find(".") != std::string::npos)
        dest_dir = file_name.substr(0, file_name.find("."));
    else
        dest_dir = file_name;
    dir_command = dir_command + "\"" + dest_dir + "\"";

    if (system(dir_command.c_str()) != 0) {
        std::cout << "Created directory: " << dest_dir << " failed!" << std::endl;
    }

    std::string copy_command = "copy ";
    std::vector<std::string> words_list, failed_list;
    int total = get_words_list(file_name, words_list);
    int failed_num = 0;
    if (total == 0) {
        std::cout << "None words in the file" << file_name << std::endl;
        exit(EXIT_FAILURE);
    }
    int cur = 0;
    for (const auto &word : words_list) {
        cur++;
        copy_command = copy_command + "\"" + source_dir + "\\" + "*" + word + "*" + "\" " + "\"" + dest_dir + "\"";
       // if (++cur < total)
            system("cls");
        show_progress(cur, total, file_name);
        if (system(copy_command.c_str()) != 0) {
            failed_list.push_back(word);
            failed_num++;
        }
        copy_command = "copy ";
    }
    if (failed_num == 0) {
        std::cout << "All of words copied success! and stored in **" + dest_dir << "** directory" << std::endl;
    }
    else {
        std::string failed_name = "Failed_copy_" + dest_dir + ".txt";
        std::ofstream ofs(failed_name.c_str(), std::fstream::out | std::fstream::app);
        std::cout << std::endl << "***The following words copied failed!***" << std::endl;
        for (const auto &word : failed_list) {
            std::cout << word + " ";
            ofs << word << std::endl;
        }
        ofs.close();
        std::cout << std::endl;
    }
    return 0;
}

int get_words_list(const std::string &infile, std::vector<std::string> &words_list)
{
    int num = 0;
    std::ifstream inf(infile.c_str());
    if (!inf) {
        std::cout << "File: "  << infile << " open error!" << std::endl;
        num = 0;
    }
    std::string line, word;
    std::istringstream ins;
    while (getline(inf, line)) {
        ins.str(line);
        ins >> word;
        words_list.push_back(word);
        num++;
        ins.sync();
        ins.clear();
    }
    inf.close();
    return num;
}




