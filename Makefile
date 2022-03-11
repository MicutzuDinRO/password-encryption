all: modified-vigenere autofill password-generator

modified-vigenere: modified-vigenere.c
	gcc -Wall -std=c99 modified-vigenere.c -o modified-vigenere

autofill: autofill.c
	gcc -Wall -std=c99 autofill.c -o autofill

password-generator: password-generator.c
	gcc -Wall -std=c99 password-generator.c -o password-generator

clean:
	rm modified-vigenere
	rm autofill
	rm password-generator
