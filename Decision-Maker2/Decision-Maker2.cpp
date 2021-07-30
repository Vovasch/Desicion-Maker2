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

#include "file_processing.h"
#include "gmm_model.h"
#include "testing_instruments.h"
#include "result_processing.h"
#include "output_of_results.h"

using namespace std;
using namespace mlpack;
using namespace mlpack::gmm;
using namespace mlpack::util;

int gmm_model::amount_of_models = gmm_model::Count_Amount_of_Models();

int main(int argc, char* argv[])
{
	// all important directories

	//where .bin files stored
	const char models_Dir[]{ "data/models"};

	//where .txt files with desciptions like:
	//MAX_VALUE_TO_BE_DEFINED: 5.2
	//MIN_VALUE_TO_BE_DEFINED: 2
	//THE_LEAST_DURATION : 50
	//THE_LONGEST_DURATION : -1
	const char descriptionOfModels_Dir[]{ "data/models_description" };

	// where results .txt stored
	const char results_Dir[]{ "results" };

	std::vector<std::string> ModelsFileNames;
	std::vector<std::string> DesciptionsOfModelsFileName;
	std::vector<std::string> ResultFileNames;

	ModelsFileNames.			 reserve(gmm_model::amount_of_models);
	DesciptionsOfModelsFileName. reserve(gmm_model::amount_of_models);
	ResultFileNames.			 reserve(gmm_model::amount_of_models);

	GetAllNameOfFilesFromDirectory(ModelsFileNames,				models_Dir);
	GetAllNameOfFilesFromDirectory(DesciptionsOfModelsFileName, descriptionOfModels_Dir);

	// type of files with results and models descriptions are same
	ResultFileNames = DesciptionsOfModelsFileName;

	Create_Files_For_Results(ResultFileNames, results_Dir);
	

	// processing a params of main() function
	char* name_of_main_testing_file;

	if (argc > 1)
		name_of_main_testing_file = argv[1];
	else if (argc <= 1)
		name_of_main_testing_file = new char[] {"main.txt"};
	else
	{
		cout << "You have enterd too much parametrs";
		return 0;
	}

	vector <gmm_model> models_for_test;
	models_for_test.reserve(gmm_model::amount_of_models);

	gmm_model::Upload_Models(models_for_test, 
		descriptionOfModels_Dir,
		models_Dir,
		DesciptionsOfModelsFileName,
		ModelsFileNames);


	int amount_of_strings_in_main_tasting_file;

	amount_of_strings_in_main_tasting_file = Get_Amount_Of_Strings_from_File(name_of_main_testing_file);


	//minus 1 for last string as a \n
	const int amount_of_probabilities{ amount_of_strings_in_main_tasting_file - 1 };

	vector<vector<double>> probabilities(gmm_model::amount_of_models, vector<double>(amount_of_probabilities, 0));

	try
	{
		Canculate_Probabilities(probabilities, models_for_test, name_of_main_testing_file);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
		return -1;
	}
	
	Rough_MurkUp(probabilities, models_for_test, results_Dir, ResultFileNames);

	//SimpleShowingOfResults();

	system("Pause");
	return 0;
}