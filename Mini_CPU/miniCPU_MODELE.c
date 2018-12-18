/*
 * -------------------------- TP du module Archi -------------------------
 *
 * ATTENTION : un outil de d�tection de plagiat logiciel sera utilis� lors de la correction, vous avez donc tout int�r�t � effectuer un travail PERSONNEL
 *
 * Un mot/registre de NBITS bits (par d�faut NBITS=16) est repr�sent� par un tableau d'entiers �gaux � 0 ou 1.
 * Une ALU est repr�sent�e par une structure ALU, avec registre accumulateur et registre d'�tat.
 * Un CPU (tr�s tr�s simplifi�) est repr�sent� par une ALU et quelques registres n�cessaires pour stocker les r�sultats interm�diaires.
 *
 * Certaines fonctions vous sont fournies, d'autres sont � implanter ou � compl�ter, de pr�f�rence dans l'ordre o� eles sont indiqu�es.
 * Il vous est fortement conseill� de lire attentivement l'ensemble des commentaires.
 *
 * Parmi les op�rations arithm�tiques et logiques, seules 4 op�rations de base sont directement fournies par l'ALU, les autres doivent �tre d�crites comme des algorithmes
 * travaillant � l'aide des op�rateurs de base de l'ALU simplifi�e et pouvant utiliser les registres du CPU.
 *
 * La fonction main() vous permet de tester au fur et � mesure les fonctions que vous implantez.
 *
 * ----------------------------------------------------------------------------------------------
 *
 * author: B. Girau
 * version: 2018-19
 */
#include <stdio.h>
#include <stdlib.h>

#define NBITS 16  // attention, votre programme doit pouvoir �tre adapt� � d'autres tailles juste en modifiant la valeur de cette constante
// en ayant toujours NBITS < 32

/////////////////////////////////////////////////////////
// d�finition de types
/////////////////////////////////////////////////////////

typedef struct {
  int* accu;
  int* flags; // indicateurs ZF CF OF NF
} ALU;

typedef struct {
  ALU alu;
  int* R0;
  int* R1;
  int* R2;
} CPU;

/////////////////////////////////////////////////////////
// fonctions d'initialisation
/////////////////////////////////////////////////////////

/*
 * allocation d'un mot entier de NBITS bits initialis� � 0
 */
int* word() {
  int* tab;
  int i;
  tab=(int*)malloc(NBITS*sizeof(int));
  for(i=0;i<NBITS;i++) tab[i]=0;
  // poids faible : tab[0]
  // poids fort : tab[NBITS-1]
  return tab;
}

/*
 * Retourne une cha�ne de caract�res d�crivant les NBITS bits
 */
char* toString(int* word) {
  int i,j=0;
  char* s=(char*)malloc((10+NBITS)*sizeof(char));
  for (i=NBITS-1;i>=0;i--) {
    if (word[i]==1) s[j]='1';
    else s[j]='0';
    j++;
  }
  return s;
}
/*
 * Initialisation du mot (mot de NBITS bits, codant un entier en C�2) avec une valeur enti�re.
 */
void setValue(int* worde,int n) {
  int n_low = n & 0x7FFFFFFF;
  // revient � mettre � 0 le bit de poids fort en 32 bits
  // on peut alors travailler sur la partie positive du codage de n
  // remarque : si n est bien codable en Ca2 sur NBITS, et si n est n�gatif, on r�cup�re quand m�me le codage de n sur NBITS en Ca2 en prenant les NBITS de poids faible de n_low
  
  /*worde=(int*)malloc(NBITS*sizeof(int));
  worde = word();*/
  int i,j;
  i = n_low ;
  char* num ;
  //Conversion du nombre en binaire
  
  for(j= 0 ; j<=NBITS ; j++){
    if( (i/2) >= 0){
      worde[j] = i%2 ;
    }
    i = i/2 ;
    
  }
  num = toString(worde);
  
  if(n>=0){
    printf("%s\n" , num);
  }
  else{
  }
}

/*
 * instanciation d'un mot de NBITS bits initialis� avec la valeur n
 */
int* initWord(int n) {
  int* tab=word();
  setValue(tab,n) ;
  return tab;
}
    
/*
 * Initialisation du mot (mot de NBITS bits) par recopie des bits du mot en param�tre.
 */
void copyValue(int* word,int* src) {
  int i ;
  for(i =0 ; i< NBITS ; i++){
    word[i] = src[i];
  }
  char* num = toString(word);
    
}

/*
 * instanciation d'un mot de NBITS bits initialis� par recopie d'un mot
 */
int* copyWord(int* src) {
  int* tab=word();
  copyValue(tab,src) ;
  return tab;
}

/*
 * initialise l'ALU
 */
ALU initALU() {
  ALU res;
  res.accu=word();
  res.flags=(int*)malloc(4*sizeof(int));
  return res;
}

/*
 * initialise le CPU
 */
