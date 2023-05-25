#include "../modems.cpp"
#include <chrono>

#define UNION_BY_RANK 0
#define UNION_BY_SIZE 1
#define WITHOUT_PATH_COMPRESSION 2

void time_algorithm(int method, string input_path, string output_path) {
	ifstream input_file(input_path);
    ofstream output_file(output_path);
    int n;
    input_file >> n;
    output_file << "n,time" << endl;
    for (int i=0; i<n; i++) {
        auto start = chrono::high_resolution_clock::now();
        switch (method)
        {
        case UNION_BY_RANK:
            modems_union_by_rank(input_file);
            break;

        case UNION_BY_SIZE:
            modems_union_by_size(input_file);
            break;

        case WITHOUT_PATH_COMPRESSION:
            modems_without_path_compression(input_file);
            break;
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
    output_file << i << "," << diff.count() << endl;
    }
}

int main() {
    time_algorithm(UNION_BY_RANK, "inputs/input.csv", "output_by_rank.csv");
    time_algorithm(UNION_BY_SIZE, "inputs/input.csv", "output_by_size.csv");
    time_algorithm(WITHOUT_PATH_COMPRESSION, "inputs/input.csv", "output_with_path_compression.csv");
    return 0;
}
