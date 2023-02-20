#include "222006848_.h"
#include "db/222006848.h"

// As esquematicas (schemas) de ambos bancos de dados. Representa como 
// o arquivo CSV está organizado e como o nosso banco de dados fará o parse
// das diferentes colunas.
static database_field_type_t schema_cidades[DATABASE_FIELD_MAX] = {
    DBINT,
    DBSTRING,
    DBSTRING,
    DBSTRING,
    DBEND
};

static database_field_type_t schema_pessoas[DATABASE_FIELD_MAX] = {
  DBSTRING,
  DBSTRING,
  DBINT,
  DBSTRING,
  DBSTRING,
  DBSTRING,
  DBEND
};

// A variável global responsável por ditar o que o programa está fazendo.
static state_t currentState = IDLE;

/// Uma função utilitária para limpar o console.
/// Ela independe (na teoría) de sistema operacional.
void clearConsole( ) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void addPerson( database_t* db, database_t* dbc ) {
  query_person_t data;
  query_city_t city_data;

  // Limpe o console.
  clearConsole( );

  // Printe o titulo.
  printf("[ Sistema de Gestao de Beneficio Social ]\n   por Joao Vitor Mendonca Merlin\n\n\n");

  // Pegue o nome do usuario.
  printf("\nDigite o nome da pessoa:\n");
  fflush(stdin);
  fgets(data.name, DATABASE_LINE_LENGTH_MAX, stdin);

  // Tire o newline do final da string.
  data.name[strlen(data.name) - 1] = '\0';

  // Valide o nome.
  if (!validateName(data.name)) {
    printf("ERRO: Nome invalido!\n");
    sleep(1.5);
    return;
  }

  // Faça o mesmo pro CPF.
  printf("\nDigite o CPF (sem formatacao):\n");
  fflush(stdin);
  fgets(data.cpf, DATABASE_LINE_LENGTH_MAX, stdin);

  data.cpf[strlen(data.cpf) - 1] = '\0';

  if (!validateCPF(data.cpf)) {
    printf("ERRO: CPF invalido!\n");
    sleep(1.5);
    return;
  }

  // E pro sexo.
  printf("\nDigite o sexo da pessoa (F/f ou M/m):\n");
  fflush(stdin);
  scanf("%c", (char*)&data.sex);

  if (data.sex != 'm' && data.sex != 'M' && data.sex != 'f' && data.sex != 'F') {
    printf("ERRO: Sexo invalido!\n");
    sleep(1.5);
    return;
  }

  // Para a residencia.
  printf("\nDigite a cidade de residencia:\n");
  fflush(stdin);
  fgets(data.city, DATABASE_LINE_LENGTH_MAX, stdin);

  data.city[strlen(data.city) - 1] = '\0';
  
  // Fazemos uma query em nosso banco de dados para saber se a cidade existe ou nao.
  if (!db_find_query_by_column(dbc, &city_data, data.city, 4, sizeof(query_city_t), NULL)) {
    printf("ERRO: Cidade/municipio invalido!\n");
    sleep(1.5);
    return;
  }

  // Copiamos, tambem, a UF respectiva da cidade.
  strcpy(data.uf, city_data.uf);
  
  // E por ultimo, pegamos a data de nascimento e a validamos.
  printf("\nPor ultimo, digite a data de nascimento (DD-MM-AAAA):\n");
  fflush(stdin);
  fgets(data.birthDate, DATABASE_LINE_LENGTH_MAX, stdin);

  data.birthDate[strlen(data.birthDate) - 1] = '\0';

  if (!validateDate(data.birthDate)) {
    printf("ERRO: Data de nascimento invalida!\n");
    sleep(1.5);
    return;
  }

  // Caso todas informacoes estejam validas, vamos inserir uma nova
  // entry no nosso banco de dados.
  if (db_write_line(db, &data, sizeof(query_person_t))) {
    printf("\n\nPessoa adicionada com sucesso.\n");
    printf("Pressione ENTER para continuar.");
    getchar();
  } else {
    printf("ERRO: Falha ao adicionar uma nova entrada ao banco de dados.\n");
    sleep(1.5);
  }
 }

void findPerson( database_t* db ) {
  query_person_t data;

  // Crie um buffer para o CPF da pessoa.
  char buffer[DATABASE_LINE_LENGTH_MAX];

  // Limpe o console e mostre o titulo.
  clearConsole( );

  printf("[ Sistema de Gestao de Beneficio Social ]\n   por Joao Vitor Mendonca Merlin\n\n\n");
  
  // Peca ao usuario o CPF da pessoa em questao.
  printf("\nDigite o CPF (sem formatacao):\n");
  fflush(stdin);
  fgets(buffer, DATABASE_LINE_LENGTH_MAX, stdin);

  buffer[strlen(buffer) - 1] = '\0';

  // Valide o CPF da pessoa.
  if (!validateCPF(buffer)) {
    printf("ERRO: CPF invalido!\n");
    sleep(1.5);
    return;
  }

  // Pesquise o CPF no banco de dados.
  // Caso este CPF nao exista, imprima uma mensagem de erro.
  if (!db_find_query_by_column(db, &data, buffer, 1, sizeof(query_person_t), NULL)) {
    printf("ERRO: CPF nao cadastrado no banco de dados.\n");
    sleep(1.5);
    return;
  }

  // Imprima as informacoes da pessoa dada.
  printf("\n\nEncontrado!\n");
  printf("      Nome: %s\n", data.name);
  printf("      Cidade: %s\n", data.city);
  printf("      UF: %s\n", data.uf);
  printf("      Sexo: %c\n", (char)data.sex);
  printf("      Data de nascimento: %s\n", data.birthDate);

  printf("\n\nPressione ENTER para continuar.");
  fflush(stdin);
  getchar();
}

