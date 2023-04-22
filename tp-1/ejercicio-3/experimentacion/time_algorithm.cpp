#include "../actividades.cpp"
#include <chrono>

void time_algorithm(string input_path, string output_path) {
	ifstream input_file(input_path);
    ofstream output_file(output_path);
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
}

int main() {
    time_algorithm("inputs/input_sorted.csv", "output_sorted.csv");
    time_algorithm("inputs/input_unsorted.csv", "output_unsorted.csv");
    return 0;
}
