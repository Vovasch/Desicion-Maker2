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

int CountAmountOfFilsInDir(const char* dir);

void GetAllNameOfFilesFromDirectory(std::vector<std::string>& namesOfFilesInDirectory, const char* directory);

void Create_Files_For_Results(const std::vector<std::string>& namesOfFiles, const char* directory);

int Get_Amount_Of_Strings_from_File(const std::string name_of_file);

// dir + / + name_of_file
void ConcatinateDirAndNameOfFile(char * result, const std::string name_of_file, const char* dir = nullptr);

void FixStartAndEndOfSoundInFile(int position, const char* dirWithResults, const std::string nameOfFileOfModel);

bool DoesThisFileExist(const std::string nameOfFile, const char* dir = nullptr);

#endif