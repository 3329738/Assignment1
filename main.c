#include <stdio.h>
int main()
{
   char choice; // To assign the user's choice of the options to
   char a, b, c, d;
   do
   {
        printf("Do you want to;\na) Encrypt with a rotation cipher\nb) Decrypt a rotation cipher\nc) Encrypt with a substitution cipher\nd) Decrypt a substitution ciper\nYour choice: "); // Offers a choice of what the code should do and prompts the user to select one
        scanf("%c\n", choice); // To read the users input to make a choice
   }
   while((choice != a) || (choice != b) || (choice != c) || (choice != d)); // Do while loop prevents error from incorrect intput i.e. none of the options

    return 0;
}
