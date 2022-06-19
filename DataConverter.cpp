#include "MatrixReader.h"
#include <iostream>
#include <string>

using namespace structures;
using namespace std;

class DataConverter {
public:
    DataConverter(){};
    ~DataConverter() {
    }

    DDLinkedList<DDLinkedList<int> *> *extractMatrixFromString(string inputText, int rowsQuant) {
        DDLinkedList<DDLinkedList<int> *> *matrix = new DDLinkedList<DDLinkedList<int> *> *();

        for (int i = 0; i < inputText.length(); i++) {
            string subString = inputText.substr(i, tagName.length());
            if (subString == tagName)
                quant++;
        }

        return quant;
    }
}
