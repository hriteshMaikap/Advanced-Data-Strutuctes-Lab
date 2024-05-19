#include <stdio.h>
#include <string.h> // For strncmp

#define STRING_LENGTH 20

int main() {
    char str1[STRING_LENGTH]; 
    char str2[STRING_LENGTH]; 

    printf("Enter a string (maximum %d characters): ", STRING_LENGTH - 1);
    fgets(str2, sizeof(str2), stdin);

    printf("Enter a string (maximum %d characters): ", STRING_LENGTH - 1);
    fgets(str1, sizeof(str1), stdin);

    // Remove trailing newline from fgets
    str2[strcspn(str2, "\n")] = '\0';
    str1[strcspn(str2, "\n")] = '\0';

    // Compare strings (consider only fixed length for comparison)
    int comparison = strncmp(str1, str2, STRING_LENGTH);

    if (comparison == 0) {
        printf("The strings are equal.\n");
    } else if (comparison>1){
        printf("%s is higher\n", str1);
    } else if(comparison<1){
        printf("%s is higer\n", str2);
    }

    return 0;
}
