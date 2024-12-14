#include<iostream>
#include<fstream>

int readint(char string[], int * position, int lenght){
    bool writing = 0;
    int read =0,i = *position;
    for(i ; i < lenght; i++){
        if(string[i] =='\000'){
            break;
        }
        if(string[i] < '0' || string[i] > '9'){
            if(writing){
                break;
            }
        }
        else{
            writing = true;
            read = read * 10 + string[i]- '0';
        }
    }
    *position = i;
    if(!writing){
        read = -1;
    }
    return read;
}

int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    char line[256] = {0};
    long long koefinces[4];
    long long posX, posY;
    unsigned long long total = 0;
    unsigned long long A, B;
    while(!input.eof()){
        int pos=0;
        input.getline(line, 256);
        if(line[0] != 0){
        koefinces[0] = readint(line, &pos, 256);
        koefinces[1] = readint(line, &pos, 256);

        pos=0;
        input.getline(line, 256);
        koefinces[2] = readint(line, &pos, 256);
        koefinces[3] = readint(line, &pos, 256);

        pos=0;
        input.getline(line, 256);
        posX = readint(line, &pos, 256) + 10000000000000;
        posY = readint(line, &pos, 256) + 10000000000000;

        B = (posY * koefinces[0] - posX * koefinces[1]) / (koefinces[0] * koefinces[3] - koefinces[1] * koefinces[2]);
        A = (posY - B * koefinces[3]) / koefinces[1];
        if( A * koefinces[0] + B * koefinces[2] == posX && A * koefinces[1] + B * koefinces[3] == posY){
            total += A * 3 + B;
        }
        
        }
        


    }
    std::cout << total;
    return 0;
}