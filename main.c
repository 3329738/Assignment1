#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct { //creates a new 2D data type
              int key; //one dimension of the data type
              int freq; //other dimension of the data type
}KeyFreq; //name of new data type

char dictionary[10001][20]; //to hold the words in the dictionary

/* rotation_encrypt encrypts single uppercase alpha characters using the formula temp = (character + key)% 26 */
char rotation_encrypt(char c, int key) { // function to encrypt using rotation ciper with a key
              char encrypted; // declaring variable to save value to return into

              if (isalpha(c)) { //checks if a letter
                           if (islower(c)) { //checks if the letter is lower case
                                         c = toupper(c); //converts lower case letter to number
                           }
                           int temp = (int)c - 65; //makes A an interger == 0 to allow easier conversions
                           temp = ((temp + key) % 26) + 65; //uses formula given and adds 26 to return to ASCII values
                           encrypted = (char)temp; //converts a back to a char and saves in encrypted
              }
              else { //if not a letter
                           encrypted = c; //saves the original character i.e. a . or space in encrypted
              }
              return encrypted; //function will return encrypted
}

/* rotation_encrypt_string converts whole stings using rotation_encrypt by entering each character individually and saving the encrypted into its original string.
This destroys the original string increasing security of the non encrypted string. If the original string needs to be kept a copy can be made prior to encryption */
void rotation_encrypt_string(char* str, int key) { //function to move through string and check each character through rotation_encrypt
              for (unsigned int i = 0; i < strlen(str); i++) { //checks each character of the string until the whole string is complete
                           str[i] = rotation_encrypt(str[i], key); 
              }
}

/* Recives user input and uses the function rotation_encrypt_string to encode user input. The user inputs the rotation key, a number for the key to rotate.
A text which will be encrypted by the rotation key*/
void do_rotation_encrypt() { //
              char rotKeyStr[20];
              int rotKey = 0;
              char str[40];
              char temp;

              printf("\n\nEnter rotation key: "); //promts user for infomation
              scanf("%s", rotKeyStr); 
              scanf("%c", &temp);
              rotKey = atoi(rotKeyStr);
              printf("\n\nEnter text to encrypt: ");
              //scanf_s("%[^\n]%*c", str, 39);
              fgets(str, 39, stdin);     //may need to remove fgets
              rotation_encrypt_string(str, rotKey);
              printf("Encrypted = %s\n", str);

}

