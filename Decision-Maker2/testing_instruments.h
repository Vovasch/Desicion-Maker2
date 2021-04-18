#pragma once

#include <iostream>
#include <string>
#include <mlpack/core/util/io.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include <utility>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>

#include "gmm_model.h"

void Canculate_Probabilities(std::vector<std::vector<double>> &results, std::vector<gmm_model> models, char* testing_file);

// My teacher said that this is Veiterbi algorithm
// But it appeared to be useless for us
void Find_Best_Averages(const std::vector<double>& input_data, std::vector<std::pair<double, int>> &results, int min_length_of_sound);
