#include "actividades.cpp"

int main() {
    ifstream input_file; input_file.open("inputs/input");
    ofstream output_file; output_file.open("output.csv");
    actividades(input_file, output_file);
    return 0;
}