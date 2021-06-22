//GIORGOS ANGELOULIS AM1995 USERNAME:CS01995
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MEGETHOS  31 //30+/0 charactires
#define ENDOF_TOKEN 1111111 //to telos tou arxeiou
#define ERROR 22222222 //error
#define AN1 33333333 //anagnoristiko h desmeymenh leksi
#define AKS2 44444444 //akeraia stathera
#define PRS3 5 //pragmatikh stathera


#define SYN_TOKEN 10 //+
#define MION_TOKEN 11 //-
#define EPI_TOKEN 12 //* */
#define DIA_TOKEN 13 // /
#define MIKR_TOKEN 14 // <
#define MEGAL_TOKEN 15 // >
#define ISON_TOKEN 16 //=
#define MIKRISON_TOKEN  17//<=
#define MEGISON_TOKEN 18 // >=
#define DIAFOR_TOKEN 19 // <>
#define ANATH_TOKEN 20// :=
#define EROT_TOKEN 21//;
#define KOMMA_TOKEN 22//,
#define OPEN_TOKEN 23 //{
#define CLOSE_TOKEN 24 //}
#define OPEN1_TOKEN 25 //(
#define CLOSE2_TOKEN 26 //)
#define OPEN3_TOKEN 27 //[
#define CLOSE3_TOKEN 28 //]
#define ID_TOKEN 31 //anagnvristiko
#define AKERST_TOKEN 32 //akeraia stathera
#define PRAGMATIKH_TOKEN 33 //pragmatikos arithmos

#define AND_TOKEN 50 //AND
#define FUNCTION_TOKEN 51 //FUNCTION
#define NOT_TOKEN 52 //NOT
#define OR_TOKEN 53 //OR
#define VAR_TOKEN 54 //VAR
#define PRINT_TOKEN 55 //PRINT
#define FOR_TOKEN 56 //FOR
#define RETURN_TOKEN 57 //RETURN
#define	DO_TOKEN 58 //DO
#define IF_TOKEN 59 //IF
#define TO_TOKEN 60 //TO
#define WHILE_TOKEN 61 // WHILE
#define ELSE_TOKEN 62 //ELSE
#define IN_TOKEN 63 //IN
#define STEP_TOKEN 64
#define CALL_TOKEN 65 //CALL
#define PROCEDURE_TOKEN 66 // PROCEDURE
#define INOUT_TOKEN 67 //INOUT
#define PROGRAM_TOKEN 68//PROGRAM
#define BEGIN_TOKEN 69 //arxi
#define DOWHILE_TOKEN 84 //dowhile

	int q_num = 1;
	int tmp_2 = 1;

	struct quad{
		int number;
		char op[4][MEGETHOS];
		struct quad *next;
	};
	struct list{
		int quad;
		struct list *next;
	};
	struct precept{
		struct list *true;
		struct list *false;
	};
	struct quad *Quad_index=NULL;

	int nextquad();
	void genquad(char op[MEGETHOS],char x[MEGETHOS],char y[MEGETHOS],char z[MEGETHOS]);
	char *newTemp();
	struct list *makelist(int x);
	struct list *merge(struct list *l1,struct list *l2);
	void backpatch(struct list *l_index,int z);
	struct list *emptylist();

	int token;
	char str[MEGETHOS];
	FILE *arxeion,*arxeion2,*arxeion3,*final_arxeion;

	void RELATIONAL_OPER(char oper[MEGETHOS]);
	void PROGRAM();
	void BLOCK(char name[MEGETHOS]);


	void DECLARATIONS();
	void VARLIST();
	void SUBPROGRAMS();
	void FUNC();
	void FUNCBODY();
	void FORMALPARS();
	void FORMALPARLIST();
	void FORMALPARITEM();
	void SEQUENCE();
	void BRACKETS_SEQ();
	void BRACK_OR_STAT();
	void STATEMENT();
	void ASSIGMENT_STAT();
	void IF_STAT();
	void ELSEPART();
	void DO_WHILE_STAT();
	void FOR_STAT();
	void RETURN_STAT();
	void PRINT_STAT();
	void WHILE_STAT();
	void STEP_PART();
	void CALL_STAT();
	void ACTUALPARS();
	void ACTUALPARLIST();
	void ACTUALPARITEM();
	void CONDITION();
	void BOOLTERM();
	void BOOLFACTOR();
	void EXPRESSION(char place[MEGETHOS]);
	void TERM(char C_place[MEGETHOS]);
	void FACTOR(char F_place[MEGETHOS]);
	void IDTAIL();
	void RELATIONAL_OPER(char oper[MEGETHOS]);
	void OPTIONAL_SIGN();
