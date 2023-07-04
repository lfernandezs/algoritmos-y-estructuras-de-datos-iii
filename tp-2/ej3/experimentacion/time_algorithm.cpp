#include "../modems.cpp"

#define UNION_BY_RANK 0
#define UNION_BY_SIZE 1
#define WITHOUT_PATH_COMPRESSION 2

void time_algorithm(int method, string input_path, string output_path) {
	ifstream input_file(input_path);
    ofstream output_file(output_path);
    int n;
    input_file >> n;
    output_file << "n,time" << endl;
    chrono::high_resolution_clock::time_point start, stop;
    pair<chrono::high_resolution_clock::time_point, chrono::high_resolution_clock::time_point> result;
    for (int i=0; i<n; i++) {
        switch (method)
        {
        case UNION_BY_RANK:
            result = modems_union_by_rank(input_file);
            start = result.first;
            stop = result.second;
            break;

        case UNION_BY_SIZE:
            result = modems_union_by_size(input_file);
            start = result.first;
            stop = result.second;
            break;

        case WITHOUT_PATH_COMPRESSION:
            result = modems_without_path_compression(input_file);
            start = result.first;
            stop = result.second;
            break;
        }
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
