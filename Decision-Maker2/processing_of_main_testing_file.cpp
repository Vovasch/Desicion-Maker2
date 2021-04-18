#include "processing_of_main_testing_file.h"
#include <iostream>



int Get_Amount_Of_Strings_from_File(const char* name_of_file)
{
	if (name_of_file)
	{
		std::ifstream file;

		file.open(name_of_file);

		if (file.is_open())
		{
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
		
	}
	throw std::exception("FATAL ERROR. Can't open file");
	return 0;

}
