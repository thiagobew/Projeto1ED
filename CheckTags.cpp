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

                // Testa se a tag bate com a ultima inserida
                char *topTag = stack->pop();
                if (strcmp(topTag, closingTag) != 0) {
                    printf("Tags diferentes %s e %s", topTag, closingTag);
                    erro = 1;
                }
                printf("Fechando Tag: %s\n", closingTag);
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
            printf("Abrindo Tag: %s\n", openingTag);
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