/*
 * Download.cpp
 * Copyright (C) 2015  <@BLUEYI-PC>
 * get url from multiple file and eliminate duplicate url, then store in Nodup_tv.txt
 * Distributed under terms of the MIT license.
 */

//#include "Download.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>

const std::string::size_type line_length = 5;
const int total_bar = 80;

std::string fixed_url = "http://baicizhan.qiniucdn.com";
std::string subname;

//read word and resource url from infile to vector
bool geturl(const std::string &infile, std::map<std::string, std::pair<std::string, std::string> > &words_url);

void show_progress(int cur, int total, std::string cur_file)
{
    double rate = static_cast<double>(cur) / static_cast<double>(total);
    int num_equal = rate * total_bar;
    std::cout << "***Downloading " << cur_file << "***" << std::endl;
    std::string progress(num_equal, '+');
    std::cout << "Total:[" << progress << "=>" << cur << "/" << total << "]" << std::endl;
}

int main(int argc, char **argv)
{
    std::map<std::string, std::pair<std::string, std::string> > words_url, failed_words;
    std::string total_tv = "Nodup_tv.txt";

    if (!geturl(total_tv, words_url)) {
        std::cout << "get url failure from file: " << total_tv << std::endl;
    }

    if (argc < 2) {
        std::cout << "None input file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        int file_num_start = 1;
        for (int i = file_num_start; i < argc; ++i) {
            if (!geturl(argv[i], words_url)) {
                std::cout << "get url failure from file: " << argv[i] << std::endl;
                continue;
            }
            std::ofstream outwords(total_tv.c_str(), std::ofstream::out | std::ofstream::app);
            for (const auto &fword : words_url) {
                outwords << fword.first << "\t" << fword.second.second << std::endl;
            }
            outwords.close();
        }
    }
    return 0;
}

bool geturl(const std::string &infile, std::map<std::string, std::pair<std::string, std::string> > &words_url)
{
    std::ifstream instream(infile.c_str());
    if (!instream) {
        std::cout << "File: " << infile << " open error!" << std::endl;
        return false;
    }
    else {
        std::string line, previous_url;
        while (getline(instream, line)) {
            if (line.length() < line_length)
                continue;
            std::string word, sentence, sub_url;
            word = line.substr(0, line.find("\t"));
            if (word.find("/") != std::string::npos) 
                word.replace(word.find("/"), 1, "_");
            if (line.find("\t") == line.find_last_of("\t"))
                sentence = "";
            else {
                if (line.find(".\t") == line.find_last_of("\t") - 1)
                    sentence = line.substr(line.find("\t") + 1, line.find_last_of("\t") - line.find("\t") - 1);
                else if (line.find(".") < line.find_last_of("\t"))
                    sentence = line.substr(line.find("\t") + 1, line.find(".") - line.find("\t") - 1);
                else
                    sentence = line.substr(line.find("\t") + 1, line.find_last_of("\t") - line.find("\t") - 1);
            }
            sub_url = line.substr(line.find_last_of("\t") + 1);
            //std::cout << "***word:" << word << "***sentence:" << sentence << "***sub_url:" << sub_url << std::endl;
            //std::cout << "***" << sentence << "***" << std::endl;
            if (sub_url == previous_url)
                continue;
            previous_url = sub_url;
            if (word.empty() || sub_url.empty())
                continue;
            sub_url = fixed_url + sub_url;
            //std::cout << "****sub_url: " << sub_url << std::endl;
            words_url.insert(std::make_pair(word, std::make_pair(sentence, sub_url)));
        }
    }
    instream.close();
    return true;
}

