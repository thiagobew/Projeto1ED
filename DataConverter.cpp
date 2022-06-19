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

    DDLinkedList<DDLinkedList<int> *> *extractMatrixFromString(string inputText) {

        DDLinkedList<DDLinkedList<int> *> *matrix = new DDLinkedList<DDLinkedList<int> *>();

        int numberOfRows = countNumberOfRows(inputText);
        DDLinkedList<int> *array = new DDLinkedList<int>[numberOfRows];
        for (int i = 0; i < numberOfRows; i ++) {
          matrix->push_back(&array[i]);
        }

        int rowNumber = 0;
        for (int i = 0; i < inputText.length(); i++) {
          cout << inputText[i];
          if (inputText[i] == ' ') {
            rowNumber++;
            continue;
          }

          matrix->at(rowNumber)->push_back((int)inputText[i]);
        }

        return matrix;
    }

    private:
      int countNumberOfRows(string inputText) {
        int count = 0;
        for (int i = 0; i < inputText.length(); i++) {
          if (inputText[i] == ' ') {
            count++;
          }
        }
        return count;
      }
};
