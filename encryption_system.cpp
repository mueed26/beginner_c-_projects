#include <iostream>
#include <fstream>
#include <limits>  // Added for input validation

using namespace std;

// Custom Stack Implementation
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T element) {
        Node* newNode = new Node(element);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (!isEmpty()) {
            Node* temp = top;
            T data = top->data;
            top = top->next;
            delete temp;
            return data;
        }
        return 0; // Stack is empty
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

// Custom Queue Implementation
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };

    Node* front;
    Node* back;

public:
    Queue() : front(nullptr), back(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }
    }

    T dequeue() {
        if (!isEmpty()) {
            Node* temp = front;
            T data = front->data;
            front = front->next;
            if (front == nullptr) {
                back = nullptr;
            }
            delete temp;
            return data;
        }
        return 0; // Queue is empty
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};

template <typename T>
class FileHandler {
public:
    static T readFromFile(const string& filePath) {
        ifstream file(filePath);
        if (file.is_open()) {
            T content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
            file.close();
            return content;
        } else {
            cout << "Error: Unable to open file for reading." << endl;
            return T();
        }
    }

    static void writeToFile(const string& filePath, const T& content) {
        ofstream file(filePath);
        if (file.is_open()) {
            file << content;
            file.close();
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

template <typename T>
class TextManipulator {
public:
    static T reverseCharacters(const T& text, Stack<char>& charStack) {
        T reversedText = "";
        for (char c : text) {
            charStack.push(c);
        }

        while (!charStack.isEmpty()) {
            reversedText += charStack.pop();
        }

        return reversedText;
    }

    static T replaceVowels(const T& text) {
        T result = "";
        for (char c : text) {
            switch (tolower(c)) {
                case 'a':
                case 'A':
                    result += '*';
                    break;
                case 'e':
                case 'E':
                    result += '@';
                    break;
                case 'i':
                case 'I':
                    result += '#';
                    break;
                case 'o':
                case 'O':
                    result += '$';
                    break;
                case 'u':
                case 'U':
                    result += '&';
                    break;
                default:
                    result += c;
            }
        }
        return result;
    }
};

template <typename T>
class Encryption : public TextManipulator<T> {
public:
    static T encrypt(const T& text) {
        Stack<char> charStack;
        T reversedText = TextManipulator<T>::reverseCharacters(text, charStack);
        T encryptedText = TextManipulator<T>::replaceVowels(reversedText);
        return encryptedText;
    }
};

template <typename T>
class Decryption : public TextManipulator<T> {
private:
    static char revertVowel(char ch) {
        switch (ch) {
            case '*':
                return 'a';
            case '@':
                return 'e';
            case '#':
                return 'i';
            case '$':
                return 'o';
            case '&':
                return 'u';
            default:
                return ch;
        }
    }

public:
    static T decrypt(const T& encryptedText, Queue<char>& charQueue) {
        T decryptedText = "";
        Stack<char> charStack;  // Custom stack for reversal

        for (char c : encryptedText) {
            charStack.push(c);
        }

        while (!charStack.isEmpty()) {
            char currentChar = charStack.pop();
            if (currentChar == ' ' || currentChar == '\n') {
                decryptedText += currentChar;
            } else {
                decryptedText += revertVowel(currentChar);
            }
        }

        return decryptedText;
    }
};

class UserInterface {
public:
    static void displayMenu() {
        cout << "1. Encrypt Text and Display Encrypted Text" << endl;
        cout << "2. Decrypt Encrypted Text and Display Original Text" << endl;
        cout << "3. Quit" << endl;
    }

    static string getInput(const string& prompt) {
        cout << prompt;
        string input;
        getline(cin, input);

        // Simple input validation
        while (cin.fail()) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input. Please enter again: ";
            getline(cin, input);
        }

        return input;
    }
};

int main() {
    while (true) {
        UserInterface::displayMenu();

        string choice = UserInterface::getInput("Enter your choice: ");

        if (choice == "1") {
            string fileName = UserInterface::getInput("Enter the file name: ");
            string inputText = FileHandler<string>::readFromFile(fileName);

            if (inputText.empty()) {
                cout << "Error: Empty input file." << endl;
                continue;
            }

            Stack<char> charStack;
            string encryptedText = Encryption<string>::encrypt(inputText);
            cout << "Encrypted Text: " << encryptedText << endl;

        } else if (choice == "2") {
            string encryptedFileName = UserInterface::getInput("Enter the encrypted file name: ");
            string encryptedText = FileHandler<string>::readFromFile(encryptedFileName);

            if (encryptedText.empty()) {
                cout << "Error: Empty encrypted file." << endl;
                continue;
            }

            Queue<char> charQueue;
            string decryptedText = Decryption<string>::decrypt(encryptedText, charQueue);
            cout << "Original Text: " << decryptedText << endl;

        } else if (choice == "3") {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

