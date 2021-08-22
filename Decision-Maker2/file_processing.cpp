#include "file_processing.h"

int CountAmountOfFilsInDir(const char* dir)
{
	int file_count = 0;

	DIR* dirp;
	struct dirent* entry;

	dirp = opendir(dir);
	while ((entry = readdir(dirp)) != NULL)
		if (entry->d_type == DT_REG)
			file_count++;

	closedir(dirp);

	return file_count;
}

void GetAllNameOfFilesFromDirectory(std::vector<std::string>& namesOfFilesInDirectory, const char* directory)
{
	DIR* dirp;

	struct dirent* entry;

	dirp = opendir(directory);

	while ((entry = readdir(dirp)) != NULL)
		if (entry->d_type == DT_REG)
		{
			namesOfFilesInDirectory.push_back(entry->d_name);
		}

	closedir(dirp);
}

int Get_Amount_Of_Strings_from_File(const std::string name_of_file)
{
	if (!name_of_file.empty())
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
	
	for (int i = 0; i < namesOfFiles.size(); i++)
	{
		
		char dirAndNameOfFile[1000];

		ConcatinateDirAndNameOfFile(dirAndNameOfFile, namesOfFiles[i], directory);
		
		files[i].open(dirAndNameOfFile);
		files[i].clear();
		files[i].close();
	}
}

void ConcatinateDirAndNameOfFile(char* result, const std::string name_of_file, const char* dir)
{
	int i = 0;
	if (dir != nullptr)
	{
		for (i = 0; dir[i] != '\0'; i++)
		{
			result[i] = dir[i];
		}


		result[i] = '/';
		i++;
	}
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
	
	ConcatinateDirAndNameOfFile(dirAndNameOfFileWhereToSave, nameOfFileOfModel, dirWithResults);
	

	std::ofstream file;
	file.open(dirAndNameOfFileWhereToSave, std::ios::app);
	

	std::stringstream result;

	result << position;

	file << result.str();
	file << "\n";

	file.close();

}

bool DoesThisFileExist(const std::string nameOfFile, const char* dir)
{
	std::fstream file;

	char dirAndNameOfFile[1000];

	ConcatinateDirAndNameOfFile(dirAndNameOfFile, nameOfFile, dir);

	file.open(dirAndNameOfFile);

	return file.is_open();
}

void ShowFileOnConsole(const std::string nameOfFile, const char* dir)
{
	std::fstream file;
	char dirAndNameOfFile[1000];
	ConcatinateDirAndNameOfFile(dirAndNameOfFile, nameOfFile, dir);

	file.open(dirAndNameOfFile);

	if (file.is_open());


	while (!file.eof())
	{
		char buff[1000];
		file.getline(buff, 1000);
		std::cout << buff << std::endl;
	}
}
