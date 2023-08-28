#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// Function to generate public and private keys
void generate_keys(int p, int q, int *e, int *d, int *n) {
    // Calculate n (modulus)
    *n = p * q;

    // Calculate Euler's totient function (phi)
    int phi = (p - 1) * (q - 1);

    // Choose public exponent (e) - Common value: 65537
    *e = 65537;
    
    // Calculate private exponent (d)
    int i;
    for(i=3;i<phi;i++)
    {  if( (i**e)%phi == 1)
         break;
    }
    *d = i;
}

// Function to perform RSA encryption
int rsa_encrypt(int plaintext, int e, int n) {
    int ciphertext = 1;

    for (int i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }

    return ciphertext;
}

// Function to perform RSA decryption
int rsa_decrypt(int ciphertext, int d, int n) {
    int plaintext = 1;

    for (int i = 0; i < d; i++) {
        plaintext = (plaintext * ciphertext) % n;
    }

    return plaintext;
}

int main() {
    int p = 61, q = 67; // Use larger prime numbers
    int e, d, n;
    char plaintext[100];
    int ciphertext[100], decrypted_text[100];

    printf("Enter the plaintext (a string of characters): ");
    scanf("%[^\n]", plaintext);

    // Generate the keys
    generate_keys(p, q, &e, &d, &n);

    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d, n): (%d, %d)\n", d, n);

    // Encrypt the string character by character
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] == ' ') {
            ciphertext[i] = ' '; // Encrypting a space character as-is
        } else {
            ciphertext[i] = rsa_encrypt((int)plaintext[i], e, n);
        }
    }

    // Print the encrypted ciphertext
    printf("Encrypted ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext character by character and convert back to characters
    printf("Decrypted plaintext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (ciphertext[i] == ' ') {
            decrypted_text[i] = ' '; // Decrypting a space character as-is
        } else {
            decrypted_text[i] = rsa_decrypt(ciphertext[i], d, n);
        }
        printf("%c", (char)decrypted_text[i]);
    }
    printf("\n");

    return 0;
}