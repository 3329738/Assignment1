#include <stdio.h>

char cipher(int string, int key);

int main(){
   int key;
   char alphabet[] = {a, b, c, d, e, f, g, h, i, j, k, l ,m , n, o, p, q, r, s, t, u, v, w, x, y, z};
   
   
   if (key > 26){
        key = 0
    }
    char ciper(string, key); 
   
    
}

char encrypted(int string, int key){
    char decrypted;
    decrypted = (string + key)(%26);
    return decrypted;
}