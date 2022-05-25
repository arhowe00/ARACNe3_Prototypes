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

std::vector<float> APMI(std::vector<float>, std::vector<float>, const float, 
		const unsigned short);

#endif /* #ifndef _ARACNE3_H_ */
