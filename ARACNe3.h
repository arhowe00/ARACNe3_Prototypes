#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

#ifndef _ARACNE3_H_
#define _ARACNE3_H_

/*
 * Square struct for APMI estimator.
 * 'x_bound1' is the x-coordinate of the bottom left of square
 * 'y_bound1' is the y-coordinate of the bottom left of square
 * 'width' is the width of the square
 * 'pts' is an array of indices
 * 'num_pts' is the size of 'pts'
 */
typedef struct {const float x_bound1, y_bound1, width; 
	const unsigned short *pts, num_pts;} square;

/*
 * Easier type to work with
 */
typedef std::unordered_map<std::string, std::vector<float>> hashmap;

float APMI(std::vector<float>, std::vector<float>, const float q_thresh, 
		const unsigned short);

void rowAPMI(hashmap &, const std::string &, const float, const unsigned short);

std::vector<std::string> readRegList(std::string);

hashmap readTransformedGexpMatrix(std::string);

#endif /* #ifndef _ARACNE3_H_ */
