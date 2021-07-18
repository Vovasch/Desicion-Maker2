#include "file_processing.h"
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

void ConcatinateDirAndNameOfFile(char* dir, char* name_of_file)
{
	int i = 1;
	while (dir[i] != '\0')
		i++;

	int e = 0;
	while (name_of_file[e] != '\0')
	{
		dir[i] = name_of_file[e];
		i++;
		e++;
	}

	i++;
	dir[i] = '\0';
}

void Create_Files_For_Results(std::vector<gmm_model>& models)
{
	std::ofstream* files;
	files = new std::ofstream[gmm_model::amount_of_models];
	
	for (int i = 0; i < gmm_model::amount_of_models; i++)
	{
		char dir[1000]{"results/"};

		int e = 8;
		for (auto c : models[i].Get_Name_of_Model())
		{
			dir[e] = c;
			e++;
		}
		dir[e] = '.';
		dir[e + 1] = 't';
		dir[e + 2] = 'x';
		dir[e + 3] = 't';
		dir[e + 4] = '\0';

		files[i].open(dir);
		files[i].clear();
		files[i].close();
	}
}

