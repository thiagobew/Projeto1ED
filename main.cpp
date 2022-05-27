#include "MatrixReader.h"
using namespace structures;

int main(int argc, char const *argv[]) {
    DDLinkedList<DDLinkedList<int> *> *lista = new DDLinkedList<DDLinkedList<int> *>();
    DDLinkedList<int> *row1 = new DDLinkedList<int>();
    DDLinkedList<int> *row2 = new DDLinkedList<int>();
    DDLinkedList<int> *row3 = new DDLinkedList<int>();

    row1->push_back(1);
    row1->push_back(0);
    row1->push_back(1);

    row2->push_back(0);
    row2->push_back(0);
    row2->push_back(1);

    row3->push_back(1);
    row3->push_back(0);
    row3->push_back(0);

    lista->push_back(row1);
    lista->push_back(row2);
    lista->push_back(row3);

    MatrixReader *reader = new MatrixReader(lista);
    cout << reader->getComponentsQuant() << endl;

    row1->clear();
    row2->clear();
    row3->clear();
    lista->clear();

    // delete row1;
    // delete row2;
    // delete row3;
    // delete lista;
    delete reader;
    return 0;
}
