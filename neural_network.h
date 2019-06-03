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

	void feed_forward() {
		for (int i = 0; i < int(layers.size() - 1); i++) {
			cout << "\n\nLayer: " << i << endl;
			Matrix* vals = nullptr;
			(i == 0) ? vals = layers[i]->matrixify_current_vals() : vals = layers[i]->matrixify_activated_vals();
			cout << "Vals\n";
			vals->print_to_console();
			Matrix* weight_matrix = weight_matrices[i];
			cout << "\nWeight Matrix\n";
			weight_matrix->print_to_console();
			Matrix* c = vals->multiply(weight_matrix);
			cout << "\nMultiplicated Matrix\n";
			c->print_to_console();	
			for (int c_index = 0; c_index < c->get_num_cols(); c_index++) {//Set current values for next layer
				layers[i + 1]->set_val(c_index, c->get_val(0, c_index));
			}
		}
	}

	void print_to_console() {
		for (int i = 0; i < int(layers.size()); i++) {
			cout << "Layer: " << i << endl;
			if (i == 0) {
				Matrix* m = layers[i]->matrixify_current_vals();
				m->print_to_console();
			}
			else {
				Matrix* m = layers[i]->matrixify_activated_vals();
				m->print_to_console();
			}
			cout << "==================\n";
			if (i < int(layers.size() - 1)) {
				cout << "Weight of layer: " << i << endl;
				weight_matrices[i]->print_to_console();
				cout << "==================\n";
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
