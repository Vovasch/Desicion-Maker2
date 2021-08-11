#include "output_of_results.h"

std::string Result_Shower::ConvertNameOfFileIntoName(const std::string nameOfFile)
{
	std::string name{ nameOfFile };

	char a = name.back();

	// erasing .txt
	for (int i = 0; i < 4; i++)
		name.pop_back();

	//a ---> A
	name[0] -= 32;

	return name;
}

void Simple_Result_Shower::Show_Results(const char* dir, std::vector<std::string> namesOfFiles)
{
	for (auto name : namesOfFiles)
	{
		std::cout << ConvertNameOfFileIntoName(name) << std::endl;

		char dirAndNameOfFile[1000];

		ConcatinateDirAndNameOfFile(dirAndNameOfFile, name, dir);

		std::ifstream file;
		file.open(dirAndNameOfFile);

		while (!(file.eof()))
		{
			char buf[1000];

			file.getline(buf, 1000);
			std::cout << buf << std::endl;
		}
		std::cout << std::endl;

		file.close();
	}
}

void SortedShowindOfResults::Show_Results(const char* dir, std::vector<std::string> namesOfFiles)
{
	struct Name_Pos_StartOrEnd
	{
		std::string name;
		int pos;
		bool StartOrEnd; //0 - start, 1 - end
	};

	std::vector<Name_Pos_StartOrEnd> results;

	for (auto name : namesOfFiles)
	{
		Name_Pos_StartOrEnd current;
		current.StartOrEnd = 1;

		current.name = ConvertNameOfFileIntoName(name);

		char dirAndNameOfFile[1000];

		ConcatinateDirAndNameOfFile(dirAndNameOfFile, name, dir);

		std::ifstream file;
		file.open(dirAndNameOfFile);

		while (!(file.eof()))
		{
			char buf[1000];

			file.getline(buf, 1000);
			current.pos = atoi(buf);
			current.StartOrEnd = !current.StartOrEnd;
			results.push_back(current);
		}

		results.pop_back();
		file.close();
	}

	std::sort(results.begin(), results.end(), [](Name_Pos_StartOrEnd a, Name_Pos_StartOrEnd b)
		{
			return a.pos < b.pos;
		});

	for (auto item : results)
	{
		std::cout << item.pos << " || " << item.name << " " << item.StartOrEnd << std::endl;
	}

	std::cout << std::endl;

}

void ResultStrategy::Set_Strategy(std::unique_ptr<Result_Shower> resultShower)
{
	this->resultShower = std::move(resultShower);

}

void ResultStrategy::Execute_Strategy(const char* dir, std::vector<std::string> namesOfFiles)
{
	this->resultShower.get()->Show_Results(dir,  namesOfFiles);
}
