//#include <unistd.h>
//#include <sys/wait.h>
//#include <sys/stat.h>
#include <vector>
//#include <string>
#include <unordered_map>
#include <iostream>
//#include <fstream>
//#include <algorithm>
#include <random>
//#include <numeric>
//#include <math.h>

#ifndef _ARACNE3_HPP_
#define _ARACNE3_HPP_

/*
 * Square struct for APMI estimator.
 * 'x_bound1' is the x-coordinate of the bottom left of square
 * 'y_bound1' is the y-coordinate of the bottom left of square
 * 'width' is the width of the square
 * 'pts' is an array of indices
 * 'num_pts' is the size of 'pts'
 */
typedef struct {const float &x_bound1, &y_bound1, &width; 
	unsigned short *pts, &num_pts;} square;

/*
 * Edge struct for regulator->target interactions.  
 */
typedef struct {const std::string &regulator, &target;
	const float mi;} edge;

/*
 * Edge struct for regulator->target interactions, with incorporated p-values.
 * This struct is only used when we are doing the first-round pruning step
 */
typedef struct {edge &edge; const float p_value;} edge_p;

/*
 * Easier type to work with
 */
typedef std::unordered_map<std::string, std::vector<float>> hashmap;

float APMI(std::vector<float>, std::vector<float>, const float q_thresh, 
		const unsigned short);

void hashmapAPMI(hashmap &, const std::string &, const float, const unsigned
		short);

const std::vector<const float> permuteAPMI(std::vector<float> &ref_vec, 
		std::vector<std::vector<float>> &target_vec, const float,
		const unsigned short);

std::vector<float> initNullMis(const unsigned int);



std::vector<std::string> readRegList(std::string);

hashmap readTransformedGexpMatrix(std::string);

#endif /* #ifndef _ARACNE3_HPP_ */
