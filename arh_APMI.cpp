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
typedef struct {const float x_bound1, x_bound2, y_bound1, y_bound2; const unsigned long n_samps;} square;

void APMI_split(vector<short> pts, vector<double> *vec_x, vector<double> *vec_y, square *s, vector<square> *ss) {
	const float E = s->n_samps / 4.0, 
	      x_thresh = (s->x_bound1 + s->x_bound2)/2.0, 
	      y_thresh = (s->y_bound1 + s->y_bound2)/2.0;

	if (s->n_samps < size_thresh) {ss->push_back(*s); return;}

	vector<short> tr_pts, br_pts, bl_pts, tl_pts;

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

	float chisq = pow(tr_pts.size() - E, 2)/E +
		pow(br_pts.size() - E, 2)/E +
		pow(bl_pts.size() - E, 2)/E +
		pow(tl_pts.size() - E, 2)/E;

	if (chisq > q_thresh) {
		square tr{x_thresh, s->x_bound2, y_thresh, s->y_bound2, tr_pts.size()}, 
		       br{x_thresh, s->x_bound2, s->y_bound1, y_thresh, br_pts.size()}, 
		       bl{s->x_bound1, x_thresh, s->y_bound1, y_thresh, bl_pts.size()}, 
		       tl{s->x_bound1, x_thresh, y_thresh, s->y_bound2, tl_pts.size()};

		APMI_split(tr_pts, vec_x, vec_y, &tr, ss);
		APMI_split(br_pts, vec_x, vec_y, &br, ss);
		APMI_split(bl_pts, vec_x, vec_y, &bl, ss);
		APMI_split(tl_pts, vec_x, vec_y, &tl, ss);
	} else {
		ss->push_back(*s);
	}
}

// WRAPPER for external use
// takes in two vectors, p-value and size thresholds
// returns vector of MI values for each region
// [[Rcpp::export]]
vector<double> APMI(vector<double> vec_x, vector<double> vec_y, double p_thresh = 0.05, unsigned short size_thresh = 4) {
	::size_thresh = size_thresh;

	vector<short> pts;
	for (short i = 0; i < vec_x.size(); i++) {
		pts.push_back(i);
	}
	unsigned short n_tot = pts.size();

	vector<square> squares;
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
	vector<double> mi_vec(mi_vals, &mi_vals[squares.size()])
	return mi_vec;
}
