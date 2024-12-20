#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

unsigned int convertStringToInt(char string[], int * position, int lenght){
    bool writing = 0;
    int read = 0, i = *position;

    for(i ; i < lenght; i++){

        int digit = 0;
        switch (string[i]){

        case 'w':
            digit = 1;
            break;
        case 'u':
            digit = 2;
            break;
        case 'b':
            digit = 3;
            break;
        case 'r':
            digit = 4;
            break;
        case 'g':
            digit = 5;
            break;
        }

        if(string[i] =='\000'){
            break;
        }
        if(digit == 0){
            if(writing){
                break;
            }
        }
        else{
            writing = true;
            read = (read << 3) + digit;
        }
    }
    
    *position = i;
    return read;
}

bool fun(unsigned int a,unsigned int b) { 
    return (a > b); 
}

unsigned int calLenght(unsigned int a){
    unsigned int temp = 0;

    while(a > 0){
        temp++;
        a = a >> 3;
    }
    return temp;
}

bool reacheable(char check[], unsigned int pos, unsigned int leanght, std::vector <unsigned int> patterns, std::vector <unsigned int> leanghts){
    bool good = 0;

    for(int i = 0; i < patterns.size(); i++){
        bool skip = 0;

        if(pos + leanghts[i] > leanght){
            skip = 1;
        }

        if(!skip){

            for(int p = 0; p < leanghts[i]; p++){
                
                if(check[pos + p] != ((patterns[i] >> (leanghts[i] - 1 - p) * 3) & 7)){
                    skip = 1;
                    break;
                }
            }
        }
        if(!skip){
            if(pos + leanghts[i] == leanght){
                return 1;
            }
            good = reacheable( check, pos + leanghts[i], leanght, patterns, leanghts);
        }

        if(good){
            break;
        }
    }
    return good;
}

int main(){
    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    char line[3001] = {0};

    std::vector <unsigned int> patterns;

    input.getline(line, 3001);

    int pos = 0;
    unsigned int temp = convertStringToInt(line, &pos, 3001);

    while(temp != 0){
        patterns.push_back(temp);
        temp = convertStringToInt(line, &pos, 3001);
    }
    
    patterns.shrink_to_fit();

    std::sort(patterns.begin(), patterns.end(), fun);

    std::vector <unsigned int> leanghts;
    leanghts.resize(patterns.size());

    for(int i = 0; i < patterns.size(); i++){
        leanghts[i] = (calLenght(patterns[i]));
    }

    char check[200];
    input.getline(line, 201);
    input.getline(line, 201);
    unsigned int total = 0;

    while(!input.eof()){
        int i = 0;
        
        while (line[i] != 0 && i < 200){
            switch(line[i]){
                case 'w':
                    check[i] = 1;
                break;
                case 'u':
                    check[i] = 2;
                break;
                case 'b':
                    check[i] = 3;
                break;
                case 'r':
                    check[i] = 4;
                break;
                case 'g':
                    check[i] = 5;
                break;
                
            }
            i++;
        }

        if(reacheable(check, 0, i, patterns, leanghts)){
            total++;
        }
        input.getline(line, 201);    
    }

    std::cout << total;
    return 0;
} 