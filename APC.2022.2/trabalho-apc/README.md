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


## English version

### Project description

The project, in C language, consisted of writing a simple database system capable of reading and writing data to a CSV file and performing different operations on top of that foundation. In the case of the project, a basic registration system for Brazilian citizens was written.

People's registration uses their CPF (individual taxpayer registration), name, date of birth, city and state of residence, and gender. The program is also capable of validating each of this information, performing queries, generating reports, among other features.

compilation and execution
The development and testing process of the project was done on a Windows 64-bit operating system. The compiler used was 'GCC', using version 11.2.0.

In the project directory, there is a Powershell script (´build.ps1´) which is used to compile the project. If it is not possible to use Powershell, the compilation can be performed using:

´´´ gcc -o debug -Wall main.c db/db.c ´´´

### Observation
This numbers (222006848) is my registration on the university
