#include <iostream>

#include "Crypto.h"
#include "CryptoString.h"
#include "CryptoFile.h"
#include <taskflow.hpp>

using namespace std;

int main() {


    /*encryptFile("life.xlsx", "lifeC.xlsx", key);
    decryptFile("lifeC.xlsx", "lifeorig.xlsx", key);

    unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
*/

    auto c1 = CryptoFile("onipot");

    c1.encrypt2("lol.mkv","lol2.mkv");
    //c1.decrypt("lol2.mkv","lolOrig.mkv");
    /*auto c1 = CryptoFile("onipot");
    c1.encrypt("lol.mkv","lol2.mkv");
    c1.decrypt("lol2.mkv","lolOrig.mkv");*/
    //decryptFile("lol2.mkv", "lolOrig.mkv", key);
    //encryptFile("lol.mkv", "lol2.mkv", key);
    //readFile1Thread("lol.mkv", "lol2.mkv", key);
    /*encryptFile("lol.mkv", "lol2.mkv", key);
    decryptFile("lol2.mkv", "lolOrig.mkv", key);*/
    system("pause");
    return 0;
}