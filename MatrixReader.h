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
        createSecondMatrix();
        __componentsQuant = calculateComponentsQuant();
    };
    ~MatrixReader() {
        __m2->clear();
        delete __m2;
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
    DDLinkedList<DDLinkedList<int> *> *__matrix;
    DDLinkedList<DDLinkedList<int> *> *__m2;

    int calculateComponentsQuant() {
        int quant = 0;
        for (size_t i = 0; i < __rows; i++)
            for (size_t j = 0; j < __columns; j++) {
                Point point = Point(i, j);
                if (isActivePoint(point)) {
                    // Se um ponto não está em closed nodes contará como um novo componente
                    if (!__m2->at(i)->at(j)) {
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
                Point neighbor = neighbors.at(i);

                if ((!open_nodes.contains(neighbor)) && (!__m2->at(neighbor.__row)->at(neighbor.__column))) {
                    open_nodes.push_front(neighbor);
                }
            }

            __m2->at(current.__row)->at(current.__column) = 1;
        }
    };

    void createSecondMatrix() {
        __m2 = new DDLinkedList<DDLinkedList<int> *>();

        for (int i = 0; i < __rows; i++) {
            DDLinkedList<int> *row = new DDLinkedList<int>();
            for (int j = 0; j < __columns; j++) {
                row->push_back(0);
            }
            __m2->push_back(row);
        }
    }

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
