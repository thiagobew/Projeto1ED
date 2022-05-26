#include "dataStructures/DDLinkedList.h"
#include "iostream"

using namespace structures;
using namespace std;

class MatrixReader {
    public:
        MatrixReader(DDLinkedList<DDLinkedList<int>*>*  &matrix) {
            __matrix = matrix;
            __rows = matrix->size();
            __columns = matrix->at(0)->size();
            __componentsQuant = calculateComponentsQuant();
            __closed_nodes = DDLinkedList<Point>();
        };
        ~MatrixReader();
        int getComponentsQuant() {
            return __componentsQuant;
        }
    private:
        class Point {
            public:
                Point(int row, int column) {
                    __row = row;
                    __column = column;
                }
                bool operator!=(Point otherPoint) {
                    if (__row != otherPoint.__row || __column != otherPoint.__column) return true;
                    return false;
                }
                int __row;
                int __column;
        };

        int __componentsQuant;
        int __rows;
        int __columns;
        DDLinkedList<Point> __closed_nodes;
        DDLinkedList<DDLinkedList<int>*>*  __matrix;
        int calculateComponentsQuant() {
            int quant = 0;
            for (size_t i = 0; i < __rows; i++) {
                for (size_t j = 0; j < __columns; j++) {
                    Point point = Point(i, j);

                    if (!__closed_nodes.contains(point)) {
                        processPoint(point);
                        quant++;
                    }
                }
            }
            return quant;
        };
        void processPoint(Point &point) {
            // Upgrade
        };

  DDLinkedList<Point> getActiveNeighbors(Point &point) {
    DDLinkedList<Point> lista;

    Point* side_positions[4];
    side_positions[0]->__row = point.__row + 1;
    side_positions[0]->__column = point.__column;
    side_positions[1]->__row = point.__row;
    side_positions[1]->__column = point.__column + 1;
    side_positions[2]->__row = point.__row;
    side_positions[2]->__column = point.__column - 1;
    side_positions[4]->__row = point.__row - 1;
    side_positions[4]->__column = point.__column;

    for (int i = 0; i < 4; i++) {
        if (isValidPoint(*side_positions[i]) && isActivePoint(*side_positions[i])) {
            lista.push_back(*side_positions[i]);
        }
    }

    return lista;
  };
  bool isActivePoint(Point &point) {
    return __matrix->at(point.__row)->at(point.__column) == 1;
  };

  bool isValidPoint(Point &point) {
    if (point.__row < 0 || point.__row >= __rows) {
      return false;
    }

    if (point.__column < 0 || point.__column >= __columns) {
      return false;
    }

    return true;
  };
};
