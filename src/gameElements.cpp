#include <iostream>
#include "shape.h"
#include "Window.h"
#include "gameElements.h"

using namespace std;


vector<index> gameBackground(int canvasSize[]) {
  int m = canvasSize[0]; // Width
  int n = canvasSize[1]; // Height
  index idx;
  vector<index> indices;

  // Left border
  idx.y = 0;
  for (int i = 0; i < m; i++) {
    idx.x = i;
    indices.push_back(idx);
  }

  // Right border
  idx.y = (n - 1);
  for (int i = 0; i < m; i++) {
    idx.x = i;
    indices.push_back(idx);
  }

  return indices;
}