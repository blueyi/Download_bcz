/*
 * Download.cpp
 * Copyright (C) 2015  <@BLUEYI-PC>
 * batch download resource file from text file
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
bool geturl(const std::string &infile, std::vector< std::pair<std::string, std::string> > &words_url);

//use wget to download url of words_url to directory dir
bool down(const std::string dir, const std::vector< std::pair<std::string, std::string> > &words_url, std::vector< std::pair<std::string, std::string> > &failed_words);

void show_progress(int cur, int total)
{
    double rate = static_cast<double>(cur) / static_cast<double>(total);
    int num_equal = rate * total_bar;
    std::string progress(num_equal, '+');
    std::cout << progress << "=>" << cur << "/" << total << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "None input file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::vector< std::pair<std::string, std::string> > words_url, failed_words;
        int file_num_start = 1;
        std::string temp1 = argv[1];
        if (temp1 == "-f") {
            std::string http_temp = argv[2];
            if (http_temp.substr(0, 6) != "http://") {
                std::cout << "There must be an correct url following of \'-f\'" << std::endl;
                exit(EXIT_FAILURE);
            }
            fixed_url = http_temp;
            file_num_start = 3;
        }
        for (int i = file_num_start; i < argc; ++i) {
            if (!geturl(argv[i], words_url)) {
                std::cout << "get url failure from file: " << argv[i] << std::endl;
                continue;
            }
            std::string dir = argv[i];
            if (dir.find(".") != std::string::npos)
                dir = dir.substr(0, dir.find("."));
            std::string dir_command = "md " + dir;
            subname = dir.substr(0, dir.find("_"));
            if(system(dir_command.c_str()) != 0)
                std::cout << "Directory: " << dir << " created error!" << std::endl;
            std::cout << "***Downloading " << argv[i] << " ***" << std::endl;
            bool is_down_ok = down(dir, words_url, failed_words);
            if (is_down_ok)
                std::cout << "All of words download success and stored in \n" << "***" << dir << "***" << std::endl;
            else {
                std::cout << "The following words can't to download " << std::endl;
                std::ofstream outwords("Error_words.txt", std::ofstream::out | std::ofstream::app);
                for (const auto &fword : failed_words) {
                    std::cout << fword.first << ": " << fword.second << std::endl;
                    outwords << fword.first << "  " << fword.second << std::endl;
                }
                outwords.close();
            }
        }
    }
    return 0;
}

bool geturl(const std::string &infile, std::vector< std::pair<std::string, std::string> > &words_url)
{
    std::ifstream instream(infile.c_str());
    if (!instream) {
        std::cout << "File: " << infile << " open error!" << std::endl;
        return false;
    }
    else {
        std::string line;
        while (getline(instream, line)) {
            if (line.length() < line_length)
                continue;
            std::string word, sub_url;
            word = line.substr(0, line.find("/") - 1);
            sub_url = line.substr(line.find("/"));
            if (word.empty() || sub_url.empty())
                continue;
            sub_url = fixed_url + sub_url;
            words_url.push_back(std::make_pair(word, sub_url));
        }
    }
    instream.close();
    return true;
}


bool down(const std::string dir, const std::vector< std::pair<std::string, std::string> > &words_url, std::vector< std::pair<std::string, std::string> > &failed_words)
{
    bool is_all_good = true;
    int cur = 0;
    int total_words = words_url.size();
    for (const auto &word_url : words_url) {
        cur++;
        show_progress(cur, total_words);
        std::string down_command = "wget -c ";
        std::string tword, turl, suffix;
        tword = word_url.first;
        turl = word_url.second;
        suffix = turl.substr(turl.find_last_of("."));
        down_command = down_command + turl + " -O " + "\"./" + dir + "/" + tword + "_" + subname + suffix + "\"";
        if (system(down_command.c_str()) != 0) {
            failed_words.push_back(word_url);
            is_all_good = false;
        }
    }
    return is_all_good;
}

