#include<iostream>
#include<fstream>
int readint(char string[], int * position, int lenght){
    bool writing = 0;
    int read = 0, i = *position;

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
    short leftRule[1176];
    short rightRule[1176];
    int positions[100], iLine[100];
    long long total = 0;

    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    char line[256] = {'\000'};

    for(int i = 0; i <1176; i++){
        int pos = 0;
        input.getline(line, 256);
        leftRule[i] = readint(line, &pos, 256);
        rightRule[i] = readint(line, &pos, 256);
    }

    while(!input.eof()){

        for(int q = 0; q < 100; q++){
            positions[q] = -1;
            iLine[q] = 0;
        }

        for(int q = 0; q < 256; q ++){
            line[q] = '\000';
        }
        
        int pos = 0;
        input.getline(line, 256);
        int temp = readint(line, &pos, 256);
        int i = 0;

        while(temp != -1 && i <= 100){
            positions[temp] = i;
            iLine[i] = temp;
            i++;
            temp = readint(line, &pos, 256);
        }
        bool add = 1;
            //A loop that swaps the elements until it passes the test. it will always find a solution if there is one
        for(int p = 0; p < 1176;){
            if(positions[leftRule[p]] > positions[rightRule[p]] && positions[leftRule[p]] != -1 && positions[rightRule[p]] != -1){
                int swap = iLine[positions[leftRule[p]]];

                iLine[positions[leftRule[p]]] = iLine[positions[rightRule[p]]];
                iLine[positions[rightRule[p]]]= swap;

                swap = positions[leftRule[p]];

                positions[leftRule[p]] = positions[rightRule[p]];
                positions[rightRule[p]] = swap;
                p = 0;
                add = 0;
            }
            else{
                p++;
            }
        }
        if (!add){
            total += iLine[(i - 1)/2];
        }

    }
    std::cout << total;
    return 0;
}