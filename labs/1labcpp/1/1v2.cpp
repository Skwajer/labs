#include <iostream>
#include <cstring>
#include <fstream>

enum encoder_mode
{
    encrypt_it,
    decrypt_it
};

class encoder
{
private:
    unsigned char *key;
    size_t key_size;

public:
    encoder(unsigned char const *k, size_t k_len);
    ~encoder();
    void mutator(unsigned char const *, size_t);
    void encode(char const *, char const *, encoder_mode);
};

encoder ::encoder(const unsigned char *k, size_t k_len)
{
    key_size = k_len;
    key = new unsigned char[key_size];
    if (key == nullptr)
    {
        throw std::bad_alloc();
    }
    memcpy(key, k, key_size);
}

encoder ::~encoder()
{
    delete[] key;
    key = nullptr;
}

void encoder ::mutator(unsigned char const *new_k, size_t new_key_size)
{
    delete[] key;
    key_size = new_key_size;
    key = new unsigned char [key_size];
    if (key == nullptr)
    {
        throw std::bad_alloc();
    }
    memcpy(key, new_k, key_size);
}

void encoder ::encode(const char *input_file, const char *output_file, encoder_mode)
{
    int i, j = 0;
    unsigned char s[256];

    for (i = 0; i < 256; ++i)
    {
        s[i] = i;
    }

    for (i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % key_size]) % 256;
        std::swap(s[i], s[j]);
    }


    std::ifstream in_file(input_file, std::ios::binary);
    if(!in_file.is_open())
    {
        throw std::runtime_error("input file isn't open");
    }

    std::ofstream out_file(output_file, std::ios::binary);
    if(!out_file.is_open())
    {
        throw std::runtime_error("output file isn't open");
    }

    char byte;
    while (in_file.read(&byte, sizeof(unsigned char)))
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        std::swap(s[i], s[j]);
        char result_byte = (byte ^ s[(s[i] + s[j]) % 256]);
        out_file.write(&result_byte, sizeof(unsigned char));
    }
    in_file.close();
    out_file.close();
}

void swap(unsigned char &a, unsigned char &b)
{
    unsigned char temp = a;
    a = b;
    b = temp;
}

int main()
{
    char const *data_file = "C:/Users/golds/ClionProjects/labs/1labcpp/1/data_file_for1.txt";
    char const *encrypted_file = "C:/Users/golds/ClionProjects/labs/1labcpp/1/resfile_for_1.bin";
    unsigned char key[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t key_size = sizeof(key);
    try
    {
        encoder enc(key, key_size);
        enc.encode(data_file, encrypted_file, decrypt_it);
        return 0;
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "Memory allocation failed: " << std::endl;
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}