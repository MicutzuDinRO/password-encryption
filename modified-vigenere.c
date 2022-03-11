// Cerinta I - Criptare Parole : Cifrul Vigenere modificat
// De Micu Alexandru 311CCb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DMAX 13500
#define SMAX 27000

// Functia de citire a cheii si a parolei ce trebuie criptata
void citire(char *cheie_init, char *cheie, char *parola) {
	fscanf(stdin, "%s ", cheie_init);
	strcpy(cheie, cheie_init);
	fscanf(stdin, "%s", parola);
}

// Functia pentru criptatea Vinegere a parolei
void cifru_Vinegere(char *cheie, char *parola) {
	int i;
	for (i = 0; i < strlen(parola); i++) {
		int dist, mic;

		// Constante generatoare de distante cifru Vinagere
		const int scad_mic = 97, scad_mare = 39;

		// Constante care modifica distanta cifru Vinagere
		const int lim_mic = 122, lim_mare = 90;

		// Daca gaseste un caracter non-alfabetic in cheie sau parola
		// nu se poate cripta Vinegere parola si returneaza INVALID
		if (isalpha(cheie[i]) == 0 || isalpha(parola[i]) == 0) {
			printf("INVALID\n");
			return;
		} else {

			// Genereaza distanta intre a/A si caracterul respectiv
			// in functie de faptul daca e majuscula/minuscula
			if (islower(cheie[i]) != 0) dist = (int)(cheie[i]) - scad_mic;
			else dist = (int)(cheie[i]) - scad_mare;
			if (islower(parola[i]) != 0) mic = 1;
			else mic = 0;

			// Cat timp distanta e diferita de zero
			// Scade distanta in functie de caracterul de pe pozitia i
			// din parola si din cheie
			while (dist != 0) {
				if (mic != 0 && dist + (int)(parola[i]) > lim_mic) {
					dist -= (lim_mic + 1 - (int)(parola[i]));
					parola[i] = 'A';
					mic = 0;
				} else if (mic != 0 && dist + (int)(parola[i]) <= lim_mic) {
					parola[i] = (char)(dist + (int)(parola[i]));
					dist = 0;
				} else if (mic == 0 && dist + (int)(parola[i]) > lim_mare) {
					dist -= (lim_mare + 1 - (int)(parola[i]));
					parola[i] = 'a';
					mic = 1;
				} else if (mic == 0 && dist + (int)(parola[i]) <= lim_mare) {
					parola[i] = (char)(dist + (int)(parola[i]));
					dist = 0;
				}
			}
		}
	}
	puts(parola);
}

int main(void) {
    char *cheie_init, *cheie, *parola;
	cheie_init = (char*) calloc(DMAX, sizeof(char));
	cheie = (char*) calloc(SMAX, sizeof(char));
	parola = (char*) calloc(DMAX, sizeof(char));
	citire(cheie_init, cheie, parola);

	// Aduce dimensiunea cheii la egalitate cu lungimea parolei sau mai mare
	while (strlen(cheie) < strlen(parola)) strcat(cheie, cheie_init);
	cifru_Vinegere(cheie, parola);
	free(cheie_init);
	free(cheie);
	free(parola);
	return 0;
}