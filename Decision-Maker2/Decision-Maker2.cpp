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

int main()
{
	char name_of_main_testing_file_from_user[100];
	//where we copy file from user
	char inner_name_of_main_testing_file[]{ "data/main.txt\0" };
	

#ifdef if_need_user_to_enter_name_of_file

	Get_Name_of_Main_Tesgin_File_From_User(name_of_main_testing_file_from_user);

#else

	Init_Main_Testing_File(name_of_main_testing_file_from_user);

#endif

	const int the_least_amount_of_string_we_can_assign_result_of_test = 10; // TODO namespace & adequаte naming

	//Need to copy in order not to change user's file
	Copy_and_Parse_Main_Testing_File(name_of_main_testing_file_from_user);

	//Now we get amount of strings from copied and chenged file
	int amount_of_string_in_main_testing_file = Get_Amount_Of_Strings_from_File(inner_name_of_main_testing_file);

	const int amount_of_testing_units = amount_of_string_in_main_testing_file / the_least_amount_of_string_we_can_assign_result_of_test;

	vector <pair<int, double>> indexes_of_sound_and_results(amount_of_testing_units);

	vector <gmm_model> models_for_test;
	models_for_test.reserve(gmm_model::amount_of_models);

	gmm_model::Upload_Models(models_for_test);
	

	system("Pause");
	return 0;
}