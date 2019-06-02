#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include<string>

using namespace std;
/*                   Column
		 0   1   2   3   4   5   6   7
Row #0 | * | * | * | * | * | * | * | * |
Row #1 | * | * | * | * | * | * | * | * |
Row #2 | * | * | * | * | * | * | * | * |
Row #3 | * | * | * | * | * | * | * | * |
Row #4 | * | * | * | * | * | * | * | * |
Row #5 | * | * | * | * | * | * | * | * |
Row #6 | * | * | * | * | * | * | * | * |
Row #7 | * | * | * | * | * | * | * | * |


vals[row number][column number]
*/


typedef vector<Neuron*> layer;

double generate_rand_num(double min_inclusive = 0.0, double max_exclusive = 1.0) {
	try {
		if (min_inclusive > max_exclusive) throw min_inclusive; 
		//Get the 0-1 random double.
		double base = (double(rand()) / (RAND_MAX));
		//Scale it up
		base *= (max_exclusive - min_inclusive);
		//Translate it along the real axis
		base += min_inclusive;
		return base;
	}
	catch(double ex){
		cout << "EXCEPTION: generate_rand_num(double, double).\n Error min_inclusive > max_exclusive.";
	}
	return 0.0;
}

class Matrix {
public:
	Matrix(int num_rows_in, int num_cols_in, bool is_random_in):num_rows(num_rows_in), num_cols(num_cols_in) {
		
		for (int r = 0; r < num_rows; r++) {
			vector <double> row_vals;
			row_vals.reserve(num_cols);
			for (int c = 0; c < num_cols; c++) {
				double r = 0.0;
				if (is_random_in) {r = generate_rand_num(); }
				row_vals.push_back(r);
			}
			vals.push_back(row_vals);
		}
	}

	int get_num_rows() { return num_rows; }
	int get_num_cols() { return num_cols; }

	Matrix* transpose() {
		 Matrix* m_t = new Matrix(num_cols, num_rows, 0);
		 for (int r = 0; r < num_rows; r++) {
			for (int c = 0; c < num_cols; c++){
				(m_t->vals)[c][r] = vals[r][c];
			}
		 }
		 return m_t;
	}

	void set_val(int r, int c, double value) {
		if (r < num_rows && c < num_cols) {
			vals[r][c] = value;
		}
		return;
	}

	double get_val(int r, int c) {
		if (r < num_rows && c < num_cols) {
			return vals[r][c];
		}
		else {
			return numeric_limits<double>::infinity();
		}
	}

	void print_to_console() {
		for (int r = 0; r < num_rows; r++) {
			for (int c = 0; c < num_cols; c++) {
				cout << vals[r][c] << ' ';
			}
			cout << '\n';
		}
	
	}

	Matrix* multiply(Matrix* m_r) {
		try {
			if (num_cols != m_r->get_num_rows()) {
				cout << "ERROR" << endl;
				throw ("Wrong Dimentions.  Format: A.multiply(&B) is A * B"s); 
			}
			cout << "Fuck" << endl;
			Matrix* c = new Matrix(num_rows, m_r->get_num_cols(), 0);

			for (int r1 = 0; r1 < c->get_num_rows(); r1++) {//Row New Matrix
				for (int c1 = 0; c1 < c->get_num_cols(); c1++) { //New column
					double sum = 0.0;
					for (int i = 0; i < num_cols; i++) {
						sum += get_val(r1, i) * m_r->get_val(i, c1);
					}//!Column in this, or row in m_r
					c->set_val(r1, c1, sum);
				}//!Column New Matrix
			}//!Row New Matrix
			return c;
		}

		catch (string x) {
			cout << "Catch Block" << endl;
			cout << x << endl;
			return new Matrix(0, 0, 0);
		}
	
	}

private:
	int num_rows;
	int num_cols;
	vector <vector<double>> vals;
};



#endif // !MATRIX_H





