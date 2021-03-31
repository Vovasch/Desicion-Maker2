#include "processing_of_main_testing_file.h"
#include <iostream>


void Copy_and_Parse_Main_Testing_File(const char* name_of_main_testing_file)
{
	if (name_of_main_testing_file)
	{
		std::ifstream file_from_user;
		std::ofstream main_testing_file;

		int amount_of_String = Get_Amount_Of_Strings_from_File(name_of_main_testing_file);

		file_from_user.open(name_of_main_testing_file);
		main_testing_file.open("data/main.txt");

		main_testing_file.clear();

		char c[1024];

		// Get last character in file
		while (!file_from_user.eof())
			file_from_user.getline(c, 1024);

		// Won't copy last string
		if ('\0' == c[0])
			amount_of_String--;


		// Go to the beginning of the file
		file_from_user.close();
		file_from_user.open(name_of_main_testing_file);

		// Copy everyting
		for (int i = 0; i < amount_of_String - 1; i++)
		{
			file_from_user.getline(c, 1024);

			main_testing_file << c;
			main_testing_file << '\n';
		}


		// In file from user last symbol of line is always \0
		// We need \n, but don't need it after last string

		//In order not no make last string a symbol '\n'
		file_from_user.getline(c, 1024);
		main_testing_file << c;

		file_from_user.close();
		main_testing_file.close();
	}
}

int Get_Amount_Of_Strings_from_File(const char* name_of_file)
{
	if (name_of_file)
	{
		std::ifstream file;

		file.open(name_of_file);

		char c[1024];
		int amount_of_strings{ 0 };


		while (!(file.eof()))
		{
			file.getline(c, 1024);
			++amount_of_strings;
		}

		file.close();

		return amount_of_strings;
	}
	return 0; 

}