void removePerson( database_t* db ) {
  query_person_t data;

  // Crie um buffer para o CPF da pessoa.
  char buffer[DATABASE_LINE_LENGTH_MAX];

  // Limpe o console e imprima o titulo.
  clearConsole( );

  printf("[ Sistema de Gestao de Beneficio Social ]\n   por Joao Vitor Mendonca Merlin\n\n\n");
  
  // Peca ao usuario o CPF da pessoa em questao.
  printf("\nDigite o CPF (sem formatacao):\n");
  fflush(stdin);
  fgets(buffer, DATABASE_LINE_LENGTH_MAX, stdin);

  buffer[strlen(buffer) - 1] = '\0';

  // Valide o CPF dado pelo usuario.
  if (!validateCPF(buffer)) {
    printf("ERRO: CPF invalido!\n");
    sleep(1.5);
    return;
  }

  // Tente achar a pessoa no banco de dados.
  // Caso ela nao exista, imprima um erro ao usuario.
  int lineNumber;
  if (!db_find_query_by_column(db, &data, buffer, 1, sizeof(query_person_t), &lineNumber)) {
    printf("ERRO: CPF nao cadastrado no banco de dados.\n");
    sleep(1.5);
    return;
  }
  
  // Delete a linha do banco de dados cujo a pessoa especificada esta.
  db_delete_line( db, lineNumber, "db/pessoas.csv" );

  printf("\n\nPessoa deletada com sucesso.\n");
  printf("Pressione ENTER para continuar.");
  getchar();
}

void listPeople( database_t* db, database_t* dbc ) {
  query_person_t data;
  query_city_t data_city;

  // Crie um buffer para o nome da cidade.
  char buffer[DATABASE_LINE_LENGTH_MAX];

  // Limpe o terminal e imprima o titulo.
  clearConsole( );

  printf("[ Sistema de Gestao de Beneficio Social ]\n   por Joao Vitor Mendonca Merlin\n\n\n");
  
  // Peca ao usuario o nome da cidade.
  printf("\nDigite o nome da cidade (sem acentos):\n");
  fflush(stdin);
  fgets(buffer, DATABASE_LINE_LENGTH_MAX, stdin);

  buffer[strlen(buffer) - 1] = '\0';

  // Pesquise o nome da cidade no banco de dados.
  // Caso ela nao exista, imprima um erro.
  if (!db_find_query_by_column(dbc, &data_city, buffer, 4, sizeof(query_city_t), NULL)) {
    printf("ERRO: Cidade invalida!\n");
    sleep(1.5);
    return;
  }

  // Crie um buffer para as pessoas da cidade.
  // Fazemos isso para poder armazenar os nomes de cada uma das pessoas
  // para depois realizarmos o sort.
  char people[MAX_LENGTH][MAX_LENGTH];

  int lineNumber = 1, id = 0;

  // Leia o arquivo do banco de dados linha por linha.
  while( db_read_line( db, &data, lineNumber++, sizeof(query_person_t) ) ) {
    // Caso a pessoa da linha atual seja residente da cidade especificada,
    // adicione-a ao buffer de pessoas.
    if (strcmp(buffer, data.city) == 0) {
      strcpy(people[id++], data.name);
    }
  }

  // Caso tenhamos achado nenhuma pessoa que more na cidade especificada,
  // imprima um aviso.
  if (id == 0) {
    printf("\n\nNao ha residentes na cidade '%s'.\n", buffer);

    printf("\n\nPressione ENTER para continuar.");
    fflush(stdin);
    getchar();
    return;
  }

  // Realize o sort dos nomes das pessoas.
  sortStrings(people, id + 1);

  // Imprima a lista de residentes.
  printf("\n\nLista de residentes de '%s': \n\n", buffer);
  for (int i = 0; i < id + 1; i++) {
    printf("     %s\n", people[i]);
  }

  printf("\n\nPressione ENTER para continuar.");
  fflush(stdin);
  getchar();
}

