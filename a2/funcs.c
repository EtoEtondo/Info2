#include "funcs.h"

void einlese_func(FILE *infile, char *woerter[], int *num_woerter, const int MAXWORT,
   const int MINZCHN){

enum{MAXCHN=60};
char c, linebuf[MAXCHN];
int ln = 0;

while(fgets(linebuf, sizeof(linebuf), infile)){
    	ln++;
printf("%s", linebuf);
	if(*num_woerter >= MAXWORT){
		fprintf(stderr, "Datei zu groß");
		break;
	}

	if(strlen(linebuf)<MINZCHN) continue;

	woerter[*num_woerter] = strdup(linebuf);
	if(woerter[*num_woerter]==NULL){
		fprintf(stderr,"Nicht genügend Speicher bei %d\n",ln);
		break;
	}

	(*num_woerter)++;
}
}

void print_func(char *woerter[],int *num_woerter,const int NUMOUT){
int b=(int)log10(*num_woerter)+1;
	for(int i=0;i<NUMOUT;i++){
	printf("%*d: %s",b , i+1, woerter[i]);
	}
printf("--------------\n");
	for(int j=(*num_woerter-NUMOUT);j< *num_woerter;j++){
	printf("%*d: %s",b , j+1, woerter[j]);
	}

}

int cmp_alph(const void *a, const void *b){
char *str1= *(char **)a;
char *str2= *(char **)b;
return strcmp(str1, str2);
}

int cmp_c3(const void *a, const void *b){
return *((*((char**)a))+2)-*((*((char**)b))+2);
}


int cmp_len(const void *a, const void *b){
char *str1= *((char **)a);
char *str2= *((char **)b);
int lena=strlen(str1);
int lenb=strlen(str2);
	if(lena-lenb==0){
		return cmp_alph(a,b);
	}else{
		return lena-lenb;
	}
}


