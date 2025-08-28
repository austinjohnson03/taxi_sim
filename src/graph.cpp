#include "graph.h"

Graph::Graph() {
  // Remove this when not testing
  int a = add_node(W_WIDTH / 2 - 200, W_HEIGHT / 2 - 200);
  int b = add_node(W_WIDTH / 2 + 200, W_HEIGHT / 2 - 200);
  int c = add_node(W_WIDTH / 2 + 200, W_HEIGHT / 2 + 200);
  int d = add_node(W_WIDTH / 2 - 200, W_HEIGHT / 2 + 200);

  add_edge(a, b);
  add_edge(b, c);
  add_edge(c, d);
  add_edge(d, a);
}

int Graph::add_node(float x, float y) {
  int id = nodes.size();
  Node new_node(id, x, y);
  nodes.push_back(new_node);
  return id;
}

void Graph::add_edge(int from, int to, float width) {
  if (from < 0 || from >= nodes.size()||
      to < 0 || to >=nodes.size()) {
    throw std::out_of_range("Invalid node ID for edge");
  }

  auto& from_neighbors = nodes[from].neighbors;
  bool exists = std::any_of(from_neighbors.begin(), from_neighbors.end(),
      [to](const std::pair<int, float>& edge) {
        return edge.first == to;
      });

  if (!exists) {
    from_neighbors.push_back({to, width});
    Edge new_edge(from, to, width);
    edges.push_back(new_edge);
  }

  auto& to_neighbors = nodes[to].neighbors; 
  exists = std::any_of(to_neighbors.begin(), to_neighbors.end(),
      [from](const std::pair<int, float>& edge) {
        return edge.first == from;
      });

  if (!exists) {
    to_neighbors.push_back({from, width});
  }
}

void Graph::draw(sf::RenderWindow& window) {
  for (const auto& edge: edges) {
    const Node& from = nodes[edge.from];
    const Node& to = nodes[edge.to];

    sf::Vector2f diff(to.x - from.x, to.y - from.y);
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float angle = std::atan2(diff.y, diff.x) * 180.f / 3.14159265f;

    sf::RectangleShape road(sf::Vector2f(length, edge.width));
    road.setOrigin(0.f, edge.width / 2.f);
    road.setPosition(from.x, from.y);
    road.setRotation(angle);
    road.setFillColor(sf::Color(100, 100, 100));

    window.draw(road);
  }

  sf::CircleShape circle(30.f);
  circle.setFillColor(sf::Color::Blue);
  circle.setOrigin(30.f, 30.f);
  for (const auto& node : nodes) {
    circle.setPosition(node.x, node.y);
    window.draw(circle);
  }
}

