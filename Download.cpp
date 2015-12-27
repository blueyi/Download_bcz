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

const std::string fixed_url = "http://baicizhan.qiniucdn.com";

bool geturl(const std::string infile, std::vector< std::map<std::string, std::string> > &words_url);
void down(const std::string &dir, const std::vector< std::map<std::string, std::string> > &words_url);

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "None input file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::vector< std::map<std::string, std::string> > words_url;
        for (int i = 1; i < argc; ++i) {
            geturl(argv[i], words_url);
            std::string dir = argv[i];
            if (dir.find(".") != std::npos)
                dir = dir.substr(0, dir.find("."));
            //std::cout << "dir = " << dir << std::endl;
        }
    }
    //system("wget http://baicizhan.qiniucdn.com/word_tv/news_play_video_1937.mp4 -O test.mp4");
    return 0;
}

bool geturl(const std::string &infile, const std::vector< std::map<std::string, std::string> > &words_url)
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
            std::map

        }
    }
    return true;
}


void down(std::vector< std::map<std::string, std::string> > &words_url)
{
}

