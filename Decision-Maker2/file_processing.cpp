#include "file_processing.h"

void GetAllNameOfFilesFromDirectory(std::vector<std::string>& namesOfFilesInDirectory, const char* directory)
{
	DIR* dirp;

	struct dirent* entry;

	// recieving all names of sound of directory with results

	dirp = opendir(directory);

	while ((entry = readdir(dirp)) != NULL)
		if (entry->d_type == DT_REG)
		{
			namesOfFilesInDirectory.push_back(entry->d_name);
		}

	closedir(dirp);
}

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

void Create_Files_For_Results(const std::vector<std::string>& namesOfFiles, const char* directory)
{
	std::ofstream* files;
	files = new std::ofstream[namesOfFiles.size()];
	
	for (int i = 0; i < gmm_model::amount_of_models; i++)
	{
		
		char dirAndNameOfFile[1000];

		ConcatinateDirAndNameOfFile(dirAndNameOfFile, directory, namesOfFiles[i]);
		
		files[i].open(dirAndNameOfFile);
		files[i].clear();
		files[i].close();
	}
}

void ConcatinateDirAndNameOfFile(char* result, const char* dir, const std::string name_of_file)
{
	int i;
	for (i = 0; dir[i] != '\0'; i++)
	{
		result[i] = dir[i];
	}

	result[i] = '/';
	i++;

	for (auto c : name_of_file)
	{
		result[i] = c;
		i++;
	}

	result[i] = '\0';
}

void FixStartAndEndOfSoundInFile(int position, const char* dirWithResults, const std::string nameOfFileOfModel)
{
	char dirAndNameOfFileWhereToSave[1000];
	
	ConcatinateDirAndNameOfFile(dirAndNameOfFileWhereToSave, dirWithResults, nameOfFileOfModel);
	

	std::ofstream file;
	file.open(dirAndNameOfFileWhereToSave, std::ios::app);
	

	std::stringstream result;

	result << position;

	file << result.str();
	file << "\n";

	file.close();

}


