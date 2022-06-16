#include "MatrixReader.h"
#include "dataStructures/LinkedStack.h"
using namespace structures;

int checkAlinhamento(const char *texto) {
  char *topo;
  int erro = 0;
  LinkedStack<char *> *stack = new LinkedStack<char *>();
  int length = strlen(texto);

  for (int i = 0; i < length - 1 && erro == 0; i++) {
    if (texto[i] == '<') {
      char *charWithTag = new char[20];

      int j = i + 1;
      while (texto[j] != '>' && j < length && texto[j] != '\0') {
        charWithTag[j] = texto[j];
        j++;
      }

      stack->push(charWithTag);
    } else if (texto[i] == '<' && texto[i + 1] == '/') {
      if (stack->empty()) {
        erro = 2;
      } else {
        char *closingTag = new char[20];

        int h = i + 2;
        while (texto[h] != '>' && h < length && texto[h] != '\0') {
          closingTag[h] = texto[h];
          h++;
        }

        topo = stack->pop();
        if (strcmp(topo, closingTag) != 0) {
          erro = 1;
        }
        delete closingTag;
      }
    }
  }
  if (erro == 0 && !stack->empty()) {
    erro = 3;
  }

  stack->clear();
  delete stack;
  return erro;
}

int main(int argc, char const *argv[]) {
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
