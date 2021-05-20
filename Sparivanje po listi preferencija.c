//Author: Toni Ivankovic
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DIME 40
#define maxN 10

int max(int a, int b){
	if(a>b) return a;
	else return b;
}

int main(){
	
	int brLjudi;
	bool okBroj=0;
	do{
		printf("Unesite broj ljudi koji sudjeluju u igri (mora biti paran broj manji od %d) > ",maxN);
		scanf(" %d",&brLjudi);
		if(brLjudi%2==0 && brLjudi <=maxN && brLjudi >0) okBroj=1;
		fflush(stdin);
	}while(okBroj==0);
	
	struct osoba{
		char IME[DIME];
		int listaPref[10];
		int par;
	} ljudi[brLjudi];
	
	//upis imena
	int i,j,k;
	for(i=0; i<brLjudi; i++){
		printf("Upisite ime %d. osobe > ",i+1);
		scanf("%[^\n]%*c",ljudi[i].IME);
		fflush(stdin);
	}
	
	//unos lista preferencije
	int tajni=0;
	printf("Tajni unos? (1/0) > ");
	scanf("%d",&tajni);
	for(i=0; i<brLjudi; i++){
		if(tajni==1){
			for(j=0;j<70;j++) printf("\n");
			for(j=0; j<brLjudi; j++) if(j!=i) printf("%d - %s\n",j+1,ljudi[j].IME);
		}
		printf("Upisite listu preferencija %d. osobe (%s) > ", i+1, ljudi[i].IME);
		for(j=0; j<brLjudi-1; j++) {
			scanf("%d",&ljudi[i].listaPref[j]);
			ljudi[i].listaPref[j]--;
			//provjera ispravnosti
			if(ljudi[i].listaPref[j] == i || ljudi[i].listaPref[j] <0 || ljudi[i].listaPref[j]>=brLjudi){
				printf("Neispravne oznake ljudi - upisite ih ponovno (osoba ne smije biti na svojoj listi i broj mora biti izmedju 1 i %d) >\n",brLjudi);
				fflush(stdin);
				j=-1;
			}
		}
		for(j=0; j<brLjudi-1; j++){
			for(k=j+1; k<brLjudi-1; k++){
				if(ljudi[i].listaPref[j] == ljudi[i].listaPref[k]){
					printf("Ista osoba unesena u listu preferencija vise puta. Ponovno ");
					i -= 1;
					k = brLjudi;
					j = brLjudi;
				}
			}
		}
		//rješavanje problema viška osoba
		fflush(stdin);
	}
	
	//unos koeficijenata za bodovanje
	int BODOVANJE[10];
	if(tajni==1) for(i=0;i<70;i++) printf("\n");
	printf("Unesite koeficijente bodovanja (njih %d) > ",brLjudi-1);
	for(i=0; i<brLjudi-1; i++) scanf("%d",&BODOVANJE[i]);
	
	int KOMBINACIJA[10];
	int pomSuma=0, maxSuma, prviProlaz=1, pomBr, dobraKomb;
	for(i=123456789;i<1000000000;i+=(pow(10,(10-brLjudi)))){
		//generiranje svih kombinacija
		pomBr=i;
		k=0;
		dobraKomb=1;
		KOMBINACIJA[0]=0;
		while(pomBr!=0){
			KOMBINACIJA[10-k-1]=pomBr%10;
			pomBr/=10;
			k++;
		}
		//eliminiranje kombinacija kojima se ponavljaju znamenke i kojima su bitne znamenke veæe od broja ljudi
		if(dobraKomb==1){
			for(j=0;j<brLjudi;j++){
				if(KOMBINACIJA[j] > brLjudi-1) {
					dobraKomb=0;
					break;
				}
				for(k=j+1;k<brLjudi;k++){
					if(KOMBINACIJA[j]==KOMBINACIJA[k]){
						dobraKomb=0;
						j=brLjudi;
						break;
					}
				}
			}
		}
		if(dobraKomb==0) continue;
		//Kombinacija je sad u KOMBINACIJI
		for(j=0; j<brLjudi/2; j++){
			//u svakom paru tražimo poziciju u listi preferencija i radimo sumu
			for(k=0; k<brLjudi-1; k++){
				if(ljudi[KOMBINACIJA[j*2+1]].listaPref[k]==KOMBINACIJA[j*2]) break;
			}
			pomSuma += BODOVANJE[k];
			for(k=0; k<brLjudi-1; k++){
				if(ljudi[KOMBINACIJA[j*2]].listaPref[k]==KOMBINACIJA[j*2+1]) break;
			}
			pomSuma += BODOVANJE[k];
		}
		//traži se maksimalna suma
		if(prviProlaz == 1 || pomSuma > maxSuma){
			prviProlaz = 0;
			maxSuma= pomSuma;
			for(j=0; j<brLjudi/2; j++){
				ljudi[KOMBINACIJA[j*2]].par = KOMBINACIJA[j*2+1];
				ljudi[KOMBINACIJA[j*2+1]].par = KOMBINACIJA[j*2];
			}
		}
		pomSuma=0;
	}
	//Ispis parova, a da se ne ispisuje duplo
	int BILI[brLjudi];
	for(i=0;i<brLjudi;i++) BILI[i]=1;
	printf("Parovi su:\n");
	for(i=0; i<brLjudi; i++){
		if(BILI[i]==0) continue;
		printf("%s i %s (%d i %d)\n",ljudi[i].IME,ljudi[ljudi[i].par].IME,i+1,ljudi[i].par+1);
		BILI[i]=0;
		BILI[ljudi[i].par]=0;
	}
	if(tajni==0) printf("Suma bodova iznosi: %d",maxSuma); 
	
	
	return 0;
}
