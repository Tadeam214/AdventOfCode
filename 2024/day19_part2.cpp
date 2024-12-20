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

unsigned int calLenght(unsigned int a){
    unsigned int temp = 0;

    while(a > 0){
        temp++;
        a = a >> 3;
    }
    return temp;
}

bool fun(unsigned int a,unsigned int b) { 
    unsigned int afrist = a >> ((calLenght(a) - 1) * 3);
    unsigned int bfrist = b >> ((calLenght(b) - 1) * 3);

    if(afrist == bfrist){
        return (a > b);
    }
    else{
        return (afrist < bfrist);
    }
}

unsigned long long reacheable(char check[], unsigned int pos, unsigned int leanght, std::vector <unsigned int> patterns, std::vector <unsigned long long > lookUp,  unsigned int quickSkip[]){
    unsigned long long good = 0;
    unsigned int read = 0;

    for(int i = 0; i < 8; i++){

        if(pos + i + 1 > leanght){
            break;
        }

        read = (read << 3 ) + (check[pos + i]);
        bool isInPatterns = 0;

        for(int w = quickSkip[check[pos] - 1]; w < quickSkip[check[pos]]; w++){
            if(patterns[w] == read){
                isInPatterns = 1;
                break;
            }
            
        }

        if(isInPatterns){
            if(pos + i + 1 == leanght){
                good += 1;
            }
            else{
                good += lookUp[pos + i + 1];
            }
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
    std::vector <unsigned long long> sums;
    
    leanghts.resize(patterns.size());
    unsigned int quickSkpi[6];

    for(int i = 0; i < 6; i++){
        quickSkpi[i] = patterns.size();
    }

    for(int i = 0; i < patterns.size(); i++){
        leanghts[i] = (calLenght(patterns[i]));
        int temp = (patterns[i] >> ((leanghts[i] - 1) * 3) )- 1;

        if (i < quickSkpi[temp]){
            quickSkpi[temp] = i;
        }
        
    }
    
    char check[200];
    input.getline(line, 201);
    unsigned long long total = 0;

    while(!input.eof()){
        int i = 0;
        input.getline(line, 201);  
        
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
        sums.resize(i);

        for(int q = 0; q < i; q++){
            sums[q] = 0;
        }
        int Index = i;

        for(int q = 0; q < i; q++){
            Index--;
            sums[Index] = reacheable(check, Index, i, patterns, sums, quickSkpi);
        }

        total += sums[0];
    }
    
    std::cout << total;
    return 0;
} 