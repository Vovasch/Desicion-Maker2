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

int Get_Amount_Of_Strings_from_File(const char* name_of_file);

// Forming a directory that will be used in loading of molel
	// dir + name_of_file
void ConcatinateDirAndNameOfFile(char* dir, char* name_of_file);

void Create_Files_For_Results(std::vector<gmm_model>& models);

void FixStartOfEndOfSoundInFile(int position, std::string nameOfModel);

#endif