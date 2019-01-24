#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

#include "lextppp.c"

void Test_Symbole (CODES_LEX, char*);
void program();
void block();
void lire();
void consts();
void vars();
void insts();
void inst();
void affec();
void si();
void tanque();
void ecrire();
void lire_r();
void expr();
void cond();
void fact();
void ecrireplus();
void lire_rplus();
void term();
void beginsec();
void end();

const char nomfichier[] = "/home/meriem/Desktop/compilaV/test0.txt";
FILE* fichier = NULL;


token Sym_cour;


void lire(){
	Sym_cour = lireFichier(fichier);
}

void Test_Symbole (CODES_LEX cl, char* messageErreur){
    if (Sym_cour.CODE == cl){
          printf("  %s", Sym_cour.NOM);
          lire();
    }
    else{
        printf("\n________________%s %s________________ \n", Sym_cour.NOM,messageErreur);
        exit(0);
    }
}

//PROGRAM ::= program ID; BLOCK.
void program(){
  printf("\n");
  lire();
  Test_Symbole(PROGRAM_TOKEN, "PROGRAM_TOKEN_ERROR");
  Test_Symbole(ID_TOKEN, "ID_TOKEN_ERROR");
  Test_Symbole(PV_TOKEN, "PV_TOKEN_ERROR");
  printf("\n\n________________FIN_PROGRAM_LIGNE________________ \n");
  block();
  Test_Symbole(PT_TOKEN, "PT_TOKEN_ERROR");
}



void block(){
  consts();
  vars();
  insts();
}

//CONSTS  ::= const ID = NUM; { ID = NUM; } | epsilon  
void consts(){
      printf("\n");
        switch (Sym_cour.CODE) {  
            case CONST_TOKEN :
                                Test_Symbole(CONST_TOKEN, "CONST_TOKEN_ERROR");
                                Test_Symbole(ID_TOKEN, "CONST_ID_TOKEN_ERROR");
                                Test_Symbole(EG_TOKEN, "CONST_EG_TOKEN_ERROR");
                                Test_Symbole(INT_TOKEN, "CONST_INT_TOKEN_ERROR");
                                Test_Symbole(PV_TOKEN, "CONST_PV_TOKEN_ERROR");
                                while (Sym_cour.CODE == ID_TOKEN){
                                      Test_Symbole(ID_TOKEN, "CONST_ID_TOKEN_ERROR");
                                      Test_Symbole(EG_TOKEN, "CONST_EG_TOKEN_ERROR");
                                      Test_Symbole(INT_TOKEN, "CONST_INT_TOKEN_ERROR");
                                      Test_Symbole(PV_TOKEN, "CONST_PV_TOKEN_ERROR");
                                }; break;
            case VAR_TOKEN : break;
            case BEGIN_TOKEN : break;
            default:  printf("\n________________CONSTS_VARS_BEGIN_ERROR________________ \n"); exit(0); break;  
        } 
        printf("\n\n________________FIN_CONSTS_______________________\n");      
}

//VARS    ::= var ID {, ID }; | epsilon

void vars(){
    printf("\n");
          switch (Sym_cour.CODE) {  
              case VAR_TOKEN :  Test_Symbole(VAR_TOKEN, "VAR_TOKEN_ERROR");
                                Test_Symbole(ID_TOKEN, "VAR_ID_TOKEN_ERROR");    
                                while (Sym_cour.CODE == VR_TOKEN){
                                    Test_Symbole(VR_TOKEN, "VAR_VR_TOKEN_ERROR");
                                    Test_Symbole(ID_TOKEN, "VAR_ID_TOKEN_ERROR");
                                }
                                Test_Symbole(PV_TOKEN, "VAR_PV_TOKEN_ERROR");
                                break;
              case BEGIN_TOKEN : break;
              default:  printf("\n________________VAR_BEGIN_ERROR________________ \n"); exit(0); break;  
        }
    printf("\n\n________________FIN_VARS________________ \n");           
}

//INSTS   ::= begin INST {; INST } end
void insts(){
   printf("\n");
      Test_Symbole(BEGIN_TOKEN, "INSTS_BEGIN_TOKEN_ERROR");
        inst();
        while (Sym_cour.CODE == PV_TOKEN){
            Test_Symbole(PV_TOKEN, "PV_TOKEN_ERROR");
            inst();
        }
        Test_Symbole(END_TOKEN, "END_TOKEN_ERROR");
        printf("\n\n________________FIN_INSTS________________ \n");
}

void beginsec(){
  inst();
  while (Sym_cour.CODE == PV_TOKEN){
      Test_Symbole(PV_TOKEN, "PV_TOKEN_ERROR");
      inst();
  }
  Test_Symbole(END_TOKEN, "END_TOKEN_ERROR");
  printf("\n\n________________FIN_INST________________ \n");
}



