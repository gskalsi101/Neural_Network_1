#include "neural_network.h"
int main(){

srand((unsigned int)time(NULL));

vector<int> topology;
topology.push_back(3);
topology.push_back(2);
topology.push_back(3);

vector<double> input;
input.push_back(1.0);
input.push_back(0.5);
input.push_back(1.0);

Neural_network nn (topology);

nn.set_current_input(input);
nn.print_to_console();

cout << "\n\n\n\n\nMatrix Tests:\n";

Matrix * m = new Matrix(4, 2, 1);
cout << "Matrix m: \n";
m->print_to_console();
Matrix * m1 = new Matrix(2, 4, 1);
cout << "\nMatrix m1:\n";
m1->print_to_console();
Matrix * m_t = m->transpose();
cout << "\nMatrix m_t:\n";
m_t->print_to_console();
Matrix * m1_t = m1->transpose();
cout << "\nMatrix m1_t:\n";
m1_t->print_to_console();

Matrix * try1 = m->multiply(m);
cout << "\nMatrix try1: \n";
try1->print_to_console();

delete m;
delete m1;
delete try1;

return 0;

}
