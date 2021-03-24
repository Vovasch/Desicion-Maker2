#pragma once

#include<fstream>
#include<vector>
#include<utility>
#include"gmm_model.h"

class tesgin_unit
{
	static std::ifstream testing_file;

	static const int amount_of_blocks_of_strings_we_can_test_int_one_unit = 5;

	std::pair<int, double>* first_block_of_strings_for_test;

	void Init(std::pair<int, double> *start);
	
};