void showReport( database_t* db ) {
  query_person_t data;

  // Limpe o console e imprima o titulo.
  clearConsole( );

  printf("[ Sistema de Gestao de Beneficio Social ]\n   por Joao Vitor Mendonca Merlin\n\n\n");
  
  int lineNumber = 2;
  int amountOfPeople = 0;

  // Crie as variaveis responsaveis por guardar as quantidades
  // de pessoas que satisfazem as condicoes especificadas.

  int prc0_15 = 0; // Pessoas de 0 a 15 anos
  int prc16_29 = 0; // Pessoas de 16 a 29 anos
  int prc30_49 = 0; // Pessoas de 30 a 49 anos
  int prc50_60 = 0; // Pessoas de 50 a 60 anos
  int prc60p = 0; // Idosos

  int prcMale = 0; // Pessoas do sexo masculino
  int prcFemale = 0; // Pessoas do sexo feminino

  // Leia o arquivo de banco de dados linha por linha.
  while( db_read_line( db, &data, lineNumber, sizeof(query_person_t) ) ) {
    // Calcule a idade da pessoa dado a sua data de nascimento e 
    // pegue o seu sexo.
    const int age = getAge( data.birthDate );
    const char sex = (char)data.sex;

    if (age >= 0 && age <= 15) {
      prc0_15++;
    }

    else if(age >= 16 && age <= 29) {
      prc16_29++;
    }

    else if(age >= 30 && age <= 49) {
      prc30_49++;
    }

    else if(age >= 50 && age <= 60) {
      prc50_60++;
    }

    else if(age > 60) {
      prc60p++;
    }

    if (sex == 'm' || sex == 'M') {
      prcMale++;
    }

    else if(sex == 'f' || sex == 'F') {
      prcFemale++;
    }

    lineNumber++;
    amountOfPeople++;
  }

  // Imprima o relatorio.
  printf("Relatorio:\n\n");

  printf(" Quantidade de pessoas: %d\n", amountOfPeople);

  printf(" Percentual de pessoas por faixa etaria:\n");
  printf("     0 a 15 anos: %.02f%%\n", (double)prc0_15 / amountOfPeople * 100);
  printf("     16 a 29 anos: %.02f%%\n", (double)prc16_29 / amountOfPeople * 100);
  printf("     30 a 49 anos: %.02f%%\n", (double)prc30_49 / amountOfPeople * 100);
  printf("     50 a 60 anos: %.02f%%\n", (double)prc50_60 / amountOfPeople * 100);
  printf("     60 ou mais anos: %.02f%%\n", (double)prc60p / amountOfPeople * 100);

  printf(" Percentual de pessoas por sexo:\n");
  printf("     Masculino: %.02f%%\n", (double)prcMale / amountOfPeople * 100);
  printf("     Feminino: %.02f%%\n", (double)prcFemale / amountOfPeople * 100);

  printf("\n\nPressione ENTER para continuar.");
  fflush(stdin);
  getchar();
}

void showMainMenu( ) {
  // Primeiramente, limpe o console.
  clearConsole( );

  // Printe o titulo e as opcoes.
  printf("[ Sistema de Gestao de Beneficio Social ]\n   por Joao Vitor Mendonca Merlin\n\n\n");

  printf("Menu de opcoes:\n");
  printf("      1) Cadastrar pessoa\n");
  printf("      2) Consultar pessoa\n");
  printf("      3) Listar pessoas por cidade\n");
  printf("      4) Gerar relatorio\n");
  printf("      5) Excluir pessoa\n");
  printf("      6) Encerrar programa\n\n\n");

  printf("Digite a opcao desejada: ");
}

int main( ) {
  database_t db_cidades, db_pessoas;

  // Criando o banco de dados.
  if (
    !db_new(
      &db_cidades,
      "C:\\Users\\Merli\\.dev\\trabalho-apc\\db\\municipios.csv",
     schema_cidades
    ) ||
    !db_new(
      &db_pessoas,
      "C:\\Users\\Merli\\.dev\\trabalho-apc\\db\\pessoas.csv",
     schema_pessoas
    )
  ) {
    return 1;
  }
  
  // Mostre o menu principal.
  showMainMenu( );

  // Pegue a entrada do usuario e continue o programa enquanto
  // ele(a) nao escolher finaliza-lo.
  scanf("%d", &currentState);
  while( currentState != EXIT ) {

    // Faca um switch para cada uma das escolhas do usuario.
    switch( currentState ) {
      case ADD:
        addPerson( &db_pessoas, &db_cidades );
        break;

      case READ:
        findPerson( &db_pessoas );
        break;

      case DELETE:
        removePerson( &db_pessoas );
        break;

      case LIST_BY_CITY:
        listPeople( &db_pessoas, &db_cidades );
        break;
        
      case REPORT:
        showReport( &db_pessoas );
        break;

      default:
        break;
    }

    // Ao final da consulta do usuario, mostre o menu principal novamente e receba 
    // um novo input.
    showMainMenu( );
    scanf("%d", &currentState);
  }

  // Feche o banco de dados apos o uso.
  db_close(&db_cidades);
  db_close(&db_pessoas);
  return 0;
}