CPU initCPU() {
  CPU res;
  res.alu=initALU();
  res.R0=(int*)malloc(NBITS*sizeof(int));
  res.R1=(int*)malloc(NBITS*sizeof(int));
  res.R2=(int*)malloc(NBITS*sizeof(int));
  return res;
}

/*Fonction puissance
 *  */
int puiss(int n , int m ){
  int puis =1;
  int i ;
  for(i=0 ; i<m ; i++){
    puis = puis*n;
  }  // � compl�ter   //nand(a , a)

  return puis;
}

/////////////////////////////////////////////////////////
// fonctions de lecture
/////////////////////////////////////////////////////////

/*
 * Retourne la valeur enti�re sign�e repr�sent�e par le mot (compl�ment � 2).
 */    
int intValue(int* word) {
  int i , sum;
  for(i = 0 ; i <= NBITS-2 ; i++){
    sum = word[i]*puiss(2,i);
  }
  sum = sum - word[NBITS-1]*puiss(2,NBITS-1);
  return sum;
  // � compl�ter
}



/*
 * Retourne l'�criture des indicateurs associ�s � l'ALU.
 */
char* flagsToString(ALU alu) {
  char *string=(char*)malloc(10*sizeof(char));
  sprintf(string,"z%dc%do%dn%d",alu.flags[0],alu.flags[1],alu.flags[2],alu.flags[3]);
  return string;
}
  // � compl�ter   //nand(a , a)

/*
 * affiche � l'�cran le contenu d'une ALU
 */
void printing(ALU alu) {
  //char* one = NULL , two = NULL ;

  char* two = toString(alu.accu);
  char* one = flagsToString(alu);
  printf("Accumulateur: %s\n",two);
  printf("Flags: %s\n",one);
    // � compl�ter
}

/////////////////////////////////////////////////////////
// fonctions de manipulations �l�mentaires
/////////////////////////////////////////////////////////

/*
 * Mise � la valeur b du bit sp�cifi� dans le mot
 */
void set(int* word,int bitIndex,int b) {
  if ((bitIndex > NBITS-1) || (bitIndex < 0)) 
    printf("valeur d'index incorrecte\n");
  word[bitIndex] = b ;
}

/*
 * Retourne la valeur du bit sp�cifi� dans le mot
 */
int get(int* word,int bitIndex) {
  if ((bitIndex > NBITS-1) || (bitIndex < 0)) 
    printf("valeur d'index incorrecte\n");
  return word[bitIndex] ;
}

/*
 * Positionne l'indicateur ZF en fonction de l'�tat de l'accumulateur
 */
void setZ(ALU alu) {
  if(*alu.accu==0){
    alu.flags[0] = 1 ;
  }
  else{
    alu.flags[0] = 0 ;
  }
}

/////////////////////////////////////////////////////////
// op�rateurs de base de l'ALU
// IMPORTANT : les indicateurs doivent �tre mis � jour
/////////////////////////////////////////////////////////

/*
 * Stocke le param�tre dans le registre accumulateur
 */
void pass(ALU alu,int* B) {
  copyValue(alu.accu , B);
  setZ(alu);
  if(*B < 0){
    alu.flags[3] = 1 ;
  }
    
}

/*
 * Effectue un NAND (NON-ET) entre le contenu de l'accumulateur et le param�tre.
 */
void nand(ALU alu,int* B) {
  int i;
  for(i=0 ; i<NBITS ; i++){
    if(alu.accu[i]==0){
      alu.accu[i]=1;
    }
    else{
      alu.accu[i]=0;
    }
    if(B[i]==0){
      B[i]=1;
    }
    else{
      B[i]=0;
    }
    
    if((alu.accu[i]==0 && B[i]==0) || (alu.accu[i]==1 && B[i]==1)){
      alu.accu[i]=1;
    }
    else{
      alu.accu[i]=0;
    }
  }
}

/*
 * D�cale le contenu de l'accumulateur de 1 bit vers la droite
 */
void shift(ALU alu) {
  int b = intValue(alu.accu);
  b =b/2;
  
  int* mot = initWord(b);
  alu.accu = mot ;
  
  // � v�rifier
}

/*
 * module Full Adder : a+b+c_in = s + 2 c_out
 * retourne un tableau contenant s et c_out
 */
int* fullAdder(int a,int b,int c_in) {
  int* res=(int*)malloc(2*sizeof(int));
  // � compl�ter
  return res;
}

/*
 * Additionne le param�tre au contenu de l'accumulateur (addition enti�re C�2).
 * Les indicateurs sont positionn�s conform�ment au r�sultat de l'op�ration.
 */
void add(ALU alu,int* B) {
  // � compl�ter
}

////////////////////////////////////////////////////////////////////
// Op�rations logiques :
////////////////////////////////////////////////////////////////////

/*
 * N�gation.
 */
void not(CPU cpu){
  nand(cpu.alu , cpu.alu);  //nand(a , a)
}

/*
 * Et.
 */
