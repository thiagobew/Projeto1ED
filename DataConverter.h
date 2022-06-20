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

    DDLinkedList<DDLinkedList<int> *> *extractMatrixFromString(string inputText, int numberOfRows, int numberOfColumns) {
        DDLinkedList<DDLinkedList<int> *> *matrix = new DDLinkedList<DDLinkedList<int> *>();

        for (int i = 0; i < numberOfRows; i++) {
            DDLinkedList<int> *row = new DDLinkedList<int>();
            matrix->push_back(row);
        }

        int dataLen = inputText.length();
        size_t currentRow = 0;
        for (size_t i = 0; i < dataLen; i++) {
            currentRow = i / numberOfColumns;
            // Conversão de char para int
            // int value = (int)inputText[i] - 48;
            matrix->at(currentRow)->push_back((int)inputText[i] - 48);
        }

        return matrix;
    }
};
