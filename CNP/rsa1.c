#include <stdio.h>
#include <math.h>

// Returns gcd of a and b
int gcd(int a, int b)
{
    int temp;
    while (1) {
        temp = a % b;
        if (temp == 0)
            return b;
        a = b;
        b = temp;
    }
}

int main()
{
    // Two random prime numbers
    int p = 3;
    int q = 7;

    // First part of public key:
    int n = p * q;

    printf("\nn=%d",n);
    // Finding other part of public key.
    // e stands for encrypt
    int e = 2;
    int phi = (p - 1) * (q - 1);
    printf("\nphi=%d",phi);
    while (e < phi) {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }
    printf("\ne=%d",e);

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d * e = 1 + k * totient
    int k = 2; // A constant value
    int d = (1 + (k * phi)) / e;
    printf("\nd=%d",d);

    // Message to be encrypted
    int msg = 24;

    printf("\nMessage data = %d", msg);

    // Encryption c = (msg ^ e) % n
    int c = fmod(pow(msg, e), n);
    printf("\nEncrypted data = %d", c);

    // Decryption m = (c ^ d) % n
    int m = fmod(pow(c, d), n);
    printf("\nOriginal Message Sent = %d\n", m);

    return 0;
}
