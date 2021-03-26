#pragma once

#include<iostream>

#include<fstream>
#include<vector>
#include<utility>
#include <mlpack/core/util/io.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include<algorithm>
#include"gmm_model.h"

class testing_unit
{
	arma::mat matrix;
	
	// Get 50 lies to test from main testing file
	void Form_Testing_File(int amount_of_lines);

public:

	static int amount_of_blocks_of_strings_we_can_test_in_one_unit;

	static std::ifstream testing_file;
	
	// Going to line in static std::ifstream testing_file
	static void Go_To_Line_In_Main_Testing_File(int line_number);

	// Mesure all probabilites of all models with arma::mat matrix where 50 lines
	// And set resutls into block of result each of 10 lines
	void Mesure_Probabilities(std::vector<std::pair<int, double>> &test, int place, std::vector<gmm_model> &models_for_test, int amount_of_lines);
	
};

extern std::ifstream testing_file;