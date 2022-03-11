// Cerinta III - Generare Parole
// De Micu Alexandru 311CCb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR_COD 3

// Genereaza caracterele necodificate ale parolei
char *gen_Par(int dim, char *parola) {
	int i;

	// Constante generare caracter
	const int lim = 32, nr_carac = 94;
	for (i = 0; i < dim; i++) {
		int x;
		x = lim + (rand() % nr_carac);
		parola[i] = (char)(x);
	}
	parola[dim] = '\0';
	return parola;
}

// Calculeaza numarul de cifre al unui numar
int nr_cifre(int x) {
	if (x == 0) return 1;
	int nr = 0;
	while (x != 0) {
		x /= 10;
		nr++;
	}
	return nr;
}

// Functia care aplica prima codificare pe un caracter
char *cod1(char c) {
	const int safe = 10;

	// Vectorul alocat static care sa retina aparitiile fiecarui caracter in
	// codificare
    static int freq[126];
	char *res, *ajut;
	ajut = (char*) malloc ((safe + nr_cifre(freq[(int)(c)])) * sizeof(char));
	res = (char*) malloc ((safe + nr_cifre(freq[(int)(c)])) * sizeof(char));

	// Transform numarul de aparintii intr-un string
	sprintf (ajut, "%d", freq[(int)(c)]);
	res[0] = c;
	res[1] = '\0';

	// Combin caracterul si numarul de aparitii intr-un pointer de char
	strcat (res, ajut);

	// Actualizez numarul de aparitii
	freq[(int)(c)]++;
	free(ajut);
	return res;
}

// Functia pentru numarul de biti ai unui numar
int num_biti(int nr) {
    int biti = 0;
    while (nr) {
        nr = nr & (nr - 1);
        biti++;
    }
    return biti;
}

// Functia pentru negarea bitilor
int inv_biti(int nr, int poz1, int poz2) {
	nr = nr ^ (1 << poz1);
	nr = nr ^ (1 << poz2);
	return nr;
}

// Functia care aplica a doua codificare pe un caracter
char *cod2(char c) {
	const int safe = 2;

	// Pozitiile fixate de enunt
	const int poz1 = 3, poz2 = 6, poz3 = 5;
	int aju, nr = (int)(c);
	char *rasp, *ajutor;

	// Neaga biti de pe pozitiile 3 si 6 iar dupa numara bitii
	nr = inv_biti(nr, poz1, poz2);
	aju = num_biti(nr);

	rasp = (char*) malloc((safe + nr_cifre(aju)) * sizeof(char));
	ajutor = (char*) malloc((safe + nr_cifre(aju)) * sizeof(char));

	// Efectueaza SAU logic pe pozitia a 5-a si seteaza LSB la 0
	nr = nr | (1 << poz3);
	nr = nr & (~1);

	// Formez un pointer char cu noul caracter obtinut dupa operatiile pe biti
	rasp[0] = (char)(nr);
	rasp[1] = '\0';

	// Transform numarul de aparintii intr-un string si
	// Combin caracterul si numarul de aparitii intr-un pointer de char
	sprintf (ajutor, "%d", aju);
	strcat(rasp, ajutor);
	free(ajutor);
	return rasp;
}

// Functia care aplica a treia codificare pe un caracter
char *cod3(char c) {
	const int safe = 2;
	char *up;
	up = (char*) malloc(safe * sizeof(char));

	// Daca caracterul e litera mica il transforma in majuscula
	if (islower(c)) c = toupper(c);
	up[0] = c;
	up[1] = '\0';
	return up;
}

// Functia care prelucreaza prin codificare si afiseaza parola
void mod_Par(int dim, char *parola, char *(*cod[NR_COD])(char)) {
	int i;
	for (i = 0; i < dim; i++) {
		int tip;
		char *aux;

		// Genereaza un numar random cu seed-ul dat si in functie de numarul
		// dat aplica codificarea corespunzatoare din pointerul de functii
		tip = rand() % NR_COD;
		aux = (*cod[tip])(parola[i]);

		// Afiseaza rezultatul generat dupa codificarea caracterului respectiv
		printf("%s", aux);
		free(aux);
	}
	printf("\n");
}

int main (void) {
	const int safe = 20;
	int seed, dim;
	char *parola;

	// Pointer-ul de functii
	char *(*cod[NR_COD])(char) = {cod1, cod2, cod3};
	scanf("%d %d", &seed, &dim);
	parola = (char*) calloc(safe * dim, sizeof(char));

	// Setez seed-ul dat de test
	srand((unsigned)(seed));
	gen_Par(dim, parola);
	mod_Par(dim, parola, cod);
	free(parola);
	return 0;
}
