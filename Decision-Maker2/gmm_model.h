#pragma once
#pragma comment(lib, "mlpack.lib")
#include <string>
#include <mlpack/methods/gmm/gmm.hpp>
#include <mlpack/core/util/io.hpp>
#include <vector>
#include "dirent.h"
#include <fstream>
#include <iostream>
#include <string>

class gmm_model
{
	std::string name;
	mlpack::gmm::GMM gmm;

	int smallest_value_to_be_defined;
	int smallest_duration_in_santi_seconds_to_be_real;
	int  biggest_duration_in_santi_seconds_to_be_real;

	// Forming a directory that will be used in loading of molel
	static void Form_Directory(char* dir, char* name_of_file);

	// Fromig a name of model set will be used by
	// gmm_model::Init_Model() to set name
	static void Form_Name_of_Model(char* name_of_file);

	// Getting integer parameters from file with descriptions 
	// of models
	static int Get_Information_From_Line(char* line);

public:
	static int amount_of_models;

	static int Count_Amount_of_Models();

	static void Upload_Models(std::vector<gmm_model> &models);
	
	//Set parameteres of model and load gmm model
	void Init_Model(const std::string name, const int smallest_value_to_be_defined, const int smallest_duration_in_santi_seconds_to_be_real, const int biggest_duration_in_santi_seconds_to_be_real);
};