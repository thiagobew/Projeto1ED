#include "MatrixReader.h"
using namespace structures;

int main(int argc, char const *argv[])
{
    DDLinkedList<DDLinkedList<int>*>* lista = new DDLinkedList<DDLinkedList<int>*>();
    DDLinkedList<int>* row1 = new DDLinkedList<int>();
    DDLinkedList<int>* row2 = new DDLinkedList<int>();

    for (int i = 0; i < 2; i++) {
        row1->push_back(i);
        row2->push_back(i);
    }
    lista->push_back(row1);
    lista->push_back(row2);
    
    MatrixReader* reader = new MatrixReader(lista);
    lista->clear();
    delete lista;
    return 0;
}