/**
 * @file Decision-Maker2.cpp
 * @author Vova Zhyvotivskyi
 * @thanks to Viktoria Megalatium
 */

#include <iostream>
#include <string>
#include <mlpack/core/util/io.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
#include <exception>
#include <thread>
#include <memory>

#include "file_processing.h"
#include "gmm_model.h"
#include "measurement_instruments.h"
#include "result_processing.h"
#include "output_of_results.h"

#include "unit_tests/main_test/main_unit_test.h"

using namespace std;
using namespace mlpack;
using namespace mlpack::gmm;
using namespace mlpack::util;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	mainTest();
#endif

	// all important directories

	const char models_Dir[]{ "data/models"}; //where .bin files stored

	const char descriptionOfModels_Dir[]{ "data/models_description" }; // where.txt files with desciptions of models stored 

	const char results_Dir[]{ "results" }; 	// where results .txt stored

	// where all names of file will be stored
	std::vector<std::string> ModelsFileNames; // .bin files 
	std::vector<std::string> DesciptionsOfModelsFileName; // .txt files with descriptins
	std::vector<std::string> ResultFileNames; // .txt files with results, will be created based on files with descriptions

	const int amountOfModels = CountAmountOfFilsInDir(models_Dir); // amount of data sets

	// for each model we have file with description and result
	ModelsFileNames.			 reserve(amountOfModels);
	DesciptionsOfModelsFileName. reserve(amountOfModels);
	ResultFileNames.			 reserve(amountOfModels);

	GetAllNameOfFilesFromDirectory(ModelsFileNames,				models_Dir);
	GetAllNameOfFilesFromDirectory(DesciptionsOfModelsFileName, descriptionOfModels_Dir);

	// types and names of files with results and models descriptions are same
	ResultFileNames = DesciptionsOfModelsFileName;

	Create_Files_For_Results(ResultFileNames, results_Dir);
	

	// processing a params of main() function

	std::string name_of_main_testing_file;

	if (argc > 1)
		name_of_main_testing_file = argv[1];
	else if (argc <= 1)
		name_of_main_testing_file = { "main.txt" };
	else
	{
		cout << "You have enterd too much parametrs";
		return 0;
	}

	// check if file we need to test exist
	if (!(DoesThisFileExist(name_of_main_testing_file)))
		return 0;

	vector <gmm_model> models_for_test;
	models_for_test.reserve(amountOfModels);

	gmm_model::Upload_Models(models_for_test, descriptionOfModels_Dir, models_Dir, DesciptionsOfModelsFileName, ModelsFileNames);


	int amount_of_strings_in_main_tasting_file;

	amount_of_strings_in_main_tasting_file = Get_Amount_Of_Strings_from_File(name_of_main_testing_file);


	//minus 1 for last string as a \n
	const int amount_of_probabilities{ amount_of_strings_in_main_tasting_file - 1 };

	vector<vector<double>> probabilities(amountOfModels, vector<double>(amount_of_probabilities, 0));

	try
	{
		// using mlpack instuments canculate how different each string if file from each model
		Canculate_Probabilities(probabilities, models_for_test, name_of_main_testing_file);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
		return -1;
	}
	
	// finding best results for each model to define which and what sound was
	Rough_MurkUp(probabilities, models_for_test, results_Dir, ResultFileNames);

	SortedShowingOfResults(results_Dir, ResultFileNames);

	system("Pause");
	return 0;
}