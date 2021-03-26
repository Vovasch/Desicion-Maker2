//#pragma comment(lib, "mlpack.lib")
#include <iostream>
#include <string>
//#include <mlpack/prereqs.hpp>
//#include "mlpack_main.hpp" // Щоб його підключити потрібно в ньому закоментувани дві строки, які викликають помилки
#include <mlpack/core/util/io.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include <utility>
#include <vector>

#include "processing_of_main_testing_file.h"
#include "testing_unit.h"
#include "gmm_model.h"

using namespace std;
using namespace mlpack;	
using namespace mlpack::gmm;
using namespace mlpack::util;


// If this marcos is present user manually enter name of testing file
// Else name will be difined as a main.txt automaticaly
//#define if_need_user_to_enter_name_of_file

int gmm_model::amount_of_models = gmm_model::Count_Amount_of_Models();

std::ifstream testing_unit::testing_file;

int testing_unit::amount_of_blocks_of_strings_we_can_test_in_one_unit = 5;
int main()
{
	char name_of_main_testing_file_from_user[100];
	//where we copy file from user
	char inner_name_of_main_testing_file[]{ "data/main.txt\0" };
	

#ifdef if_need_user_to_enter_name_of_file

	Get_Name_of_Main_Tesgin_File_From_User(name_of_main_testing_file_from_user);

#else
	// Name of main testing file will be defult = data/main.txt
	Init_Main_Testing_File(name_of_main_testing_file_from_user);

#endif

	const int the_least_amount_of_string_we_can_assign_result_of_test = 10; // TODO namespace & adequаte naming

	const int amount_of_layers_of_test = 5;

	const int the_least_amount_of_string_to_be_tested = 50;

	//Need to copy in order not to change user's file
	Copy_and_Parse_Main_Testing_File(name_of_main_testing_file_from_user);

	//Now we get amount of strings from copied and chenged file
	int amount_of_string_in_main_testing_file = Get_Amount_Of_Strings_from_File(inner_name_of_main_testing_file);

	const int amount_of_testing_units = amount_of_string_in_main_testing_file / the_least_amount_of_string_we_can_assign_result_of_test;

	// where results of rough markup will be stored
	vector <pair<int, double>> indexes_of_sound_and_result(amount_of_testing_units, { 0,-100 });

	vector <gmm_model> models_for_test;
	models_for_test.reserve(gmm_model::amount_of_models);

	gmm_model::Upload_Models(models_for_test);

	// Rough markuping
	for (int i = 0; i < amount_of_layers_of_test; i++)
	{
		testing_unit::testing_file.open(inner_name_of_main_testing_file);
		testing_unit::Go_To_Line_In_Main_Testing_File(i * the_least_amount_of_string_we_can_assign_result_of_test);

		for (int e = i; e < indexes_of_sound_and_result.size(); e+= testing_unit::amount_of_blocks_of_strings_we_can_test_in_one_unit)
		{
			testing_unit test;
			test.Mesure_Probabilities(indexes_of_sound_and_result, e,models_for_test, the_least_amount_of_string_to_be_tested);	
		}
		testing_unit::testing_file.close();
	}

	int counter = 1;

	// Showing results of rough markuping
	for (auto i : indexes_of_sound_and_result)
	{
		cout << counter++ << " " << models_for_test[i.first].Get_Name_of_Model() << " " << i.second << endl;
	}

	system("Pause");
	return 0;
}