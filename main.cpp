#include "neural_network.h"
using namespace std;
int main(){

srand((unsigned int)time(NULL));
/*
vector<int> topology;
topology.push_back(3);
topology.push_back(2);
topology.push_back(1);

vector<double> input;
input.push_back(1.0);
input.push_back(0.5);

Neural_network nn (topology);

nn.set_current_input(input);
nn.print_to_console();

cout << "\n\n\n\n\nMatrix Tests:\n";

Matrix * m = new Matrix(2, 1, 1);
cout << "Matrix m: \n";
m->print_to_console();
Matrix * m1 = new Matrix(1, 2, 1);
cout << "\nMatrix m1:\n";
m1->print_to_console();
Matrix * m_t = m->transpose();
cout << "\nMatrix m_t:\n";
m_t->print_to_console();
Matrix * m1_t = m1->transpose();
cout << "\nMatrix m1_t:\n";
m1_t->print_to_console();

Matrix * multiplicated = m->multiply(m1);
cout << "\nMatrix multiplicated: \n";
multiplicated->print_to_console();

delete m;
delete m1;
delete multiplicated;

cout << "\n\n\n\n\nBegin second tests\n\n";
vector<double> input1;
input1.push_back(1);
input1.push_back(.1);
input1.push_back(1);

vector<int>topology1;
for(int i = 3; i > 0; i--){
	topology1.push_back(i);
}

Neural_network n2(topology1);
n2.set_current_input(input1);
n2.feed_forward();
n2.print_to_console();
*/

vector<double> input3 {1, 0, 1};

vector<int> topology3 {3, 2, 3};

Neural_network * nn3 = new Neural_network(topology3);
nn3->set_current_input(input3);
nn3->set_current_target(input3);

for (int i = 0; i < 2; i++) {
	cout << "Epoch " << i << endl;
	nn3->feed_forward();
	nn3->set_errors();
	cout << "Total Error: " << nn3->get_total_error() << endl;
	nn3->back_prop();
}
delete nn3;

return 0;

}
