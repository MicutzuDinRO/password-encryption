// Cerinta II - Automatically fill
// De Micu Alexandru 311CCb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DMAX 170

typedef struct {
	char *camp, *valoare;
} pereche;

// Citesc pointerul de struct
void citire(int *dim, pereche *date) {
	int i;
	for (i = 0; i < *dim; i++) {
		date[i].camp = (char*) calloc(DMAX, sizeof(char));
		date[i].valoare = (char*) calloc(DMAX, sizeof(char));
		scanf("%s %s", date[i].camp, date[i].valoare); 
	}
}

// Verific daca caracterul poate sa faca parte dintr-un camp sau nu
int e_Bun(char c) {
	if (isalnum(c) || c == '_') return 1;
	return 0;
}

// Compara cuvantul dat cu fiecare camp din date pana gaseste unul la fel
// sau se termina pointer-ul
void compara_Date(char *cuv, int dim, pereche *date) {
	int i;
	for (i = 0; i < dim; i++) {
		if (!strcmp(cuv, date[i].camp)) {
			strcpy(cuv, date[i].valoare);
			return;
		}
	}
}

// Functia in care inlocuiesc campurile cerute cu valorile date
void fill(int dim, pereche *date) {
	char *mesaj, citit;
	int l = 0;
	mesaj = (char*) malloc(DMAX * sizeof(char));
	getchar();

	// Citesc mesajul caracter cu caracter pana la finalul fisierului
	while ( (citit = getchar()) != EOF) {
		if (e_Bun(citit)) {
			mesaj[l]=citit;
			l++;
			mesaj[l]='\0';
		}

		// Daca caracterul nu poate sa faca parte dintr-un cuvant si nu e
		// vreo secventa anterioara atunci afisez caracterul actual.
		// Altfel compar cuvantul format dinainte cu datele primite
		// afiseaza ce se obtine si "resetez" cuvantul
		else if (l == 0) printf("%c", citit);
		else {
			compara_Date(mesaj, dim, date);
			printf("%s%c", mesaj, citit);
			free(mesaj);
			mesaj = (char*) malloc(DMAX * sizeof(char));
			l = 0;
		}
	}

	// Verific sa nu fii ramas un cuvant de printat
	if (l != 0) {
		compara_Date(mesaj, dim, date);
		printf("%s", mesaj);
	}
	free(mesaj);
}

// Eliberez pointer-ul struct
void elibereaza(int dim, pereche *date) {
	int i;
	for (i = 0; i < dim; i++) {
		free(date[i].camp);
		free(date[i].valoare);
	}
	free(date);
}

int main() {
	pereche *date;
	int dim;
	scanf("%d", &dim);
	date = (pereche*) calloc(dim, sizeof(pereche));
	citire (&dim, date);
	fill(dim, date);
	elibereaza(dim, date);
	return 0;
}