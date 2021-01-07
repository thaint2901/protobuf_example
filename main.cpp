// g++ 

// g++ -I /usr/local/include -L /usr/local/lib/ ./main.cpp protobuf.pb.cc -o main

#include <iostream>
#include <string>
#include <vector>
#include "protobuf.pb.h"
using namespace std;

typedef unsigned char uchar;
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
static std::string base64_encode(const std::string &in) {
    std::string out;

    int val=0, valb=-6;
    for (uchar c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back(b[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back(b[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}


static std::string base64_decode(const std::string &in) {

    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T[b[i]] = i;

    int val=0, valb=-8;
    for (uchar c : in) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            out.push_back(char((val>>valb)&0xFF));
            valb-=8;
        }
    }
    return out;
}

 
int main(int argc, char** argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    data::Person p;

    p.set_name("Martin Vorbrodt");
    p.set_dob(19800830);
    p.set_email("martin@vorbrodt.blog");

    vector<float> fData (1000, 0);
    // Create 1000 random values
    for (int i = 0; i < fData.size(); i++)
    {
        fData[i] = rand() % 1001;
    }
    *p.mutable_emb() = {fData.begin(), fData.end()};

    string binary;
    p.SerializeToString(&binary);
    // cout << binary.c_str() << endl;

    // data::Person p2;
    // p2.ParseFromString(binary);

    // cout << "Name  = " << p2.name() << endl;
    // cout << "DOB   = " << p2.dob() << endl;
    // cout << "EMail = " << p2.email() << endl;
    // int element_size;
    // string element_name;
    // for (int i=0; i < p2.emb_size(); i++) {
    //     cout << "EMail = " << p2.emb(i) << endl;
    // }
    
    google::protobuf::ShutdownProtobufLibrary();

    string binary_b64;
    binary_b64 = base64_encode(binary);
    cout << binary_b64 << endl;

    return 0;
}