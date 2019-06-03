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
	Matrix* matrixify_current_vals() {
		Matrix* m = new Matrix(1, int(neurons.size()), 0);
		for (int c = 0; c < int(neurons.size()); c++) {
			m->set_val(0, c, neurons[c]->get_current_val());
		}
		return m;
	}
	Matrix* matrixify_activated_vals() {
		Matrix* m = new Matrix(1, int(neurons.size()), 0);
		for (int c = 0; c < int(neurons.size()); c++) {
			m->set_val(0, c, neurons[c]->get_activated_val());
		}
		return m;
	}
	Matrix* matrixify_derived_vals() {
		Matrix* m = new Matrix(1, int(neurons.size()), 0);
		for (int c = 0; c < int(neurons.size()); c++) {
			m->set_val(0, c, neurons[c]->get_derived_val());
		}
		return m;
	}
	int get_size() { return size; }
	double get_activated_val(int index) {
		return neurons[index]->get_activated_val();
	}

private:
	int size;
	vector<Neuron*> neurons;
};

#endif // !LAYER_H
