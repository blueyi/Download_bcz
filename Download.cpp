/*
 * Download.cpp
 * Copyright (C) 2015  <@BLUEYI-PC>
 *
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

const std::string fixed_url = "http://baicizhan.qiniucdn.com";
std::string subname;
//read word and resource url from infile to map
bool geturl(const std::string &infile, std::map<std::string, std::string> &words_url);
//use wget to download url of words_url to directory dir
bool down(const std::string dir, const std::map<std::string, std::string> &words_url, std::map<std::string, std::string> &failed_words);

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "None input file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::map<std::string, std::string> words_url, failed_words;
        for (int i = 1; i < argc; ++i) {
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
                    outwords << fword.first << fword.second << std::endl;
                }
                outwords.close();
            }
        }
    }
    //system("wget http://baicizhan.qiniucdn.com/word_tv/news_play_video_1937.mp4 -O test.mp4");
    return 0;
}

bool geturl(const std::string &infile, std::map<std::string, std::string> &words_url)
{
    std::ifstream instream(infile.c_str());
    if (!instream) {
        std::cout << "File: " << infile << " open error!" << std::endl;
        return false;
    }
    else {
        std::string line;
        while (getline(instream, line)) {
            std::string word, sub_url;
            std::istringstream isstream(line);
            isstream >> word >> sub_url;
            if (word.empty() || sub_url.empty())
                continue;
            sub_url = fixed_url + sub_url;
            words_url.insert(std::make_pair(word, sub_url));
        }
    }
    instream.close();
    return true;
}


bool down(const std::string dir, const std::map<std::string, std::string> &words_url, std::map<std::string, std::string> &failed_words)
{
    bool is_all_good = true;
    for (const auto &word_url : words_url) {
        std::string down_command = "wget -c ";
        std::string tword, turl, suffix;
        tword = word_url.first;
        turl = word_url.second;
        suffix = turl.substr(turl.find_last_of("."));
        down_command = down_command + turl + " -O " + "./" + dir + "/" + tword + "_" + subname + suffix;
        if (system(down_command.c_str()) != 0) {
            failed_words.insert(word_url);
            is_all_good = false;
        }
    }
    return is_all_good;
}

