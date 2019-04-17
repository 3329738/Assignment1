#include <stdio.h>

#include <ctype.h>

 

char rotation_encrypt(char c, int key) {
      char encrypted;

      if (isalpha(c)) {
            if (islower(c)) {
                  c = toupper(c);
            }
            int temp = (int)c - 65;
            temp = (temp + key);
            temp = (temp % 26) + 65;
            encrypted = (char)temp;
      }
      else {
            encrypted = c;
      }

      return encrypted;
}

char rotation_decrypt(char c, int key) {
      char decrypted;

      if (isalpha(c)) {
            if (islower(c)) {
                  c = toupper(c);
            }
            int temp = (int)c - 65;
            temp = (temp - key);
            if (temp < 0) {
                  temp = temp + 26;
            }
            temp = (temp % 26);
            temp += 65;
            decrypted = (char)temp;
      }
      else {
            decrypted = c;
      }

      return decrypted;
}

char substitution_encrypt(char c, char* key) {
      char encrypted; 

      if (isalpha(c)) {
            if (islower(c)) {
                  c = toupper(c);
            }
            encrypted = key[(int)c - 65];
      }
      else {
            encrypted = c;
      }
      
      return encrypted;
}

char substitution_decrypt(char c, char* key) {
      char decrypted = '?';

      if (isalpha(c)) {
            if (islower(c)) {
                  c = toupper(c);
            }
            for (int i = 0; i < 26; i++) {
                  if (key[i] == c) {
                        decrypted = (char)(i + 65);
                        
                        break;
                  }
            }
      }
      else {
            decrypted = c;
      }

      return decrypted;
}


void test() {
      char key1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
      
      char key2[] = { 'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O', 'N','M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A' };

      printf("running\n");
      char result;

      result = rotation_decrypt('a', 1);
      printf("result = %c\n", result);

      result = rotation_encrypt('a', 1);
      printf("result = %c\n", result);

      result = substitution_encrypt('b', key2);
      printf("result = %c\n", result);

      result = substitution_decrypt('y', key2);
      printf("result = %c\n", result);
}

int main() {
      test();

return 0;
}