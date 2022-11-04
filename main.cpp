#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string s;

class IReader
{
public:
    IReader() {}
    virtual ~IReader() {}
    virtual void runReader(int& chunk_size, string& str, int& start) = 0;
};


class IWriter
{
public:
    IWriter() {}
    virtual ~IWriter() {}
    virtual void runWriter(string str) = 0;
};


class Encrypt
{
public:
    int wrap(int number, int maxvalue);

    char* encrypt(char* rawText, int key)
    {


        int i = 0;
        const char upperAlph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 27 -- длина строки, +1 пустое значение
        const char lowerAlph[27] = "abcdefghijklmnopqrstuvwxyz";
        while (rawText[i] != NULL)
        {
            i++;
        }
        char* text = new char[i];
        i = 0;
        while (rawText[i] != NULL)
        {
            if (isalpha(rawText[i])) // isalpha -- чи є символ в  алфавіті
            {
                if (isupper(rawText[i])) // перевіряє, чи є  у верхньому регістрі
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
};

class Decrypt
{
public:
    char* decrypt(char* encryptedText, int key)
    {
        Encrypt e;
        return e.encrypt(encryptedText, -key);
    }
};

class FileReader : public IReader
{
public:
    void runReader(int& chunk_size, string& str, int& start)
    {
        Encrypt e;

        string filePath = "D:\\Example.txt";
        string line;
        ifstream in(filePath, ifstream::binary);

        int temp_chunk_size = chunk_size;
        int counterLiterals = 0;
        bool breakCycle = false;
        bool continueCycle = false;
        if (in.is_open())
        {
            while (true) {
                char* buffer = new char[chunk_size];
                in.seekg(start);
                in.read(buffer, temp_chunk_size);

                for (int i = 0; i < temp_chunk_size; i++)
                {
                    if (buffer[i] == '\r')
                    {
                        start = counterLiterals + 1;

                        temp_chunk_size = chunk_size - counterLiterals + 1;
                        str += '\n';
                        delete[] buffer;
                        continueCycle = true;
                        break;
                    }

                    if (buffer[i] == '\n')
                    {
                        continue;
                    }
                    counterLiterals++;
                    str += buffer[i];
                }

                if (breakCycle)
                {
                    breakCycle = false;
                    delete[] buffer;
                    break;;
                }

                if (continueCycle)
                {
                    continueCycle = false;
                    continue;
                }
                start += chunk_size;
                delete[] buffer;
                break;
            }
        }

        in.close();
    }
};

class FileWriter : public IWriter
{
public:
    void runWriter(string str)
    {
        string filePath = "D:\\Input.txt";
        ofstream out;

        out.open(filePath, std::ios::app);

        if (out.is_open())
        {
            out << str;
        }
        out.close();
    }



};

int Encrypt::wrap(int number, int maxvalue)
{
    if (number < 0)
    {
        number += maxvalue * (-number / maxvalue + 1); // для від'ємнних чисел що обернеться навколо нуля і границь
    }
    return number % maxvalue;
}


int main()
{

    int chunk_size = 128;
    int temp_chunk_size;
    string str = "";
    int start = 0;
    Encrypt e;
    Decrypt d;
    IReader* ir = new FileReader();
    IWriter* ew = new FileWriter();

    bool deleteExistFile = true;


    string tempStr = "";
    int select = 0;
    char* temp;

    cout << "Encrypt - 1; Decrypt - 2: ";
    cin >> select;

    switch (select)
    {
        case 1:
            temp_chunk_size = chunk_size;
            ir->runReader(chunk_size, str, start);
            temp = e.encrypt((char*)str.c_str(), 3);

            for (int i = 0; i < temp_chunk_size; i++)
            {
                if (temp[i] == '\n')
                {
                    tempStr += temp[i];
                    temp_chunk_size += 1;
                    continue;
                }
                tempStr += temp[i];
            }
            ew->runWriter(tempStr);
            tempStr = "";
            str = "";
            delete[] temp;

        case 2:
            temp_chunk_size = chunk_size;
            ir->runReader(chunk_size, str, start);
            temp = d.decrypt((char*)str.c_str(), 3);

            for (int i = 0; i < temp_chunk_size; i++)
            {
                if (temp[i] == '\n')
                {
                    tempStr += temp[i];
                    temp_chunk_size += 1;
                    continue;
                }
                tempStr += temp[i];
            }
            ew->runWriter(tempStr);
            tempStr = "";
            str = "";
            delete[] temp;
    }
    return 0;
}