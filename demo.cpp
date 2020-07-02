#include "layout.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>

int main(int argc, const char *argv[]) {

	if (argc < 3) {
		std::cerr << "Wrong number of the input arguments!\n";
		std::cerr << "Usage: ... ";
		std::cerr << "<input_file> <output_file> ";
		std::cerr << "[num_iter]";
		std::cerr << std::endl;
		return -1;
	}

	const size_t num_iter = ((argc > 3)? atol(argv[3]): (1));
	assert(num_iter > 0);

	std::ifstream finp(argv[1]);
	size_t num_vert, num_edge; finp >> num_vert >> num_edge;
	std::vector<std::pair<size_t, size_t>> edge;
	for (int i = 0; i < num_edge; ++ i) {
		int a, b; finp >> a >> b; edge.push_back({a, b});
	}
	finp.close();

	Layout layout(std::move(edge));
	for (int i = 0; i < num_iter; ++ i) {
		layout.run();
		const double per = (double(i + 1) / num_iter);
		std::cout << (100 * per) << "%";
		std::cout << std::endl;
	}

	std::ofstream fout(argv[2]);
	for (int i = 0; i < num_vert; ++i) {
		if (!layout.getState(i)) continue;
		auto &p = layout.getPosition(i);
		fout << p.coord[0];
		fout << "\t";
		fout << p.coord[1];
		fout << "\t";
		fout << p.coord[2];
		fout << "\n";
	}
	fout.close();

	return 0;
}
