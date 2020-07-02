#pragma once
#include "forcelayout.cc/layout.h"
#include <unordered_map>
#include <memory>

struct Layout {

	Layout(const LayoutSettings &settings, const std::vector<std::pair<size_t, size_t>> &edge): _settings(settings), _edge(edge) { init(); }

	Layout(const std::vector<std::pair<size_t, size_t>> &edge): Layout(LayoutSettings(), edge) {}

	Layout(const LayoutSettings &settings, std::vector<std::pair<size_t, size_t>> &&edge):
	       _settings(settings), _edge(std::move(edge)) { init(); }

	Layout(std::vector<std::pair<size_t, size_t>> &&edge):
	       Layout(LayoutSettings(), std::move(edge)) {}

	void setPosition(size_t id, const Vector3<3> &pos) const { _layout->setPosition(id, pos); }
	const Vector3<3> &getPosition(size_t id) const { return _layout->getBody(id)->pos; }

	void setState(size_t id, bool on) { _used[id] = on; }
	bool getState(size_t id) const { return _used[id]; }

	void update() {
		for (size_t i = 0; i < _used.size(); ++ i) { if (_used[i]) _point[i] = getPosition(i); }
		initGraph(); initLayout();
	}

	void run(size_t num = 1) {
		for (size_t t = 0; t < num; ++ t) _layout->step();
	}

private:
	void initLayout() {
		_layout = std::make_shared<ForceLayout<3>>(*_graph, _settings);
		for (const auto &p: _point) if (_used[p.first]) _layout->setPosition(p.first, p.second);
	}

	void initGraph() {

		_graph = std::make_shared<Graph>();
		for (int i = 0; i < _used.size(); ++ i) { if (_used[i]) _graph->addNode(i); }
		for (int i = 0; i < _edge.size(); ++ i) {
			int b = _edge[i].second;
			int a = _edge[i].first;
			if (_used[a] && _used[b]) { _graph->addLink(a, b); }
		}
	}

	void initPoint() {
		size_t maxId = 0; for (const auto &e: _edge) {
		maxId = std::max(maxId, std::max(e.first, e.second));
		}
		_used.resize(maxId + 1, true);
	}

	void init() {
		initPoint(); initGraph(); initLayout(); 
	}

	LayoutSettings _settings;
	mutable std::shared_ptr<ForceLayout<3>> _layout;
	std::unordered_map<size_t, Vector3<3>> _point;
	std::shared_ptr<Graph> _graph;
	std::vector<std::pair<size_t, size_t>> _edge;
	std::vector<int> _used;
};
