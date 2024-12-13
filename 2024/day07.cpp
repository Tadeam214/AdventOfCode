#include<iostream>
#include<fstream>
#include<cmath>
unsigned long long readint(char string[], int * position, int lenght){
    bool writing = 0;
    unsigned long long read = 0,i = *position;
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
    char line[256];
    unsigned long long total = 0;

    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    
    while(!input.eof()){
        input.getline(line, 256);
        int pos = 0, i = 0;
        unsigned long long target = readint(line, &pos, 256), ints[65], temp;
        char oprera[64];

        for(int p = 0; p < 64; p++){
            oprera[p] = 0;
        }
        temp = readint(line, &pos, 256);

        while(temp != -1){
            ints[i] = temp;
            i++;
            temp = readint(line, &pos, 256);
        }

        for(int p = 0; p < pow(3, i - 1) ; p++){
            long long a = ints[0];
            int b;

            for(int q = 0; q < i - 1; q++){
                b = ints[q + 1];
                switch(oprera[q]){

                        case 0:
                        a = a + b;
                    break;

                        case 1:
                        a = a * b;
                    break;

                        case 2: 
                        int c = 1;
                        while(c <= b){
                            a *= 10;
                            c *= 10;
                        }
                        a = a + b;
                    break;
                }
            }
            if(a == target){
                total += target;
                break;
            }

            for (int p = 0; p < 64; p++){
                if (oprera[p] >= 2){
                    oprera[p] = 0;
                }
                else{
                    oprera[p] += 1;
                    break;
                }
            }
        }
    }
    std::cout << total;
    return 0;
}

/*  part one I managed to salvege it 
    mul is a bitmap of operations: 1 = mul, 0 = add

    while(!input.eof()){
        input.getline(line, 256);
        int pos = 0, i = 0;
        unsigned long long target = readint(line, &pos, 256), ints[65], temp;
        unsigned long long mul = 0;
        temp = readint(line, &pos, 256);

        while(temp != -1){
            ints[i] = temp;
            i++;
            temp = readint(line, &pos, 256);
        }
        for(int p = 0; p < pow(2, i - 1) ; p++){
            long long a = ints[0];
            int b;
            for(int q = 0; q < i - 1; q++){
                b = ints[q + 1];
                if((mul & (1 << q))){
                    a = a * b;
                }
                else{
                    a = a + b;
                }
            }
            if(a == target){
                total += target;
                break;
            }
            mul++;

        }
    }
    std::cout << total;
    return 0;
*\