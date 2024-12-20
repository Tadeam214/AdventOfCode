#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

int readint(char string[], int * position, int lenght){
    bool writing = 0;
    int read = 0,i = *position;

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
    
    char line[256];
    int pos = 0;
    input.getline(line, 256);
    int a = readint(line, &pos, 256);

    pos = 0;
    input.getline(line, 256);
    int b = readint(line, &pos, 256);

    pos = 0;
    input.getline(line, 256);
    int c = readint(line, &pos, 256);

    input.getline(line, 256);
    input.getline(line, 256);

    std::vector<char> program;

    pos = 0;
    int temp = readint(line, &pos, 256);

    while(temp >= 0){
        program.push_back(temp);
        temp = readint(line, &pos, 256);
    }
    
    program.shrink_to_fit();

    int z = 0, o = 1, tw = 2, tr = 3;

    int* comboLookUp[] = {&z, &o, &tw, &tr, &a, &b, &c};
    int instructionPointer = 0;

    while(instructionPointer < program.size()){

        switch (program[instructionPointer]){

        case 0:
            a = a / (int) pow(2, *comboLookUp[ program[instructionPointer + 1]]);
            instructionPointer +=2;
        break;

        case 1:
            b = b ^ program[instructionPointer + 1];
            instructionPointer +=2;
        break;

        case 2:
            b = (*comboLookUp[ program[instructionPointer + 1]]) & 7;
            instructionPointer +=2;
        break;

        case 3:
            if(a != 0 && program[instructionPointer + 1] != instructionPointer){
                instructionPointer = program[instructionPointer + 1];
            }
            else{
                instructionPointer +=2;
            }
        break;

        case 4:
            b = b ^ c;
            instructionPointer +=2;
        break;

        case 5:
            std::cout << ((*comboLookUp[ program[instructionPointer + 1]]) & 7) << ',';
            instructionPointer +=2;
        break;

        case 6:
            b = a / (int) pow(2, *comboLookUp[ program[instructionPointer + 1]]);
            instructionPointer +=2;
        break;

        case 7:
            c = a / (int)pow(2, *comboLookUp[ program[instructionPointer + 1]]);
            instructionPointer +=2;
        break;
        }
    }
    return 0;
}