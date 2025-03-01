#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define POS_FILE "comuni.txt"
#define LENGHT 16
#define MAX 50
#define MAX_FILE 20

char mesi[]="ABCDEHMLPRST";

char da_int_a_char(int a){
    return (char)(a + '0');
}

int is_date_valid(int *dd,int *mm,int *yyyy){
    if(*yyyy > 1925 && *yyyy < 2026){
        if(*mm > 0 && *mm < 13){
            if(*dd > 0 && *dd < 32){
                return 1;
            }
        }
    }
    return 0;
}


int is_letter(char a){
    if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){
        return 1;
    }else{
        return 0;
    }
}

int is_vocal(char a){
    if(is_letter(a)){
        a = tolower(a);
        switch(a){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return 1;
            default:
                return 0;
            }
    }
}

void get_nome(char *nome){
    printf("Inserire il nome:\t\t\t");
    scanf("%s",nome);
}

void get_cognome(char *cognome){
    printf("Inserire il cognome:\t\t\t");
    scanf("%s",cognome);
}

void get_data(int *dd,int *mm,int *yyyy){
    printf("Inserire il giorno di nascita (dd mm yyyy):\t\t");
    scanf("%d %d %d",dd,mm,yyyy);
}

void get_genere(int *dd){
    char gen;
    printf("Inserire il genere M/F:\t\t\t");
    scanf(" %c",&gen);
    if(gen == 'F'){
        *dd += 40;
    }
}

int get_comune(char *cod_com){
    char comune[MAX];
    FILE *fl;
    fl = fopen(POS_FILE,"r");
    char buffer[MAX_FILE];

    if(fl == NULL){
        printf("Errore nell'apertura file comuni.txt\n");
        return 1;
    }

    printf("Inserire il comune di nascita:\t\t\t");
    scanf("%s",comune);

    for(int i=0; comune[i] != '\0';i++){
        comune[i] = toupper(comune[i]);
    }

    while(fgets(buffer,MAX_FILE,fl)){
        if(strstr(buffer,comune)){
            strncpy(cod_com,buffer,4);
            fclose(fl);
            return 0;
        }
        
    }
    printf("Codice città non trovato\n");
    
    fclose(fl);
    return 0;
}

void calcola_lettere(char *elemento,char *consonanti,char *vocali,int *maxcons,int *maxvocali){

    for(int i=0; *(elemento+i) != '\0';i++){
        if(is_vocal(*(elemento+i))){

            *(vocali + *maxvocali) = *(elemento+i);
            *maxvocali = *maxvocali + 1;

        }else if(is_letter(*(elemento+i))){

            *(consonanti + *maxcons) = *(elemento+i);
            *maxcons = *maxcons + 1;
        }
    }
}

void calcola_config(char *cons_cog,char *cons_nom,int *maxcons_cog,int *maxcons_nom,char *voc_cog,char *voc_nom,int *maxvoc_cog,int *maxvoc_nom,char *config){ 
    //arr di cons, max di cons, arr di voc, max  di voc, config
    char *p= cons_cog;      //parte dalle consonanti del cognome
    int j= 0;
    for(int i= 0; i< 6; i++){
        if(i == 3){         //dopo 3 si passa al nome
            p= cons_nom;    //il puntatore passa a cog_nom
            j= 0;   
        }else if(j == *maxcons_cog && p == cons_cog){    //se si arriva al massimo di cons del cog
            p= voc_cog;     //il punt passa a voc_cog
            j= 0;
        }else if(j == *maxcons_nom && p == cons_nom){   //se si arriva al massimo di cons del nom
            p= voc_nom;     //il punt passa a voc_nom
            j= 0;
        }
        if(j == *maxvoc_cog && p == voc_cog){           //casi di mancanza di lettere
            *(config +i) = 'X';
            continue;
        }else if(j == *maxvoc_nom && p == voc_nom){
            *(config +i) = 'X';
            continue;
        }

        *(config + i) = *(p + j); 
        j++;
    }
}

void crea_codice(char *codice,char *nome,char *cognome,int *dd,int *mm,int *yyyy,char *cod_com){
    char cons1[MAX],voc1[MAX];              //consonanti e vocali del cognome
    char cons2[MAX],voc2[MAX];              //consonanti e vocali del nome
    int maxc1= 0,maxv1= 0;                  //numero di cons e voc del cognome
    int maxc2= 0,maxv2= 0;                  //numero di cons e voc del nome
    char config[7];
    calcola_lettere(cognome,cons1,voc1,&maxc1,&maxv1);
    calcola_lettere(nome,cons2,voc2,&maxc2,&maxv2);
    //printf("Consonanti cognome: %d\nVocali cognome: %d\nConsonanti nome: %d\nVocali nome: %d",maxc1,maxv1,maxc2,maxv2);
    calcola_config(cons1,cons2,&maxc1,&maxc2,voc1,voc2,&maxv1,&maxv2,config);

    for(int i= 0; i< 6;i++){
        *(codice + i) = toupper(*(config + i));             //6 di config nome/cognome
    }

    *(codice + 6) = da_int_a_char(*yyyy % 100 / 10);        //2 cifre del anno di nascita
    *(codice + 7) = da_int_a_char(*yyyy % 10);

    *(codice + 8) = mesi[*mm - 1];                          //lettera del mese

    *(codice + 9) = da_int_a_char(*dd / 10);                //2 cifre del giorno
    *(codice +10) = da_int_a_char(*dd % 10);

    for(int i= 11;i< 15;i++){                               //4 caratteri del comune
        *(codice + i) = *(cod_com + (i - 11));
    }
    
    //*(codice +15) = get_special()

    printf("\nCodice fiscale:\t\t%s\n",codice);
}


int main(){

char nome[MAX],cognome[MAX],cod_com[4];
int giorno,mese,anno;
char codice[LENGHT];

printf("\n----\tCalcolatore di codice fiscale----\n");
get_nome(nome);
get_cognome(cognome);
do{
    get_data(&giorno,&mese,&anno);
    if(!is_date_valid(&giorno,&mese,&anno)){
        printf("Reinserire la data di nascita\n");
    }
}while(!is_date_valid(&giorno,&mese,&anno));

get_genere(&giorno);
get_comune(cod_com);
crea_codice(codice,nome,cognome,&giorno,&mese,&anno,cod_com);
}
