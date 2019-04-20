#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

void rotation_encrypt_string(char* str, int key){
    for(unsigned int i = 0; i < strlen(str); i++ ){
        str[i] = rotation_encrypt(str[i], key);
    }
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

void rotation_decrypt_string(char* str, int key){
    for(unsigned int i = 0; i < strlen(str); i++){
        str[i] = rotation_decrypt(str[i], key);
    }
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

void  substitution_encrypt_string(char* str, char* key){
    for(unsigned int i = 0; i < strlen(str); i++){
        str[i] = substitution_encrypt(str[i], key);
    } 
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

void substitution_decrypt_string(char* str, char* key){
    for(unsigned int i = 0; i < strlen(str); i++){
        str[i] = substitution_decrypt(str[i], key);
    }
}

void test() {
      char key1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
      char key2[] = { 'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O', 'N','M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A' };
      char str1[] = {"fred"};
      char str2[] = {"kwji"};
      char str3[] = {"pdqr"};

printf("%s\n", key1);

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
      
      rotation_encrypt_string(str1, 5);
      printf("String encrypted is: %s\n", str1);
      
      rotation_decrypt_string(str2, 5);
      printf("String decrypted is: %s\n", str2);
      
      substitution_encrypt_string(str1, key2);
      printf("String encrypted is: %s\n", str1);
      
      substitution_decrypt_string(str3, key2);
      printf("String decrypted is: %s\n", str3);
}

int main() {
      test();

return 0;
}