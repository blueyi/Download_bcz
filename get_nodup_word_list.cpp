/*
 * nodup.cpp
 * Copyright (C) 2015  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <fstream>
#include <set>
#include <string>

int main(int argc, char **argv)
{
    std::set<std::string> nodup;
    std::ifstream inf(argv[1]);
    std::ofstream outf("nodup.txt", std::ofstream::out | std::ofstream::app);
    std::string line;
    while (getline(inf, line)) {
       nodup.insert(line);
    }
    inf.close();
    for (const auto &word : nodup) {
        outf << word << std::endl;
    }
    outf.close();
    return 0;
}


