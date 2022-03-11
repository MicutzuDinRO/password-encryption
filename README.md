- Micu Alexandru


Password Encryption: Vigenere cypher modified

- Description:

    We started by implementing the data reading function, after that
data changes character by character, based on the generated key length being
at least equal to the length of the password. It checks at the same time
validity of the 2 strings. I also dynamically assigned the password and keys
and it was necessary to free the memory before I finished so that it would not occur
a memory leak.
                     

Auto-fill

- Description:
    
    The first challenge here was how do I take the final message word for word and
in the end I chose to work character by character to have more flexibility 
code in case of an error, I have more control over the characters 
and consume less dynamically allocated memory. I check the characters if
can be part of a field or are delimiters and depending on the 
current and previous results I process that part of the message and a 
display afterwards, so that I don't store the data in a new pointer that consumes
even more memory. I also considered strcmp, strstr or strtok, but they were more
complex and harder to debug.


Password generator

- Description: 

    In the first phase I didn't understand how and which encodings are applied on characters.
Then I thought that bits 3 and 6 in encoding 2 should be inverted with each other.
or that we have to count all characters the same as the given one instead of just
the characters changed by encoding 1. Anyway, first I took care of
the password generation and processing functions, where I had some
problems that I forgot to put modulo 94 instead of modulo 93 and had a huge effect on the results.
The biggest problem was with memory allocation and memory leaks.
Initially allocated too little and didn't even run well on all tests, then dropped to
memcheck just because of some pointers of size 1 and I realized after that better safe than sorry.