#define VARIABLE 0
#define PARAMETER 1
#define FUNCTION 2
#define VALUE 100
#define REFERENCE 101

	struct entity{
		char name[MEGETHOS];
		int type;
		int offset;
		int paraMode;
		struct entity *next;
		int vathos;
	};
	struct scope{
		char name[MEGETHOS];
		int vathos;
		int stigm;
		struct entity *entit_list;
		struct scope *next;
	};

	struct scope * SCOPES=NULL;
	void create_scope(char name[MEGETHOS]);
	void remove_scope();
	void add_entity(char name[MEGETHOS],int type,int paraMode);
	void printtable();
	void loadta(char t[MEGETHOS],int a);

	int lex(char token1[MEGETHOS]);
	void print_quads();

	int main(int argc,char *argv[]){

		if(argc != 3){
			printf("lathos!!\n");
			return 0;
		}
		arxeion=fopen(argv[1],"r");
		if(arxeion==NULL){
			printf("ERROR while opening file!!\n");
			return 0;
		}

		arxeion2=fopen(argv[2],"w");
		if(arxeion2==NULL){
			printf("ERROR while opening file!!\n");
			return 0;
		}

		token=lex(str);//diabazo tin proti lektiki monada
		PROGRAM(); //kalo tin arxikh synarthsh tou syntaktikou analyth
		print_quads(); //typonoume oles tis tetrades tou endiamesou
		fclose(arxeion);
		return 0;
	}

