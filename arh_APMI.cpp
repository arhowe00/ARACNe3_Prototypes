// [[Rcpp::depends(BH)]]
// [[Rcpp::plugins("cpp11")]]

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <boost/math/distributions/chi_squared.hpp>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

static float q_thresh = 7.815;
static unsigned short size_thresh, tot_squares;
typedef struct {float x_bound1, x_bound2, y_bound1, y_bound2; unsigned long n_samps;} square;

void APMI_split(vector<short> pts, vector<double> *vec_x, vector<double> *vec_y, square *p, vector<square> *ps) {
	float E = p->n_samps / 4.0;
	float x_thresh = (p->x_bound1 + p->x_bound2)/2.0;
	float y_thresh = (p->y_bound1 + p->y_bound2)/2.0;

	if (p->n_samps < size_thresh) {ps->push_back(*p); return;}

	vector<short> pts1, pts2, pts3, pts4;

	for (short &p : pts) {
		if ((*vec_x)[p] >= x_thresh && (*vec_y)[p] >= y_thresh) {
			pts1.push_back(p);
		} else if ((*vec_x)[p] >= x_thresh && (*vec_y)[p] <= y_thresh) {
			pts2.push_back(p);
		} else if ((*vec_x)[p] <= x_thresh && (*vec_y)[p] <= y_thresh) {
			pts3.push_back(p);
		} else {
			pts4.push_back(p);
		}
	}

	float chisq = pow(pts1.size() - E, 2)/E +
		pow(pts2.size() - E, 2)/E +
		pow(pts3.size() - E, 2)/E +
		pow(pts4.size() - E, 2)/E;

	if (chisq > q_thresh) {
		square tr{x_thresh, p->x_bound2, y_thresh, p->y_bound2, pts1.size()};
		square br{x_thresh, p->x_bound2, p->y_bound1, y_thresh, pts2.size()};
		square bl{p->x_bound1, x_thresh, p->y_bound1, y_thresh, pts3.size()};
		square tl{p->x_bound1, x_thresh, y_thresh, p->y_bound2, pts4.size()};

		APMI_split(pts1, vec_x, vec_y, &tr, ps);
		APMI_split(pts2, vec_x, vec_y, &br, ps);
		APMI_split(pts3, vec_x, vec_y, &bl, ps);
		APMI_split(pts4, vec_x, vec_y, &tl, ps);
	} else {
		ps->push_back(*p);
	}
}

float* APMIptr(vector<double> vec_x, vector<double> vec_y, double p_thresh = 0.05, unsigned short size_thresh = 4) {
	::size_thresh = size_thresh;

	vector<short> pts;
	for (short i = 0; i < vec_x.size(); i++) {
		pts.push_back(i);
	}
	unsigned short n_tot = pts.size();

	vector<square> squares;
	square p{0.0, 1.0, 0.0, 1.0, n_tot};
	APMI_split(pts, &vec_x, &vec_y, &p, &squares);
	tot_squares = squares.size();

	float *mi_vals = static_cast<float*>(malloc(squares.size() * sizeof(float))), mi;
	short i = 0;
	for (auto sq : squares) {
		const float pxy = sq.n_samps/(float) n_tot, marginal = sq.x_bound2 - sq.x_bound1;
		mi_vals[i] = isfinite(mi = pxy*log(pxy/marginal/marginal)) ? mi : 0.0;
		++i;
	}
	return mi_vals;
}

// WRAPPER for external use
// takes in two vectors, p-value and size thresholds
// returns vector of MI values for each region
// [[Rcpp::export]]
vector<double> APMI(vector<double> vec_x, vector<double> vec_y, double p_thresh = 0.05, unsigned short size_thresh = 4) {
	float *mis = APMIptr(vec_x, vec_y, p_thresh, size_thresh);
	vector<double> returnvec;
	for (auto i = 0; i < tot_squares; ++i) {returnvec.push_back(mis[i]);}
	free(mis);
	return returnvec;
}
