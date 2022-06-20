#include "CheckTags.cpp"
#include "DataConverter.h"
#include "DataExtractor.h"

using namespace structures;
using namespace std;

int main() {
    char xmlfilename[100];

    fstream xlmFile;
    // Copyrightstd::cin >> xmlfilename;  // entrada
    xlmFile.open("data/dataset2.xml", ios::in);

    // Le arquivo xml
    string texto;
    if (xlmFile.is_open()) {
        string line;
        while (getline(xlmFile, line)) {
            texto += line;
        }
        xlmFile.close();
    }

    // Conversão de string para char*
    char *inputText = new char[texto.length()];
    for (int i = 0; i < texto.length(); i++) {
        inputText[i] = texto[i];
    }

    // Verifica se está corretamente alinhado
    int hasError = checkAlinhamento(inputText, texto.length());
    printf("Error Quant = %d\n", hasError);
    if (hasError == 0) {
        printf("XML válido!\n");
    } else {
        return 0;
        printf("XML inválido!\n");
    }

    // Extrai e Converte os dados
    DataExtractor extractor = DataExtractor();
    DataConverter converter = DataConverter();
    string imageData;
    int imageHeight;

    int quantImages = extractor.getStringQuantInText(texto, "<img>");

    for (int i = 0; i < quantImages; i++) {
        imageData = extractor.extractDataFromTagIgnoringXfirst(texto, "data", i);
        imageHeight = stoi(extractor.extractDataFromTagIgnoringXfirst(texto, "height", i));

        DDLinkedList<DDLinkedList<int> *> *matriz;
        matriz = converter.extractMatrixFromString(imageData, imageHeight);

        MatrixReader *reader = new MatrixReader(matriz);
        int result = reader->getComponentsQuant();
        cout << "Quant Componentes da Matrix " << i + 1 << ": " << result << endl;

        delete matriz;
        delete reader;
    }

    delete inputText;
    return 0;
}

