#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

const int generator = 0x11021;


//similar to crc_tx
unsigned int crc_check(std::string data, int num, unsigned int crc)
{
    // data=data+"0000000000000000";
    // num+=16;
    
    // figure out the remainder of the data with generator, if the remainder equals to zero, then return Pass, if not, return Not Pass.
    for (int i=0; i<num;i++){
        crc <<= 1;
        crc=crc^(int(data[i]-'0'));// to input a new bit of data
        std::string str1 = std::bitset<17>(crc).to_string();
        if(crc&0x10000){
            crc=(crc) ^ (generator);
        }
        std::string str2 = std::bitset<17>(crc).to_string();
        int n = 2;
    }
    return crc;
}

int main()
{
    std::string data;
    std::ifstream file("pa1_data/dataRx.txt");
    while (std::getline(file, data))
    {
        int num = data.length();
        unsigned int crc = 0;
        int result = crc_check(data, num, crc);// result to record the final remainder
        if (result==0){
            std::cout << "Pass"<< std::endl;
        }
        else std::cout << "Not Pass: "  << std::endl;
        
    }
    return 0;
}
