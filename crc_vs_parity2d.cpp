#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

const int generator = 0x11021;

//the same with crc_tx and crc_rx
std::string crc16(std::string data, int num, unsigned int crc)
{
    data=data+"0000000000000000";
    num+=16;
    for (int i=0; i<num;i++){
        crc <<= 1;
        crc=crc^(int(data[i]-'0'));
        std::string str1 = std::bitset<17>(crc).to_string();
        if(crc&0x10000){
            crc=(crc) ^ (generator);
        }
        std::string str2 = std::bitset<17>(crc).to_string();
        int n = 2;
    }
    return std::bitset<16>(crc).to_string();
}

//figure our the parity code
std:: string parity(std::string data,int num)
{
    std::string parity_data="";
    int row=0;
    std::string col="00000000";
    std::string r="";
    for(int i=0;i<num;i++){
    // figure out a new bit of row, and append it
        if(i%8==0){
            if(i!=0){
                parity_data=parity_data+std::bitset<1>(row).to_string();
                r+=(row+'0');
                row=0;
            }
        }
        row=row^int(data[i]-'0');
        parity_data=parity_data+std::bitset<1>(data[i]).to_string();
        // XOR a new bit of data to col
        col[i%8]=(int(col[i%8]-'0')^int(data[i]-'0'))+'0';
    }
    r+=row+'0';
    parity_data=parity_data+std::bitset<1>(row).to_string();
    int label=0;//to record to final bit of row and col
    for(int i=0;i<8;i++){
        label^=col[i]-'0';
    }
    std::cout << "2D Parity: Col: " <<col<<"   Row: "<<r<<label<<";"<<"   result: ";
    col+=label+'0';
    parity_data+=col;
    return parity_data;
}
// similar to "parity", but change 8 to 9
std:: string parity_check(std::string data){
    int num=data.length();
    int row=0;
    std::string col="000000000";
    for(int i=0;i<num;i++){
        if(i%9==8){
            row^=data[i]-'0';
            // to figure out the row, and return false if row !=0
            if(row==1){
                return "Not Pass";
            }
            row=0;
            }
        else{
            row^=data[i]-'0';
        }
        // same with the row
        col[i%9]=(int(col[i%9]-'0')^int(data[i]-'0'))+'0';
    }
    if(col!="000000000"){
        return "Not Pass";
    }
    else return "Pass";

}

int main()
{
    std::string data;
    std::ifstream file("pa1_data/dataVs.txt");
    std::string parity_data="";
    std::string result_crc;
    std::string crc_data;
    while (file >> data)
    {
        int num = data.length();
        if(num<65){
            parity_data=parity(data,num);
            // std:: cout<<parity_check(parity_data)<<std::endl;
            // std::cout<<data<<std::endl;
            // std::cout<<parity_data<<std::endl;
            unsigned int crc = 0;
            result_crc = crc16(data, num, crc);
            crc_data=data+result_crc;
            // std::cout << "CRC: " <<result_crc<<"   result:" << std::endl;
        }
        else{
            for(int i=0;i<data.length();i++){
                parity_data[i]=(parity_data[i]-'0')^(data[i]-'0')+'0';
            }
            std:: cout<<parity_check(parity_data)<<std::endl;
            for(int i=0;i<data.length();i++){
                crc_data[i]=(crc_data[i]-'0')^(data[i]-'0')+'0';
            }
            std::cout << "CRC: " <<result_crc<<"                        result: ";
            std::string check_crc = crc16(data, data.length(), 0);
            if (check_crc=="0000000000000000"){
                std::cout << "Pass"<< std::endl;
            }
            else std::cout << "Not Pass: "  << std::endl;
        }
    }
    return 0;
}
