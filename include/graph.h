#pragma once 

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

#define W_WIDTH 1280
#define W_HEIGHT 720
#define X_1 

class Graph {
  public:
    struct Node {
      int id;
      float x, y;
      std::vector<std::pair<int, float>> neighbors;
      Node(int id, float x, float y) : id(id), x(x), y(y) {}
    };

    struct Edge {
      int from;
      int to;
      float width;
      Edge(int from, int to, float width) : from(from), to(to), width(width) {}
    };

    Graph();

    int add_node(float x, float y);
    void add_edge(int from, int to, float width = 20.f);

    std::vector<Node> get_nodes() const { return nodes; }
    std::vector<Edge> get_edges() const { return edges; }

    void draw(sf::RenderWindow& window);

  private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};
