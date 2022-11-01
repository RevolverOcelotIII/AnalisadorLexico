#ifndef ANALEX

#define ANALEX 

 

#define TAM_MAX_LEXEMA 31 

 

enum TOKEN_CAT {ID=1, PR, SN, CT_I, CT_F, CT_C, CT_S, FIM_ARQ}; 

/* Onde: ID: Identificador, PR: Palavra Reservada; SN: Sinal; CT_*: Constante numérica ou caracter, LT: cadeia de caracter */ 

 

enum PAL_RESERV {CLASS=1, CODE, DATA, INTERN, VOID, CHAR, INT, FLOAT, BOOL, IF, ELSE, WHILE, FOR, RETURN, DELETE}; //completar com nomes de códigos correspondentes às palavras reservadas restantes de MinObjC 

 

enum SINAIS {PONTO_VIRG = 1, DOIS_PONTOS, DIVISAO,  ATRIBUICAO, ADICAO, SUBTRACAO, MULTIPLICACAO, DIVISAO, MODIFICADOR,
 A_PARANETESE, F_PARENTESE, A_CHAVE, F_CHAVE, MAIOR, MENOR, A_COLCHETE, F_COLCHETE, E_COMERC, NAO, VIRGULA, OU, IDENTIF_PONTEIRO, ASPAS_S, ASPAS_D, PONTO}; //completar com nomes de códigos correspondentes sinais restantes de MinObjC 

 

typedef 

  struct {  

    enum TOKEN_CAT cat;// deve receber uma das constantes de enum TOKEN_CAT 

    union {// parte variável do registro 

      int codigo;// para tokens das categorias PR e SN 

      int indice;// indica o índice da tabela onde o Analex armazenou um literal (cadeia de caracter) para tokens da cat. LT 

      char lexema[TAM_MAX_LEXEMA];// cadeia de caractares que corresponde o nome do token da cat. ID 

      int valInt; // valor da constante ineira em tokens da cat. CT_I 

      float valFloat; // valor da constante ineira em tokens da cat. CT_F 

      char caracter; // caracter do token da cat. CT_C 

    }; 

} TOKEN;    // Tipo TOKEN 

 

#endif 