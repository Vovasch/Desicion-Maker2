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
	
	static const int amount_of_blocks_of_strings_we_can_test_int_one_unit = 5;

	void Form_Testing_File(int amount_of_lines);

public:

	static std::ifstream testing_file;
	
	static void Go_To_Line(int line_number);

	void Mesure_Probabilities(std::vector<std::pair<int, double>> &test, int place, std::vector<gmm_model> &models_for_test, int amount_of_lines);
	
};

extern std::ifstream testing_file;