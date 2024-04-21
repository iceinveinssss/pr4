#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>


class String 
{
protected:
    char* data;   
    int length;   

public:
 
    String() : data(nullptr), length(0) {}

   
    String(const char* str) 
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

 
    String(char c) 
    {
        length = 1;
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
    }

 
    String(const String& other) 
    {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    virtual ~String() 
    {
        delete[] data;
    }

    
    int getLength() const 
    {
        return length;
    }

  
    void clear() 
    {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    
    String& operator=(const String& other) 
    {
        if (this != &other) 
        {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }
};


class BitString : public String 
{
public:
    
    BitString() : String() {}

    BitString(const char* str) : String() 
    {
        bool valid = true;
        for (int i = 0; str[i] != '\0'; ++i) 
        {
            if (str[i] != '0' && str[i] != '1') 
            {
                valid = false;
                break;
            }
        }
        if (valid) 
        {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        }
        else 
        {
            data = new char[1];
            data[0] = '\0';
            length = 0;
        }
    }

   
    BitString(const BitString& other) : String(other) {}

  
    ~BitString() {}


    void toggleSign() 
    {
        for (int i = 0; i < length; ++i) 
        {
            data[i] = (data[i] == '0') ? '1' : '0';
        }
    }

    BitString operator+(const BitString& other) 
    {
        int max_length = std::max(this->length, other.length);
        char* result = new char[max_length + 1];
        result[max_length] = '\0';

       
        char* a = new char[max_length + 1];
        char* b = new char[max_length + 1];
        std::fill(a, a + max_length - this->length, '0');
        std::strcpy(a + max_length - this->length, this->data);
        std::fill(b, b + max_length - other.length, '0');
        std::strcpy(b + max_length - other.length, other.data);

    
        int carry = 0;
        for (int i = max_length - 1; i >= 0; i--) 
        {
            int bit_a = a[i] - '0';
            int bit_b = b[i] - '0';
            int sum = bit_a + bit_b + carry;
            result[i] = (sum % 2) + '0'; 
            carry = sum / 2; 
        }

        delete[] a;
        delete[] b;

        BitString result_string;
        result_string.data = result;
        result_string.length = max_length;
        return result_string;
    }

    bool operator==(const BitString& other) 
    {
        return (length == other.length && strcmp(data, other.data) == 0);
    }
};


int main() 
{
    std::vector<String*> array; 
    int choice;
    bool running = true;

    while (running) 
    {
        std::cout << "1. Create new String\n";
        std::cout << "2. Create new BitString\n";
        std::cout << "3. Display all strings\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            std::cout << "Enter a string: ";
            char buffer[1024];
            std::cin >> buffer;
            array.push_back(new String(buffer));
            break;
        }
        case 2: 
        {
            std::cout << "Enter a bit string: ";
            char buffer[1024];
            std::cin >> buffer;
            array.push_back(new BitString(buffer));
            break;
        }
        case 3: 
        {
            for (size_t i = 0; i < array.size(); ++i) 
            {
                std::cout << "String " << i << ": " << array[i]->getLength() << " characters" << std::endl;
            }
            break;
        }
        case 4:
            running = false;
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    }

    // Освобождение памяти
    for (auto str : array) 
    {
        delete str;
    }

    return 0;
}