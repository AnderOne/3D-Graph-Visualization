#pragma once
#include "forcelayout.cc/layout.h"
#include <memory>

struct Layout {

	Layout(const LayoutSettings &settings, const std::vector<int> &used, const std::vector<std::pair<size_t, size_t>> &edge, const std::vector<Vector3<3>> &point): Layout(settings, used, edge) {

		for (int i = 0; i < used.size(); ++ i) { if (used[i]) _layout->setPosition(i, point[i]); }
	}

	Layout(const std::vector<int> &used, const std::vector<std::pair<size_t, size_t>> &edge, const std::vector<Vector3<3>> &point):
	Layout(LayoutSettings(), used, edge, point) {}

	Layout(const LayoutSettings &settings, const std::vector<int> &used, const std::vector<std::pair<size_t, size_t>> &edge) {

		for (int i = 0; i < used.size(); ++ i) { if (used[i]) _graph.addNode(i); }
		for (int i = 0; i < edge.size(); ++ i) {
			int b = edge[i].second;
			int a = edge[i].first;
			if (used[a] && used[b]) { _graph.addLink(a, b); }
		}
		_layout = std::make_shared<ForceLayout<3>>(
		_graph, settings
		);
	}

	Layout(const std::vector<int> &used, const std::vector<std::pair<size_t, size_t>> &edge):
	Layout(LayoutSettings(), used, edge) {}

	const Vector3<3> &get(size_t id) const { return _layout->getBody(id)->pos; }

	void run(size_t num = 1) {
		for (size_t t = 0; t < num; ++ t) { _layout->step(); }
	}

private:
	mutable std::shared_ptr<ForceLayout<3>> _layout;
	Graph _graph;
};
