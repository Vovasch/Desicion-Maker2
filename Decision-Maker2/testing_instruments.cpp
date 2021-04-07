#include "testing_instruments.h"

void Canculate_Probabilities(std::vector<std::vector<double>>& results, std::vector<gmm_model> models, char* testing_file)
{
	arma::mat matrix;

	mlpack::data::Load(testing_file, matrix);

	for (size_t i = 0; i < matrix.n_cols; ++i)
	{
		arma::dvec test = matrix.unsafe_col(i);

		for (int e = 0; e < models.size(); ++e)
		{
			results[e][i] = models[e].Get_GMM().LogProbability(test);
		}
	}

	

}

void Canculate_Sums_on_Smallets_Lengths(const std::vector<double>& input_data, std::vector<std::pair<double, int>>& results, int min_length_of_sound)
{
	results.resize(input_data.size(), { 0,0 });

	if (min_length_of_sound > input_data.size())
		throw; // TODO

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

		double current_average = with_prev_average;

		with_prev_average /= (i - results[i - 1].second + 1);

		/*double current_average = 0;

		for (int e = i - min_length_of_sound+1; e <=i; ++e)
			current_average += input_data[e];*/

		for (int e = results[i - 1].second; e <= i - min_length_of_sound; e++)
			current_average -= input_data[e];

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

void Find_Peaks(const std::vector<std::pair<double, int>>& input, std::vector<int>& peaks)
{
	peaks.resize(input.size(), 0);

	if (input.back() > input[input.size() - 2])
		peaks[peaks.size() - 1] = 1;

	for (int i = 1; i < input.size() - 1; ++i)
		if (input[i].first > input[i - 1].first && input[i].first > input[i + 1].first)
			peaks[i] = 1;
}
