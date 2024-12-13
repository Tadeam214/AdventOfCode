#include<iostream>
#include<fstream>

int main(){
    std::ifstream startFile;
    startFile.open("input.txt", std::ofstream::in );
    if (startFile.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    long long total = 0;
    char temp, mul[4] = {'u','l','('};
    bool n =1;

    while(!startFile.eof()){
        int a =0, b= 0;
        bool good = 1;
        startFile >> temp;
        // part one
        if('m'== temp && n){
            for(int i =0; i < 3; i++){
                startFile >> temp;
                if(!(mul[i] == temp)){
                    good=0;
                    break;
                }
            }

            if(good){
                while(true){
                    startFile >> temp;
                    if(temp >= '0' && temp <='9'){
                        a = a * 10 + (temp - '0');
                    }
                    else{
                        break;
                    }
                }
                if(temp ==',' && good){
                    while(true){
                        startFile >> temp;
                        if(temp >= '0' && temp <='9'){
                            b = b * 10 + (temp - '0');
                        }
                        else{
                            break;
                        }
                    }
                    if(temp == ')'){
                        total += a*b;
                    }

                }
            }
        }
        //part two
        else if('d'== temp){
            startFile >> temp;
            if('o' == temp){
                startFile >> temp;
                if('(' == temp){
                    startFile >> temp;
                    if(')' == temp){
                            n =1;
                    }
                }
                else if('n' == temp){
                    startFile >> temp;
                    if('\'' == temp){
                        startFile >> temp;
                        if('t' == temp){
                            startFile >> temp;
                            if('(' == temp){
                                startFile >> temp;
                                if(')' == temp){
                                    n =0;
                                }
                            }
                        } 
                    }  
                }
            }
        }

    }
    std::cout<<total;
    return 0;
}