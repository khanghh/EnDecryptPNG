//
//  main.cpp
//  EnDecryptPNG
//
//  Created by Khang Hoang on 1/22/18.
//  Copyright © 2018 Khang Hoang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void DecryptPNGII(char* data, int dataLen, char*& array, int& arrayLen) {
    arrayLen = dataLen - 18;
    array = new char[arrayLen];
    array[0] = 67;
    array[1] = 87;
    array[2] = 83;
    memcpy(array + 124, data + 21, dataLen - 142);
    memcpy(array + 3, data + dataLen - 121, 121);
}

void EncryptPNGII(char* data, int dataLen, char*& array, int& arrayLen) {
    arrayLen = dataLen + 18;
    array = new char[arrayLen];
    for (int i = 0; i < 21; i++) {
        array[i] = i;
    }
    memcpy(array + 21, data + 124, dataLen - 124);
    memcpy(array + arrayLen - 121, data + 3, 121);
}

int main(int argc, const char * argv[]) {
    char* data = nullptr;
    int dataLen = 0;
    char* exportData = nullptr;
    int exportDataLen = 0;
    for (int i = 0; i < argc; i++) {
        string infile = string(argv[i]);
        string outfile = string();
        ifstream ifs(infile.c_str(), ios::ate | ios::binary);
        if (ifs) {
            dataLen = (int)ifs.tellg();
            ifs.seekg(0, ifs.beg);
            data = new char[dataLen];
            ifs.read(data, dataLen);
            ifs.close();
            if (strcmp((*(argv+i) + strlen(argv[i]) - 4), ".swf") == 0
                || strcmp((*(argv+i) + strlen(argv[i]) - 4), ".SWF") == 0) {
                outfile = string(infile).replace(infile.length() - 4, 4, ".png");
                EncryptPNGII(data, dataLen, exportData, exportDataLen);
                ofstream ofs(outfile.c_str(), ios::out | ios::binary);
                ofs.write(exportData, exportDataLen);
                ofs.close();
                cout << infile << " >> " << outfile << endl;
            }
            else if (strcmp((*(argv+i) + strlen(argv[i]) - 4), ".png") == 0
                     || strcmp((*(argv+i) + strlen(argv[i]) - 4), "PNG") == 0) {
                outfile = string(infile).replace(infile.length() - 4, 4, ".swf");
                DecryptPNGII(data, dataLen, exportData, exportDataLen);
                ofstream ofs(outfile.c_str(), ios::out | ios::binary);
                ofs.write(exportData, exportDataLen);
                ofs.close();
                cout << infile << " >> " << outfile << endl;
            }
        }
        delete[] data;
        delete[] exportData;
    }
    return 0;
}
