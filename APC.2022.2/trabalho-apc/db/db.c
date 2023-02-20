#include "222006848.h"

bool db_new( database_t* db, const char* filePath,
            database_field_type_t schema[DATABASE_FIELD_MAX] ) {

  static const char* FLAGS = "a+";

  // Abra o arquivo de banco de dados.
  FILE* file = fopen( filePath, FLAGS );

  // Imprima um erro e retorne falso caso essa
  // operacao tenha dado erro.
  if ( file == NULL ) {
    fprintf(stderr, "[DB] Erro ao criar/abrir o arquivo especificado.\n");
    return false;
  }

  // Inicialize as variaveis da struct database_t.
  db->m_file = file;
  memcpy( db->m_schema, schema, sizeof(int) * DATABASE_FIELD_MAX );
  strcpy( db->m_filePath, filePath );

  printf("[DB] Banco de dados criado com sucesso.\n");
  return true;
}

bool db_close( database_t* db ) {
  // Tente fechar o arquivo de banco de dados.
  if ( fclose( db->m_file ) == 0 ) {
    printf("[DB] Arquivo fechado com sucesso.\n");
    return true;
  }

  // Caso a operacao tenha dado erro, imprima um erro e
  // retorne falso.
  fprintf(stderr, "[DB] Erro ao fechar o arquivo do banco de dados.\n");
  return false;
}

bool db_read_line_raw( database_t* db, char* endBuffer, int lineNumber ) {
  bool found = false;
  size_t line = 1;

  // Crie um buffer para cada uma das linhas.
  char buffer[DATABASE_LINE_LENGTH_MAX];

  // Leia o arquivo linha por linha.
  while( fgets(buffer, DATABASE_LINE_LENGTH_MAX, db->m_file) ) {
    // Caso a linha atual seja igual a linha especificada,
    // copie-a dentro do nosso buffer.
    if ( line >= lineNumber ) {
      if (strcpy( endBuffer, buffer ) != NULL)
          found = true;

      break;
    }

    line++;
  }

  // Retorne o cursor para o inicio do arquivo.
  fseek(db->m_file, 0, SEEK_SET);
  return found;
}

bool db_read_line( database_t* db, void* buffer, int lineNumber, size_t schemaSize ) {
  char lineBuffer[DATABASE_LINE_LENGTH_MAX];

  // Leia os "bytes" da linha. Caso isso falhe, retorne falso.
  if (!db_read_line_raw(db, lineBuffer, lineNumber)) {
    return false;
  }

  // Caso o buffer seja nulo, isso significa que nao queremos saber
  // do conteudo da linha, portanto retorne apenas que a linha existe.
  if (buffer == NULL) {
    return true;
  }
  
  size_t offset = 0;

  for (int i = 0; i < DATABASE_FIELD_MAX; i++) {
    const database_field_type_t fieldType = db->m_schema[i];

    // Caso estejamos no final da struct/schema, pare o processo.
    if (fieldType == DBEND) {
      break;
    }

    // Cheque para saber se estamos acessando partes da memoria
    // que nos pertence.
    if (offset >= schemaSize) {
      return false;
    }

    // Pegue o token/field.
    char* str = strdup(lineBuffer);
    const char* tok = strtok(str, ";");
    size_t n = i + 1;

    while (tok && *tok) {
      if (!--n) {
        break;
      }

      tok = strtok(NULL, ";\n");
    }
    
    // Faça a conversão do token/field para o tipo especificado.
    // Logo apos convertelo, faca a manipulacao de memoria a modo
    // de salvar cada field em seu respectivo espaco de memoria
    // dentro da struct 'buffer' dada pelo usuario.
    switch (fieldType) {
      // No caso de uma string, copie-a.
      case DBSTRING:
        strcpy( ((char*)buffer + offset), tok );

        offset += DATABASE_LINE_LENGTH_MAX;
        break;

      // No caso de um inteiro, converta-o e copie-o.
      case DBINT:
        int n = atoi( tok );

        memcpy( ((char*)buffer + offset), &n, sizeof(int) );

        offset += sizeof(int);
        break;

      // No caso de uma boolean, converta-a e copie-a.
      case DBBOOL:
        bool b;

        if ( strstr( tok, "true" ) != NULL || strstr( tok, "1" ) != NULL ) {
          b = true;
        }

        else if ( strstr( tok, "false" ) != NULL || strstr( tok, "0" ) != NULL ) {
          b = false;
        }

        else {
          b = false;
        }

        memcpy( ((char*)buffer + offset), &b, sizeof(bool) );

        offset += sizeof(bool);
        break;

      default:
        break;
    }
  }

  return true;
}

