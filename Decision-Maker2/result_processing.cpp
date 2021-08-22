#include "result_processing.h"

std::string Result_Saver::ConvertNameOfFileIntoName(const std::string nameOfFile)
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

void Simple_Result_Saver::Show_Results(const char* dir, const std::vector<std::string>& namesOfFiles, const std::string& resultFile, const std::vector<std::vector<double>>& probabilites)
{
	std::ofstream file_res(resultFile);

	if (!file_res.is_open())
		return;

	file_res.clear();

	for (auto name = namesOfFiles.begin(); name != namesOfFiles.end(); ++name)
	{

		file_res << ConvertNameOfFileIntoName(*name);
		file_res << '\n';

		char dirAndNameOfFile[1000];

		ConcatinateDirAndNameOfFile(dirAndNameOfFile, *name, dir);

		std::ifstream file;
		file.open(dirAndNameOfFile);

		while (true)
		{
			

			char buf[1000];

			file.getline(buf, 1000);
			if (file.eof())
				break;
			file_res << buf << "  ";

			if (probabilites.size())
				file_res << probabilites[std::distance(namesOfFiles.begin(), name)][atoi(buf)] << std::endl;
			else
				file_res << std::endl;

			
		}
		file_res << std::endl;

		file.close();
	}

	file_res.close();
}

void SortedSavingOfResults::Show_Results(const char* dir, const std::vector<std::string>& namesOfFiles, const std::string& resultFile, const std::vector<std::vector<double>>& probabilites)
{
	struct Name_Pos_StartOrEnd
	{
		std::string name;
		int pos;
		bool StartOrEnd; //0 - start, 1 - end
		double probability;
	};

	std::vector<Name_Pos_StartOrEnd> results;

	for (auto name = namesOfFiles.begin(); name != namesOfFiles.end(); ++name)
	{
		Name_Pos_StartOrEnd current;
		current.StartOrEnd = 1;

		current.name = ConvertNameOfFileIntoName(*name);

		char dirAndNameOfFile[1000];

		ConcatinateDirAndNameOfFile(dirAndNameOfFile, *name, dir);

		std::ifstream file;
		file.open(dirAndNameOfFile);

		while (!(file.eof()))
		{
			char buf[1000];

			file.getline(buf, 1000);
			current.pos = atoi(buf);
			current.StartOrEnd = !current.StartOrEnd;
			current.probability = probabilites[std::distance(namesOfFiles.begin(), name)][current.pos];
			results.push_back(current);
		}

		results.pop_back();
		file.close();
	}

	std::sort(results.begin(), results.end(), [](Name_Pos_StartOrEnd a, Name_Pos_StartOrEnd b)
	{
		return a.pos < b.pos;
	});


	std::ofstream file_res(resultFile);
	file_res.clear();
	for (auto item : results)
	{
		file_res << item.pos << " || " << item.name << " " << item.StartOrEnd <<  "    " << item.probability << std::endl;
	}

	file_res << std::endl;
}

void ResultSavingStrategy::Set_Strategy(std::unique_ptr<Result_Saver> resultShower)
{
	this->resultShower = std::move(resultShower);
}

void ResultSavingStrategy::Execute_Strategy(const char* dir, const std::vector<std::string>& namesOfFiles, const std::string& resultFile, const std::vector<std::vector<double>>& probabilites)
{
	this->resultShower.get()->Show_Results(dir, namesOfFiles, resultFile, probabilites);
}