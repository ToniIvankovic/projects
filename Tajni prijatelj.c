//Toni Ivankovic
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIME 40

int main(){
	
	int brLjudi;
	printf("Unesite broj ljudi koji sudjeluju u igri > ");
	scanf(" %d",&brLjudi);
	fflush(stdin);
	
	struct osoba{
		char IME[DIME];
		int izvuceno;
	} ljudi[brLjudi];
	
	//upis imena
	int i;
	for(i=0; i<brLjudi; i++){
		printf("Upisite ime %d. osobe > ",i+1);
		scanf("%[^\n]",ljudi[i].IME);
		fflush(stdin);
	}
	
	srand((unsigned)time(NULL));
	int j, ponovi = 1;
	
	//random covjeku dodjeljujemo zadnjeg, a da to nije on sam
	int imaZadnjeg;
	do{
		imaZadnjeg = rand() % brLjudi;
	}while(imaZadnjeg == brLjudi-1);
	ljudi[imaZadnjeg].izvuceno = brLjudi-1;
	
	//dodjela izvucenih svima ostalima
	for(i=0; i<brLjudi; i++){
		//dodjela svima osim zadnjem
		if(i != imaZadnjeg){	
			//dodjela i provjera je li sam sebe
			do{
				ljudi[i].izvuceno = rand() % (brLjudi-1);
				if(ljudi[i].izvuceno != i) ponovi = 0;
				else ponovi = 1;
				//provjeri je li netko prije izvukao nekoga kao i ti
				for(j=0; j<i; j++){
					if(ljudi[i].izvuceno == ljudi[j].izvuceno) ponovi = 1;
				}
			} while(ponovi != 0);
		}
	}
	
	//ispis izvucenih parova
	printf("Za tajni ispis unesite '1', inace '0' > ");
	int tajni;
	scanf("%d",&tajni);
	fflush(stdin);
	for(i=0; i<brLjudi; i++){
		if(tajni==1){
			printf("%d. osoba (%s):",i+1,ljudi[i].IME);
			scanf("%*c");
			for(j=0;j<70;j++) printf("\n");
		}
		printf("Osoba %s izvukla je osobu %s.\n",ljudi[i].IME,ljudi[ljudi[i].izvuceno].IME);
		if(tajni==1) {
			scanf("%*c");
			for(j=0; j<70; j++) printf("\n");
		}
	}
	
	return 0;
}
