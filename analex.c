#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "analex.h"
#define TAM_LEXEMA 50
#define TAM_NUM 20

void error(char msg[])
{

  printf("%s\n", msg);
  exit(1);
}

TOKEN AnaLex(FILE *fd)
{

  int estado;

  char lexema[TAM_LEXEMA] = "";

  int tamanho_lexema = 0;

  char digitos[TAM_NUM] = "";

  int tamanho_digito = 0;

  TOKEN token;

  estado = 0;

  while (1)
  {

    char c = fgetc(fd);

    switch (estado)
    {

    case 0:
      if (c == ' ' || c == '\t')
        estado = 0;
      else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
      { // inicio de identificador - inicializa lexema

        estado = 1;

        lexema[tamanho_lexema] = c;

        lexema[++tamanho_lexema] = '\0';
      }

      else if (c >= '1' && c <= '9')
      { // inicio de constante inteira - inicializa digitos

        estado = 10;

        digitos[tamanho_digito] = c;

        digitos[++tamanho_digito] = '\0';
      }

      else if (c == ';')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = PONTO_VIRG;

        return token;
      }

      else if (c == ':')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = DOIS_PONTOS;

        return token;
      }

      else if (c == '+')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = ADICAO;

        return token;
      }

      else if (c == '-')
      { // sinal de subtracao - monta e devolve token

        token.cat = SN;

        token.codigo = SUBTRACAO;

        return token;
      }

      else if (c == '*')
      { // sinal de multiplicacao - monta e devolve token

        token.cat = SN;

        token.codigo = MULTIPLICACAO;

        return token;
      }

      else if (c == '/')
      { // sinal de divisao - monta e devolve token
        estado = 13;
        /*
        token.cat = SN;

        token.codigo = DIVISAO;

        return token;
        */
      }

      else if (c == '=')
      { // sinal de atribuicao - monta e devolve token
        estado = 5;
        /*
        token.cat = SN;

        token.codigo = ATRIBUICAO;

        return token;
        */
      }

      else if (c == '%')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = MODIFICADOR;

        return token;
      }

      else if (c == '(')
      { // sinal de abre parenteses - monta e devolve token

        token.cat = SN;

        token.codigo = A_PARANETESE;

        return token;
      }

      else if (c == ')')
      { // sinal de fecha parenteses - monta e devolve token

        token.cat = SN;

        token.codigo = F_PARENTESE;

        return token;
      }

      else if (c == '{')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = A_CHAVE;

        return token;
      }

      else if (c == '}')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = F_CHAVE;

        return token;
      }

      else if (c == '>')
      { // sinal de adicao - monta e devolve token
        estado = 6;
        /*
        token.cat = SN;

        token.codigo = MAIOR;

        return token;
        */
      }

      else if (c == '<')
      { // sinal de adicao - monta e devolve token
        estado = 7;
        /*
        token.cat = SN;

        token.codigo = MENOR;

        return token;
        */
      }

      else if (c == '[')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = A_COLCHETE;

        return token;
      }

      else if (c == ']')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = F_COLCHETE;

        return token;
      }

      else if (c == '&')
      { // sinal de adicao - monta e devolve token
        estado = 8;
        /*
        token.cat = SN;

        token.codigo = E_COMERC;

        return token;
        */
      }

      else if (c == '!')
      { // sinal de adicao - monta e devolve token
        estado = 9;
        /*
        token.cat = SN;

        token.codigo = NAO;

        return token;
        */
      }

      else if (c == ',')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = VIRGULA;

        return token;
      }

      else if (c == '|')
      { // sinal de adicao - monta e devolve token
        estado = 12
        /*
        token.cat = SN;

        token.codigo = OU;

        return token;
        */
      }

      else if (c == '^')
      { // sinal de adicao - monta e devolve token

        token.cat = SN;

        token.codigo = IDENTIF_PONTEIRO;

        return token;
      }

      else if (c == '\'')
      { // sinal de adicao - monta e devolve token

        estado = 2;
        /*
        lexema[tamanho_lexema] = c;
        lexema[++tamanho_lexema] = '\0';
        */
      }

      else if (c == '"')
      { // sinal de adicao - monta e devolve token

        estado = 4;
        /*
        lexema[tamanho_lexema] = c;
        lexema[++tamanho_lexema] = '\0';
        */
      }

      else if (c == EOF)
      { // fim da expressao encontrado

        token.cat = FIM_ARQ;

        return token;
      }

      else

        error("Caracter invalido na expressao!"); // sem transicao valida no AFD

      break;

    case 1:
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_'))
      {

        estado = 1;

        lexema[tamanho_lexema] = c; // acumula caracteres lidos em lexema

        lexema[++tamanho_lexema] = '\0';
      }

      else
      { // transicao OUTRO* do estado 1 do AFD
        ungetc(c, fd);
        // tratamento de palavras reservadas
        if (lexema == "class")
        {
          token.cat = PR;
          token.codigo = CLASS;
          return token;
        }
        else if (lexema == "code")
        {
          token.cat = PR;
          token.codigo = CODE;
          return token;
        }
        else if (lexema == "data")
        {
          token.cat = PR;
          token.codigo = DATA;
          return token;
        }
        else if (lexema == "intern")
        {
          token.cat = PR;
          token.codigo = INTERN;
          return token;
        }
        else if (lexema == "void")
        {
          token.cat = PR;
          token.codigo = VOID;
          return token;
        }
        else if (lexema == "char")
        {
          token.cat = PR;
          token.codigo = CHAR;
          return token;
        }
        else if (lexema == "int")
        {
          token.cat = PR;
          token.codigo = INT;
          return token;
        }
        else if (lexema == "float")
        {
          token.cat = PR;
          token.codigo = FLOAT;
          return token;
        }
        else if (lexema == "bool")
        {
          token.cat = PR;
          token.codigo = BOOL;
          return token;
        }
        else if (lexema == "if")
        {
          token.cat = PR;
          token.codigo = IF;
          return token;
        }

        else if (lexema == "else")
        {
          token.cat = PR;
          token.codigo = ELSE;
          return token;
        }

        else if (lexema == "while")
        {
          token.cat = PR;
          token.codigo = WHILE;
          return token;
        }

        else if (lexema == "for")
        {
          token.cat = PR;
          token.codigo = FOR;
          return token;
        }

        else if (lexema == "return")
        {
          token.cat = PR;
          token.codigo = RETURN;
          return token;
        }
        else if (lexema == "delete")
        {
          token.cat = PR;
          token.codigo = DELETE;
          return token;
        }

        // monta token identificador e retorna

        token.cat = ID;

        strcpy(token.lexema, lexema);

        return token;
      }

      break;
    case 2:
      if ((isprint(c) || c == '\n' || c == '\0') && c != '\'' && c != '\\')
      {
        estado = 3;
        lexema[tamanho_lexema] = c;
        lexema[++tamanho_lexema] = '\0';
      }
      else
        error("caracter invalido na expressao");
      break;

    case 3:
      if (c == '\'')
      {
        token.cat = CT_C;

        token.caracter = lexema[tamanho_lexema];

        return token;
      }
      break;

    case 4:
      if (isprint(c) && c != '"' && c != '\n')
      {
        lexema[tamanho_lexema] = c;
        lexema[++tamanho_lexema] = '\0';
      }
      else if (c == '"')
      {
        token.cat = CT_S;

        strcpy(token.lexema, lexema);
        // token.indice = *token.lexema;
        return token;
      }
      break;
    case 5:
      if(c == '=')
      {
        token.cat = SN;
        token.codigo = COMPARACAO;
        return token;
      }else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = ATRIBUICAO;

        return token;
      }
      break;

    case 6:
      if(c == '=')
      {
        token.cat = SN;
        token.codigo = MAIOR_IGUAL;
        return token;
      }else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = MAIOR;

        return token;
      }
      break;

    case 7:
      if(c == '=')
      {
        token.cat = SN;
        token.codigo = MENOR_IGUAL;
        return token;
      }else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = MENOR;

        return token;
      }
      break;

    case 8:
      if(c == '&')
      {
        token.cat = SN;
        token.codigo = AND;
        return token;
      }else
      {
        error ("caracter invalido na expressao")
      }
      break;
    
    case 9:
      if(c == '=')
      {
        token.cat = SN;
        token.codigo = NAO_IGUAL;
        return token;
      }else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = NAO;

        return token;
      }
      break;

    case 10:
      if (c >= '0' && c <= '9')
      {

        estado = 10;

        digitos[tamanho_digito] = c; // acumula digitos lidos na variaavel digitos

        digitos[++tamanho_digito] = '\0';
      }
      else if (c == '.')
      {
        estado = 11;

        digitos[tamanho_digito] = c;

        digitos[++tamanho_digito] = '\0';
      }
      else
      { // transicao OUTRO* do estado 10 do AFD

        // monta token constante inteira e retorna

        ungetc(c, fd);

        token.cat = CT_I;

        token.valInt = atoi(digitos);

        return token;
      }
      break;

    case 11:
      if (c >= '0' && c <= '9')
      {
        digitos[tamanho_digito] = c;

        digitos[++tamanho_digito] = '\0';
      }
      else
      {
        ungetc(c, fd);

        token.cat = CT_F;

        token.valFloat = atof(digitos);

        return token;
      }
      break;

    case 12:
      if(c == '|')
      {
        token.cat = SN;
        token.codigo = OU;
        return token;
      }else
      {
        error ("caracter invalido na expressao")
      }
      break;
    // Tratamento de comentario
    case 13:
      if(c == '*') estado = 14;
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = DIVISAO;

        return token;
      }
      break;
    case 14:
      if(c=='*') estado = 15;
      else estado = 14;
      break;

    case 15:
      if (c=='/') estado = 0;
      else estado = 14;
      break;
    }
  }
}

