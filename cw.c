#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int count_words(const char *sentence) {
    int count = 0, in_word = 0;

    while (*sentence) {
        if (isspace(*sentence) || *sentence == ',' || *sentence == '.') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        sentence++;
    }

    return count;
}

int compare_sentences(const void *a, const void *b) {
    const char **sentence1 = (const char **)a;
    const char **sentence2 = (const char **)b;

    int words1 = count_words(*sentence1);
    int words2 = count_words(*sentence2);

    return words2 - words1; 
}

void sort_sentences(char **sentences, int sentence_count) {
    qsort(sentences, sentence_count, sizeof(char *), compare_sentences);
}
void process_dollar(char **sentences, int sentence_count) {
    int i;
    for (i = 0; i < sentence_count; ++i) {
        char *sentence = sentences[i];
        char *new_sentence = malloc(strlen(sentence) + 1); 
        int new_index = 0; 
        int first_dollar = -1, last_dollar = -1; 
        int j;

        for (j = 0; sentence[j] != '\0'; ++j) {
            if (sentence[j] == '$') {
                if (first_dollar == -1) {
                    first_dollar = j;
                }
                last_dollar = j; 
            }
        }

        if (first_dollar == -1) {
            strcpy(new_sentence, sentence);
        } else if (first_dollar == last_dollar) {
            for (j = 0; sentence[j] != '\0'; ++j) {
                if (j != first_dollar) {
                    new_sentence[new_index++] = sentence[j];
                }
            }
            new_sentence[new_index] = '\0';
        } else {
            for (j = 0; j < first_dollar; ++j) {
                new_sentence[new_index++] = sentence[j];
            }
            for (j = last_dollar + 1; sentence[j] != '\0'; ++j) {
                new_sentence[new_index++] = sentence[j];
            }
            new_sentence[new_index] = '\0';
        }

        free(sentences[i]);
        sentences[i] = new_sentence;
    }
}
char **split_text_by_sentences(int *sentence_count) {
    char **sentences = NULL;      
    char *text = NULL;             
    size_t text_size = 0;         
    size_t sentence_capacity = 0;  
    char buffer[256];             
    *sentence_count = 0;

    printf("Введите текст. Завершите ввод двумя Enter:\n");
    int empty_line_count = 0;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strcmp(buffer, "\n") == 0) {
            empty_line_count++;
            if (empty_line_count == 2) {
                break;  
            }
        } else {
            empty_line_count = 0; 
        }

        size_t buffer_len = strlen(buffer);
        if (buffer[buffer_len - 1] == '\n') {
            buffer[buffer_len - 1] = ' ';
        }

        text = realloc(text, text_size + buffer_len + 1);
        if (!text) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
        strcpy(text + text_size, buffer);
        text_size += buffer_len;
    }
    char *token = strtok(text, ".");
    while (token != NULL) {
        while (isspace((unsigned char)*token)) {
            token++;
        }
        char *end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end)) {
            *end = '\0';
            end--;
        }

        if (*token == '\0') {
            token = strtok(NULL, ".");
            continue;
        }

        if (*sentence_count >= sentence_capacity) {
            sentence_capacity = (sentence_capacity == 0) ? 10 : sentence_capacity * 2;
            sentences = realloc(sentences, sentence_capacity * sizeof(char *));
            if (!sentences) {
                fprintf(stderr, "Ошибка выделения памяти для предложений\n");
                free(text);
                exit(1);
            }
        }
        sentences[*sentence_count] = malloc(strlen(token) + 1);
        if (!sentences[*sentence_count]) {
            fprintf(stderr, "Ошибка выделения памяти для предложения\n");
            free(text);
            exit(1);
        }
        strcpy(sentences[*sentence_count], token);
        (*sentence_count)++;
        token = strtok(NULL, ".");
    }

    free(text);
    return sentences;
}
void remove_even_indices(char **sentences, int *sentence_count) {
    int i, new_index = 0;
    for (i = 0; i < *sentence_count; ++i) {
        if (i % 2 != 0) {
            sentences[new_index++] = sentences[i];
        } else {
            free(sentences[i]);
        }
    }

    *sentence_count = new_index;
}
void count_and_display_characters(char **sentences, int sentence_count) {
    int counts[256] = {0};
    int seen[256] = {0};
    int i, j;

    printf("\n#############\n");

    for (i = 0; i < sentence_count; ++i) {
        const char *sentence = sentences[i];
        for (j = 0; sentence[j] != '\0'; ++j) {
            unsigned char c = sentence[j];
            if (!isspace(c) && c != ',' && c != '.') {
                if (counts[c] == 0) {
                    seen[c] = 1;
                }
                counts[c]++;
            }
        }
    }

    for (i = 0; i < 256; ++i) {
        if (counts[i] > 0 && seen[i]) {
            printf("%c: %d\n", (char)i, counts[i]);
        }
    }
}

int compare_ignore_case(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

void remove_duplicates(char **sentences, int *sentence_count) {
    int i, j, k;

    for (i = 0; i < *sentence_count; ++i) {
        if (sentences[i] == NULL) {
            continue;
        }

        for (j = i + 1; j < *sentence_count; ++j) {
            if (sentences[j] != NULL && compare_ignore_case(sentences[i], sentences[j])) {
                free(sentences[j]);
                sentences[j] = NULL;
            }
        }
    }

    k = 0;
    for (i = 0; i < *sentence_count; ++i) {
        if (sentences[i] != NULL) {
            sentences[k++] = sentences[i];
        }
    }
    *sentence_count = k;
}
int menu() {
    int choice;
    printf("\nВыберите операцию:\n");
    printf("1) Удалить символы до первого '$' и после последнего '$'.\n");
    printf("2) Отсортировать предложения по уменьшению количества слов.\n");
    printf("3) Вывести все символы в тексте и их количество.\n");
    printf("4) Удалить все предложения с чётным индексом.\n");
    printf("Введите номер операции: ");
    if (scanf("%d", &choice) != 1) {
        printf("Ошибка: некорректный ввод.\n");
        return -1;
    }
    return choice;
}
void print_sentences(char **sentences, int sentence_count) {
    printf("\nТекущий список предложений:\n");
    int i;
    for (i = 0; i < sentence_count; i++) {
        printf("[%s]\n", sentences[i]);
    }
}
int main() {
    int sentence_count = 0;
    char **sentences = split_text_by_sentences(&sentence_count);
    printf("\nОбработка повторяющихся строк...:\n");
    print_sentences(sentences, sentence_count);
    remove_duplicates(sentences, &sentence_count);
    printf("\nРазбитый текст после обработки повторяющихся строк:\n");
    print_sentences(sentences, sentence_count);
    int i;
    int choice = menu();
    if (choice == -1) {
        for (i = 0; i < sentence_count; i++) {
            free(sentences[i]);
        }
        free(sentences);
        return 1;
    }

    switch (choice) {
        case 1:
            process_dollar(sentences, sentence_count);
            break;
        case 2:
            sort_sentences(sentences, sentence_count);
            break;
        case 3:
            count_and_display_characters(sentences, sentence_count);
            break;
        case 4:
            remove_even_indices(sentences, &sentence_count);
            break;
        default:
            printf("Ошибка: некорректный номер операции.\n");
            break;
    }

    print_sentences(sentences, sentence_count);

    for (i = 0; i < sentence_count; i++) {
        free(sentences[i]);
    }
    free(sentences);

    return 0;
}

