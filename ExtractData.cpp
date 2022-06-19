#include "MatrixReader.h"
#include <iostream>
#include <string>

using namespace structures;
using namespace std;

class DataExtractor {
public:
    DataExtractor(){};
    ~DataExtractor() {
    }

    int getStringQuantInText(string inputText, string tagName) {
        int quant = 0;
        for (int i = 0; i < inputText.length(); i++) {
            string subString = inputText.substr(i, tagName.length());
            if (subString == tagName)
                quant++;
        }

        return quant;
    }

    void extractListFromImg(string imgText) {
        char *inputChar = new char[imgText.length()];
        for (int i = 0; i < imgText.length(); i++) {
            inputChar[i] = imgText[i];
        }

        if (checkAlinhamento(inputChar, imgText.length()) != 0) {
            printf("Invalid Img Text\n");
            return;
        }

        int quant = getStringQuantInText(imgText, "<img>");
        for (int i = 0; i < quant; i++) {
            string dataText = extractDataFromTagIgnoringXfirst(imgText, "data", i);
            printf("Img number %d:\n", i + 1);
            cout << dataText << endl;
        }

        DDLinkedList<DDLinkedList<int> *> *lista = new DDLinkedList<DDLinkedList<int> *>();

        DDLinkedList<int> *row1 = new DDLinkedList<int>();
        DDLinkedList<int> *row2 = new DDLinkedList<int>();
        DDLinkedList<int> *row3 = new DDLinkedList<int>();
    }

private:
    int getSizeToTagEnd(string inputText, int maxLength, int start) {
        int i = start;
        int size = 0;
        while (inputText[i] != '>' && i < maxLength && inputText[i] != '\0') {
            size++;
            i++;
        }

        return size;
    }

    char convertStringToChar(string stringText) {
        char charText[stringText.length()];

        for (int i = 0; i < stringText.length(); i++) {
            charText[i] = stringText[i];
        }

        return *charText;
    }

    string extractStringFromText(string inputText, int start, int size) {
        int real_index = start;
        string outPalavra;
        for (int i = 0; i < size; i++) {
            outPalavra.resize(outPalavra.size() + 1);
            outPalavra[i] = inputText[real_index];
            real_index++;
        }

        return outPalavra;
    }

    string extractDataFromTagIgnoringXfirst(string inputText, string tagName, int timesIgnored) {
        string outputText;
        int maxLength = inputText.size();
        int index = -1;
        bool isReading = false;
        bool ignoring = false;

        for (; index < maxLength - 1;) {
            index++;
            // Verifica se é uma tag de abertura
            if (inputText[index] == '<') {
                if (isReading)
                    return outputText;

                // Pega o tamanho da tag atual
                int quantLetters = getSizeToTagEnd(inputText, maxLength, index + 1);
                int sizeArray = quantLetters + 1;

                string openingTag = extractStringFromText(inputText, index + 1, quantLetters);
                if (openingTag == tagName) {
                    if (timesIgnored > 0) {
                        timesIgnored--;
                    } else {
                        isReading = true;
                        // Reajusta index para começar a ler
                        index += sizeArray;
                    }
                }
            } else if (isReading) {
                // Se está lendo
                outputText.resize(outputText.size() + 1);
                outputText[outputText.size() - 1] = inputText[index];
            }
        }
    }
};
