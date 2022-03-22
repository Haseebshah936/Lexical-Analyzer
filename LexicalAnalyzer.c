#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ifKeyword(char *str);
int ifNumber(char *str);
int ifIdentifier(char *str);

int main()
{

    FILE *fp = fopen("code.txt", "r");

    if (fp == NULL)
    {
        perror("File opening Error");
        return -1;
    }
    char *token;
    char line[256];

    // Reading file line by line
    while (fgets(line, 256, fp) != NULL)
    {
        // Tokenizing line on basis of spaces
        token = strtok(line, " ");
        /* walk through other tokens */
        while (token != NULL)
        {
            if (ifKeyword(token)) // Checking if tokenized word is Keyword
            {
                printf("Keyword %s\n", token);
            }
            else
            {
                size_t len = strlen(token);
                // Creating a dynamic array for storing pure word without special characters
                // other than underscore
                char *word = (char *)malloc(len);
                int index = 0; // Counter for word index
                for (int i = 0; i < len; i++)
                {
                    // Checking if character contain spacial character other then underscore
                    if (token[i] != '\t' && token[i] != '\n' && token[i] != '_' && !isalpha(token[i]) && !isdigit((int)token[i]))
                    {
                        // Terminating string with '\0' to avoid printing dummy values
                        word[index] = '\0';
                        if (ifKeyword(word)) // Checking if pure word is a keyword
                        {
                            printf("Keyword %s\n", word);
                        }
                        else if (ifNumber(word) && index) // Checking if pure word is a number
                        {
                            printf("Number %s\n", word);
                        }
                        else if (ifIdentifier(word) && index) // Checking if pure word is an Identifier
                        {
                            printf("Identifier %s\n", word);
                        }
                        else if (index)
                        {
                            printf("Incorrect Identifier %s\n", word);
                        }

                        index = 0; // Initializing index with 0
                        printf("Spec %c\n", token[i]);
                    }
                    else if (token[i] != '\t' && token[i] != '\n')
                    {
                        word[index++] = token[i]; // Creating pure word
                    }
                }
                // Terminating string with '\0' to avoid printing dummy values
                word[index] = '\0';
                if (ifKeyword(word)) // Checking if pure word is a keyword
                {
                    printf("Keyword %s\n", word);
                }
                else if (ifNumber(word) && index) // Checking if pure word is a number
                {
                    printf("Number %s\n", word);
                }
                else if (ifIdentifier(word) && index) // Checking if pure word is an Identifier
                {
                    printf("Identifier %s\n", word);
                }
                else if (index)
                {
                    printf("Incorrect Identifier %s\n", word);
                }
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    return 0;
}

int ifKeyword(char *str)
{
    char *keyword[32] = {"auto",
                         "break",
                         "case",
                         "char",
                         "const",
                         "continue",
                         "default",
                         "do",
                         "double",
                         "else",
                         "enum",
                         "extern",
                         "float",
                         "for",
                         "goto",
                         "if",
                         "int",
                         "long",
                         "register",
                         "return",
                         "short",
                         "signed",
                         "sizeof",
                         "static",
                         "struct",
                         "switch",
                         "typedef",
                         "union",
                         "unsigned",
                         "void",
                         "volatile",
                         "while"};

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(str, keyword[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int ifNumber(char *str)
{
    int digit = 1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]) || str[i] == '\0')
        {
            digit = 0;
            break;
        }
    }
    return digit;
}

int ifIdentifier(char *str)
{
    if (str[0] == '_' || isalpha(str[0]))
        return 1;
    return 0;
}