#include<iostream>
#include<fstream>


int main(){
    const int hieght = 50;
    const int leanght = 50;
    char world[hieght*leanght] = {'.'};
    bool antiNode[hieght*leanght] = {0};
    int total = 0;

    std::ifstream input;
    input.open("input.txt", std::ofstream::in );
    if (input.fail()) {
		std::cout << "Error happend with inFile.";
		exit(1);
	}
    
    for(int i = 0; i < hieght*leanght; i++){
        input >> world[i];
    }
    
    for(int i = 0; i < hieght*leanght; i++){
        if(world[i] != '.'){
            int rootX = i % leanght;
            int rootY = i / hieght;
            for(int p = 0; p < hieght*leanght; p++){
                if(i != p && world[i] == world[p]){
                    int disX = ((p % leanght) - rootX);
                    int disY = ((p / hieght) - rootY);
                    int branchX = rootX;
                    int branchY = rootY;
                    while(true){
                        branchX += disX;
                        branchY += disY;
                        if(branchX >= 0 && branchX < leanght && branchY >= 0 && branchY < hieght){
                            antiNode[branchX + branchY * leanght] = 1;
                        }
                        else{
                            break;
                        }
                    }            

                }
            }
        }
    }

    for(int i = 0; i < hieght*leanght; i++){
        if(i % hieght == 0){
            std::cout << std::endl;
        }
        if(antiNode[i]){
            
            std::cout << '#';
            total++;
        }
        else{
            std::cout << world[i];
        }
    }
    std::cout << total;
    return 0;
}