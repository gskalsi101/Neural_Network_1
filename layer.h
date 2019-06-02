#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include "matrix.h"
#include <vector>

class Layer {
public:
	Layer(int size_in):size(size_in) {
		for (int i = 0; i < size; i++) {
			neurons.push_back(new Neuron(0.0));
		}
	}
	void set_val(int index, double val) {
		neurons[index]->set_val(val);
	}
	Matrix* maxtixify_current_vals() {
		Matrix* m = new Matrix(1, int(neurons.size()), 0);
		for (int c = 0; c < int(neurons.size()); c++) {
			m->set_val(0, c, neurons[c]->get_current_val());
		}
		return m;
	}
	Matrix* maxtixify_activated_vals() {
		Matrix* m = new Matrix(1, int(neurons.size()), 0);
		for (int c = 0; c < int(neurons.size()); c++) {
			m->set_val(0, c, neurons[c]->get_activated_val());
		}
		return m;
	}
	Matrix* maxtixify_derived_vals() {
		Matrix* m = new Matrix(1, int(neurons.size()), 0);
		for (int c = 0; c < int(neurons.size()); c++) {
			m->set_val(0, c, neurons[c]->get_derived_val());
		}
		return m;
	}

private:
	int size;
	vector<Neuron*> neurons;
};

#endif // !LAYER_H