#pragma once

class String {
private:
    char* data;
    size_t length;

public:
    // Default constructor
    String() : data(nullptr), length(0) {}

    // Constructor with char array
    String(const char* str) : data(nullptr), length(0) {
        if (str) {
            length = crt::custom_strlen(str);
            data = new char[length + 1];
            crt::custom_strcpy(data, str);
        }
    }

    // Copy constructor
    String(const String& other) : data(nullptr), length(other.length) {
        if (other.data) {
            data = new char[length + 1];
            crt::custom_strcpy(data, other.data);
        }
    }

    // Move constructor
    String(String&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }

    // Destructor
    ~String() {
        delete[] data;
    }

    // Copy assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            if (other.data) {
                data = new char[length + 1];
                crt::custom_strcpy(data, other.data);
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Move assignment operator
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    bool operator==(const String& other) const {
        // Compare the lengths first
        if (length != other.length)
            return false;

        // Compare the actual string data
        return crt::custom_strcmp(data, other.data) == 0;
    }

    // Getter for the length of the string
    size_t size() const {
        return length;
    }

    char* begin() {
        return data;
    }

    // Returns a const iterator to the beginning of the string
    const char* begin() const {
        return data;
    }

    // Returns an iterator to the end of the string
    char* end() {
        return data + length;
    }

    // Returns a const iterator to the end of the string
    const char* end() const {
        return data + length;
    }

    // Overloaded index operator for read-only access
    const char& operator[](size_t index) const {
        return data[index];
    }

    // Overloaded index operator for assignment
    char& operator[](size_t index) {
  
        return data[index];
    }

    void append(const char* str) {
        size_t strLength = crt::custom_strlen(str);
        char* newData = new char[length + strLength + 1];

        // Copy existing data to the new buffer
        if (data != nullptr) {
            crt::custom_strcpy(newData, data);
            delete[] data;
        }

        // Append the new string to the end
        crt::custom_strcpy(newData + length, str);
        length += strLength;
        newData[length] = '\0';
        data = newData;
    }

   
    // Convert the string to a const char*
    const char* c_str() const {
        return data;
    }
};


class WString {
private:
    wchar_t* data;
    size_t length;

public:
    // Default constructor
    WString() : data(nullptr), length(0) {}

    // Constructor with wide character array
    WString(const wchar_t* str) : data(nullptr), length(0) {
        if (str) {
            length = crt::custom_wcslen(str);
            data = new wchar_t[length + 1];
            crt::custom_wcscpy(data, str);
        }
    }

    // Copy constructor
    WString(const WString& other) : data(nullptr), length(other.length) {
        if (other.data) {
            data = new wchar_t[length + 1];
            crt::custom_wcscpy(data, other.data);
        }
    }

    // Move constructor
    WString(WString&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }

    template <typename Iterator>
    WString(Iterator begin, Iterator end) : data(nullptr), length(0) {
        Iterator it = begin;
        while (it != end) {
            ++length;
            ++it;
        }

        data = new wchar_t[length + 1];

        size_t i = 0;
        for (it = begin; it != end; ++it) {
            data[i++] = *it;
        }
        data[length] = L'\0';
    }

    // Destructor
    ~WString() {
        delete[] data;
    }

    // Copy assignment operator
    WString& operator=(const WString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            if (other.data) {
                data = new wchar_t[length + 1];
                crt::custom_wcscpy(data, other.data);
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Move assignment operator
    WString& operator=(WString&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // Getter for the length of the string
    size_t size() const {
        return length;
    }

    void append(const  wchar_t* str) {
        size_t strLength = crt::custom_wcslen(str);
        wchar_t* newData = new wchar_t[length + strLength + 1];

        // Copy existing data to the new buffer
        if (data != nullptr) {
            crt::custom_wcscpy(newData, data);
            delete[] data;
        }

        // Append the new string to the end
        crt::custom_wcscpy(newData + length, str);
        length += strLength;
        newData[length] = '\0';
        data = newData;
    }
    // Convert the string to a const wchar_t*
    const wchar_t* c_str() const {
        return data;
    }
};