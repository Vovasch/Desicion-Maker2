#include "gmm_model.h"
#include "file_processing.h"

double gmm_model::Get_Information_From_Line(char* line)
{
    int i = 2;
    while (line[i] != ' ') 
        i++;

    return atof(&line[i]);
}

void gmm_model::Form_Name_of_Model(char* name_of_file)
{
    int lenght_of_File_tipe = 4; //.txt

    int i = 0;
    while (name_of_file[i] != '\0')
        ++i;
    name_of_file[i - lenght_of_File_tipe] = '\0';
}

int gmm_model::Count_Amount_of_Models()
{
    int file_count = 0;

    DIR* dirp;
    struct dirent* entry;
    
    dirp = opendir("data/models");
    while ((entry = readdir(dirp)) != NULL)         
        if (entry->d_type == DT_REG) 
            file_count++;

    closedir(dirp);
    
    return file_count;
}

void gmm_model::Upload_Models(std::vector<gmm_model>& models)
{
    DIR* dirp;
    struct dirent* entry;

    std::ifstream describing_file;

    const int amount_of_params_of_model = 4;
    double params[amount_of_params_of_model];
 
    char buff[200];

    dirp = opendir("data/models_description");
    while ((entry = readdir(dirp)) != NULL)
    {
        char directory[1000]{ "data/models_description/" };
        if (entry->d_type == DT_REG)
        {           
            ConcatinateDirAndNameOfFile(directory, entry->d_name);

            describing_file.open(directory);

            int i = 0;

            while ((!describing_file.eof()))
            {
                describing_file.getline(buff, 200);
                
                params[i] = gmm_model::Get_Information_From_Line(buff);

                ++i;
            }

            Form_Name_of_Model(entry->d_name);
           
            gmm_model gmm(entry->d_name, params[0], params[1], params[2], params[3]);

            models.push_back(gmm);
            describing_file.close();
        }           
    }
    closedir(dirp);
}