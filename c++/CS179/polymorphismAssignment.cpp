// This program demonstrates an application
// of pure virtual functions.
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Encryption
{
protected:
    ifstream inFile;
    ofstream outFile;
public:
    Encryption(const string& inFileName,
              const string& outFileName);
    virtual ~Encryption();
    // Pure virtual function
    virtual char transform(char ch, int key = 1) const = 0;
    // Do the actual work.
    virtual void encrypt(int k) final;
    // Custom decrypt function
    virtual void decrypt(int k) final;
};

//*****************************************************
// Constructor opens the input and output file.
//*****************************************************
Encryption::Encryption(const string& inFileName,
                      const string& outFileName)
{
    inFile.open(inFileName);
    outFile.open(outFileName);
    if (!inFile)
    {
        cout << "The file " << inFileName
            << " cannot be opened.";
        exit(1);
    }
    if (!outFile)
    {
        cout << "The file " << outFileName
            << " cannot be opened.";
        exit(1);
    }
}

//*****************************************************
//Destructor closes files.
//*****************************************************
Encryption::~Encryption()
{
    inFile.close();
    outFile.close();
}

//*****************************************************
//Encrypt function uses the virtual transform
//member function to transform individual characters.
//*****************************************************
void Encryption::encrypt(int userKey)
{
    char ch;
    char transCh;
    inFile.get(ch);
    while (!inFile.fail())
    {
        transCh = transform(ch, userKey);
        outFile.put(transCh);
        inFile.get(ch);
    }
}

void Encryption::decrypt(int userKey)
{
    char ch;
    char transCh;
    try
    {
        inFile.get(ch);
        while (!inFile.fail())
        {
            transCh = transform(ch, userKey);
            outFile.put(transCh);
            inFile.get(ch);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

// The subclass simply overides the virtual
// transformation function
class SimpleEncryption : public Encryption
{
public:
    char transform(char ch, int key) const override
    {
        return ch + key;
    }

    SimpleEncryption(const string& inFileName,
                     const string& outFileName)
        : Encryption(inFileName, outFileName)
    {
    }
};

int main()
{
    string inFileName, outFileName;
    int key;
    cout << "Enter name of file to encrypt: ";
    cin >> inFileName;
    cout << "Enter name of file to receive "
         << "the encrypted text: ";
    cin >> outFileName;
    cout << "Enter key: ";
    cin >> key;
    SimpleEncryption obfuscate(inFileName, outFileName); // calls constructor
    obfuscate.encrypt(key);
    cout << "File encrypted." << endl;
    obfuscate.~SimpleEncryption();
    key = key * (-1);
    SimpleEncryption deobfuscate(outFileName, "decrypted.txt");
    deobfuscate.decrypt(key);
    return 0;
}