#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

struct t_rand {

	t_rand(int mod, int cur = 0): _mod(mod), _cur(cur) {}

	void set(int cur) { _cur = (cur % _mod); }

	int get() {
		constexpr int MAGIC = (1 << 17) - 1;
		return _cur = (_cur + MAGIC) % _mod;
	}

private:
	int _mod, _cur;
};

std::pair<int, int> get_edge_by_ind(int i) {
	int a = int((sqrt(1 + 8 * i) - 1) / 2) + 1, b = i - (a * (a - 1)) / 2;
	return std::make_pair(a, b);
}

int main(int argc, const char* argv[]) {

	if (argc < 4) {
		std::cerr << "Wrong number of the input arguments!\n";
		std::cerr << "Usage: ... ";
		std::cerr << "<output_file> <num_vert> <num_edge> ";
		std::cerr << "[RAND_SEED]";
		std::cerr << std::endl;
		return -1;
	}
	int num_vert = atoi(argv[2]), num_edge = atoi(argv[3]);
	int max_edge = (num_vert * (num_vert - 1)) / 2;
	if (num_edge > max_edge) num_edge = max_edge;
	t_rand rand(max_edge);
	if (argc > 4) { rand.set(atoi(argv[4])); }

	std::ofstream fout(argv[1]);
	fout << num_vert << "\n";
	fout << num_edge << "\n";
	for (int i = 0; i < num_edge; ++ i) {
		auto e = get_edge_by_ind(rand.get());
		fout << e.second;
		fout << "\t";
		fout << e.first;
		fout << "\n";
	}
	fout.close();

	return 0;
}
