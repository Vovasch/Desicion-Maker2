#pragma once

#ifndef TESTING_INSTRUMENTS
#define TESTING_INSTRUMENTS

#include <iostream>
#include <string>
#include <mlpack/core/util/io.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include <utility>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <exception>
#include <Windows.h>

#include "gmm_model.h"
#include "file_processing.h"
void Canculate_Probabilities(std::vector<std::vector<double>> &results, std::vector<gmm_model> models, char* testing_file);

// My teacher said that this is Veiterbi algorithm
// But it appeared to be useless for us
void Find_Best_Averages(const std::vector<double>& input_data, std::vector<std::pair<double, int>> &results, int min_length_of_sound);

void Rough_MurkUp(const std::vector<std::vector<double>>& probabilites, const std::vector<gmm_model> models, const char* dirWithWhereToSaveResults, const std::vector<std::string> nameOfFilesWhereToSaveResults);

#endif