#include<iostream>
#include<fstream>

int readint(char string[], int * position, int lenght){
    bool writing = 0;
    int read = 0, i = *position;
    for(i ; i < lenght; i++){
        if(string[i] == ' ' || string[i] == '\n'|| string[i] == '\000'){
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

bool check(int a, int b, int incresing){
    if((incresing == 1 && a >= b)){
        return 0;             
    }
    else if(incresing == -1 && a <= b){
        return 0; 
                    
    }
    if(!(abs(a - b) >= 1 && abs(a - b) <= 3)){
        return 0;
                        
    }
    return 1;
}

int main(){
    std::ifstream startFile;
    startFile.open("input.txt", std::ofstream::in );
    if (startFile.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    
    int count =0;
    for(int i = 0; i < 1000; i++){
        bool  safe = 1, remove = 1;
        char temp[100] = {'\000'};
        int a = 0,b =0, incresing=0, position = 0, set[100]= {0};
        startFile.getline(temp, 100);
        int Index = 0;
        while(true){
            a = readint(temp, &position, 100);
            if(a == -1){
                break;
            }
            set[Index] = a;
            Index++;
        }
        // part one
        for(int p = 0; p < Index - 1; p++){
            if(incresing ==0){
                if(set[p] < set[p+1]){
                    incresing = 1;
                }
                else if(set[p] > set[p+1]){
                    incresing = -1;
                }
                else if(set[p] == set[p+1]){
                    safe = 0;
                    break;
                }
            }

            if(!check(set[p], set[p+1], incresing)){
                safe = 0;
                break;
            }
        }
        //part two
        if(!safe){
            for(int q = 0; q < Index; q++){
                safe = 1;
                incresing = 0;

                for(int p = 0; p < Index - 2; p++){
                    if(incresing ==0){
                        // short hand if statements to incriment by one => cheks the set and skips one data point
                        if(set[(p >= q) ? (p+1) : (p)] < set[(p + 1 >= q) ? (p+2) : (p+1)]){
                            incresing = 1;
                        }
                        else if(set[(p >= q) ? (p+1) : (p)] > set[(p + 1 >= q) ? (p+2) : (p+1)]){
                            incresing = -1;
                        }
                        else if(set[(p >= q) ? (p+1) : (p)] == set[(p + 1 >= q) ? (p+2) : (p+1)]){
                            safe = 0;
                            break;
                        }
                    }
                    if(!check(set[(p >= q) ? (p+1) : (p)], set[(p + 1 >= q) ? (p+2) : (p+1)], incresing)){
                    safe = 0;
                    break;
                    }
                }
                if(safe){
                    break;
                }
            }    
            
            }
        

        if(safe){
            count++;
        }
    }
    
    
    std::cout << count;
    return 0;
}