#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int size;
    int* dicionario;     // chaves
    char** conteudo;     // dados (strings)
    bool* used;          // status (true se ocupado)
} SimpleHashTable;

// Prototipos
SimpleHashTable* create_table(int size);
void destroy_table(SimpleHashTable* table);
int add(SimpleHashTable* table, int key, const char* data);
char* get(SimpleHashTable* table, int key);
int remove_key(SimpleHashTable* table, int key);
void resize_on_new(SimpleHashTable** table_ref, int new_size);
void resize_in_situ(SimpleHashTable* table, int new_size);
void print_table(SimpleHashTable* table);


// Método Construtor (inicializa a SimpleHashTable com o tamanho indicado)
SimpleHashTable* create_table(int size) {
    SimpleHashTable* table = (SimpleHashTable*)malloc(sizeof(SimpleHashTable));
    table->size = size;
    table->dicionario = (int*)malloc(size * sizeof(int));
    table->conteudo = (char**)malloc(size * sizeof(char*));
    table->used = (bool*)malloc(size * sizeof(bool));

    for (int i = 0; i < size; i++) {
        table->dicionario[i] = -1;
        table->conteudo[i] = (char *)malloc(5 * sizeof(char));
        strcpy(table->conteudo[i], "None");
        table->used[i] = false;
    }

    return table;
}

// Método Destrutor (libera memória alocada)
void destroy_table(SimpleHashTable* table) {
    for (int i = 0; i < table->size; i++)
        free(table->conteudo[i]);
    free(table->dicionario);
    free(table->conteudo);
    free(table->used);
    free(table);
}

// Método add (adiciona um elemento (data) na tabela, associando-o a uma chave (key)
// e retorna a posição onde foi colocado ou -1 se não conseguiu colocar
int add(SimpleHashTable* table, int key, const char* data) {
    // seu codigo aqui
    int initial_index = key % table->size;
    int index = initial_index;

    if (table->used[index]) {
        while (table->used[index]) {
            if (++index == table->size) {
                index = 0;
            }

            if (index == initial_index) {
                return -1;
            }
        }
    }

    // Se chegou aqui eh porque ja tem o indice certo e garante
    // que a tabela nao ta cheia

    table->used[index] = true;
    table->dicionario[index] = key;

    if (table->conteudo[index] != NULL) {
        free(table->conteudo[index]);
    }

    table->conteudo[index] = malloc(strlen(data) + 1);
    strcpy(table->conteudo[index], data);

    return 0;

}

// Método get (recupera o conteúdo (data) associado a uma chave (key) e retorna o conteúdo ou None se não achou)
char* get(SimpleHashTable* table, int key) {
    // seu codigo aqui
    int initial_index = key % table->size;
    int index = initial_index;

    if (table->dicionario[index] != key) {
        while (table->dicionario[index] != key) {
            if (++index == table->size) {
                index = 0;
            }

            if (index == initial_index) {
                return "None";
            }
        }
    }

    return table->conteudo[index];
}

// Método que remove um elemento da tabela (retorna a posição onde estava ou -1 se não achou)
int remove_key(SimpleHashTable* table, int key) {
    // seu codigo aqui
}

// modifica tamanho da tabela criando nova tabela (retorna true se conseguir)
void resize_on_new(SimpleHashTable** table_ref, int new_size) {
    // seu codigo aqui
}

// modifica tamanho da tabela nela mesmo (retorna true se conseguir)
void resize_in_situ(SimpleHashTable* table, int new_size) {
    // seu codigo aqui
}

// Mostra conteúdo da tabela (para depuração)
void print_table(SimpleHashTable* table) {
    printf("-----------------------------------\n");
    printf("(pos)[key] = %-15s (%s)\n", "data", "used");
    printf("-----------------------------------\n");

    for (int i = 0; i < table->size; i++) {
        printf("(%03d)[%03d] = %-15s (%s)\n",
               i,
               table->dicionario[i],
               table->conteudo[i],
               table->used[i] ? "true" : "false");
    }
}

int main() {
    SimpleHashTable* hash_table = create_table(10);
    char buffer[20];

    for (int i = 0; i < 20; i++) {
        sprintf(buffer, "valor %d", i);
        if (add(hash_table, i, buffer) != -1)
            printf("valor %d inserido com sucesso.\n", i);
        else
            printf("ERRO ao inserir valor %d!\n", i);
    }

    print_table(hash_table);

    destroy_table(hash_table);
    return 0;
}
