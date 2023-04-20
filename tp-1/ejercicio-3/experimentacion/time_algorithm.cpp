#include "../actividades.cpp"
#include <chrono>

int main() {
    ifstream input_file("inputs/input.csv");
    ofstream output_file("output.csv");
    int n;
    input_file >> n;
    output_file << "n,time" << endl;
    for (int i=0; i<n; i++) {
        auto start = chrono::high_resolution_clock::now();
        actividades_maximales(input_file);
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
    output_file << i << "," << diff.count() << endl;
    }
    return 0;
}