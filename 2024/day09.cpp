#include<iostream>
#include<fstream>
#include<vector>

int main(){
    
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}

    long long id = 0;
    char temp;
    bool space = 0;
    input >> temp;

    
    unsigned long long total = 0;
    std::vector <int> tape; 

    while(!input.eof()){
        
        if(space){
            for(int p = 0; p < temp - '0'; p++){
                // -1 is used as empty
                tape.push_back(-1);
            }
        }
        else{
            if(temp - '0' != 0){
                for(int p = 0; p < temp - '0'; p++){

                    tape.push_back(id);
                }
                id++;
            }
            
        }
        space = !space;
        input >> temp;

    }
        //part one would go here
    tape.shrink_to_fit();

    for(int i = 0; tape.size() - i > 0; i++){
        if(tape[tape.size() - 1 - i] != -1){
            int pos = tape.size() - 2 - i;
            int tempI = tape[tape.size() - 1 - i];
            int lenght = 1;

            while(pos > 0 && tape[pos] == tempI){
                lenght++;
                pos--;
            }
            bool write = 0;
            int p = 0;

            for(p; p <= pos; p++){
                int space = 0;
                if(tape[p] == -1){
                    int add = 0;
                    while(p + add <= pos && tape[p + add] == -1){
                        space++;
                        add++;
                    }
                    if(space >= lenght){
                        write = 1;
                        break;
                    }
                }
            }
            if(write){

                for(int q = 0; q < lenght; q++){
                    tape[p + q] = tempI;
                    tape[pos + 1 + q] = -1; 
                }
            }
            i += lenght - 1;
            
        }
    }

    for(long long i = 0; i < tape.size(); i++){  
        if(tape[i] != -1){
            total += i * (tape[i]);
        }  
    }
    std::cout << total;
    return 0;
}
/*  part one 
    "something fish" was a test totalM is the aomunt of files in tape, used in debugging to see if some files got deletet

    tape.shrink_to_fit();

    while(tape[tape.size() - 1] == -1){
        tape.pop_back();
    }

    for(long long i = 0; i < tape.size(); i++){
        
        if(tape[i] == -1){
            tape[i] = tape[tape.size() - 1];
            tape.pop_back();
        }
        while(tape[tape.size() - 1] == -1){
            tape.pop_back();
        }
    }
    if (tape.size() != totalM){
        std::cout <<" something fish " << tape.size() << std::endl << totalM << std::endl;
    }
    for(long long i = 0; i < tape.size(); i++){  
        if(tape[i] != -1){
            total += i * (tape[i]);
        }
        
        
    }
*/