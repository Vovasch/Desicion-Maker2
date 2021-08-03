#include "gmm_model.h"
#include "file_processing.h"

double gmm_model::Get_Information_From_Line(char* line)
{
    int i = 2;
    while (line[i] != ' ') 
        i++;

    return atof(&line[i]);
}

void gmm_model::Upload_Models(std::vector<gmm_model>& models, 
    const char* dirWitDescriptionOfModels,
    const char* dirWithModels,
    const std::vector<std::string> namesOfFilesWithDescriptionOfModels,
    const std::vector<std::string> namesOfFilesWithModels)
{
    std::ifstream describing_file;

    const int amount_of_params_of_model = 4;
    double params[amount_of_params_of_model];
 
    for (int i = 0; i < namesOfFilesWithModels.size(); i++)
    {
        char buff[200];

        char directoryAndNameOfDescribingFile[1000];

        ConcatinateDirAndNameOfFile(directoryAndNameOfDescribingFile, namesOfFilesWithDescriptionOfModels[i], dirWitDescriptionOfModels);

        describing_file.open(directoryAndNameOfDescribingFile);

        int e = 0;

        while ((!describing_file.eof()))
        {
            describing_file.getline(buff, 200);

            params[e] = gmm_model::Get_Information_From_Line(buff);

            ++e;
        }

        char directoryAndNameOfModel[1000];
        ConcatinateDirAndNameOfFile(directoryAndNameOfModel, namesOfFilesWithModels[i], dirWithModels);

        gmm_model gmm(namesOfFilesWithModels[i], params[0], params[1], params[2], params[3], directoryAndNameOfModel);

        models.push_back(gmm);
        describing_file.close();
    }
}