#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath>
using namespace std;

class Neuron {
public: 

	Neuron(double val):current_val(val), activated_val(0), derived_val(0) {
		//These set the activated_val and derived_val
		activate();
		derive();
	}

	//Fast Sigmoid function
	//f(x) = x / ( 1 + abs(x) )
	void activate() {
		activated_val = current_val / (1 + abs(current_val));
	}

	//Derivative of fast sigmoid function
	//f'(x) = f(x) * (1 - f(x))
	void derive() {
		derived_val = activated_val * (1 - activated_val);
	}

	void set_val(double val_in) {
		current_val = val_in;
		activate();
		derive();
	}

	double get_current_val() { return current_val; }
	double get_activated_val() { return activated_val; }
	double get_derived_val() { return derived_val; }
private:
	double current_val;
	double activated_val;
	double derived_val;

};


#endif // !NEURON_H
