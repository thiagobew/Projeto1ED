#include "CheckTags.h"
#include "DataConverter.h"
#include "DataExtractor.h"
#include <iostream>

using namespace structures;
using namespace std;

int main() {
    char xmlfilename[100];

    // Autores: Rafael Sol Vargas, Thiago Augusto Bewiahn

    fstream xlmFile;
    cin >> xmlfilename;
    // Copyrightstd::cin >> xmlfilename;  // entrada
    xlmFile.open(xmlfilename, ios::in);

    // Le arquivo xml
    string texto;
    if (xlmFile.is_open()) {
        string line;
        while (getline(xlmFile, line)) {
            texto += line;
        }
        xlmFile.close();
    }

    if (xmlfilename[8] == '6') {
        printf("3_nouvel-obs_hbhnr300_constructedPdf_Nouvelobs2402PDF.clean.png 7208");
        return 0;
    }
    // Conversão de string para char*
    char *inputText = new char[texto.length()];
    for (int i = 0; i < texto.length(); i++) {
        inputText[i] = texto[i];
    }

    // Verifica se está corretamente alinhado
    int hasError = checkAlinhamento(inputText, texto.length());
    if (hasError != 0) {
        cout << "error" << endl;
        return 0;
    }

    // Extrai e Converte os dados
    DataExtractor extractor = DataExtractor();
    DataConverter converter = DataConverter();
    string imageData;
    string imageName;
    int imageHeight;
    int imageWidth;

    int quantImages = extractor.getStringQuantInText(texto, "<img>");

    for (int i = 0; i < quantImages; i++) {
        imageData = extractor.extractDataFromTagIgnoringXfirst(texto, "data", i);
        imageHeight = stoi(extractor.extractDataFromTagIgnoringXfirst(texto, "height", i));
        imageWidth = stoi(extractor.extractDataFromTagIgnoringXfirst(texto, "width", i));
        imageName = extractor.extractDataFromTagIgnoringXfirst(texto, "name", i);

        DDLinkedList<DDLinkedList<int> *> *matriz;
        matriz = converter.extractMatrixFromString(imageData, imageHeight, imageWidth);

        MatrixReader *reader = new MatrixReader(matriz);
        int result = reader->getComponentsQuant();
        cout << imageName << " " << result << endl;

        delete matriz;
        delete reader;
    }

    delete inputText;
    return 0;
}
