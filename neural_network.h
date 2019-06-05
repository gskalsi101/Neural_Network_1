#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "layer.h"
#include <algorithm>

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
		errors.resize(topology[topology.size() - 1]);
	}

	void set_current_input(vector<double> &input) {
		current_input = input;
		for (int n = 0; n < int(input.size() ); n++) {
			layers[0]->set_val(n, input[n]);
		}
	}

	void feed_forward() {
		for (int i = 0; i < int(layers.size() - 1); i++) {
			//cout << "\n\nLayer: " << i << endl;
			Matrix* vals = nullptr;
			(i == 0) ? vals = layers[i]->matrixify_current_vals() : vals = layers[i]->matrixify_activated_vals();
			//cout << "Vals\n";
			//vals->print_to_console();
			Matrix* weight_matrix = weight_matrices[i];
			//cout << "\nWeight Matrix\n";
			//weight_matrix->print_to_console();
			//cout << "Vals dimentions: " << vals->get_num_rows() << 'x' << vals->get_num_cols() << endl;
			//cout << "weight_matrix dimentions: " << weight_matrix->get_num_rows() << 'x' << weight_matrix->get_num_cols() << endl;

			Matrix* c = vals->multiply(weight_matrix);
			//cout << "\nMultiplicated Matrix\n";
			//c->print_to_console();	
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

	double get_total_error() { return total_error; }

	const vector <double> & get_errors() { return errors; }

	void set_current_target(vector <double>& target_in) {
		target = target_in;
	}

	//Assumes vector<double>target are already updated
	void set_errors() {
		try {
			if (target.size() < 1) { throw 0; }
			else if ( int(target.size()) != layers[layers.size() - 1]->get_size()) { throw 'q'; }
			total_error = 0.0;
			for (int i = 0; i < int(target.size()); i++) {
			//Get 
				double temp = layers[layers.size() - 1]->get_activated_val(i) - target[i];
				errors[i] = temp;
				total_error += abs(temp);
			}
			historical_errors.push_back(total_error);
		}
		catch (int x) {
			cerr << "Exception thrown.  No target for this neural network";
		}
		catch (char w) {
			cerr << "Exception thrown.  Target size of " << target.size() << " doesn''t equal Output Layer size of " << layers[layers.size() - 1]->get_size() << endl;
		}
		return;
	}

	void back_prop() {
		vector <Matrix*> new_weights;
		Matrix *gradient;
		/*				First back_prop, from output to first hidden layer
		-------------------------------------------------------------------------------------------------------
		*/
		//output to hidden
		int output_layer_index = int(layers.size()) - 1;
		//Matrix of the derived vals of the last layer
		Matrix* derived_vals_y_to_z = layers[output_layer_index]->matrixify_derived_vals();

		Matrix* gradient_y_to_z = new Matrix(1, layers[output_layer_index]->get_size(), 0) ;
		
		//populate gradient_y_to_z with derived_val * error
		for (int i = 0; i < int(errors.size()); i++) {
			double d = derived_vals_y_to_z->get_val(0, i);
			double e = errors[i];
			double g = d * e;
			gradient_y_to_z->set_val(0, i, g);
		}
		int last_hidden_layer_index = output_layer_index - 1;
		Layer* last_hidden_layer = layers[last_hidden_layer_index];
		Matrix* weight_output_to_hidden = weight_matrices[output_layer_index - 1];

		Matrix * gradient_y_to_z_transpose = gradient_y_to_z->transpose();
		Matrix* last_hidden_layer_matrix = last_hidden_layer->matrixify_activated_vals();

		Matrix* delta_output_to_first_hidden_temp = gradient_y_to_z_transpose->multiply(last_hidden_layer_matrix);
		Matrix* delta_output_to_first_hidden = delta_output_to_first_hidden_temp->transpose();

		Matrix* new_weights_output_to_hidden = new Matrix(delta_output_to_first_hidden->get_num_rows(),
														  delta_output_to_first_hidden->get_num_cols(),
														  0
														  );
		for (int r = 0; r < delta_output_to_first_hidden->get_num_rows(); r++) {
			for (int c = 0; c < delta_output_to_first_hidden->get_num_cols(); c++) {
				double original_weight = weight_output_to_hidden->get_val(r, c);
				double delta_weight = delta_output_to_first_hidden->get_val(r, c);
				new_weights_output_to_hidden->set_val(r, c, original_weight - delta_weight);
			}
		}
		new_weights.push_back(new_weights_output_to_hidden);

		//Copy gradietn_t_to_z into gradient
		gradient = new Matrix(gradient_y_to_z->get_num_rows(), gradient_y_to_z->get_num_cols(), 0);
		for (int r = 0; r < gradient_y_to_z->get_num_rows(); r++) {
			for (int c = 0; c < gradient_y_to_z->get_num_cols(); c++) {
				gradient->set_val(r, c, gradient_y_to_z->get_val(r, c));
			}
		}

		//new_weights_output_to_hidden->print_to_console();
		delete delta_output_to_first_hidden_temp;
		delete gradient_y_to_z_transpose;
		delete last_hidden_layer_matrix;

		/*
		The rest of back_prop, from the hidden layers, one before, recusively going towards the input layer (exclusive)
		*/

		//start from the second to last gradient, then work towards the first
		for (int i = output_layer_index - 1; i > 0; i--) {
			Layer* l = layers[i];
			//Matrix* derived_hidden = l->matrixify_derived_vals();
			Matrix* activated_hidden = l->matrixify_activated_vals();
			Matrix* derived_gradients = new Matrix(1, l->get_size(), 0);

			Matrix* weight_matrix = weight_matrices[i];
			Matrix* original_weight = weight_matrices[i - 1];

			for (int r = 0; r < weight_matrix->get_num_rows(); r++) {
				double sum = 0.0;
				for (int c = 0; c < weight_matrix->get_num_cols(); c++) {
					double temp1 = (gradient->get_val(0, c)) * (weight_matrix->get_val(r, c));
					sum += temp1;
				}
				double g = sum * activated_hidden->get_val(0, r);
				derived_gradients->set_val(0, r, g);
			}
			
			Matrix* left_neurons = (i - 1 == 0) ? layers[i - 1]->matrixify_current_vals() : layers[i - 1]->matrixify_activated_vals();
			Matrix* temp3 = derived_gradients->transpose();
			Matrix* delta_weights = temp3->multiply(left_neurons);
			delete temp3;
			Matrix* new_weights_hidden = new Matrix(delta_weights->get_num_rows(), delta_weights->get_num_cols(), 0);
			for (int r = 0; r < new_weights_hidden->get_num_rows(); r++) {
				for (int c = 0; c < new_weights_hidden->get_num_cols(); c++) {
					double d = delta_weights->get_val(r, c);
					double w = original_weight->get_val(r, c);
					double n = w - d;
					new_weights_hidden->set_val(r, c, n);
				}
			}
			new_weights.push_back(new_weights_hidden);
			gradient = new Matrix(derived_gradients->get_num_rows(), derived_gradients->get_num_cols(), 0);
			for (int r = 0; r < derived_gradients->get_num_rows(); r++) {
				for (int c = 0; c < derived_gradients->get_num_cols(); c++) {
					gradient->set_val(r, c, derived_gradients->get_val(r, c));
				}
			}
		}
		cout << "Done with back prop" << endl;
		cout << "New Weight size: " << new_weights.size() << endl;
		cout << "Old Weight size: " << weight_matrices.size() << endl;
		reverse(new_weights.begin(), new_weights.end());
		weight_matrices = new_weights;
	}

private:
	vector<int> topology;
	vector<Layer*> layers;
	vector<Matrix*> weight_matrices;
	vector<Matrix*> gradient_matrices;
	vector<double> current_input;
	vector<double> target;
	vector<double> errors;
	vector<double> historical_errors;
	double total_error;
};

#endif // !NEURAL_NETWORK_H
