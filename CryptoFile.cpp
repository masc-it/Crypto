//
// Created by Mauro on 03/11/2019.
//

#include "CryptoFile.h"

unsigned long long getTotalSystemMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
}

void CryptoFile::encrypt(char* in, char* out){
    std::fstream ifile(in, std::ios::in | std::ios::binary | std::ios::ate);
    std::fstream ofile(out, std::ios::out | std::ios::binary);

    if (!(ifile.is_open() && ofile.is_open())) {  }

    size_t size   = ifile.tellg();

    if (size > getTotalSystemMemory()){
        std::cout << "insufficient memory" << std::endl;
        return;
    }

    auto buffer = new unsigned char[size];

    std::cout << "Reading file.." << std::endl;
    ifile.seekg(0, std::ios::beg);
    ifile.read((char*)buffer, size);

    applyBuffer8Thread(buffer, size, &crypt_v1b);

    std::cout << "Writing to disk.." << std::endl;
    ofile.write((char*)buffer, size);

    delete[] buffer;
    ifile.close();
    ofile.close();
}


void CryptoFile::decrypt(char* in, char* out){
    std::fstream ifile(in, std::ios::in | std::ios::binary | std::ios::ate);
    std::fstream ofile(out, std::ios::out | std::ios::binary);

    if (!(ifile.is_open() && ofile.is_open())) {  }

    size_t size   = ifile.tellg();

    if (size > getTotalSystemMemory()){
        std::cout << "insufficient memory" << std::endl;
        return;
    }

    auto buffer = new unsigned char[size];

    std::cout << "Reading file.." << std::endl;
    ifile.seekg(0, std::ios::beg);
    ifile.read((char*)buffer, size);

    applyBuffer8Thread(buffer, size, decrypt_v1b);

    std::cout << "Writing to disk.." << std::endl;
    ofile.write((char*)buffer, size);
    delete[] buffer;
    ifile.close();
    ofile.close();
}

void CryptoFile::applyBuffer8Thread(unsigned char* buffer, size_t &size,
        std::function<unsigned char(unsigned char buff, const char *key, size_t key_length)> crypt){

    
    auto key = get_key();
    auto key_length = get_key_length();
    
    tf::Executor executor;

    tf::Taskflow tf;
    auto start = std::chrono::system_clock::now();

    auto START = tf.emplace(
            [&start] () {


                std::cout << "Started!" << std::endl;
                start = std::chrono::system_clock::now();

            });

    auto END = tf.emplace([&start] () {

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        printf("encryption ended in = %lld ms\n", static_cast<long long int>(elapsed.count()));

    });


    unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
    for ( auto i = 0U; i < concurentThreadsSupported; i++) {

        auto startt = i * size/concurentThreadsSupported;
        auto end = (i + 1 ) * size/concurentThreadsSupported;
        tf.emplace(

                [&buffer, &size, &crypt, &key, &key_length, startt, end] () mutable {

                        for (auto k = startt; k < end; k++) {
                            buffer[k] = crypt(buffer[k], key, key_length);

                        }
                }).precede(END).succeed(START);


    }
    executor.run(tf).wait();

}


void CryptoFile::encrypt2(char* in, char* out){
    std::fstream ifile(in, std::ios::in | std::ios::binary | std::ios::ate);
    std::fstream of(out, std::ios::out | std::ios::binary);
    of.close();
    std::fstream ofile(out, std::ios::app | std::ios::binary);

    if (!(ifile.is_open() )) {  }

    size_t size   = ifile.tellg();

    size_t byte_read = 0;
    size_t byte_read_rel = 0;
    size_t chunk_size = size;
    if ( size >= getTotalSystemMemory() || size > 2000000000) {
        chunk_size = 1000000000;
    }

    auto bb = new unsigned char[chunk_size];

    ifile.seekg(0, std::ios::beg);

    std::cout << "start reading" << std::endl;
    while ( byte_read <= size ){

        ifile.read((char*)bb, chunk_size);

        size_t in_read = ifile.gcount();
        if (in_read == 0) break;

        byte_read+=in_read;
        byte_read_rel+=in_read;


        if ( byte_read_rel % chunk_size == 0 || byte_read == size){

            applyBuffer8Thread(bb, byte_read_rel, crypt_v1b);

            std::cout << "Writing to disk" << std::endl;
            ofile.write((char*)bb, byte_read_rel);

            byte_read_rel = 0;

        }
    }

    delete[]bb;
    ifile.close();
    ofile.close();
}