//INST    ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | epsilon
void inst(){
    printf("\n");
    switch (Sym_cour.CODE) {
          case BEGIN_TOKEN :    Test_Symbole(BEGIN_TOKEN, "INST_BEGIN_TOKEN_ERROR");
                                beginsec();
                                printf("\n________________FIN_INST_INSTS________________ \n"); 
                                break;

          case ID_TOKEN :       Test_Symbole(ID_TOKEN, "ID_TOKEN_ERROR");
                                affec();
                                printf("\n________________FIN_INST_AFFEC________________ \n");
                                break;

          case IF_TOKEN :       Test_Symbole(IF_TOKEN, "IF_TOKEN_ERROR");
                                si();
                                printf("\n________________FIN_INST_IF________________ \n"); 
                                break;

          case WRITE_TOKEN :    Test_Symbole(WRITE_TOKEN, "WRITE_TOKEN_ERROR");
                                ecrire();
                                printf("\n________________FIN_INST_WRITE________________ \n");
                                break;                               

          case READ_TOKEN :     Test_Symbole(READ_TOKEN, "READ_TOKEN_ERROR");
                                lire_r();
                                printf("\n________________FIN_INST_READ________________ \n");
                                break;

          case WHILE_TOKEN :    Test_Symbole(WHILE_TOKEN, "WHILE_TOKEN_ERROR");
                                tanque();
                                printf("\n________________FIN_INST_WHILE________________ \n");
                                break;

          default : break;   
    }
}


//AFFEC   ::= ID := EXPR
void affec(){
     Test_Symbole(AFF_TOKEN,"AFF_TOKEN_ERROR");
     expr();
}

//SI      ::= if COND then INST 
void si(){
    cond();
    Test_Symbole(THEN_TOKEN, "THEN_TOKEN_ERROR");
    inst();
}


//TANTQUE ::= while COND do INST 
void tanque(){
    cond();
    Test_Symbole(DO_TOKEN, "DO_TOKEN_ERROR");
    inst();
}


//ECRIRE  ::= write (EXPR {, EXPR}) 
void ecrire(){
            Test_Symbole(PO_TOKEN,"PO_TOKEN_ERROR");
            expr();
            while(Sym_cour.CODE == VR_TOKEN){
              Test_Symbole(VR_TOKEN,"VR_TOKEN_ERROR");
              expr();
            }
            Test_Symbole(PF_TOKEN,"PF_TOKEN_ERROR");
}

//LIRE    ::= read ( ID { , ID } )
void lire_r(){
        Test_Symbole(PO_TOKEN,"PO_TOKEN_ERROR");
        Test_Symbole(ID_TOKEN, "ID_TOKEN_ERROR");
        while(Sym_cour.CODE == VR_TOKEN){
          Test_Symbole(VR_TOKEN,"VR_TOKEN_ERROR");
          Test_Symbole(ID_TOKEN, "ID_TOKEN_ERROR");
        }
        Test_Symbole(PF_TOKEN,"PF_TOKEN_ERROR");
 }

//COND    ::= EXPR [= | <> | < | > | <= | >=] EXPR
void cond(){
	  expr();
      	if(Sym_cour.CODE == EG_TOKEN || Sym_cour.CODE == DIFF_TOKEN || Sym_cour.CODE == INF_TOKEN || Sym_cour.CODE == SUP_TOKEN || Sym_cour.CODE == INFEG_TOKEN || Sym_cour.CODE == SUPEG_TOKEN){
            printf("  %s", Sym_cour.NOM);
            lire();
            expr();
        }else{
            printf("\n________________COND_ERROR________________ \n");
            exit(0);
        }
}

//EXPR    ::= TERM { [+|-] FACT}
void expr(){
    term();
    while( Sym_cour.CODE == PLUS_TOKEN || Sym_cour.CODE == MOINS_TOKEN){
        printf("  %s", Sym_cour.NOM);
        lire();
        term();
    }
}

//TERM    ::= FACT { [*|/] FACT }
void term(){
    fact();
    while( Sym_cour.CODE  == MULT_TOKEN || Sym_cour.CODE == DIV_TOKEN){
          printf("  %s", Sym_cour.NOM);
          lire();
          fact();
    }
}

//FACT    ::= ID | NUM | (EXPR)
void fact(){
    switch (Sym_cour.CODE) {
    case ID_TOKEN:  Test_Symbole(ID_TOKEN, "ID_TOKEN_ERROR");
                    break;
    case INT_TOKEN: Test_Symbole(INT_TOKEN, "INT_TOKEN_ERROR");  break;
    case PO_TOKEN:  Test_Symbole(PO_TOKEN, "PO_TOKEN_ERROR");
                    expr();
                    Test_Symbole(PF_TOKEN, "PF_TOKEN_ERROR");
                    break;
    default: printf("\n________________FACT_ERROR________________ \n"); exit(0); break;  
    }
}

int main(){

	fichier = fopen(nomfichier, "r");
	if(fichier != NULL){		
    	   program();
    			 if(Sym_cour.CODE == FIN_TOKEN){
    			 		  printf("\n BRAVO: le programme est correcte!!!\n");
    			 }else{
    			 		  printf("\n PAS BRAVO: fin de programme erronée!!!!\n");	
    			 }  
	} else {
    		printf("Erreur d'ouverture du fichier source..\n\n");
    		exit(0);
	}
	fclose(fichier);


	return 0;
}