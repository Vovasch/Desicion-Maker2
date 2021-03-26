#include "testing_unit.h"

void testing_unit::Form_Testing_File(int amount_of_lines)
{
	std::ofstream part_of_main_testing_file_to_test;

	part_of_main_testing_file_to_test.open("data/testing.txt");
	part_of_main_testing_file_to_test.clear();

	char data_to_copy[1024];

	int curent_amount_of_string{ 0 };

	// Coping from main testing file
	while ((!testing_file.eof()) && (curent_amount_of_string < amount_of_lines))
	{
		testing_file.getline(data_to_copy, 1024);
		part_of_main_testing_file_to_test << data_to_copy;
		part_of_main_testing_file_to_test << '\n';
		++curent_amount_of_string;
	}

	part_of_main_testing_file_to_test.close();

}

void testing_unit::Go_To_Line_In_Main_Testing_File(int line_number)
{
	char c[1024];

	for (int i = 0; i < line_number; i++)
		testing_file.getline(c, 1024);

}

void testing_unit::Mesure_Probabilities(std::vector<std::pair<int, double>>& test, int place, std::vector<gmm_model>& models_for_test, int amount_of_lines)
{
	
	this->Form_Testing_File(amount_of_lines);

	mlpack::data::Load("data/testing.txt", this->matrix);

	std::vector<double>res_of_Canculation_of_Probabilities_with_all_Bases(models_for_test.size(), 0);

	// Canculating probabilities
	for (int i = 0; i < models_for_test.size(); ++i)
	{
		for (int e = 0; e < this->matrix.n_cols; ++e)
			res_of_Canculation_of_Probabilities_with_all_Bases[i] += models_for_test[i].Get_GMM().LogProbability(matrix.unsafe_col(e));

		res_of_Canculation_of_Probabilities_with_all_Bases[i] /= matrix.n_cols;
		//std::cout << res_of_Canculation_of_Probabilities_with_all_Bases[i]<< std::endl;
	}

	// Find best result
	auto it = std::max_element(res_of_Canculation_of_Probabilities_with_all_Bases.begin(), res_of_Canculation_of_Probabilities_with_all_Bases.end());
	
	// Get to iterator where to write result
	auto block = test.begin()+place;

	int counter = 0;
	
	// Writing results
	while(counter < this->amount_of_blocks_of_strings_we_can_test_in_one_unit &&  block != test.end())
	{
		if (*it > block->second)
		{
			block->first = std::distance(res_of_Canculation_of_Probabilities_with_all_Bases.begin(),it);
			block->second = *it;
		}
		++block;
		++counter;
	}

}


extern std::ifstream testing_file;