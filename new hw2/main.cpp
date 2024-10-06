//
//  main.cpp
//  new hw2
//
//  Created by Valeria Dudinova on 06.10.2024.
//

#include <iostream>

using namespace std;

class MyString {
private:
    char* str;         // Вказівник на рядок
    int length;        // довжина рядка
    static int objCount; // Статичне  поле для підрахунку кількості об'єктів

    int calcLength(const char* s) const
    {
        int len = 0;
        while (s[len] != '\0')
        {
            len++;
        }
        return len;
    }

public:
    // Конструктор за замовчуванням - рядок завдовжки 80 символів
    MyString() {
        length = 80;
        str = new char[length + 1];
        str[0] = '\0';
        objCount++;
    }

    // Конструктор, що створює рядок довільного розміру
    MyString(int size)
    {
        length = size;
        str = new char[length + 1];
        str[0] = '\0';
        objCount++;
    }

    // Конструктор, який приймає рядок від користувача
    MyString(const char* input)
    {
        length = calcLength(input);
        str = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            str[i] = input[i];
        }
        str[length] = '\0';
        objCount++;
    }

    ~MyString() {
        delete[] str;
        objCount--;
    }

    void input()
    {
        cout << "Enter line: ";
        char buffer[1000];
        cin.getline(buffer, 1000);
        length = calcLength(buffer);
        delete[] str;
        str = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            str[i] = buffer[i];
        }
        str[length] = '\0';
    }

    void output() const
    {
        cout << str << endl;
    }

    // Метод копіювання рядка
    void MyStrcpy(MyString& obj)
    {
        delete[] str;
        length = obj.length;
        str = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            str[i] = obj.str[i];
        }
        str[length] = '\0';
    }

    // Пошук підрядки у рядку
    bool MyStrStr(const char* substr)
    {
        int substrLength = calcLength(substr);
        for (int i = 0; i <= length - substrLength; i++)
        {
            int j = 0;
            while (j < substrLength && str[i + j] == substr[j])
            {
                j++;
            }
            if (j == substrLength)
            {
                return true;
            }
        }
        return false;
    }

    // Пошук символу у рядку
    int MyChr(char c) {
        for (int i = 0; i < length; i++)
        {
            if (str[i] == c) {
                return i;
            }
        }
        return -1;
    }

    // Повертає довжину рядка
    int MyStrLen() const
    {
        return length;
    }

    void MyStrCat(MyString& b)
    {
        char* temp = new char[length + b.length + 1];
        for (int i = 0; i < length; i++)
        {
            temp[i] = str[i];
        }
        for (int i = 0; i < b.length; i++)
        {
            temp[length + i] = b.str[i];
        }
        temp[length + b.length] = '\0';

        delete[] str;
        str = temp;
        length += b.length;
    }

    void MyDelChr(char c)
    {
        int newLen = 0;
        for (int i = 0; i < length; i++)
        {
            if (str[i] != c)
            {
                str[newLen++] = str[i];
            }
        }
        str[newLen] = '\0';
        length = newLen;
    }

    // Порівняння рядків
    int MyStrCmp(MyString& b)
    {
        int i = 0;
        while (str[i] != '\0' && b.str[i] != '\0')
        {
            if (str[i] < b.str[i]) return -1;
            if (str[i] > b.str[i]) return 1;
            i++;
        }
        if (str[i] == '\0' && b.str[i] == '\0') return 0;
        if (str[i] == '\0') return -1;
        return 1;
    }

    MyString operator+(MyString& b)
    {
        MyString result(length + b.length);
        for (int i = 0; i < length; i++)
        {
            result.str[i] = str[i];
        }
        for (int i = 0; i < b.length; i++)
        {
            result.str[length + i] = b.str[i];
        }
        result.str[length + b.length] = '\0';
        result.length = length + b.length;
        return result;
    }
    
    // Перевантаження оператора інкременту (збільшення довжини рядка на 1)
    MyString& operator++()
    {
        char* temp = new char[length + 2];
        for (int i = 0; i < length; i++)
        {
            temp[i] = str[i];
        }
        temp[length] = ' ';
        temp[length + 1] = '\0';

        delete[] str;
        str = temp;
        length++;
        return *this;
    }

    // Перевантаження оператора декремента (зменшення довжини рядка на 1)
    MyString& operator--()
    {
        if (length > 0) {
            str[length - 1] = '\0';
            length--;
        }
        return *this;
    }

    MyString& operator=(const MyString& b)
    {
        if (this != &b)
        {
            delete[] str;
            length = b.length;
            str = new char[length + 1];
            for (int i = 0; i < length; i++)
            {
                str[i] = b.str[i];
            }
            str[length] = '\0';
        }
        return *this;
    }

    static int getObjectCount()
    {
        return objCount;
    }
};

int MyString::objCount = 0;

int main()
{
    MyString str1("Hello");
    MyString str2(" `World`");
    str1.MyStrCat(str2);
    str1.output();

    MyString str3 = str1 + str2;
    str3.output();

    cout << "String length: " << str1.MyStrLen() << endl;

    ++str1;
    str1.output();

    --str1;
    str1.output();

    return 0;
}
