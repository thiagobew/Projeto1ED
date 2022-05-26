#include "dataStructures/DDLinkedList.h"

using namespace structures;

struct Point {
  int row;
  int column;
};

class MatrixReader {
public:
  MatrixReader(DDLinkedList<DDLinkedList<int> *> *&matrix) {
    __matrix = matrix;
    __componentsQuant = calculateComponentsQuant();
  };
  ~MatrixReader();
  int getComponentsQuant() { return __componentsQuant; }

private:
  int __componentsQuant;
  DDLinkedList<DDLinkedList<int> *> *__matrix;
  int calculateComponentsQuant() {
    // Upgrade
    return 0;
  };
  void processPoint(struct Point &point){
      // Upgrade
  };
  DDLinkedList<Point> getActiveNeighbors(struct Point &point) {
    // Upgrade
    DDLinkedList<Point> lista;
    struct Point side_positions[4];
    side_positions[0].row = point.row + 1;
    side_positions[0].column = point.column;
    side_positions[1].row = point.row;
    side_positions[1].column = point.column + 1;
    side_positions[2].row = point.row;
    side_positions[2].column = point.column - 1;
    side_positions[4].row = point.row - 1;
    side_positions[4].column = point.column;

    for (int i = 0; i < 4; i++) {
      if (isValidPoint(side_positions[i]) && isActivePoint(side_positions[i])) {
        lista.push_back(side_positions[i]);
      }
    }

    return lista;
  };
  bool isActivePoint(struct Point &point) {
    // Upgrade
    return __matrix->at(point.row)->at(point.column) == 1;
  };
  bool isValidPoint(struct Point &point) {
    if (point.row < 0 || point.row >= __rows) {
      return false;
    }

    if (point.column < 0 || point.column >= __columns) {
      return false;
    }

    return true;
  };
};
