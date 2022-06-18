#include "MatrixReader.h"
#include "dataStructures/LinkedStack.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace structures;
using namespace std;

void extractWordToChar(char *texto, int start, int size, char *outPalavra) {
    int real_index = start;
    for (int i = 0; i < size; i++) {
        // BIZARRO: Esses dois prints dão segmentation fault, mesmo eu usando essas variáveis
        // printf("Char: %s\n", texto[real_index]);
        // printf("Char: %s\n", outPalavra[i]);
        outPalavra[i] = texto[real_index];
        real_index++;
    }
}

void initializeArray(char *array, int size) {
    for (int index = 0; index < size; index++) {
        if (index == size - 1)
            array[index] = '\0';
        else
            array[index] = 'a';
    }
}

int getTagSize(const char *texto, int max_len, int start) {
    int i = start;
    int size = 0;
    while (texto[i] != '>' && i < max_len && texto[i] != '\0') {
        size++;
        i++;
    }

    return size;
}

int checkAlinhamento(char *texto, int length) {
    char *topo;
    int erro = 0;
    LinkedStack<char *> *stack = new LinkedStack<char *>();

    for (int i = 0; i < length - 1 && erro == 0; i++) {
        if (texto[i] == '<' && texto[i + 1] == '/') {
            // Verifica se é uma fechadura de tag
            if (stack->empty()) {
                erro = 2;
            } else {
                // Pega o tamanho da tag de fechamento
                int quantLetters = getTagSize(texto, length, i + 2);
                int sizeArray = quantLetters + 1;
                // Inicializa os valores do array de chars
                char closingTag[sizeArray];
                for (int index = 0; index < sizeArray; index++) {
                    if (index == quantLetters)
                        closingTag[index] = '\0';
                    else
                        closingTag[index] = 'a';
                }
                // Extrai a tag do texto
                extractWordToChar(texto, i + 2, quantLetters, closingTag);

                printf("Tag de fechadura: %s\n", closingTag);
                topo = stack->pop();
                if (strcmp(topo, closingTag) != 0) {
                    printf("Tags diferentes %s e %s", topo, closingTag);
                    erro = 1;
                }
            }
        } else if (texto[i] == '<') {
            // Verifica se é uma abertura de tag
            // Pega o tamanho da tag atual
            int quantLetters = getTagSize(texto, length, i + 1);
            int sizeArray = quantLetters + 1;

            // Inicializa o array de chars
            char openingTag[sizeArray];
            for (int index = 0; index < sizeArray; index++) {
                if (index == quantLetters)
                    openingTag[index] = '\0';
                else
                    openingTag[index] = 'a';
            }
            // Extrai a tag para o char criado
            extractWordToChar(texto, i + 1, quantLetters, openingTag);

            printf("Tag de abertura: %s\n", openingTag);
            stack->push(openingTag);
        }
    }
    if (erro == 0 && !stack->empty()) {
        cout << stack->top() << endl;
        erro = 3;
    }

    stack->clear();
    delete stack;
    return erro;
}

int main() {

    char xmlfilename[100];
    fstream newfile;

    // Copyrightstd::cin >> xmlfilename;  // entrada

    newfile.open("dataset1.xml", ios::in);

    string texto;
    if (newfile.is_open()) {
        string line;

        while (getline(newfile, line)) {
            texto += line;
        }

        cout << texto << endl;
        newfile.close();
    }

    char *paraCheckAlinhamento = new char[texto.length()];
    for (int i = 0; i < texto.length(); i++) {
        paraCheckAlinhamento[i] = texto[i];
    }

    int valido = checkAlinhamento(paraCheckAlinhamento, texto.length());

    cout << "Erro: " << valido << endl;

    delete paraCheckAlinhamento;
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