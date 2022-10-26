#include <iostream>
using namespace std;



char* encrypt(char* rawText, int key)
{
    int i = 0;
    const char upperAlph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 27 -- длина строки +1 пустое значение
    const char lowerAlph[27] = "abcdefghijklmnopqrstuvwxyz";
    while (rawText[i] != NULL)
    {
        i++;
    }
    char *text = new char[i];
    i = 0;
    while(rawText[i] != NULL)
    {
        if(isalpha(rawText[i])) // isalpha -- чи є символ в  алфавіті
        {
            if(isupper(rawText[i])) // проверяет находится ли в верхнем регистре
            {
                text[i] = (upperAlph[((rawText[i] - 'A') + key) % 26]);
            }
            else
            {
                text[i] = (lowerAlph[((rawText[i] - 'a') + key) % 26]);
            }
        }
        else
        {
            text[i] = (rawText[i]);
        }
        i++;
    }
    return text;
}

int main()
{
    cout << encrypt("Roses are red, violets are blue", 1);
}