#pragma once

#ifndef OUTPUT_OF_RESULTS
#define OUTPUT_OF_RESULTS

#include<vector>
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>

#include "dirent.h"
#include "file_processing.h"

// bird.txt -> Bird
std::string ConvertNameOfFileIntoName(const std::string nameOfFile);

void SimpleShowingOfResults(const char* dir, std::vector<std::string> namesOfFiles);

void SortedShowingOfResults(const char* dir, std::vector<std::string> namesOfFiles);



#endif OUTPUT_OF_RESULTS