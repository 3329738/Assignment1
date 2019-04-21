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
      
      rotation_decrypt_string(str1, 5);
      printf("String decrypted is: %s\n", str1);
      
      substitution_encrypt_string(str1, key2);
      printf("String encrypted is: %s\n", str1);
      
      substitution_decrypt_string(str1, key2);
      printf("String decrypted is: %s\n", str1);
}

int main() {
      test();
   
   int choice;
   
   do {
       printf("Do you want to;\n1) Encrypt with a rotation cipher\n2) Decrypt a rotation cipher\n3) Encrypt with a substitution cipher\n4) Decrypt a substitution ciper\nEnter your choice: "); // Offers a choice of what the code should do and prompts the user to select one
       fflush(stdout);
       scanf("%d\n", &choice);
       /*
       switch(choice){
           case 1: rotation_encrypt_string;
           break;
           case 2: rotation_decrypt_string;
           break;
           case 3: substitution_encrypt_string;
           break;
           case 4: substiution_decrypt_string;
           break;
           default: printf("Error, invalid input\n");
       }
   */
   }

   while((choice != 1) || (choice != 2) || (choice != 3) || (choice != 4)); // Do while loop prevents error from incorrect intput i.e. none of the options
   
   return 0;
}