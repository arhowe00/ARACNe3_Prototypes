// [[Rcpp::depends(BH)]]
// [[Rcpp::plugins("cpp11")]]

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <math.h>
//#include <boost/math/distributions/chi_squared.hpp>
//#include <Rcpp.h>

//using namespace Rcpp;
using namespace std;


/*
 * Global variables will be modified, but q_thresh is set by default here
 */
static float q_thresh;
static unsigned short size_thresh, tot_squares;
typedef struct {const float x_bound1, x_bound2, y_bound1, y_bound2; const unsigned long n_samps;} square;


/*
 * Recursive tessellation of XY plane (regulator-target expression for each sample)
 * 
 * pts a vector of indices to access in vec_x and vec_y
 * vec_x a pointer to the original X-expression vector
 * vec_y a pointer to the original Y-expression vector
 * s a pointer to the square we are considering to partition
 * ss a pointer to a vector of squares that cannot be further split
 *
 * returns nothing; values computed from pointers to original
 */
void APMI_split(vector<short> pts, vector<float> *vec_x, vector<float> *vec_y, square *s, vector<square> *ss) {
	// expected counts for chi-square, thresholds for potential partition of
	// square
	const float E = s->n_samps / 4.0, 
	      x_thresh = (s->x_bound1 + s->x_bound2)/2.0, 
	      y_thresh = (s->y_bound1 + s->y_bound2)/2.0;

	// vector of indices for quadrants, to test chi-square
	vector<short> tr_pts, br_pts, bl_pts, tl_pts;

	// points that belong to each quandrant are discovered and sorted
	for (auto &p : pts) {
		if ((*vec_x)[p] >= x_thresh && (*vec_y)[p] >= y_thresh) {
			tr_pts.push_back(p);
		} else if ((*vec_x)[p] >= x_thresh && (*vec_y)[p] <= y_thresh) {
			br_pts.push_back(p);
		} else if ((*vec_x)[p] <= x_thresh && (*vec_y)[p] <= y_thresh) {
			bl_pts.push_back(p);
		} else {
			tl_pts.push_back(p);
		}
	}
	
	// if we have less points in the square than
	if (s->n_samps < size_thresh) {ss->push_back(*s); return;}

	// if we have the initial square, we must partition once
	if (s->n_samps == vec_x->size()) {goto partition;}

	// compute chi-square
	float chisq = pow(tr_pts.size() - E, 2)/E +
		pow(br_pts.size() - E, 2)/E +
		pow(bl_pts.size() - E, 2)/E +
		pow(tl_pts.size() - E, 2)/E;

	if (chisq > q_thresh) {
	partition: 
		square tr{x_thresh, s->x_bound2, y_thresh, s->y_bound2, tr_pts.size()}, 
		       br{x_thresh, s->x_bound2, s->y_bound1, y_thresh, br_pts.size()}, 
		       bl{s->x_bound1, x_thresh, s->y_bound1, y_thresh, bl_pts.size()}, 
		       tl{s->x_bound1, x_thresh, y_thresh, s->y_bound2, tl_pts.size()};

		APMI_split(tr_pts, vec_x, vec_y, &tr, ss);
		APMI_split(br_pts, vec_x, vec_y, &br, ss);
		APMI_split(bl_pts, vec_x, vec_y, &bl, ss);
		APMI_split(tl_pts, vec_x, vec_y, &tl, ss);
	} else {
		// if we don't partition, then we add the square to the vector
		ss->push_back(*s);
	}
}

// Takes in two expression vectors (regulator-target) and computes APMI for
// each partition of the observation space
//
// vec_x an X expression vector
// vec_y a Y experssion vector
// q_thresh q-value for chi-square bin independence
// size_thresh minimum points in a tile to consider chi-square and partition
//
// returns a vector of all MI values computed in the observation space
//
// [[Rcpp::export]]
vector<float> APMI(vector<float> vec_x, vector<float> vec_y, float q_thresh = 7.815, unsigned short size_thresh = 4) {
	// Set global variables
	::size_thresh = size_thresh;
	::q_thresh = q_thresh;

	// Make a 
	//
	// CHANGE PTS AS UNSIGNED SHORT * TO WORK WITH APMI RECURSE
	const unsigned short n_tot = vec_x.size();
	const short pts[vec_x.size()];
	for (short i = 0; i < n_tot; i++) { pts[i] = i; }


	vector<square> squares;
	// q_thresh should be a variable
	// matrix and list of regulators
	square s{0.0, 1.0, 0.0, 1.0, n_tot};	
	APMI_split(pts, &vec_x, &vec_y, &s, &squares);
	tot_squares = squares.size();

	float mi_vals[squares.size()], mi;
	short i = 0;
	
	for (auto sq : squares) {
		const float pxy = sq.n_samps/(float) n_tot, marginal = sq.x_bound2 - sq.x_bound1;
		mi_vals[i] = isfinite(mi = pxy*log(pxy/marginal/marginal)) ? mi : 0.0;
		++i;
	}
	vector<float> mi_vec(mi_vals, &mi_vals[squares.size()]);
	return mi_vec;
}

int main() {}
