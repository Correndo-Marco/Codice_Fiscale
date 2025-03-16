#ifndef FUNZIONI_CODICE_FISCALE_H
#define FUNZIONI_CODICE_FISCALE_H

void printascelte();
char da_int_a_char(int a);
int is_date_valid(int *dd,int *mm,int *yyyy);
int is_letter(char a);
int is_vocal(char a);
int is_acc(char a);
char trasforma_accento(char a);
void get_nome(char *nome);
void post_nome(char *codice,char *nome);
void get_cognome(char *cognome);
void post_cognome(char *codice,char *cognome);
void get_data(int *dd,int *mm,int *yyyy);
void post_date(char *codice,int *dd,int *mm,int *yyyy,char *genere);
void get_genere(int *dd);
int get_comune(char *cod_com);
int post_comune(char *codice,char *comune);
void calcola_lettere(char *elemento,char *consonanti,char *vocali,int *maxcons,int *maxvocali);
void calcola_config(char *cons_cog,char *cons_nom,int *maxcons_cog,int *maxcons_nom,char *voc_cog,char *voc_nom,int *maxvoc_cog,int *maxvoc_nom,char *config);
char get_special(char *codice);
void crea_codice(char *codice,char *nome,char *cognome,int *dd,int *mm,int *yyyy,char *cod_com);
void trasforma_diretta(char *codice);
int trasforma_inversa(char *codice);

#endif