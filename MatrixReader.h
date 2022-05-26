#include "dataStructures/DDLinkedList.h"

using namespace structures;

struct Point {
    int row;
    int column;
};

class MatrixReader {
    public:
        MatrixReader(DDLinkedList<DDLinkedList<int>*>*  &matrix) {
            __matrix = matrix; 
            __componentsQuant = calculateComponentsQuant();
        };
        ~MatrixReader();
        int getComponentsQuant() {
            return __componentsQuant;
        }
    private:
        int __componentsQuant;
        DDLinkedList<DDLinkedList<int>*>*  __matrix;
        int calculateComponentsQuant() {
            // Upgrade
            return 0;
        };
        void processPoint(struct Point &point) {
            // Upgrade
        };
        DDLinkedList<Point> getActiveNeighbors(struct Point &point) {
            // Upgrade
            DDLinkedList<Point> lista;
            return lista;
        };
        bool isActivePoint(struct Point &point) {
            // Upgrade
            return true;
        };
        bool isValidPoint(struct Point &point) {
            // Upgrade
            return true;
        };

};


