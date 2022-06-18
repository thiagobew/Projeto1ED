#include "dataStructures/DDLinkedList.h"
#include "iostream"

using namespace structures;
using namespace std;

class MatrixReader {
public:
    MatrixReader(DDLinkedList<DDLinkedList<int> *> *&matrix) {
        __matrix = matrix;
        __rows = matrix->size();
        __columns = matrix->at(0)->size();
        __componentsQuant = calculateComponentsQuant();
        __closed_nodes = DDLinkedList<Point>();
    };
    ~MatrixReader() {
        __closed_nodes.clear();
        delete __matrix;
    }
    int getComponentsQuant() {
        return __componentsQuant;
    }

private:
    class Point {
    public:
        int __row;
        int __column;
        Point() {
            __row = 0;
            __column = 0;
        }

        Point(int row, int column) {
            __row = row;
            __column = column;
        }

        bool operator!=(Point otherPoint) {
            if (__row != otherPoint.__row || __column != otherPoint.__column)
                return true;
            return false;
        }
    };

    int __componentsQuant;
    int __rows;
    int __columns;
    DDLinkedList<Point> __closed_nodes;
    DDLinkedList<DDLinkedList<int> *> *__matrix;

    int calculateComponentsQuant() {
        int quant = 0;
        for (size_t i = 0; i < __rows; i++)
            for (size_t j = 0; j < __columns; j++) {
                Point point = Point(i, j);
                if (isActivePoint(point)) {
                    if (!__closed_nodes.contains(point)) {
                        processPoint(point);
                        quant++;
                    }
                }
            }
        return quant;
    };

    void processPoint(Point &point) {
        DDLinkedList<Point> open_nodes = DDLinkedList<Point>();
        open_nodes.push_front(point);

        while (open_nodes.size() > 0) {
            Point current = open_nodes.pop_front();
            DDLinkedList<Point> neighbors = getActiveNeighbors(current);

            for (size_t i = 0; i < neighbors.size(); i++) {
                Point neighbor = neighbors.pop_front();

                if ((!open_nodes.contains(neighbor)) && (!__closed_nodes.contains(neighbor))) {
                    open_nodes.push_front(neighbor);
                }
            }

            __closed_nodes.push_front(current);
        }
    };

    DDLinkedList<Point> getActiveNeighbors(Point &point) {
        DDLinkedList<Point> lista;

        Point side_pos[4];
        side_pos[0] = Point(point.__row + 1, point.__column);
        side_pos[1] = Point(point.__row, point.__column + 1);
        side_pos[2] = Point(point.__row - 1, point.__column);
        side_pos[3] = Point(point.__row, point.__column - 1);

        for (int i = 0; i < 4; i++) {
            if (isValidPoint(side_pos[i]) && isActivePoint(side_pos[i])) {
                lista.push_back(side_pos[i]);
            }
        }

        return lista;
    };

    bool isActivePoint(Point &point) {
        return __matrix->at(point.__row)->at(point.__column) != 0;
    };

    bool isValidPoint(Point &point) {
        if (point.__row < 0 || point.__row >= __rows)
            return false;

        if (point.__column < 0 || point.__column >= __columns)
            return false;

        return true;
    };
};
