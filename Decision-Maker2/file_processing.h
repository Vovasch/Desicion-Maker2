#pragma once

#ifndef FILE_PROCESSING
#define FILE_PROCESSING

#include<fstream>
#include<exception>
#include"gmm_model.h"
#include<vector>
#include<string>
#include<sstream>
#include<iostream>

void GetAllNameOfFilesFromDirectory(std::vector<std::string>& namesOfFilesInDirectory, const char* directory);

void Create_Files_For_Results(const std::vector<std::string>& namesOfFiles, const char* directory);

int Get_Amount_Of_Strings_from_File(const char* name_of_file);

// dir + / + name_of_file
void ConcatinateDirAndNameOfFile(char * result, const char* dir, const std::string name_of_file);

void FixStartAndEndOfSoundInFile(int position, const char* dirWithResults, const std::string nameOfFileOfModel);

#endif