int lex(char token1[MEGETHOS]){
		int katastash;
		int i;
		int input;
		char s;
		int pinakas[9][21]={

			{0,ENDOF_TOKEN,1,2,SYN_TOKEN,MION_TOKEN,EPI_TOKEN,3,6,7,ISON_TOKEN,8,EROT_TOKEN,KOMMA_TOKEN,OPEN_TOKEN,CLOSE_TOKEN,OPEN1_TOKEN,CLOSE2_TOKEN,OPEN3_TOKEN,CLOSE3_TOKEN,ERROR},
			{AN1,AN1,1,1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1,AN1},
			{AKS2,AKS2,AKS2,2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2,AKS2},
			{DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,4,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN,DIA_TOKEN},
			{4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
			{4,4,4,4,4,4,5,0,4,4,4,4,4,4,4,4,4,4,4,4,4},
			{MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,DIAFOR_TOKEN,MIKRISON_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN,MIKR_TOKEN},
			{MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGISON_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN,MEGAL_TOKEN},
			{ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ANATH_TOKEN,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,}
		};


		katastash = 0;//gia na ksekinhso apo tin arxikh katastash
		i=0; //gia na pav stin prvti thesi toy string
		while(katastash >=0 && katastash <9){
			s=getc(arxeion);//diabazo ton epomeno xaraktira apo to arxeio
			if(isspace(s)){
				input=0;
			}else if(s == EOF){
				input=1;
			}
			else if(isalpha(s)){
				input=2;
			}else if (isdigit(s)){
				input=3;
			}else if(s == '+'){
				input=4;
			}else if(s == '-'){
				input=5;
			}else if(s == '*'){
				input=6;
			}else if(s == '/'){
				input=7;
			}else if(s == '<'){
				input=8;
			}else if(s == '>'){
				input=9;
			}else if(s == '='){
				input=10;
			}else if(s == ':'){
				input=11;
			}else if(s == ';'){
				input=12;
			}else if(s == ','){
				input=13;
			}else if(s == '{'){
				input=14;
			}else if(s == '}'){
				input=15;
			}else if(s == '('){
				input=16;
			}else if(s == ')'){
				input=17;
			}else if(s == '['){
				input=18;
			}else if(s == ']'){
				input=19;
			}else {
				input=20;
			}
			katastash=pinakas[katastash][input]; //paei sth epomenh katastash
			token1[i]=s; //apoth tin epomenh lektikh monada
			i++; //kathe fora pou diabazo ayksano to i kata ena
			if(katastash == 0){ //oso eimai sto miden den thelo na kratiso kati ara bazo i=0
			i=0;
			}

		}
	token1[i]='\0';
	if(katastash == MIKR_TOKEN || katastash == AN1 || katastash == AKS2 || katastash == PRS3 || katastash == MEGAL_TOKEN  ){
		ungetc(s,arxeion);//epistrefo sto arxeio ton teleytaio xarakthra pou exo diabasei
		token1[i-1]='\0';
	}
	if(katastash == AN1 ){
		if(strcmp(token1,"and")==0){
			return AND_TOKEN;
		}
		if(strcmp(token1,"function")==0){
			return FUNCTION_TOKEN;
		}
		if(strcmp(token1,"not")==0){
			return NOT_TOKEN;
		}
		if(strcmp(token1,"or")==0){
			return OR_TOKEN;
		}
		if(strcmp(token1,"var")==0){
			return VAR_TOKEN;
		}
		if(strcmp(token1,"print")==0){
			return PRINT_TOKEN;
		}
		if(strcmp(token1,"for")==0){
			return FOR_TOKEN;
		}
		if(strcmp(token1,"return")==0){
			return RETURN_TOKEN;
		}
		if(strcmp(token1,"do")==0){
			return DO_TOKEN;
		}
		if(strcmp(token1,"if")==0){
			return IF_TOKEN;
		}
		if(strcmp(token1,"to")==0){
			return TO_TOKEN;
		}
		if(strcmp(token1,"while")==0){
			return WHILE_TOKEN;
		}
		if(strcmp(token1,"else")==0){
			return ELSE_TOKEN;
		}
		if(strcmp(token1,"in")==0){
			return IN_TOKEN;
		}
		if(strcmp(token1,"step")==0){
			return STEP_TOKEN;
		}
		if(strcmp(token1,"call")==0){
			return CALL_TOKEN;
		}
		if(strcmp(token1,"procedure")==0){
			return PROCEDURE_TOKEN;
		}
		if(strcmp(token1,"inout")==0){
			return INOUT_TOKEN;
		}
		if(strcmp(token1,"program")==0){
			return PROGRAM_TOKEN;
		}
		return ID_TOKEN;
	}
	else if(katastash == AKS2){
		return AKERST_TOKEN;
	}else if(katastash == PRS3){
		return PRAGMATIKH_TOKEN;
	}
	return katastash;
	}
void PROGRAM(){
	char name[MEGETHOS];
	if(token == PROGRAM_TOKEN){
		token=lex(str);
		if(token == ID_TOKEN){
			create_scope(str);
			strcpy(name,str);
			token=lex(str);
			BLOCK(name);
			printtable();
			remove_scope();
		}else{
			printf("ERROR program name expected!!");
			exit(1);
		}
	}else{
		printf("ERROR i want program and i found:%s\n",str);
		exit(1);
	}
}

void BLOCK(char name[MEGETHOS]){
		if(token == OPEN_TOKEN){
			DECLARATIONS();
			SUBPROGRAMS();
			genquad("begin_block",name,"_","_");
			SEQUENCE();
			if(token == CLOSE_TOKEN){
				token=lex(str);
				genquad("end_block",name,"_","_");
			}else{
				printf("ERROR i want '}' and i found:%s,%d\n",str,token);
				exit(1);
			}
		}else{
			printf("ERROR i want '{' and i found:%s\n",str);
			exit(1);
		}

}
void DECLARATIONS(){
	token=lex(str);
	while(token == VAR_TOKEN){
		token=lex(str);
		if(token == ID_TOKEN){
			VARLIST();
		}
		if(token == EROT_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want ';' and i found:%s\n",str);
			exit(1);
		}
	}
}

void VARLIST(){
	if(token == ID_TOKEN){
		add_entity(str,VARIABLE,0);
		token=lex(str);
		while(token == KOMMA_TOKEN){
			token=lex(str);
			if(token == ID_TOKEN){
				add_entity(str,VARIABLE,0);
				token=lex(str);
			}else{
				printf("ERROR i want 'ID' and i found:%s\n",str);
				exit(1);
			}
		}
	}
}
void SUBPROGRAMS(){
	while(token == PROCEDURE_TOKEN || token == FUNCTION_TOKEN){
		FUNC();
	}
}

void FUNC(){
	char name[MEGETHOS];
	if(token == PROCEDURE_TOKEN){
		token=lex(str);
		if(token==ID_TOKEN){
			strcpy(name,str);
			token=lex(str);
			add_entity(name,FUNCTION,0);
			create_scope(name);
			FUNCBODY(name);
			remove_scope();
		}
	}
	else if (token==FUNCTION_TOKEN){
		token=lex(str);
		if(token==ID_TOKEN){
			strcpy(name,str);
			token=lex(str);
			add_entity(name,FUNCTION,0);
			create_scope(name);
			FUNCBODY(name);
			remove_scope();
		}
	}else{
		printf("ERROR i want procedure or function and i found: %s\n",str);
		exit(1);
	}
}

void FUNCBODY(char name[MEGETHOS]){
	//char name[MEGETHOS];
	strcpy(name,str);
	printf("funcbodhy %s\n",name);
	token=lex(str);

	FORMALPARS();

	printf("funcbodhy block %s\n",name);
	BLOCK(name);
}

void FORMALPARS(){
	if(token == OPEN1_TOKEN){
		token=lex(str);
		if(token != CLOSE2_TOKEN){
			FORMALPARLIST();
		}
		if(token == CLOSE2_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}
	else{
		printf("ERROR i want '(' and i found:%s\n",str);
		exit(1);
	}
}

void FORMALPARLIST(){
	FORMALPARITEM();
	while(token == KOMMA_TOKEN){
		token=lex(str);
		FORMALPARITEM();
	}
}

void FORMALPARITEM(){
	if(token == IN_TOKEN || token == INOUT_TOKEN){
		token=lex(str);
		if(token==ID_TOKEN){
			token=lex(str);
		}
		else{
			printf("ERROR i want name and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want 'IN' or 'INOUT' and i found:%s\n",str);
		exit(1);
	}
}

void SEQUENCE(){
	STATEMENT();
	while(token == EROT_TOKEN){
		token = lex(str);
		STATEMENT();
	}
}

void BRACKETS_SEQ(){
	if(token == OPEN_TOKEN){
		token = lex(str);
		SEQUENCE();
		if(token == CLOSE_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want '}' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want '{' and i found:%s\n",str);
		exit(1);
	}
}

void BRACK_OR_STAT(){
	if(token == OPEN_TOKEN){
		BRACKETS_SEQ();
	}else{
		STATEMENT();
	}
}

void STATEMENT(){
	if(token == ID_TOKEN){
		ASSIGMENT_STAT();
	}else if(token == IF_TOKEN){
		IF_STAT();
	}else if(token == WHILE_TOKEN){
		WHILE_STAT();
	}else if(token == DO_TOKEN){
		DO_WHILE_STAT();
	}else if(token == FOR_TOKEN){
		FOR_STAT();
	}else if(token == CALL_TOKEN){
		CALL_STAT();
	}else if(token == RETURN_TOKEN){
		RETURN_STAT();
	}else if(token == PRINT_TOKEN){
		PRINT_STAT();
	}
}

void ASSIGMENT_STAT(){
	char place[MEGETHOS];
	char name[MEGETHOS];
	if(token == ID_TOKEN){
		strcpy(name,str);
		token=lex(str);
		if(token == ANATH_TOKEN){
			token=lex(str);
			printf("ASS %s %d\n",str,token);
			EXPRESSION(place);
			genquad(":=",place,"_",name);
		}else{
			printf("ERROR i want ':=' and i found:%s %d\n",str,token);
			exit(1);
		}
	}else{
		printf("ERROR i want 'ID' and i found:%s\n",str);
		exit(1);
	}
}

void IF_STAT(){
	struct precept c;
	struct list *list_1;
	token = lex(str);
	if(token == OPEN1_TOKEN){
		token = lex(str);
		CONDITION(&c);
		if(token == CLOSE2_TOKEN){
			token=lex(str);
			backpatch(c.true,nextquad());
			BRACK_OR_STAT();
			list_1=makelist(nextquad());
			genquad("jump","_","_","_");
			backpatch(c.false,nextquad());
			ELSEPART();
			backpatch(list_1,nextquad());
		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want '(' and i found:%s\n",str);
		exit(1);
	}
}

void ELSEPART(){
	if(token == ELSE_TOKEN){
		token=lex(str);
		BRACK_OR_STAT();
	}
}

void DO_WHILE_STAT(){
	struct precept c;
	int a;
	char tmp[MEGETHOS];

	int do_start=nextquad();
	//token = lex(str);
	if(token == DO_TOKEN){
		token=lex(str);
		BRACK_OR_STAT();
		if(token == WHILE_TOKEN){
			token=lex(str);
			if(token == OPEN1_TOKEN){
				token=lex(str);
				CONDITION(&c);
				backpatch(c.true,do_start);
				backpatch(c.false,nextquad());
				if(token == CLOSE2_TOKEN){
					token=lex(str);
				}else{
					printf("ERROR i want ')' and i found:%s\n",str);
					exit(1);
				}
			}else{
				printf("ERROR i want '(' and i found:%s\n",str);
				exit(1);
			}
		}else{
			printf("ERROR i want 'while' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want 'DO' and i found:%s\n",str);
		exit(1);
	}
}

void RETURN_STAT(){
	struct precept c;
	char place[MEGETHOS];
	token = lex(str);
	if(token == OPEN1_TOKEN){
		token=lex(str);
		EXPRESSION(place);
		genquad("retv","_","_",place);
		if(token == CLOSE2_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want '(' and i found:%s\n",str);
		exit(1);
	}
}

void PRINT_STAT(){
	char place[MEGETHOS];
	token=lex(str);
	if(token == OPEN1_TOKEN){
		token=lex(str);
		EXPRESSION(place);
		genquad("out","_","_",place);
		if(token == CLOSE2_TOKEN){
			token = lex(str);
		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want '(' and i found:%s\n",str);
		exit(1);
	}
}

void WHILE_STAT(){
	struct precept c;
	char while_start[MEGETHOS];

	sprintf(while_start,"%d",nextquad());

	token=lex(str);
	if(token == OPEN1_TOKEN){
		token=lex(str);
		CONDITION(&c);
		if(token == CLOSE2_TOKEN){
			token=lex(str);
			backpatch(c.true,nextquad());

			BRACK_OR_STAT();
			genquad("jump","_","_",while_start);
			backpatch(c.false,nextquad());

		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want '(' and i found:%s\n",str);
		exit(1);
	}
}

void STEP_PART(char place[MEGETHOS]){
	if(token == STEP_TOKEN){
		token=lex(str);
		EXPRESSION(place);
	}
}

void CALL_STAT(){
	token=lex(str);
	if(token == ID_TOKEN){
		token=lex(str);
		ACTUALPARS();
	}else{
		printf("ERROR i want 'ID' and i found:%s\n",str);
		exit(1);
	}
}

void ACTUALPARS(){
	if(token == OPEN1_TOKEN){
		token=lex(str);
		ACTUALPARLIST();
		if(token == CLOSE2_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want '(' and i found:%s\n",str);
		exit(1);
	}
}

void ACTUALPARLIST(){
	ACTUALPARITEM();
	while(token == KOMMA_TOKEN){
		token=lex(str);
		ACTUALPARITEM();
	}
}

void ACTUALPARITEM(){
	char place[MEGETHOS];
	if(token == IN_TOKEN){
		token=lex(str);
		EXPRESSION(place);
	}else if(token == INOUT_TOKEN){
		token=lex(str);
		if(token == ID_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want 'ID' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want 'IN' or 'INOUT' and i found:%s\n",str);
		exit(1);
	}
}

void CONDITION(struct precept *c){
	struct precept b1,b2;
	BOOLTERM(&b1);
	c->true=b1.true;
	c->false=b1.false;

	while(token == OR_TOKEN){
		token=lex(str);
		backpatch(c->false,nextquad());
		BOOLTERM(&b2);
		c->false = b2.false;
		c->true=merge(c->false,b2.true);
	}
}

void BOOLTERM(struct precept *s){
	struct precept b1,b2;
	BOOLFACTOR(&b1);
	s->true=b1.true;
	s->false=b1.false;
	while(token == AND_TOKEN){
		token=lex(str);
		backpatch(s->true,nextquad());
		BOOLFACTOR(&b2);
		s->true=b1.true;
		s->false=merge(s->false,b2.false);
	}
}

void BOOLFACTOR(struct precept *b1){
	char place1[MEGETHOS];
	char place2[MEGETHOS];
	char oper[MEGETHOS];
	struct precept c;


	if(token == NOT_TOKEN){
		token=lex(str);
		if(token == OPEN3_TOKEN){
			token=lex(str);
			CONDITION(&c);
			b1->true=c.false;
			b1->false=c.true;
			if(token == CLOSE3_TOKEN){
				token=lex(str);
			}else{
				printf("ERROR i want ']' and i found:%s\n",str);
				exit(1);
			}
		}else{
			printf("ERROR i want '[' and i found:%s\n",str);
			exit(1);
		}
	}else if(token == OPEN3_TOKEN){
		token=lex(str);
		CONDITION(&c);
		b1->true=c.true;
		b1->false=c.false;
		if(token == CLOSE3_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want ']' and i found:%s\n",str);
			exit(1);
		}
	}else{
		EXPRESSION(place1);
		printf("boolfactor1 %s %d\n",str,token);

		RELATIONAL_OPER(oper);

		EXPRESSION(place2);
		b1->true=makelist(nextquad());
		genquad(oper,place1,place2,"_");
		b1->false=makelist(nextquad());
		genquad("jump","_","_","_");
	}
}
void EXPRESSION(char place[MEGETHOS]){
	char *t;
	char A_place[MEGETHOS];
	char B_place[MEGETHOS];
	char oper[MEGETHOS];
	TERM(A_place);
	while(token == SYN_TOKEN || token == MION_TOKEN){
		strcpy(oper,str);
		token=lex(str);
		TERM(B_place);
		t=newTemp();
		genquad(oper,A_place,B_place,t);
		strcpy(A_place,t);
	}
	strcpy(place,A_place);
}

void TERM(char C_place[MEGETHOS]){
	char *t_2;
	char D_place[MEGETHOS];
	char E_place[MEGETHOS];
	char oper[MEGETHOS];
	FACTOR(D_place);
	while(token == EPI_TOKEN || token== DIA_TOKEN){
		strcpy(oper,str);

		token=lex(str);
		FACTOR(E_place);
		t_2=newTemp();
		genquad(oper,D_place,E_place,t_2);
		strcpy(D_place,t_2);
	}
	strcpy(C_place,D_place);
}

void FACTOR(char F_place[MEGETHOS]){
	char G_place[MEGETHOS];
	if(token == AKERST_TOKEN || token == PRS3){
		strcpy(F_place,str);
		token=lex(str);
	}else if(token == OPEN1_TOKEN){
		token=lex(str);
		EXPRESSION(G_place);
		strcpy(F_place,G_place);
		if(token == CLOSE2_TOKEN){
			token=lex(str);
		}else{
			printf("ERROR i want ')' and i found:%s\n",str);
			exit(1);
		}
	}else if(token == ID_TOKEN){
		strcpy(F_place,str);
		token=lex(str);
		IDTAIL();
	}else{
		printf("ERROR i want 'const','(','ID' and i found:%s?%d\n",str,token);
		exit(1);
	}
}

void IDTAIL(){
	if(token == OPEN1_TOKEN){
		ACTUALPARS();
	}
}

void RELATIONAL_OPER(char oper[MEGETHOS]){
	if(token == ISON_TOKEN){
		strcpy(oper,str);
		token=lex(str);
	}else if(token == MEGAL_TOKEN){
		strcpy(oper,str);
		token=lex(str);
		printf("assdfsdfsdf %d\n",token);
	}else if( token == MIKR_TOKEN){
		strcpy(oper,str);
		token=lex(str);
	}else if(token == MIKRISON_TOKEN){
		strcpy(oper,str);
		token=lex(str);
	}else if(token == MEGISON_TOKEN){
		strcpy(oper,str);
		token=lex(str);
	}else if(token == DIAFOR_TOKEN){
		strcpy(oper,str);
		token=lex(str);
	}else{
		printf("ERROR i want '=','<','>','>=','<=','<>' and i found:%s\n",str);
		exit(1);
	}
}

void OPTIONAL_SIGN(){
	if(token == SYN_TOKEN || token == MION_TOKEN){
		token=lex(str);
	}
}

void FOR_STAT(){
	char place1[MEGETHOS];
	char place2[MEGETHOS];
	char place3[MEGETHOS];
	token=lex(str);
	if(token == ID_TOKEN){
		token=lex(str);
		if(token == ANATH_TOKEN){
			token=lex(str);
			EXPRESSION(place1);
			if(token == TO_TOKEN){
				token=lex(str);
				EXPRESSION(place2);
				STEP_PART(place3);
			}else{
				printf("ERROR i want 'TO' and i found:%s\n",str);
				exit(1);
			}
		}else{
			printf("ERROR i want ':=' and i found:%s\n",str);
			exit(1);
		}
	}else{
		printf("ERROR i want 'ID' and i found:%s\n",str);
		exit(1);
	}
}


int nextquad(){
	return q_num;
};
void genquad(char op[MEGETHOS],char x[MEGETHOS],char y[MEGETHOS],char z[MEGETHOS]){
	struct quad *x_index;
	struct quad *prev_index;
	struct quad *tmp_index;
	x_index = (struct quad *)malloc(sizeof(struct quad));
	if(x_index == NULL){
		exit(1);
	}
	strcpy(x_index->op[0],op);
	strcpy(x_index->op[1],x);
	strcpy(x_index->op[2],y);
	strcpy(x_index->op[3],z);
	x_index->number=q_num;
	q_num++;
	x_index->next=NULL;
	prev_index=NULL;
	tmp_index=Quad_index;
	while(tmp_index != NULL){
		prev_index = tmp_index;
		tmp_index=tmp_index->next;
	}
	if(prev_index == NULL){
		Quad_index=x_index;
	}else{
		prev_index->next=x_index;
	}
}
char *newTemp(){
	char *s;
	s=(char *)malloc(MEGETHOS*sizeof(char));
	if(s==NULL){
		exit(1);
	}
	sprintf(s,"T_%d",tmp_2);
	add_entity(s,VARIABLE,0);
	tmp_2=tmp_2+1;
	return s;
}

struct list *makelist(int x){
	struct list *l;
	l=(struct list *)malloc(sizeof(struct list));
	if(l == NULL){
		exit(1);
	}
	l->quad=x;
	l->next=NULL;
	return l;
}
struct list *merge(struct list *l1,struct list *l2){
	struct list *prev_index;
	struct list *tmp_index;
	if(l1 == NULL){
		return l2;
	}else if(l2 == NULL){
		return l1;
	}
	prev_index=NULL;
	tmp_index = l1;
	while(tmp_index != NULL){
		prev_index=tmp_index;
		tmp_index = tmp_index->next;
	}
	prev_index->next = l2;
	return l1;
}

void backpatch(struct list *l_index,int z){
	struct list *ltmp_index;
	struct quad *ztmp_index;
	ltmp_index=l_index;
	while(ltmp_index != NULL){
		ztmp_index = Quad_index;
		while(ztmp_index != NULL){
			if(ztmp_index->number == ltmp_index->quad){
				sprintf(ztmp_index->op[3],"%d",z);
				break;
			}
			ztmp_index=ztmp_index->next;
		}
		ltmp_index=ltmp_index->next;
	}
}

struct list *emptylist(){
	struct list *l2;
	l2=(struct list *)malloc(sizeof(struct list));
	if(l2 == NULL){
		exit(1);
	}
	l2->quad=0;
	l2->next=NULL;
	return l2;
}

void print_quads(){
	struct quad *tmp_index=Quad_index;


	while(tmp_index != NULL){
		fprintf(arxeion2,"%d %s %s %s %s\n",tmp_index->number,tmp_index->op[0],tmp_index->op[1],tmp_index->op[2],tmp_index->op[3]);
		/*if(strcmp(tmp_index->op[0],":=")==0){
			fprintf(arxeion3,"%s=%s\n",tmp_index->op[3],tmp_index->op[1]);
		}*/
		tmp_index=tmp_index->next;
	}


}
void create_scope(char name[MEGETHOS]){
	struct scope *news_scope;
	news_scope=(struct scope *)malloc(sizeof(struct scope));
	strcpy(news_scope->name,name);
	news_scope->entit_list=NULL;
	if(SCOPES == NULL){
		SCOPES=news_scope;
		news_scope->vathos=0;
		news_scope->next=NULL;
	}else{
		news_scope->vathos=SCOPES->vathos+1;
		news_scope->next=SCOPES;
		SCOPES=news_scope;
	}

}
void remove_scope(){
	if(SCOPES==NULL){
		printf("Den yparxei scope gia diagrafh!!");
		exit(1);
	}
	SCOPES=SCOPES->next;
}
void add_entity(char name[MEGETHOS],int type,int paraMode){
	struct entity *new_entity;
	struct entity *tmp_1;
	struct entity *prev;
	int last_set=-1;
	new_entity=(struct entity *)malloc(sizeof(struct entity));
	strcpy(new_entity->name,name);
	new_entity->type=type;
	new_entity->paraMode=paraMode;
	new_entity->next=NULL;
	new_entity->vathos=SCOPES->vathos;
	prev=NULL;
	tmp_1=SCOPES->entit_list;
	while(tmp_1 != NULL){
		prev=tmp_1;
		if(tmp_1->type != FUNCTION){
			last_set=tmp_1->offset;
		}
		tmp_1=tmp_1->next;
	}
	if(prev==NULL){
		SCOPES->entit_list=new_entity;
		new_entity->offset=12;
	}else{
		prev->next=new_entity;
		new_entity->offset=last_set+4;
	}
}
struct entity *search_entity(char name[MEGETHOS]){
	struct scope *tmp_2;
	struct entity *entities;
	tmp_2=SCOPES;
	while(tmp_2!=NULL){
		entities=tmp_2->entit_list;
		while(entities !=NULL){
			if(strcmp(entities->name,name)==0){
				return entities;
			}
			entities=entities->next;
		}
		tmp_2=tmp_2->next;
	}
	return NULL;
}
void printtable(){
	struct entity *entity_tmp;
	struct scope *scope_tmp;
	scope_tmp=SCOPES;
	while(scope_tmp!=NULL){
		entity_tmp=scope_tmp->entit_list;
		printf("SCOPE: %s\n",scope_tmp->name);
		printf("\t");
		while(entity_tmp !=NULL){
			if(entity_tmp->type==VARIABLE){
				printf("%s (%d) ->",entity_tmp->name,entity_tmp->offset);
			}else if(entity_tmp->type==PARAMETER){
				printf("%s (PARAM - %d) ->",entity_tmp->name,entity_tmp->offset);
			}else{
				printf("%s->",entity_tmp->name);
			}
			entity_tmp=entity_tmp->next;
		}
		printf("\n");
		scope_tmp=scope_tmp->next;
	}
}
void loadta(char t[MEGETHOS],int a){
	struct entity *ent;
	ent=search_entity(t);
	if(isdigit(t[0])){
		fprintf(final_arxeion,"movi R[%d], %s\n",a,t);
		return;
	}else if(ent->vathos==0){
		fprintf(final_arxeion,"movi R[%d],M[%d]\n",a,600+ent->offset);
	}else if(ent->vathos==SCOPES->vathos && ent->type==VARIABLE){
		fprintf(final_arxeion,"movi R[%d],M[R[0] + %d]\n",a,ent->offset);
	}else if(ent->vathos==SCOPES->vathos && ent->type==PARAMETER && ent -> paraMode==VALUE){
		fprintf(final_arxeion,"movi R[%d],M[R[0] +%d\n]",a,ent->offset);
	}else if(ent->vathos==SCOPES->vathos && ent->type==PARAMETER && ent->paraMode==VALUE){
		fprintf(final_arxeion,"movi R[255],M[R[0] + %d]\n",ent->offset);
		fprintf(final_arxeion,"movi R[%d],M[R[255]]\n",a);
	}

}
void storewz(char w[MEGETHOS],int z){
	struct entity *ent_a;
	ent_a=search_entity(w);
	if(ent_a->vathos==0){
		fprintf(final_arxeion,"movi M[%d],R[%d]\n",600+ent_a->offset,z);
	}else if(ent_a->vathos==SCOPES->vathos && ent_a->type==VARIABLE){
		fprintf(final_arxeion,"movi M[R[0] + %d], R[%d]\n",ent_a->offset,z);
	}else if(ent_a->vathos==SCOPES->vathos && ent_a->type==PARAMETER && ent_a->paraMode==VALUE){
		fprintf(final_arxeion,"movi M[R[0] + %d], R[%d]\n",ent_a->offset,z);
	/*}else if(ent_a->vathos==SCOPES->vathos && ent_a->type=PARAMETER && ent_a->paraMode==VALUE){
		fprintf(final_arxeion,"movi R[255], M[R[0] + %d]\n",ent_a->offset);
		fprintf(final_arxeion,"movi M[R[255]], R[%d]\n",z);
	}*/
	}
}

















