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
    input.getline(line, 256);
    input.getline(line, 256);
    input.getline(line, 256);
    input.getline(line, 256);
    input.getline(line, 256);

    std::vector<char> program;

    int pos = 0;
    int temp = readint(line, &pos, 256);

    while(temp >= 0){
        program.push_back(temp);
        temp = readint(line, &pos, 256);
    }
    
    program.shrink_to_fit();

    unsigned long long z = 0, o = 1, tw = 2, tr = 3, a, b, c;
    unsigned long long* comboLookUp[] = {&z, &o, &tw, &tr, &a, &b, &c};

    int findDigit = program.size();
    unsigned long long Answear =0;
    unsigned long long skip =0;


    while(findDigit > 0){
        findDigit--;
        bool gold = 0;
        unsigned long long i;

        for( i = (skip >> (findDigit * 3)) & 7; i < 8; i++){

            a = Answear + (i << (findDigit * 3));
            b = 0;
            c = 0;

            int curentPos = 0;
            int instructionPointer = 0;
            
            while(instructionPointer < program.size() && !gold){

                switch (program[instructionPointer]){

                case 0:
                    a = a / (unsigned long long) pow(2, *comboLookUp[ program[instructionPointer + 1]]);
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
                    if((findDigit == curentPos) && (((*comboLookUp[ program[instructionPointer + 1]]) & 7) == program[findDigit])){
                        gold = 1;
                        break;
                    }
                    curentPos++;
                    instructionPointer +=2;
                break;

                case 6:
                    b = a / (unsigned long long) pow(2, *comboLookUp[ program[instructionPointer + 1]]);
                    instructionPointer +=2;
                break;

                case 7:
                    c = a / (unsigned long long)pow(2, *comboLookUp[ program[instructionPointer + 1]]);
                    instructionPointer +=2;
                break;
                }

                if(gold){
                    break;
                }
            }
            
            if(gold){
                break;
            }
        }

        if(gold){
            Answear += i << (findDigit * 3);
        }
        else{
            // if this is wrong combination we return to the start and we increas skip and set all skip's lower bits to 0
            skip += 1 << (findDigit * 3 + 3);
            skip = skip & (~0 << findDigit * 3 + 3);

            findDigit = program.size();
            Answear=0;
        }
    }
        
    std::cout << Answear;
    return 0;
}