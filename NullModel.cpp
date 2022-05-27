#include "ARACNe3.h"

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

vector<float> *null_mis;

/*
 * Computes 1 million null mutual information values from the number of samples.
 * To reduce runtime, we emulate rowAPMI but 
 */
vector<float> initNullMIs(const unsigned short &tot_num_samps) {
	// make the permute vector, the ref vector, send to permuteAPMI
	//
}
