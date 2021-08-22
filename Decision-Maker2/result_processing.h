#pragma once

#ifndef RESUT_PROCESSING
#define RESUT_PROCESSING

#include<vector>
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<memory>

#include "dirent.h"
#include "file_processing.h"

class Result_Saver
{
protected:
	// bird.txt -> Bird
	std::string ConvertNameOfFileIntoName(const std::string nameOfFile);

public:
	void virtual Show_Results(const char* dir,
		const std::vector<std::string>& namesOfFiles,
		const std::string& resultFile,
		const std::vector<std::vector<double>>& probabilites = std::vector<std::vector<double>>(0)) = 0;
};

class Simple_Result_Saver : public Result_Saver
{
public:
	void Show_Results(const char* dir,
		const std::vector<std::string>& namesOfFiles,
		const std::string& resultFile,
		const std::vector<std::vector<double>>& probabilites = std::vector<std::vector<double>>(0)) override;
};

class SortedSavingOfResults : public Result_Saver
{
public:
	void Show_Results(const char* dir,
		const std::vector<std::string>& namesOfFiles,
		const std::string& resultFile,
		const std::vector<std::vector<double>>& probabilites = std::vector<std::vector<double>>(0)) override;
};

class ResultSavingStrategy
{
private:
	std::unique_ptr<Result_Saver> resultShower;
public:

	void Set_Strategy(std::unique_ptr<Result_Saver> resultShower);

	void Execute_Strategy(const char* dir,
		const std::vector<std::string>& namesOfFiles,
		const std::string& resultFile,
		const std::vector<std::vector<double>>& probabilites = std::vector<std::vector<double>>(0));
};

#endif
