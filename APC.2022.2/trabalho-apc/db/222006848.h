#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <memory.h>

#ifndef DATABASE_APC_HH
#define DATABASE_APC_HH
#define DATABASE_FIELD_MAX 10
#define DATABASE_LINE_LENGTH_MAX 256

/// 'database_field_type_t'
/// O enum responsável por denifir os tipos dentro da schema
/// do nosso banco de dados.
typedef enum {
  DBEND = -1,
  DBINT,
  DBBOOL,
  DBSTRING,
} database_field_type_t;

/// 'database_t'
/// A struct responsável por guardar todas as informações
/// referentes a um banco de dados.
typedef struct {

  /// O arquivo responsável por guardar as informações dessa instância de banco
  /// de dados.
  FILE* m_file;

  /// O caminho do arquivo de banco de dados.
  char m_filePath[256];

  /// Representa a schema do nosso banco de dados CSV. Ajuda a organizar e validar os valores
  /// inseridos e lidos pelo sistema.
  database_field_type_t m_schema[DATABASE_FIELD_MAX];

  /// A caractere delimitadora do nosso arquivo CSV.
  char* m_delim;

} database_t;

/// Cria uma nova instância do banco de dados.
bool db_new( database_t* db, const char* filePath, 
    database_field_type_t schema[DATABASE_FIELD_MAX] ); 

/// Lê uma linha qualquer do nosso banco de dados e a salva dentro de um buffer. Retorna verdadeiro caso
/// a linha exista e seja válida.
bool db_read_line_raw( database_t* db, char* buffer, int lineNumber );

/// Lê uma linha qualquer do banco de dados, faz a conversão dos dados para os tipos especificados
/// pela a schema e os salva dentro do buffer, uma struct que representa uma query qualquer. Retorna
/// verdadeiro caso a linha exista e seja válida.
bool db_read_line( database_t* db, void* buffer, int lineNumber, size_t schemaSize );

/// Escreve/adiciona uma linha no banco de dados.
bool db_write_line_raw( database_t* db, const char* data );

/// Escreve/adiciona uma query/struct qualquer no banco de dados.
bool db_write_line( database_t* db, void* data, size_t schemaSize );

/// Faça uma query/pesquisa no banco de dados dada uma colúna específica.
bool db_find_query_by_column( database_t* db, void* buffer, const char* query, int columnNumber, size_t schemaSize, int* lineResult );

/// Reescreve o banco de dados sem a linha selecionada.
bool db_delete_line( database_t*, int lineNumber, const char* fileName );

/// Fecha uma instância existente de um banco de dados.
bool db_close( database_t* db );

#endif
