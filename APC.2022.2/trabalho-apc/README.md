# Projeto final de APC
## Por João Vitor Mendonça Merlin (222006848)
## Prof. Giovanni

### Descrição do projeto
O projeto, em linguagem C, consistia em escrever um simples sistema de banco de dados capaz de ler e escrever
dados a um arquivo CSV e realizar diferentes operações em cima dessa fundação. No caso do projeto, foi
escrito um básico sistema de cadastro de cidadões brasileiros.


O cadastro das pessoas utiliza seu CPF (individual taxpayer registration), nome, data de nascimento,
cidade e estado de residencia, e sexo. O programa também é capaz de validar cada uma dessas informações,
realizar queries, gerar relatórios, dentre outras funcionalidades.

### Compilação e execução
O processo de desenvolvimento e teste do projeto foi feito em um sistema operacional Windows 64-bits.
O compilador utilizado foi o ´GCC´, utilizando a versão **11.2.0**. 

No diretorio do projeto, existe um script de Powershell (´build.ps1´) cujo é utilizado para compilar o
projeto. Caso não seja possível utilizar o Powershell, a compilação pode ser realizada utilizando:

´´´
gcc -o debug -Wall main.c db/db.c
´´´