void and(CPU cpu,int* B) {
  copyValue(cpu.R0 , cpu.alu);
  nand( cpu
  not(nand(cpu.alu , B)); //not(nand(a,a))
}


/*
 * Ou.
 */
void or(CPU cpu,int* B) {
  nand(nand(cpu.alu , cpu.alu) , nand(B , B));  ///nand(nand(a,a) , nanad(b,b))
}

/*
 * Xor.
 */
void xor(CPU cpu,int* B) {
  or(and(not(cpu), B) , and(cpu , not(B)));// or(and(not(a) , b) , and(a , not(b)))
}

/*
 * D�cale le receveur de |n| positions.
 * Le d�calage s'effectue vers la gauche si n>0 vers la droite dans le cas contraire.
 * C'est un d�calage logique (pas de report du bit de signe dans les positions 
 * lib�r�es en cas de d�calage � droite).
 * L'indicateur CF est positionn� avec le dernier bit "perdu".
 */
void logicalShift(CPU cpu,int n) {
  // � compl�ter
}

/////////////////////////////////////////////////////////
// Op�rations arithm�tiques enti�res
/////////////////////////////////////////////////////////

/*
 * Oppos�.
 */
void opp(CPU cpu) {
  // � compl�ter
}

/*
 * Soustraction.
 */
void sub(CPU cpu,int* B) {
  // � compl�ter
}

/*
 * Multiplication.
 */
void mul(CPU cpu,int* B) {
  // � compl�ter
}

/////////////////////////////////////////////////////////
// Programme de test
/////////////////////////////////////////////////////////

int main(int argc,char *argv[]) {
  
  /*
    Ce programme est fourni � titre d'exemple pour permettre de tester simplement vos fonctions.
    Il vous est bien entendu possible de le modifier/compl�ter, ou encore d'�crire vos propres fonctions de test.
   */
  
  int* operand;
  ALU alu;
  CPU cpu;
  
  int chosenInt,integer ;
  int go_on = 1 ;
  
  char* menu =     
    "              Programme de test\n\n0  Quitter\n1  setValue(operande,int)\n2  pass(alu,operande)\n3  printing(alu)\n4  afficher toString(operande)\n5  afficher intValue(operande)\n6  afficher intValue(accu)\n7  accu=nand(accu,operande)\n8  accu=add(accu,operande)\n9  accu=sub(accu,operande)\n10  accu=and(accu,operande)\n11 accu=or(accu,operande)\n12 accu=xor(accu,operande)\n13 accu=not(accu)\n14 accu=opp(accu)\n15 accu=shift(accu)\n16 accu=logicalShift(accu,int)\n17 accu=mul(accu,operande)\n\n" ;
  
  char* invite = "--> Quel est votre choix  ? " ;
  
  printf("%s",menu) ; 

  operand=word();
  cpu=initCPU();
  alu=cpu.alu;
  
  while (go_on==1) {
    printf("%s",invite);
    scanf("%d",&chosenInt);
    switch (chosenInt) {
    case 0 : 
      go_on = 0 ;
      break ;
    case 1 :
      printf("Entrez un nombre :"); 
      scanf("%d",&integer);
      setValue(operand,integer);
      break ;
    case 2 : 
      pass(alu,operand);
      break ;
    case 3 : 
      printing(alu);
      break ;
    case 4 : 
      printf("%s\n",toString(operand));
      break ;
    case 5 : 
      printf("intValue(operand)=%d\n",intValue(operand));
      break ;
    case 6 : 
      printf("intValue(accu)=%d\n",intValue(alu.accu));
      break ;
    case 7 : 
      nand(alu,operand);
      printf("apres nand(), accu = ");
      printing(alu);
      break ;
    case 8 : 
      add(alu,operand);
      printf("apres add(), accu = ");
      printing(alu);
      break ;
    case 9 : 
      sub(cpu,operand);
      printf("apres sub(), A = ");
      printing(alu);
      break ;
    case 10 : 
      and(cpu,operand);
      printf("apres and(), A = ");
      printing(alu);
      break ;
    case 11 : 
      or(cpu,operand);
      printf("apres or(), A = ");
      printing(alu);
      break ;
    case 12 : 
      xor(cpu,operand);
      printf("apres xor(), A = ");
      printing(alu);
      break ;
    case 13 : 
      not(cpu);
      printf("apres not(), A = ");
      printing(alu);
      break ;
    case 14 : 
      opp(cpu);
      printf("apres opp(), A = ");
      printing(alu);
      break ;
    case 15 : 
      shift(alu);
      printf("apres shift(), A = ");
      printing(alu);
      break ;
    case 16 : 
      printf("Entrez un entier :") ;
      scanf("%d",&integer);
      logicalShift(cpu,integer);
      printf("apres logicalshift(%d), A = ",integer);
      printing(alu);
      break ;
    case 17 : 
      mul(cpu,operand);
      printf("apres mul(), A = ");
      printing(alu);
      break ;
    default : 
      printf("Choix inexistant !!!!\n");
      printf("%s",menu);
    }
  }
  printf("Au revoir et a bientot\n");
  return 0;
}


  
