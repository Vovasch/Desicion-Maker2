#include "measurement_instruments.h"

void Canculate_Probabilities(std::vector<std::vector<double>>& results, std::vector<gmm_model> models, const std::string testing_file)
{
	arma::mat matrix;

	bool correct_opening = mlpack::data::Load(testing_file, matrix);

	if (!correct_opening)
		throw std::exception("FATAL ERROR. Can't load data from main testing file");

	for (size_t i = 0; i < matrix.n_cols; ++i)
	{
		arma::dvec test = matrix.unsafe_col(i);

		for (int e = 0; e < models.size(); ++e)
		{
			results[e][i] = models[e].Get_GMM().LogProbability(test);
		}
	}
}

void Find_Best_Averages(const std::vector<double>& input_data, std::vector<std::pair<double, int>>& results, int min_length_of_sound)
{
	results.resize(input_data.size(), { 0,0 });

	if (min_length_of_sound > input_data.size())
		throw std::exception("Sound is too short");

	for (int i = 0; i < min_length_of_sound; ++i)
	{
		for (int e = 0; e <= i; ++e)
			results[i].first += input_data[e];
		results[i].first /= (i + 1);
	}

	for (int i = min_length_of_sound; i < input_data.size(); ++i)
	{
		double prev_sum = results[i - 1].first;

		prev_sum *= (i - results[i - 1].second);

		double with_prev_average = prev_sum;
		with_prev_average += input_data[i];

		with_prev_average /= (i - results[i - 1].second + 1);

		double current_average = 0;

		for (int e = i - min_length_of_sound+1; e <=i; ++e)
			current_average += input_data[e];

		current_average /= min_length_of_sound;

		if (with_prev_average >= current_average)
		{
			results[i].first = with_prev_average;
			results[i].second = results[i - 1].second;
		}
		else
		{
			results[i].first = current_average;
			results[i].second = (i - min_length_of_sound+1);
		}
	}
}

void Rough_MurkUp(const std::vector<std::vector<double>>& probabilites, const std::vector<gmm_model> models, const char* dirWithWhereToSaveResults, const std::vector<std::string> nameOfFilesWhereToSaveResults)
{
	bool* lookForEndingOfSound = new bool[probabilites.size()]{ 0 };

	double* sumCurrent = new double[probabilites.size()]{ 0 };

	double* averageOfProbabilitesCurrent = new double[probabilites.size()]{ 0 };
	
	
	for (int i = 0; i < probabilites[0].size(); i++)
	{
		for (int e = 0; e < probabilites.size(); e++)
		{
			sumCurrent[e] += probabilites[e][i];
			if (i < models[e].Get_Smallest_Duration())
			{
				averageOfProbabilitesCurrent[e] = sumCurrent[e] / i+1;
			}
			else
			{
				sumCurrent[e] -= probabilites[e][i - models[e].Get_Smallest_Duration()];
				averageOfProbabilitesCurrent[e] = sumCurrent[e] / models[e].Get_Smallest_Duration();
			}

			if (!lookForEndingOfSound[e])
			{
				if (averageOfProbabilitesCurrent[e] >= models[e].Get_Max_Value_To_Be_Defined())
				{
					FixStartAndEndOfSoundInFile(i-models[e].Get_Smallest_Duration(), dirWithWhereToSaveResults, nameOfFilesWhereToSaveResults[e]);
					lookForEndingOfSound[e] = 1;
				}
			}
			else
			{
				if (averageOfProbabilitesCurrent[e] < models[e].Get_Min_Value_To_Be_Defined())
				{
					FixStartAndEndOfSoundInFile(i- models[e].Get_Smallest_Duration(), dirWithWhereToSaveResults, nameOfFilesWhereToSaveResults[e]);
					lookForEndingOfSound[e] = 0;
				}
			}
		}

		if (i % 200 == 0)
		{
			// show results
		}
	}
}