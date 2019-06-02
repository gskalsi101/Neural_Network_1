#include "neural_network.h"
int main(){
srand((unsigned int)time(NULL));

vector<int> topology;
topology.push_back(3);
topology.push_back(2);
topology.push_back(3);

vector<double> input;
input.push_back(1.0);
input.push_back(0.0);
input.push_back(1.0);

Neural_network nn (topology);

nn.set_current_input(input);
nn.print_to_console();

return 0;
}
