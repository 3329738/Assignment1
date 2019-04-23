#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
              int key;
              int freq;
}KeyFreq;

char dictionary[10001][20];

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

void rotation_encrypt_string(char* str, int key) {
              for (unsigned int i = 0; i < strlen(str); i++) {
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

void rotation_decrypt_string(char* str, int key) {
              for (unsigned int i = 0; i < strlen(str); i++) {
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

void  substitution_encrypt_string(char* str, char* key) {
              for (unsigned int i = 0; i < strlen(str); i++) {
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

void substitution_decrypt_string(char* str, char* key) {
              for (unsigned int i = 0; i < strlen(str); i++) {
                           str[i] = substitution_decrypt(str[i], key);
              }
}



void do_rotation_encrypt() {
              char rotKeyStr[20];
              int rotKey = 0;
              char str[40];
              char temp;

              printf("\n\nEnter rotation key: ");
              scanf("%s", rotKeyStr);
              scanf("%c", &temp);
              rotKey = atoi(rotKeyStr);
              printf("\n\nEnter text to encrypt: ");
              //scanf_s("%[^\n]%*c", str, 39);
              fgets(str, 39, stdin);     
              rotation_encrypt_string(str, rotKey);
              printf("Encrypted = %s\n", str);

}

void do_rotation_decrypt() {
              char rotKeyStr[20];
              int rotKey = 0;
              char str[40];
              char temp;

              printf("\n\nEnter rotation key: ");
              scanf("%s", rotKeyStr, 19);
              scanf("%c", &temp, 1);
              rotKey = atoi(rotKeyStr);
              printf("\n\nEnter text to decrypt: ");
              fgets(str, 39, stdin);
              rotation_decrypt_string(str, rotKey);
              printf("Decrypted = %s\n", str);

}

bool is_valid_key(char* key){
              bool is_valid = true;
              int sum = 0;
              if (strlen(key) == 26) {
                           for (int i = 0; i < 26; i++) {
                                         key[i] = toupper(key[i]);
                                         sum = sum + key[i];
                                         if (!isalpha(key[i])) {
                                                       is_valid = false;
                                                       printf("Error: string is not all alpha\n");
                                                       break;
                                         }
                           }
                           if (sum != 2015) {
                                         is_valid = false;
                                         printf("Error: string contains repeats of letters\n");
                           }
              }
              else {
              is_valid = false;
              printf("Error: String is not 26 characters long\n");
              }
              
              return is_valid;
}

void do_substitution_encrypt() {
              char KeyStr[27];
              char str[40];
              char temp;
              char Key;


              printf("\n\nEnter substitution key of 26 unique letters: ");
              scanf("%c", &temp, 1);
              fgets(KeyStr, 27, stdin);
              
              if (is_valid_key(KeyStr)) {
                           printf("\n\nEnter text to encrypt: ");
                           scanf("%c", &temp, 1);
                           fgets(str, 39, stdin);
                           substitution_encrypt_string(str, KeyStr);
                           printf("Encrypted = %s\n", str);
              }
              

}

void do_substitution_decrypt() {
              char KeyStr[27];
              char str[40];
              char temp;
              char Key;

              printf("\n\nEnter substitution key of 26 characters: ");
              scanf("%c", &temp);
              fgets(KeyStr, 27, stdin);
              
              if (is_valid_key(KeyStr)) {
                           printf("\n\nEnter text to decrypt: ");
                           scanf("%c", &temp);
                           fgets(str, 39, stdin);
                           substitution_decrypt_string(str, KeyStr);
                           printf("Decrypted = %s\n", str);
              }
}

void read_dictionary() {
              char str[21];
              int index = 0;
              FILE* f;

              fopen(str *f ./google-10000-english.txt);

              while (!feof(f)) {
                           //fgets(str, 21, f);
                           fscanf_s(f, "%s\n", str, 21);

                           // FIXME figure out where the \n s are coming from
                           for (int i = 0; i < strlen(str); i++) {
                                         //if (str[i] == '\0')
                                         //          str[i] = '\0';
                                         
                                         if (isalpha(str[i])) {
                                                       str[i] = toupper(str[i]);
                                         }

                           }
                                         
                           strcpy_s(dictionary[index], 21, str);
                           index++;
              }
              fclose(f);

}

bool is_in_dictionary(char* str ) {
              bool found = false;
              for (int i = 0; i < 10000; i++) {
                           if (strcmp(dictionary[i], str) == 0) {
                                         printf("found it\n");
                                         found = true;
                           }

              }
              return found;
}

void add_key(int key, KeyFreq *freqs){
              freqs[0].key = 12;
              freqs[0].freq = 1;

              
}

void brute_force_rotation() {
              char str[10000];
              char temp;
              char* token;
              char* next_token;
              KeyFreq freqs[100] = {0};

              printf("Enter text to decrypt: ");
              scanf_s("%c", &temp, 1);
              fgets(str, 10000, stdin);
              const char s[2] = " ";
              token = strtok_s(str, s, &next_token);

              // While there are tokens in "string1" or "string2"
              while (token != NULL)
              {
                           // Get next token:
                           //if (token != NULL)
                           //{
                                         printf(" %s\n", token);
                                         
                                         for (int i = 1; i < 26; i++) {
                                                       char* temp = _strdup(token);
                                                       rotation_decrypt_string(temp, i);
                                                       if (is_in_dictionary(temp)) {
                                                                    printf("Key is: %d, Str = %s, Temp = %s\n", i, str, temp);
                                                       }
                                                       free(temp);
                                         }
                                         token = strtok_s(NULL, s, &next_token);

                           
              }
              
}

void brute_force_substitution() {

}

void test() {
              //char key1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
              char key2[] = { 'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O', 'N','M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A' };
              char str1[] = { "fred" };

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

              read_dictionary();
}

int main() {
              read_dictionary();

              /*
              char key1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
              char key2[] = { 'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O', 'N','M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A' };
              char str1[] = { "fred" };
              char str2[] = { "pbon" };
              char str3[] = { "uivw" };
              */
              char choice;

              do {
              printf("\n\nDo you want to;\n");
              printf("1) Encrypt with a rotation cipher\n");
              printf("2) Decrypt a rotation cipher\n");
              printf("3) Encrypt with a substitution cipher\n");
              printf("4) Decrypt a substitution ciper\n");
              printf("5) Brute force on rotation ciper\n");
              printf("6) Brute force on a substitution ciper\n");
              printf("7) Quit\n");
              printf("Enter your choice: "); // Offers a choice of what the code should do and prompts the user to select one
              scanf_s("%c", &choice, 1);

                           switch(choice){
                                         case '1': do_rotation_encrypt();
                                                       break;
                                         case '2': do_rotation_decrypt();
                                                       break;
                                         case '3': do_substitution_encrypt();
                                                       break;
                                         case '4': do_substitution_decrypt();
                                                       break;
                                         case '5': brute_force_rotation();
                                                       break;
                                         case '6': brute_force_substitution();
                                                       break;
                                         case '7': choice = 0;
                                                       break;
                                         default: printf("Error, invalid input\n");
                           }

              }
              while(choice != 0); // Do while loop prevents error from incorrect intput i.e. none of the options

              return 0;
}