#include "ARACNe3.hpp"

/*
 * This file is the null-model module of ARACNe3.  It is a separate file because
 * for the first pruning step, we will need to calculate a p-value based on the
 * eCDF for the null mutual information of gene expression marginals, calculated
 * via APMI from 1,000,000 random vectors.  The vector is sorted and stored on
 * the heap, and it will be accessible for p-value calculation from the global
 * variable pointer null_mis.  null_mis is to be free'd after the first pruning
 * step.
 *
 */

//std::vector<float> *null_mis;

/*
 * Computes 1 million null mutual information values from the number of samples.
 * To reduce runtime, we emulate rowAPMI but 
 */
std::vector<float> initNullMIs(const unsigned int tot_num_samps) {
	// make the permute vector, the ref vector, send to permuteAPMI
	std::cout << "TEST" << std::endl;
	float ref_arr[tot_num_samps];
	for (unsigned short i = 0; i < tot_num_samps; ++i) {
		ref_arr[i] = i/(float) tot_num_samps;
	}
	std::cout << "TEST" << std::endl;
	std::vector<float> ref_vec(&ref_arr[0], &ref_arr[tot_num_samps]);

	// an array of vectors
	std::vector<float> target_arr[1000000];
	std::cout << "TEST" << std::endl;

	auto rng = std::default_random_engine {};
	for (unsigned int i = 0; i < 1000000; ++i) {
		target_arr[i] = std::vector<float>(ref_vec);
		std::shuffle(std::begin(target_arr[i]), std::end(target_arr[i]),
				rng);
	}
	std::cout << "TEST" << std::endl;

	std::vector<std::vector<float>> target_vec(&target_arr[0],
			&target_arr[1000000]);
	std::cout << "TEST" << std::endl;

	//std::vector<float> mi_vec = permuteAPMI(ref_vec, target_vec,
	//		7.815, 4);

	return ref_vec;
}

int main() {
	std::vector<float> mis = initNullMIs(100);
	for (auto &num : mis) { std::cout << num << std::endl; }
}
