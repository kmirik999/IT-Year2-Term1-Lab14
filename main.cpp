#include <iostream>
using namespace std;

int wrap(int number, int maxvalue)
{
    if(number < 0)
    {
        number += maxvalue * (-number / maxvalue + 1); // для від'ємнних чисел що обернеться навколо нуля і границь
    }
    return number % maxvalue;
}

char* encrypt(char* rawText, int key)
{
    int i = 0;
    const char upperAlph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 27 -- длина строки, +1 пустое значение
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
            if(isupper(rawText[i])) // перевіряє, чи є  у верхньому регістрі
            {
                text[i] = upperAlph[wrap(rawText[i] - 'A' + key, 26)];
            }
            else
            {
                text[i] = lowerAlph[wrap(rawText[i] - 'a' + key, 26)];
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
char* decrypt(char* encryptedText, int key)
{
    return encrypt(encryptedText, - key);
}


int main()
{
    char *encrypted = encrypt("Roses are red, violets are blue", 2);
    cout << encrypted << endl;
    cout << decrypt(encrypted, 2);
}
