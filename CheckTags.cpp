#include "dataStructures/LinkedStack.h"
#include <cstring>

using namespace structures;

int getTagSize(const char *texto, int max_len, int start) {
    int i = start;
    int size = 0;
    while (texto[i] != '>' && i < max_len && texto[i] != '\0') {
        size++;
        i++;
    }

    return size;
}

int checkAlinhamento(const char *texto) {
    char *topo;
    int erro = 0;
    LinkedStack<char *> *stack = new LinkedStack<char *>();
    int length = strlen(texto);

    for (int i = 0; i < length - 1 && erro == 0; i++) {
        // Se é uma abertura de tag
        if (texto[i] == '<') {
            char *charWithTag = new char[20];

            int j = i + 1;
            while (texto[j] != '>' && j < length && texto[j] != '\0') {
                charWithTag[j] = texto[j];
                j++;
            }

            stack->push(charWithTag);
            // Se é uma fechadura de tag
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

int main() { return 0; }
