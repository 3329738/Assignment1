#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Defining functions above main in groups of what each one does
 with the last group being miscellaneous */
char rotation_encrypt(char c, int key);
char rotation_decrypt(char c, int key);
char substitution_encrypt(char c, char* key);
char substitution_decrypt(char c, char* key);

void rotation_encrypt_string(char* str, int key);
void rotation_decrypt_string(char* str, int key);
void substitution_encrypt_string(char* str, char* key);
void substitution_decrypt_string(char* str, char* key);

void do_rotation_encrypt();
void do_rotation_decrypt();
void do_substitution_encrypt();
void do_substitution_decrypt();

void brute_force_rotation();
void brute_force_substitution();

char is_valid_key(char* key);
void read_dictionary();
char is_in_dictionary(char* str);
//void add_key(int key, KeyFreq *freqs);

typedef struct { //creates a new 2D data type
    int key; //one dimension of the data type to store the key used
    int freq; //other dimension of the data type to store how often the key appears
    }KeyFreq; //name of new data type

char dictionary[10001][20]; //to hold the words in the dictionary

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
        printf("Enter your choice: ");  //promts user for infomation
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
    while(choice != 0); // Exits only when the user is done with the program
    return 0;
}

/* rotation_encrypt encrypts single uppercase alpha characters using the formula temp = (character + key)% 26 */
char rotation_encrypt(char c, int key) { //function to encrypt using rotation ciper with a key
    char encrypted; //declaring variable to save value to return into
    
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

/* rotation_decrypt decrypts single characters when given the key they were encoded in using the formula given */
char rotation_decrypt(char c, int key) {
    char decrypted;
    
    if (isalpha(c)) { //checks if letter
        if (islower(c)) { //checks if letter is lower case
            c = toupper(c); //converts to uppercase
        }
        int temp = (int)c - 65; //converts c to an interger and makes A == 0
        temp = (temp - key);
        if (temp < 0) { //erases problem with modulus of a negative number by changing to a positive but still changing the key as the negative number would
            temp = temp + 26;
        }
        temp = (temp % 26) + 65;
        decrypted = (char)temp;
    }
    else {
        decrypted = c;
    }
    return decrypted;
}

 /* the key must be an array as it will have 26 individual letters, each letter of the alphabet */
char substitution_encrypt(char c, char* key) {
    char encrypted;
    
    if (isalpha(c)) {
        if (islower(c)) {
            c = toupper(c);
        }
        encrypted = key[(int)c - 65]; //converts c to a number (its ASCII value) and makes A = to 0. The use of it in the array key allows A = the first value of the array key and so on
    }
    else {
        encrypted = c;
    }
    return encrypted;
}

 /* decrypts a text when the key used to encrypt it is known. It does this by making the first value =  A and so on */
char substitution_decrypt(char c, char* key) {    char decrypted = '?'; //if unable to decrypt a question mark will appear
    
    if (isalpha(c)) {
        if (islower(c)) {
            c = toupper(c);
        }
        for (int i = 0; i < 26; i++) { //uses i to go through each individual element of the array as it starts at 0 and continues to 26, which should be the last element as the array has length of alphabet 26
            if (key[i] == c) { //checks each element until one = the desired letter
                decrypted = (char)(i + 65); //makes a letter from the ASCII table
                break; //leaves the for loop as the correct letter has already been found so no more need to be checked
            }
        }
    }
    else {
        decrypted = c; //used for spaces and other non letters to not change their value
    }
    return decrypted;
}

/* rotation_encrypt_string converts whole stings using rotation_encrypt 
by entering each character individually and saving the encrypted into 
its original string. This destroys the original string increasing security
of the non encrypted string. If the original string needs to be kept a 
copy can be made prior to encryption */
void rotation_encrypt_string(char* str, int key) {
    for (unsigned int i = 0; i < strlen(str); i++) { //as i increments each component of str is inputed into the desired function
        str[i] = rotation_encrypt(str[i], key);
    }
}

/* rotation_decrypt_string converts whole stings using rotation_decrypt 
by entering each character individually and saving the encrypted into 
its original string. This destroys the original string increasing security
of the non encrypted string. If the original string needs to be kept a 
copy can be made prior to encryption */
void rotation_decrypt_string(char* str, int key) {
    for (unsigned int i = 0; i < strlen(str); i++) { //as i increments each component of str is inputed into the desired function
    str[i] = rotation_decrypt(str[i], key);
    }
}

/* substitution_encrypt_string converts whole stings using substitution_encrypt 
by entering each character individually and saving the encrypted into 
its original string. This destroys the original string increasing security
of the non encrypted string. If the original string needs to be kept a 
copy can be made prior to encryption */
void substitution_encrypt_string(char* str, char* key) {
    for (unsigned int i = 0; i < strlen(str); i++) { //as i increments each component of str is inputed into the desired function
        str[i] = substitution_encrypt(str[i], key);
    }
}

/* substitution_decrypt_string converts whole stings using substitution_decrypt 
by entering each character individually and saving the encrypted into 
its original string. This destroys the original string increasing security
of the non encrypted string. If the original string needs to be kept a 
copy can be made prior to encryption */
void substitution_decrypt_string(char* str, char* key) {
    for (unsigned int i = 0; i < strlen(str); i++) { //as i increments each component of str is inputed into the desired function
        str[i] = substitution_decrypt(str[i], key);
    }
}

/* Recives user input and uses the function rotation_encrypt_string to encode 
user input. The user inputs the rotation key which is a number for the alphabet to rotate
 and a text which will be encrypted by the rotation key*/
void do_rotation_encrypt() {
    char rotKeyStr[20];
    int rotKey = 0;
    char str[40];
    char temp;
    
    printf("\nEnter rotation key: "); //promts user for infomation
    scanf("%s%c", rotKeyStr, &temp); //temp absorbs problem and prevents scanf from skipping
    rotKey = atoi(rotKeyStr); //converts sting data type to interger data type
    printf("\nEnter text to encrypt: "); // prompts for information
    fgets(str, 39, stdin); //reads input and stops when newline character is read and stores in specified string
    rotation_encrypt_string(str, rotKey); //enters user input into rotation_encrypt_string
    printf("Encrypted = %s\n", str); //prints encrpyted 
}

/* Recives user input and uses the function rotation_decrypt_string to decode 
user input. The user inputs the rotation key which is a number the alphabet has rotated
 and a text which will be decrypted using the rotation key*/
void do_rotation_decrypt() {
    char rotKeyStr[20];
    int rotKey = 0;
    char str[40];
    char temp;
    
    printf("\nEnter rotation key: "); //promts user for infomation
    scanf("%s%c", rotKeyStr, &temp); //temp absorbs problem and prevents scanf from skipping
    rotKey = atoi(rotKeyStr); //converts sting data type to interger data type
    printf("\nEnter text to decrypt: "); //promts user for infomation
    fgets(str, 39, stdin); //reads input and stops when newline character is read and stores in specified string
    rotation_decrypt_string(str, rotKey); //enters user input into rotation_decypt_string
    printf("Decrypted = %s\n", str); //prints decrypted
}

/* Recives user input and uses the function substitution_encrypt_string to encode 
user input. The user inputs the substituton key which is the alphabet in a random order
 and a text which will be encrypted by the substitution key*/
void do_substitution_encrypt() {
    char keyStr[27];
    char str[40];
    char temp;
    //char key;
    
    printf("\nEnter substitution key of 26 unique letters: "); //promts user for infomation
    scanf("%c", &temp);
    fgets(keyStr, 27, stdin);
    if (is_valid_key(keyStr)) {
        printf("\nEnter text to encrypt: "); //promts user for infomation
        scanf("%c", &temp);
        fgets(str, 39, stdin);
        substitution_encrypt_string(str, keyStr); //enters user input into substitution_encrypt_string
        printf("Encrypted = %s\n", str);
    }
}

/* Recives user input and uses the function substitution_decrypt_string to decode 
user input. The user inputs the substituton key which is the alphabet in a random order
 and a text which will be decrypted using the substitution key*/
void do_substitution_decrypt() {
    char keyStr[27];
    char str[40];
    char temp;
    //char key;
    
    printf("\nEnter substitution key of 26 characters: "); //promts user for infomation
    scanf("%c", &temp);
    fgets(keyStr, 27, stdin);
    if (is_valid_key(keyStr)) {
        printf("\nEnter text to decrypt: "); //promts user for infomation
        scanf("%c", &temp);
        fgets(str, 39, stdin);
        substitution_decrypt_string(str, keyStr); //enters user input into substitutiontion_decrypt_string
        printf("Decrypted = %s\n", str);
    }
}

/* recieves user input and tries each rotation key and prints the key, string and ... */
void brute_force_rotation() {
    char str[10000];
    char temp;
    char* token;
    char* next_token;
    KeyFreq freqs[100] = {0};
    
    printf("Enter text to decrypt: "); //promts user for infomation
    scanf("%c", &temp);
    fgets(str, 10000, stdin);
    const char s[2] = " ";
    token = strtok(str, s);
    while (token != NULL) {
        printf(" %s\n", token);
        for (int i = 1; i < 26; i++) {
            char* temp = strdup(token);
            rotation_decrypt_string(temp, i);
            if (is_in_dictionary(temp)) {
                printf("Key is: %d, Str = %s, Temp = %s\n", i, str, temp);
            }
            free(temp);
        }
        token = strtok(NULL, str);
    }    
}

void brute_force_substitution() {

}

/* Used to check the substitution keys are valid, it ensures the key has a length of 26, each character is a unique letter and amkes all uppercase */
char is_valid_key(char* key){
    char valid_key = 1;
    int sum = 0;
    
    if (strlen(key) == 26) { //checks length correct
        for (int i = 0; i < 26; i++) { //goes through each element of string
            key[i] = toupper(key[i]); //changes to uppercase if needed
            sum = sum + key[i]; //adds each character in the string to ensure each is unique
            if (!isalpha(key[i])) { //makes sure all elements are letters
                valid_key = 0;
                printf("Error: string is not all alpha\n");
                break;
            }
        }
        if (sum != 2015) { //if each character is a unique uppercase letter the total will be 2015
        valid_key = 0;
            printf("Error: string contains repeats of letters\n");
        }
    }
    else { //if length is not correct
        valid_key = 0;
        printf("Error: String is not 26 characters long\n");
    }
    return valid_key;
}

/* Reads the file words */
void read_dictionary() {
    char str[21]; //assume words wont be bigger than 21 so string wont need to be
    int index = 0;
    FILE* f;
    
    f = fopen("words", "r"); //opens words allowing the function to read it
    while (!feof(f)) { //feof tests end of file so while loop continues until end of file
        fgets(str, 21, f); //stores words in str
        fscanf(f, "%s\n", str);
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == '\0')
            str[i] = '\0';
            if (isalpha(str[i])) {
                str[i] = toupper(str[i]); //makes every word uppercase so it is consistant throughout the program to prevent case errors
            }
        }
        strcpy(dictionary[index], str); //makes a copy of str into dictionary
        index++; //each element of dictionary
    }
    fclose(f);
}

/*used to check if each word is contained within dictionary or not */
char is_in_dictionary(char* str) {
    char found = 0;
    
    for (int i = 0; i < 10000; i++) { //checks each word in dictionary by comparing strings
        if (strcmp(dictionary[i], str) == 0) {
            printf("found it\n");
            found = 1;
        }
    }
    return found;
}

/*void add_key(int key, KeyFreq *freqs){
    freqs[0].key = 12;
    freqs[0].freq = 1;
    for () {
			  }
}*/