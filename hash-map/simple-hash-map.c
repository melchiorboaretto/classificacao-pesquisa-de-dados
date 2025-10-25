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
bool resize_on_new(SimpleHashTable** table_ref, int new_size);
bool resize_in_situ(SimpleHashTable* table, int new_size);
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
    int initial_index = key % table->size;
    int index = initial_index;

    if (table->dicionario[index] != key) {
        while (table->dicionario[index] != key) {
            if (++index == table->size) {
                index = 0;
            }

            if (index == initial_index) {
                return -1;
            }
        }
    }

    table->dicionario[index] = -1;
    table->used[index] = false;
    free(table->conteudo[index]);
    table->conteudo[index] = malloc(5*sizeof(char));
    strcpy(table->conteudo[index], "None");

    return 0;
}

// modifica tamanho da tabela criando nova tabela (retorna true se conseguir)
bool resize_on_new(SimpleHashTable** table_ref, int new_size) {
    // seu codigo aqui

    SimpleHashTable *old_table = *table_ref;
    SimpleHashTable *new_tableptr = malloc(sizeof(SimpleHashTable));
    if (new_tableptr == NULL) {
        return false;
    }

    int *new_dictptr = malloc(sizeof(int) * new_size);
    if (new_dictptr == NULL) {
        free(new_tableptr);
        return false;
    }

    char **new_contentptr = malloc(sizeof(char *) * new_size);
    if (new_contentptr == NULL) {
        free(new_tableptr);
        free(new_dictptr);
        return false;
    }

    bool *new_usedptr = malloc(sizeof(bool) * new_size);
    if (new_usedptr == NULL) {
        free(new_tableptr);
        free(new_dictptr);
        free(new_contentptr);
        return false;
    }

    // Initializing the new vectors
    for (int i = 0; i < new_size; i++) {
        new_dictptr[i] = -1;
        new_usedptr[i] = false;
    }

    memcpy(new_dictptr, old_table->dicionario, old_table->size * sizeof(int));
    memcpy(new_contentptr, old_table->conteudo, old_table->size * sizeof(char *));
    memcpy(new_usedptr, old_table->used, old_table->size * sizeof(bool));

    for (int i = 0; i < new_size; i++) {
        if (new_contentptr[i] == NULL) {
            new_contentptr[i] = malloc(5 * sizeof(int));
            strcpy(new_contentptr[i], "None");
        }
    }

    free(old_table->dicionario);
    free(old_table->conteudo);
    free(old_table->used);

    (*table_ref)->dicionario = new_dictptr;
    (*table_ref)->conteudo = new_contentptr;
    (*table_ref)->used = new_usedptr;

    (*table_ref)->size = new_size;

    return true;
}

// modifica tamanho da tabela nela mesmo (retorna true se conseguir)
bool resize_in_situ(SimpleHashTable* table, int new_size) {
    // seu codigo aqui
    return false;
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
