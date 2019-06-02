#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "layer.h"

class Neural_network {
public:
	Neural_network(vector<int> &topology){
		this->topology = topology;
		for (int i = 0; i < int(topology.size()); i++) {
			layers.push_back(new Layer(topology[i]));
		}
		for (int i = 0; i < int(topology.size() - 1); i++) {
			weight_matrices.push_back(new Matrix(topology[i], topology[i + 1], 1));
		}
	}

	void set_current_input(vector<double> &input) {
		current_input = input;
		for (int n = 0; n < int(input.size() ); n++) {
			layers[0]->set_val(n, input[n]);
		}
	}

	void print_to_console() {
		for (int i = 0; i < int(layers.size()); i++) {
			cout << "Layer " << i << endl;
			if (i == 0) {
				Matrix* m = layers[i]->maxtixify_current_vals();
				m->print_to_console();
			}
			else {
				Matrix* m = layers[i]->maxtixify_activated_vals();
				m->print_to_console();
			}
		}

	}
private:
	vector<int> topology;
	vector<Layer*> layers;
	vector<Matrix*> weight_matrices;
	vector<double> current_input;
};

#endif // !NEURAL_NETWORK_H
