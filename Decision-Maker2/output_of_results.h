#pragma once

#ifndef OUTPUT_OF_RESULTS
#define OUTPUT_OF_RESULTS

#include<vector>
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<memory>

#include "dirent.h"
#include "file_processing.h"

class Result_Shower
{
protected:
	// bird.txt -> Bird
	std::string ConvertNameOfFileIntoName(const std::string nameOfFile);

public:
	void virtual Show_Results(const char* dir, std::vector<std::string> namesOfFiles) = 0;
};

class Simple_Result_Shower : public Result_Shower
{
public:
	void Show_Results(const char* dir, std::vector<std::string> namesOfFiles) override;

};

class SortedShowindOfResults : public Result_Shower
{
public:
	void Show_Results(const char* dir, std::vector<std::string> namesOfFiles) override;
};

class ResultStrategy
{
private:
	std::unique_ptr<Result_Shower> resultShower;
public:

	void Set_Strategy(std::unique_ptr<Result_Shower> resultShower);

	void Execute_Strategy(const char* dir, std::vector<std::string> namesOfFiles);

	
};


#endif OUTPUT_OF_RESULTS