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

	int max_value_to_be_defined;
	int min_value_to_be_defined;
	int smallest_duration_in_santi_seconds_to_be_real;
	int  biggest_duration_in_santi_seconds_to_be_real;

	// Forming a directory that will be used in loading of molel
	// dir + name_of_file
	static void Form_Directory(char* dir, char* name_of_file);

	// Fromig a name of model set will be used by
	// bird.txt -> bird.bin
	static void Form_Name_of_Model(char* name_of_file);

	// Getting double parameters from file with descriptions 
	// of models
	// LENGTH 5
	// Function will return 5
	static double Get_Information_From_Line(char* line);

public:

	static int amount_of_models;

	static int Count_Amount_of_Models();

	gmm_model(std::string name, int max_value_to_be_defined, int min_value_to_be_defined, int smallest_duration_in_santi_seconds_to_be_real, int biggest_duration_in_santi_seconds_to_be_real) :
		name(name),
		max_value_to_be_defined(max_value_to_be_defined),
		min_value_to_be_defined(min_value_to_be_defined),
		smallest_duration_in_santi_seconds_to_be_real(smallest_duration_in_santi_seconds_to_be_real),
		biggest_duration_in_santi_seconds_to_be_real(biggest_duration_in_santi_seconds_to_be_real)
	{
		std::string path{ "data/models/" };
		std::string format{ ".bin" };

		path += name;
		path += format;

		mlpack::data::Load(path, "model", this->gmm);
	}


	
	//Set parameteres of model and load gmm model
	void Init_Model(const std::string name, const int smallest_value_to_be_defined, const int smallest_duration_in_santi_seconds_to_be_real, const int biggest_duration_in_santi_seconds_to_be_real);

	mlpack::gmm::GMM& Get_GMM()  { return this->gmm; }

	std::string Get_Name_of_Model() const { return this->name; }
	
	double Get_Min_Value_To_Be_Defined() const { return this->min_value_to_be_defined; }

	double Get_Max_Value_To_Be_Defined() const { return this->max_value_to_be_defined; }
	
	int Get_Smallest_Duration() const { return this->smallest_duration_in_santi_seconds_to_be_real; }
	
	int Get_Biggest_Duration() const {return this->biggest_duration_in_santi_seconds_to_be_real;}

	// Using mlpack instrument upload models into objects GMM
	static void Upload_Models(std::vector<gmm_model>& models);

};