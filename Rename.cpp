/*
 * Download.cpp
 * Copyright (C) 2015  <@BLUEYI-PC>
 * rename downloaded file to original file name
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
const std::vector<char> exclude_char{'*', '\?', '\"', '\\', '/', '|', ':', '<', '>'};
std::string fixed_url = "http://baicizhan.qiniucdn.com";

int rfind_offset = 6;
bool is_rename_ok = false;
const std::string subname = "tv";

//read word and resource url from infile to vector
bool geturl(const std::string &infile, std::multimap<std::string, std::pair<std::string, std::string> > &words_url);

bool rename(const std::multimap<std::string, std::pair<std::string, std::string> > &words_url, std::multimap<std::string, std::pair<std::string, std::string> > &failed_words, std::multimap<std::string, std::pair<std::string, std::string> > &keep_words);

//replace some character belongs to exclude_char
std::string& replace_ex(std::string &str, const std::vector<char> &exclude = exclude_char)
{
    for (const auto &ex : exclude) {
        while (str.find(ex) != std::string::npos) {
            str.replace(str.find(ex), 1, "_");
        }
    }
    return str;
}


int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "None input file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::multimap<std::string, std::pair<std::string, std::string> > words_url, failed_words, keeped_words;
        int file_num_start = 1;
        int file_num_end = argc;
        for (int i = file_num_start; i < file_num_end; ++i) {
            words_url.clear();
            if (!geturl(argv[i], words_url)) {
                std::cout << "get url failure from file: " << argv[i] << std::endl;
                continue;
            }
            
            //output the list of failed download
            bool is_rename_ok = rename(words_url, failed_words, keeped_words);
            if (is_rename_ok)
              std::cout << "All of words rename success" << std::endl; 
            else {
                std::cout << std::endl;
                std::cout << "***The following words rename failed!***" << std::endl;
                std::string error_fname = "Error_rename.txt";
                std::ofstream outwords(error_fname.c_str(), std::ofstream::out | std::ofstream::app);
                for (const auto &fword : failed_words) {
                    if (fword.second.first.empty()) {
                        std::cout << fword.first << ": " << fword.second.second << std::endl;
                        outwords << fword.first << "\t" << fword.second.second << std::endl;
                    }
                    else {
                        std::cout << fword.first << ": " << fword.second.first << " " << fword.second.second << std::endl;
                        outwords << fword.first << "\t" << fword.second.first << "\t" << fword.second.second << std::endl;
                    }
                }
                outwords.close();
            }

            std::string keep_fname = "keeped_name.txt";
            std::ofstream outwords(keep_fname.c_str(), std::ofstream::out | std::ofstream::app);
            std::cout << std::endl;
            std::cout << "***The following words name keeped!***" << std::endl;
            for (const auto &fword : keeped_words) {
                if (fword.second.first.empty()) {
                    std::cout << fword.first << ": " << fword.second.second << std::endl;
                    outwords << fword.first << "\t" << fword.second.second << std::endl;
                }
                else {
                    std::cout << fword.first << ": " << fword.second.first << " " << fword.second.second << std::endl;
                    outwords << fword.first << "\t" << fword.second.first << "\t" << fword.second.second << std::endl;
                }
            }
            outwords.close();
        }
    }
    return 0;
}

bool geturl(const std::string &infile, std::multimap<std::string, std::pair<std::string, std::string> > &words_url)
{
    std::ifstream instream(infile.c_str());
    if (!instream) {
        std::cout << "File: " << infile << " open error!" << std::endl;
        return false;
    }
    else {
        std::string line, previous_url;
        while (getline(instream, line)) {
            if (line.find_first_not_of(" ") != std::string::npos)
              line = line.substr(line.find_first_not_of(" "));
            if (line.length() < line_length || line.find("/") == std::string::npos)
              continue;
            std::string word, sentence, sub_url;

            //ascertain sentence and 
            if (line.find("http://") != std::string::npos)
              rfind_offset = line.size() - line.find("http://");
            else
              rfind_offset = 6;
            if (line.find("\t") == line.rfind("\t"))
              sentence = "";
            else {
                if (line.find(".\t") == line.rfind("\t") - 1)
                  sentence = line.substr(line.find("\t") + 1, line.rfind("\t") - line.find("\t") - 1);
                else if (line.rfind(".", line.size() - rfind_offset) != std::string::npos && line.find("\t") < line.rfind(".", line.size() - rfind_offset))
                  sentence = line.substr(line.find("\t") + 1, line.rfind(".", line.size() - rfind_offset) - line.find("\t") - 1);
                else
                  sentence = line.substr(line.find("\t") + 1, line.rfind("\t") - line.find("\t") - 1);
            }
            replace_ex(sentence);

            if (line.find("\t") != std::string::npos)
              sub_url = line.substr(line.rfind("\t") + 1);

            //ascertain file name and download url
            if (line.find("\t") != std::string::npos)
              word = line.substr(0, line.find("\t") - 0);
            else if (line.find("http://") == 0) {
                if (line.find(".") != std::string::npos)
                  word = line.substr(line.rfind("/") + 1, line.rfind(".") - line.rfind("/") - 1);
                else
                  word = line.substr(line.rfind("/") + 1);
                sub_url = line;
            }
            replace_ex(word);
            //std::cout << "***word:" << word << "***sentence:" << sentence << "***sub_url:" << sub_url << std::endl;
            //std::cout << "***" << sentence << "***" << std::endl;
            if (sub_url == previous_url)
              continue;
            previous_url = sub_url;
            if (word.empty() || sub_url.empty())
              continue;
            if (sub_url.find("http://") == std::string::npos)
              sub_url = fixed_url + sub_url;
            //std::cout << "****sub_url: " << sub_url << std::endl;
            words_url.insert(std::make_pair(word, std::make_pair(sentence, sub_url)));
        }
    }
    instream.close();
    return true;
}

bool rename(const std::multimap<std::string, std::pair<std::string, std::string> > &words_url, std::multimap<std::string, std::pair<std::string, std::string> > &failed_words, std::multimap<std::string, std::pair<std::string, std::string> > &keep_words)
{
    int success_num = 0;
    bool is_all_good = true;
    for (const auto &word_url : words_url) {
        std::string rename_command = "ren ";
        std::string tword, tsentence, turl, suffix, origin_file_name, new_file_name;
        tword = word_url.first;
        tsentence = word_url.second.first;
        turl = word_url.second.second;
        if (turl.find(".") != std::string::npos)
          suffix = turl.substr(turl.rfind(".") + 1);
        else
          suffix = "";

        if (tsentence.empty())
          origin_file_name = tword + "_" + subname + "." + suffix;
        else
          origin_file_name = tword + "_" + tsentence  + "_" + subname + "." + suffix;

        new_file_name = turl.substr(turl.rfind("/") + 1);

        rename_command = rename_command + "\"" + origin_file_name + "\" \"" + new_file_name + "\"";
        std::cout << "****rename_command: " << rename_command << std::endl;
        if (new_file_name.find(tword) == std::string::npos) {
            keep_words.insert(word_url);
            continue;
        }

        if (system(rename_command.c_str()) != 0) {
            failed_words.insert(word_url);
            is_all_good = false;
        }
        else
          success_num++;
    }
    std::cout << "****rename number: " << success_num << std::endl;
    return is_all_good;
}

