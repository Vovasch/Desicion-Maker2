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

using namespace std;
using namespace mlpack;	
using namespace mlpack::gmm;
using namespace mlpack::util;


// If this marcos is present user manually enter name of testing file
// Else name will be difined as a main.txt automaticaly
//#define if_need_user_to_enter_name_of_file


int main()
{
	char name_of_main_testing_file_from_user[100];
	char inner_name_of_main_testing_file[]{ "data/main.txt" };

#ifdef if_need_user_to_enter_name_of_file

	Get_Name_of_Main_Tesgin_File_From_User(name_of_main_testing_file_from_user);

#else

	Init_Main_Tesgin_File(name_of_main_testing_file_from_user);

#endif

	//Need to copy in order not to change user's file
	Copy_and_Parse_Main_Testing_File(name_of_main_testing_file_from_user);

	int strings{0};

	//Now we get amount of strings from copied and chenged file
	strings = Get_Amount_Of_Strings_from_File(inner_name_of_main_testing_file);
	

	system("Pause");
	return 0;
}