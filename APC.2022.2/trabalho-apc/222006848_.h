#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 256

/// Uma enum utilitária para cada um das ações\estagios possíveis do programa.
typedef enum {
  IDLE = -1,
  ADD = 1,
  READ,
  LIST_BY_CITY,
  REPORT,
  DELETE,
  EXIT
} state_t;

/// A struct que define uma query no banco de dados das pessoas cadastradas.
typedef struct {
  char cpf[MAX_LENGTH];
  char name[MAX_LENGTH];
  int sex;
  char city[MAX_LENGTH];
  char uf[MAX_LENGTH];
  char birthDate[MAX_LENGTH];
} query_person_t;

/// A struct que define uma query no banco de dados das cidades e municípios.
typedef struct {
  int id;
  char uf[MAX_LENGTH];
  char __pad[MAX_LENGTH]; // Essa string é referente ao nome da cidade com acento, mas não a utilizaremos.
  char city_univeral[MAX_LENGTH]; 
} query_city_t;

/// A função responsável por validar um nome.
bool validateName(char* str) {
  bool hasValidChar = false;

  // Leia a string, char por char.
  while ( *str != '\0' ) {
    char c = *str;

    // Checamos se a caractere atual não é alfabetica.
    if ( !( c >= 'a' && c <= 'z' ) && !( c >= 'A' && c <= 'Z' ) ) {
      // Caso ela também não seja um whitepace, teremos que essa caractere é
      // uma caractere especial ou um número, invalidando o nome.
      if ( c != ' ' ) {
        return false;
      }
    }

    // Caso contrário, podemos afirmar que o nome tem no mínimo uma caractere alfabetica.
    else {
      hasValidChar = true;
    }

    str++;
  }

  return hasValidChar;
}

/// A função responsável por validar um CPF baseado no algoritmo Módulo 11.
bool validateCPF(char* cpf) {
  // Primeiro checamos se a string não tem exatamente 11 caracteres. Dessa
  // forma descartamos CPFs inválidos ou com formatação.
  if (strlen(cpf) != 11) {
    return false;
  }

  int digits[11];

  // Convertemos os digitos do CPF para inteiros.
  for (int i = 0; i < 11; i++) {
    // Caso achemos uma caractere que não seja um número, então
    // o CPF é invalido.
    if (!(cpf[i] >= '0' && cpf[i] <= '9')) {
      return false;
    }

    digits[i] = (int)cpf[i] - '0';
  }

  int result = 0;
  int multiplier = 2;

  for (int i = 8; i >= 0; i--) {
    result += digits[i] * multiplier++;
  }

  // Checamos se o primeiro digito não é igual o digito que calculamos.
  if (digits[9] != ( result * 10 ) % 11) {
    return false;
  }

  result = 0;
  multiplier = 2;

  for (int i = 9; i >= 0; i--) {
    result += digits[i] * multiplier++;
  }

  // E também checamos se o segundo digito é condizente.
  if (digits[10] != ( result * 10 ) % 11) {
    return false;
  }

  return true;
}

/// A função responsável por validar datas.
bool validateDate(char* str) {
  // Se a string da data nâo possuí exatamente dez caracteres, então
  // ela está formatada errado ou não tem digitos o suficiente.
  if (strlen(str) != 10) {
    return false;
  }

  char* temp = strdup(str);

  int year, month, day;

  // Pegamos a data atual.
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  // Caso a conversão do tempo não seja sucedida, a data é invalida.
  if (sscanf(str, "%d-%d-%d", &day, &month, &year) == EOF) {
    free(temp);
    return false;
  }
  
  free(temp);

  // Caso o ano de nascimento seja menor do que 1900 ou maior do que o ano atual, 
  // ele é invalido.
  if (year < 1900 || year > 1900 + tm.tm_year ) {
    return false;
  }

  // Caso o mes seja menor do que um e maior do que doze, ou que estejamos no ano atual e
  // o mês está afrente do mês atual, a data é invalida.
  if (month < 1 || month > 12 || ( year - 1900 == tm.tm_year && month - 1 > tm.tm_mon )) {
    return false;
  }

  // Mesmo processo para os dias, considerando as diferentes
  // quantidades de dias para cada mês. Não é levado em consideração
  // anos bissextos.
  if (
    ( month == 1 && ( day < 1 || day > 31 ) ) ||
    ( month == 2 && ( day < 1 || day > 28 ) ) ||
    ( month == 3 && ( day < 1 || day > 31 ) ) ||
    ( month == 4 && ( day < 1 || day > 30 ) ) ||
    ( month == 5 && ( day < 1 || day > 31 ) ) ||
    ( month == 6 && ( day < 1 || day > 30 ) ) ||
    ( month == 7 && ( day < 1 || day > 31 ) ) ||
    ( month == 8 && ( day < 1 || day > 31 ) ) ||
    ( month == 9 && ( day < 1 || day > 30 ) ) ||
    ( month == 10 && ( day < 1 || day > 31 ) ) ||
    ( month == 11 && ( day < 1 || day > 30 ) ) ||
    ( month == 12 && ( day < 1 || day > 31 ) ) ||
    ( year - 1900 == tm.tm_year && month - 1 == tm.tm_mon && day > tm.tm_mday ) 
  ) {
    return false;
  }

  return true;
}

/// A funcao responsavel por receber uma data em forma de string
/// e retornar a idade da pessoa.
int getAge( char* dateStr ) {
  int year, month, day;

  char* temp = strdup(dateStr);

  // Pegamos a data atual.
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  // Caso a conversão do tempo não seja sucedida, a data é invalida.
  if (sscanf(dateStr, "%d-%d-%d", &day, &month, &year) == EOF) {
    free(temp);
    return false;
  }
  
  free(temp);
  
  // Calculamos a idade baseado apenas nos anos.
  int age = ( tm.tm_year + 1900 ) - year - 1;

  // Depois checamos se a pessoa ja realizou seu aniversario
  // este ano.
  if ( month < tm.tm_mon + 1 )
    age++;
  
  else if( month == tm.tm_mon + 1 && day <= tm.tm_mday )
    age++;

  return age;
}


/// A funcao utilitaria responsavel por realizar
/// o sort de uma lista de strings utilizando o 
/// algoritmo Bubble Sort.
void sortStrings(char arr[][MAX_LENGTH], int n) {
    char temp[MAX_LENGTH];

    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-1-i; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], temp);
            }
        }
    }
}
