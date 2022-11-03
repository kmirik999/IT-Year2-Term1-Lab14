#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//string s;

class InterfaceReader {
public:
    InterfaceReader() {}

    virtual ~InterfaceReader() {}

    void runReader(int key);
};


class InterfaceWriter {
public:
    InterfaceWriter() {}

    virtual ~InterfaceWriter() {}

    virtual void runWriter() = 0;
};


class Encrypt {
public:
    int wrap(int number, int maxvalue);

    char *encrypt(char *rawText, int key) {
        int i = 0;
        const char upperAlph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 27 -- длина строки, +1 пустое значение
        const char lowerAlph[27] = "abcdefghijklmnopqrstuvwxyz";
        while (rawText[i] != NULL) {
            i++;
        }
        char *text = new char[i];
        i = 0;
        while (rawText[i] != NULL) {
            if (isalpha(rawText[i])) // isalpha -- чи є символ в  алфавіті
            {
                if (isupper(rawText[i])) // перевіряє, чи є  у верхньому регістрі
                {
                    text[i] = upperAlph[wrap(rawText[i] - 'A' + key, 26)];
                } else {
                    text[i] = lowerAlph[wrap(rawText[i] - 'a' + key, 26)];
                }
            } else {
                text[i] = (rawText[i]);
            }
            i++;
        }

        //InterfaceWriter::runWriter(text);
        return text;
    }
};

class Decrypt {
public:
    char *decrypt(char *encryptedText, int key) {
        Encrypt e;
        return e.encrypt(encryptedText, -key);
    }
};

class FileReader : virtual public InterfaceReader {
public:
    virtual void runReader(int key) {
        Encrypt e;

        string filePath = "D:\\Example.txt";
        string line;
        string s;

        ifstream in(filePath, ifstream::binary);

        const int chunk_size = 5;
        int bytes_to_read = 0;
        int safe_index = 0;
        if (in.is_open()) {
            while (getline(in, line)) {
                if (!line.empty()) {
                    while (safe_index < line.size()) {
                        if (line[safe_index] == '\r') {
                            s += line[safe_index];
                            break;
                        }

                        if (bytes_to_read == chunk_size && safe_index < line.size()) {
                            safe_index++;
                            bytes_to_read = 0;
                            //string encText =
                            e.encrypt((char *) s.c_str(), key);
                            //runWriter();

                            s = "";

                            continue;
                        } else if (bytes_to_read == chunk_size && safe_index == line.size()) {
                            safe_index++;
                            bytes_to_read = 0;

                            e.encrypt((char *) s.c_str(), key);
                            s = "";

                            break;
                        }

                        s += line[safe_index];
                        safe_index++;
                        bytes_to_read++;

                    }
                }

                safe_index = 0;

            }
        }

        in.close();
    }
};

class FileWriter : virtual public InterfaceWriter {
public:
    void runWriter(string str) {
        string filePath = "D:\\Input.txt";
        ofstream out;

        out.open(filePath);
        if (out.is_open()) {
            out << str;
        }

        out.close();
    }
};

int Encrypt::wrap(int number, int maxvalue) {
    if (number < 0) {
        number += maxvalue * (-number / maxvalue + 1); // для від'ємнних чисел що обернеться навколо нуля і границь
    }
    return number % maxvalue;
}


int main() {

    InterfaceReader* ir = new FileReader();
    InterfaceWriter* ew = new FileWriter();
    ir->runReader(3);


    Encrypt e;
    Decrypt d;
    std::string input_text;
    int key;
    string repeat;
    while (true)
    {
        cout << "enter text: ";
        cin >> input_text;

        cout << "enter key: ";
        cin >> key;

        int select_command;
        cout << "Choose the command (1-encrypt, 2- decrypt):\n";
        cin >> select_command;

        switch (select_command) {
            case 1:
                cout << e.encrypt((char*)input_text.c_str(), key) << endl;
                break;
            case 2:
                cout << d.decrypt((char*)input_text.c_str(), key);
                break;
        }
        cout << "\nrepeat the program: ";
        cin >> repeat;

        if (repeat == "yes")
        {
            continue;
        }
        else if (repeat == "no")
        {
            break;
        }
    }
}