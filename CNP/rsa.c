#include <stdio.h>
#include <math.h>

// Returns gcd of a and b
int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
}

// Code to demonstrate RSA algorithm
int main()
{
    // Two random prime numbers
    int p = 3;
    int q = 7;

    // First part of public key:
    int n = p * q;

    // Finding other part of public key.
    // e stands for encrypt
    int e = 2;
    int phi = (p - 1) * (q - 1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient
    int k = 2; // A constant value
    int d = (1 + (k * phi)) / e;

    // Message to be encrypted
    int msg = 11;

    printf("Message data = %d", msg);

    // Encryption c = (msg ^ e) % n
    int c = pow(msg, e);
    c = c % n;
    printf("\nEncrypted data = %d", c);

    // Decryption m = (c ^ d) % n
    int m = pow(c, d);
    m = m % n;
    printf("\nOriginal Message Sent = %d", m);

    return 0;
}