int main()
{

  FILE *fd;

  TOKEN tk;

  if ((fd = fopen("expressao.dat", "r")) == NULL)

    error("Arquivo de entrada da expressao nao encontrado!");

  while (1)
  {

    tk = AnaLex(fd);

    switch (tk.cat)
    {

      case ID:
        printf("<ID, %s> ", tk.lexema);

        break;

      case SN:
        switch (tk.codigo)
        {

      case ADICAO:
        printf("<SN, ADICAO> ");

        break;

      case SUBTRACAO:
        printf("<SN, SUBTRACAO> ");

        break;

      case MULTIPLICACAO:
        printf("<SN, MULTIPLICACAO> ");

        break;

      case DIVISAO:
        printf("<SN, DIVISAO> ");

        break;

      case ATRIBUICAO:
        printf("<SN, ATRIBUICAO> ");

        break;

      case A_PARANETESE:
        printf("<SN, ABRE_PARENTESES> ");

        break;

      case F_PARENTESE:
        printf("<SN, FECHA_PARENTESES> ");

        break;
      }

      break;

    case CT_I:
      printf("<CT_I, %d> ", tk.valInt);

      break;

    case FIM_ARQ:
      printf("\nFim da expressao encontrado.\n");
    }

    if (tk.cat == FIM_ARQ)
      break;
  }

  fclose(fd);

  return 0;
}