bool db_write_line_raw( database_t* db, const char* data ) {
  // Tente imprimir um buffer qualquer ao arquivo.
  bool valid = fprintf(db->m_file, data) > -1;

  // Resete o cursor do arquivo.
  fseek(db->m_file, 0, SEEK_SET);

  return valid;
}

bool db_write_line( database_t* db, void* data, size_t schemaSize ) {
  size_t offset = 0;

  // Faca um for para cada um dos fields da struct especificada.
  for (int i = 0; i < DATABASE_FIELD_MAX; i++) {
    const database_field_type_t fieldType = db->m_schema[i];

    // Cheque se chegamos ao final da struct ainda.
    if (fieldType == DBEND) {
      break;
    }

    // Cheque se ainda estamos acessando partes da memoria que
    // nos pertence.
    if (offset >= schemaSize) {
      return false;
    }

    // Dependendo do tipo do field, converta-o de volta
    // para string e imprima-o no arquivo.
    switch (fieldType) {
      case DBSTRING:
        char buffer[DATABASE_LINE_LENGTH_MAX];

        if (strcpy( buffer, (char*)data + offset) == NULL) {
          fprintf(stderr, "[DB] Falha ao salvar STRING ao banco de dados.\n");
          return false;
        }

        if (i != 0) {
          fprintf(db->m_file, ";");
        }

        fprintf( db->m_file, buffer );

        offset += DATABASE_LINE_LENGTH_MAX; 
        break;

      case DBINT:
        int n = *(int*)((char*)data + offset);

        if (i != 0) {
          fprintf(db->m_file, ";");
        }

        fprintf(db->m_file, "%d", n);

        offset += sizeof(int);
        break;

      case DBBOOL:
        bool b = *(bool*)((char*)data + offset);

        if (i != 0) {
          fprintf(db->m_file, ";");
        }

        fprintf(db->m_file, "%s", b ? "true" : "false");

        offset += sizeof(bool);
        break;

      default:
        break;
    }
  }

  // Nao esqueca de pular uma linha no final.
  fprintf(db->m_file, "\n");

  // E de resetar o cursor do arquivo.
  fseek(db->m_file, 0, SEEK_SET);
  return true;
}

bool db_find_query_by_column( database_t* db, void* buffer, const char* string, int columnNumber, size_t schemaSize, int* lineResult ) {
  // Cheque se a linha e valida.
  if ( columnNumber <= 0 || columnNumber >= DATABASE_FIELD_MAX ) {
    return false;
  }

  // Crie um buffer para cada uma das linhas.
  char lineBuffer[DATABASE_LINE_LENGTH_MAX];
  size_t currentLine = 1;

  // Leia o arquivo linha por linha.
  while( db_read_line_raw( db, lineBuffer, currentLine ) ) {
    // Pegue o field desejado da linha atual.
    char* str = strdup(lineBuffer);
    const char* tok = strtok(str, ";");
    size_t n = columnNumber;

    while (tok && *tok) {
      if (!--n) {
        break;
      }

      tok = strtok(NULL, ";\n");
    }

    // Compare o field com a nossa query.
    // Caso este seja igual, entao salve as informacoes
    // dessa linha dentro da nossa struct usando 'db_read_line'.
    if ( strcmp( tok, string ) == 0 ) {
      // Caso o usuario deseje receber, tambem, a linha
      // cujo a query foi encontrada, retorne-a.
      if (lineResult != NULL)
        *lineResult = currentLine;

      return db_read_line( db, buffer, currentLine, schemaSize );
    }

    currentLine++;
  }
 
  return false;
}

bool db_delete_line( database_t* db, int lineNumber, const char* fileName ) {
  // Primeiramente abra um arquivo temporario.
  FILE* temp = fopen("db/delete.tmp", "w+");
  size_t line = 1;

  char buffer[DATABASE_LINE_LENGTH_MAX];

  // Leia o nosso banco de dados linha por linha.
  while( fgets(buffer, DATABASE_LINE_LENGTH_MAX, db->m_file) ) {
    // Caso a linha atual nao seja igual a linha que queremos deletar,
    // imprima esta linha no arquivo temporario. Fazemos isso para ignorar
    // a linha que queremos deletar do banco de dados.
    if ( line != lineNumber ) {
      fprintf(temp, buffer);
    }

    line++;
  }

  // Feche ambos arquivos.
  fclose(temp);
  fclose(db->m_file);

  // Delete o arquivo do banco de dados original e 
  // substitua-o pelo arquivo temporario.
  remove(db->m_filePath);
  rename("db/delete.tmp", fileName);

  // Reabra o arquivo do banco de dados.
  db->m_file = fopen(db->m_filePath, "a+");

  // E, por ultimo, resete o cursor do arquivo, de precaucao.
  fseek(db->m_file, 0, SEEK_SET);
  return true;
}