/* roation_decrypt decrypts single characters when given the key they were encoded in using the formula given */
char rotation_decrypt(char c, int key) {
              char decrypted;

              if (isalpha(c)) { //checks if letter
                           if (islower(c)) { //checks if letter is lower case
                                         c = toupper(c); //converts to uppercase
                           }
                           int temp = (int)c - 65; //converts c to sn interger and makes A == 0
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

void do_rotation_decrypt() {
              char rotKeyStr[20];
              int rotKey = 0;
              char str[40];
              char temp;

              printf("\n\nEnter rotation key: ");
              scanf("%s", rotKeyStr);
              scanf("%c", &temp);
              rotKey = atoi(rotKeyStr);
              printf("\n\nEnter text to decrypt: ");
              fgets(str, 39, stdin);
              rotation_decrypt_string(str, rotKey);
              printf("Decrypted = %s\n", str);

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

void do_substitution_encrypt() {
              char keyStr[27];
              char str[40];
              char temp;
              char key;

              printf("\n\nEnter substitution key of 26 unique letters: ");
              scanf("%c", &temp);
              fgets(keyStr, 27, stdin);
              
              if (is_valid_key(keyStr, key)) {
                           printf("\n\nEnter text to encrypt: ");
                           scanf("%c", &temp);
                           fgets(str, 39, stdin);
                           substitution_encrypt_string(str, keyStr);
                           printf("Encrypted = %s\n", str);
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

void do_substitution_decrypt() {
              char keyStr[27];
              char str[40];
              char temp;
              char key;

              printf("\n\nEnter substitution key of 26 characters: ");
              scanf("%c", &temp);
              fgets(keyStr, 27, stdin);
              
              if (is_valid_key(keyStr, key)) {
                           printf("\n\nEnter text to decrypt: ");
                           scanf("%c", &temp);
                           fgets(str, 39, stdin);
                           substitution_decrypt_string(str, keyStr);
                           printf("Decrypted = %s\n", str);
              }
}

bool is_valid_key(char* key){
              bool is_valid_key = true;
              int sum = 0;
              if (strlen(key) == 26) {
                           for (int i = 0; i < 26; i++) {
                                         key[i] = toupper(key[i]);
                                         sum = sum + key[i];
                                         if (!isalpha(key[i])) {
                                                       is_valid_key = false;
                                                       printf("Error: string is not all alpha\n");
                                                       break;
                                         }
                           }
                           if (sum != 2015) {
                                         is_valid_key = false;
                                         printf("Error: string contains repeats of letters\n");
                           }
              }
              else {
              is_valid_key = false;
              printf("Error: String is not 26 characters long\n");
              }
              
              return is_valid_key;
}

void read_dictionary() {
              char str[21];
              int index = 0;
              FILE* f;

              fopen("./google-10000-english.txt", "r"/*const char *filename, const char *mode*/);

              while (!feof(f)) {
                           //fgets(str, 21, f);
                           fscanf(f, "%s\n", str);

                           // FIXME figure out where the \n s are coming from
                           for (int i = 0; i < strlen(str); i++) {
                                         //if (str[i] == '\0')
                                         //          str[i] = '\0';
                                         
                                         if (isalpha(str[i])) {
                                                       str[i] = toupper(str[i]);
                                         }

                           }
                                         
                           strcpy(dictionary[index], str);
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

/*void add_key(int key, KeyFreq *freqs){
              freqs[0].key = 12;
              freqs[0].freq = 1;
			  //for () {

			  }

              
}*/

void brute_force_rotation() {
              char str[10000];
              char temp;
              char* token;
              //char* next_token;
              //KeyFreq freqs[100] = {0};

              printf("Enter text to decrypt: ");
              scanf("%c", &temp);
              fgets(str, 10000, stdin);
              const char s[2] = " ";
              token = strtok(str, s/*&next_token*/);

              // While there are tokens in "string1" or "string2"
              while (token != NULL)
              {
                           // Get next token:
                           //if (token != NULL)
                           //{
                                         printf(" %s\n", token);
                                         
                                         for (int i = 1; i < 26; i++) {
                                                       char* temp = strdup(token);
                                                       rotation_decrypt_string(temp, i);
                                                       if (is_in_dictionary(temp)) {
                                                                    printf("Key is: %d, Str = %s, Temp = %s\n", i, str, temp);
                                                       }
                                                       free(temp);
                                         }
                                         token = strtok(NULL, str /*char *str, const char *delim*/);

                           
              }
              
}

void brute_force_substitution() {
	printf("Sorry not worth the marks");

}

/*void test() {
              char key1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
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
}*/

int main() {
              read_dictionary();
              char choice; //initialises variable to hold the users menu choice

              do { //do while loop continues until the while condition is met
			  /*Offers a choice of what the code should do and prompts the user to select one*/
              printf("\n\nDo you want to;\n");
              printf("1) Encrypt with a rotation cipher\n");
              printf("2) Decrypt a rotation cipher\n");
              printf("3) Encrypt with a substitution cipher\n");
              printf("4) Decrypt a substitution ciper\n");
              printf("5) Brute force on rotation ciper\n");
              printf("6) Brute force on a substitution ciper\n");
              printf("7) Quit\n");
              printf("Enter your choice: "); 
              scanf("%c", &choice); //Reads the input of the user's choice

                           switch(choice){ //Allows the user to do their chosen option
                                         case '1': do_rotation_encrypt(); 
                                                       break; //break exits the function so all other cases below aren't executed
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
                                         case '7': choice = 0; //creates the condition needed to exit the code
                                                       break;
                                         default: printf("Error, invalid input\n"); //Tells the user their input was wrong and will not complete any action
                           }

              }
              while(choice != 0); // Exits only when the user is done with the program i.e. choice = 0 

              return 0;
}