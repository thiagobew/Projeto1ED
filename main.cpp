#include "CheckTags.cpp"
#include "DataConverter.cpp"
#include "DataExtractor.cpp"

using namespace structures;
using namespace std;

int main() {
    char xmlfilename[100];

    fstream xlmFile;
    // Copyrightstd::cin >> xmlfilename;  // entrada
    xlmFile.open("data/dataset1.xml", ios::in);

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
    int imageWidth;

    int quantImages = extractor.getStringQuantInText(texto, "<img>");

    for (int i = 0; i < quantImages; i++) {
        imageData = extractor.extractDataFromTagIgnoringXfirst(texto, "data", i);
        imageHeight = stoi(extractor.extractDataFromTagIgnoringXfirst(texto, "height", i));
        imageWidth = stoi(extractor.extractDataFromTagIgnoringXfirst(texto, "width", i));

        DDLinkedList<DDLinkedList<int> *> *matriz;
        matriz = converter.extractMatrixFromString(imageData, imageHeight, imageWidth);

        /* printf("Matriz\n");
        while (matriz->size() > 0) {
            DDLinkedList<int> *row = matriz->pop_front();

            while (row->size() > 0) {
                printf("%d", row->pop_front());
            }
            printf("\n");
        } */

        MatrixReader *reader = new MatrixReader(matriz);
        int result = reader->getComponentsQuant();
        cout << "Quant Componentes da Matrix " << i + 1 << ": " << result << endl;

        delete matriz;
        delete reader;
    }

    delete inputText;
    return 0;
}

/* int main(int argc, char const *argv[]) {
  DDLinkedList<DDLinkedList<int> *> *lista =
      new DDLinkedList<DDLinkedList<int> *>();
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
 */