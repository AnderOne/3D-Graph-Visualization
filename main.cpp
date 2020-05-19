#include "forcelayout.cc/layout.h"
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
	Graph graph;

	std::ifstream finp(argv[1]);
	size_t num_vert, num_edge; finp >> num_vert >> num_edge;
	for (int i = 0; i < num_vert; ++ i) graph.addNode(i);
	for (int i = 0; i < num_edge; ++ i) {
		int a, b; finp >> a >> b; graph.addLink(a, b);
	}
	finp.close();

	ForceLayout<3> layout(graph);
	for (int i = 0; i < num_iter; ++ i) {
		layout.step();
		const double per = (double(i + 1) / num_iter);
		std::cout << (100 * per) << "%" << std::endl;
	}

	std::ofstream fout(argv[2]);
	for (int i = 0; i < num_vert; ++i) {
		const auto* body = layout.getBody(i);
		assert(body);
		fout << body->pos.coord[0];
		fout << "\t";
		fout << body->pos.coord[1];
		fout << "\t";
		fout << body->pos.coord[2];
		fout << "\n";
	}
	fout.close();

	return 0;
}
