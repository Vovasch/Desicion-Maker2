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

#include "processing_of_main_testing_file.h"
#include "gmm_model.h"
#include "testing_instruments.h"

using namespace std;
using namespace mlpack;	
using namespace mlpack::gmm;
using namespace mlpack::util;


int gmm_model::amount_of_models = gmm_model::Count_Amount_of_Models();

int main(int argc, char* argv[])
{
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

	gmm_model::Upload_Models(models_for_test);

	int amount_of_strings_in_main_tasting_file = Get_Amount_Of_Strings_from_File(name_of_main_testing_file);

	
	vector<vector<double>> probabilities(gmm_model::amount_of_models, { 0 });



	//minus 1 for last string as a \n
	for (auto& it : probabilities)
		it.resize(amount_of_strings_in_main_tasting_file - 1, 0);
	
	Canculate_Probabilities(probabilities, models_for_test, name_of_main_testing_file);
	

	vector<vector<pair<double, int>>> average_results;

	average_results.resize(probabilities.size(), { {0,0} });

	/*vector<double> test{ -1,-2,-3,-4,-5,-6,10,10,10,-1 };
	vector<pair<double, int>> res_test;

	Canculate_Sums_on_Smallets_Lengths(test, res_test, 3);*/

	for (int i = 0; i < probabilities.size(); i++)
		Canculate_Sums_on_Smallets_Lengths(probabilities[i], average_results[i], models_for_test[i].Get_Smallest_Duration());

	int counter = 0;

	/*for (int i = 0; i < average_results[0].size(); ++i)
	{
		cout << ++counter << " ";

		for (int e = 0; e < avarenge_resutls.size(); ++e)
		{
			cout << average_results[e][i].second << " ";

			double res = average_results[e][i].first;

			if (res >= 0)
				cout << " ";
			cout << res << " ";

			double prob = probabilities[e][i];

			if (prob >= 0)
				cout << " ";
			cout << prob;

			
		}
		cout << endl;
	}*/

	vector<vector<int>> peaks(average_results.size(), { 0 });

	for (int i = 0; i < average_results.size(); ++i)
		Find_Peaks(average_results[i], peaks[i]);

	for (int i = 0; i < 1; i++)
		for (int e = 0; e < peaks[i].size(); ++e)
			cout << peaks[i][e] << endl;


	

	system("Pause");
	return 0;
}