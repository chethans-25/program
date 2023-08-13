#include <stdio.h>
#include <math.h>
 
  int rem(  int x,   int y){
      int REM=x-y*(x/y);
    return REM;
}//end of rem

  int powerr(  int a,  int b){
  int p,x=b;
if (x<=0) return 1;
else if(x==1) return a;
else return a*powerr(a,x-1);
}//end of powerr

// Returns gcd of a and b
  int gcd(  int a,   int h)
{
      int temp;
    while (1) {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
    
}//end of gcd
 
// Code to demonstrate RSA algorithm
  int main()
{
    // Two random prime numbers
      int p = 8;
      int q = 9;
 
    // First part of public key:
      int n = p * q;
 
    // Finding other part of public key.
    // e stands for encrypt
      int e = 2;
      int phi = (p - 1) * (q - 1);
    
    while (e < phi) {
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
      printf("\nd=%d",d);
 
    // Message to be encrypted
      int msg = 12;
 
    printf("\nMessage data = %d", msg);
    
    // Encryption c = (msg ^ e) % n
      int c = rem(powerr(msg, e),n);
      printf("\nmsg^e=%d",powerr(msg, e));
    //c = rem(c, n);
    printf("\nEncrypted data = %d", c);
 
    // Decryption m = (c ^ d) % n
    
      int m = rem(powerr(c, d),n);
      printf("\nmsg^e=%d",powerr(c, d));
    //m = rem(m, n);
    printf("\nOriginal Message Sent = %d", m);
    printf("\ne = %d", e);
    return 0;
    

}//end of main
