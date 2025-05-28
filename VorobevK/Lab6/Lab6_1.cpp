#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;
class seabattle{
    public:
    int o[10][10]; //0 is free space 1 is blocked
    int e[10][10]; //2 is ship 3 is damaged ship
    int remx=-1,remy=-1;


    seabattle(){};


    void placeboat(int a){
        int s=0;
        while (s!=1){
            int t1=rand()%(11-a),t2=rand()%(10);
            s=1;
            for(int i=0;i<a;i++){
                if(o[t1+i][t2]!=0)s=0;
            };
            if (s==1){
                for(int i=0;i<a;i++){
                    o[t1+i][t2]=2;
                };
                break;
            };
            t1=rand()%(10);
            t2=rand()%(11-a);
            s=1;
            for(int i=0;i<a;i++){
                if(o[t1][t2+i]!=0)s=0;
            };
            if (s==1){
                for(int i=0;i<a;i++){
                    o[t1][t2+i]=2;
                };
            };
        };
    };


    void updateo(){ //blocks unavailable sectors in own board
        for (int i=0; i<10;i++){
            for (int j=0; j<10;j++){
                if (o[i][j]==2){
                    
                    if(i-1>=0 && j-1>=0){ //top left
                        if(o[i-1][j-1]==0)o[i-1][j-1]=1;
                    };
                    
                    if(i-1>=0){ //top
                        if(o[i-1][j]==0)o[i-1][j]=1;
                    };
                    
                    if(i-1>=0 && j+1<=9){ //top right
                        if(o[i-1][j+1]==0)o[i-1][j+1]=1;
                    };
                    
                    if(j+1<=9){ //right
                        if(o[i][j+1]==0)o[i][j+1]=1;
                    };
                    
                    if(i+1<=9 && j+1<=9){ //bottom right
                        if(o[i+1][j+1]==0)o[i+1][j+1]=1;
                    };
                    
                    if(i+1<=9){ //bottom
                        if(o[i+1][j]==0)o[i+1][j]=1;
                    };
                    
                    if(i+1<=9 && j-1>=0){ //bottom left
                        if(o[i+1][j-1]==0)o[i+1][j-1]=1;
                    };
                    
                    if(j-1>=0){ //left
                        if(o[i][j-1]==0)o[i][j-1]=1;
                    };
                };
            };
        };
    };


    void updatee(){ //blocks unavailable sectors in enemy board
        for (int i=0; i<10;i++){
            for (int j=0; j<10;j++){
                if (e[i][j]==3){
                    
                    if(i-1>=0 && j-1>=0){ //top left
                        if(e[i-1][j-1]==0)e[i-1][j-1]=1;
                    };
                    
                    if(i-1>=0){ //top
                        if(e[i-1][j]==0)e[i-1][j]=1;
                    };
                    
                    if(i-1>=0 && j+1<=9){ //top right
                        if(e[i-1][j+1]==0)e[i-1][j+1]=1;
                    };
                    
                    if(j+1<=9){ //right
                        if(e[i][j+1]==0)e[i][j+1]=1;
                    };
                    
                    if(i+1<=9 && j+1<=9){ //bottom right
                        if(e[i+1][j+1]==0)e[i+1][j+1]=1;
                    };
                    
                    if(i+1<=9){ //bottom
                        if(e[i+1][j]==0)e[i+1][j]=1;
                    };
                    
                    if(i+1<=9 && j-1>=0){ //bottom left
                        if(e[i+1][j-1]==0)e[i+1][j-1]=1;
                    };
                    
                    if(j-1>=0){ //left
                        if(e[i][j-1]==0)e[i][j-1]=1;
                    };
                };
            };
        };
    };


    int boatcheck(int a, int b){
        for(int i=0;i<4;i++){ //right
            if(b+i<=9){
                if(o[a][b+i]==1) break;
                if(o[a][b+i]==2) return 1;
            };
        };

        for(int i=0;i<4;i++){ //left
            if(b-i>=0){
                if(o[a][b-i]==1) break;
                if(o[a][b-i]==2) return 1;
            };
        };

        for(int i=0;i<4;i++){ //top
            if(a-i>=0){
                if(o[a-i][b]==1) break;
                if(o[a-i][b]==2) return 1;
            };
        };

        for(int i=0;i<4;i++){ //bottom
            if(a+i<=9){
                if(o[a+i][b]==1) break;
                if(o[a+i][b]==2) return 1;
            };
        };
        return 2;
    };


    int whatdoidonow(int a,int b){
        for(int i=1;i<4;i++){ //right
            if(b+i<=9){
                if(e[a][b+i]==1) break;
                if(e[a][b+i]==0) return 2;
            }else break;
        };

        for(int i=1;i<4;i++){ //left
            if(b-i>=0){
                if(e[a][b-i]==1) break;
                if(e[a][b-i]==0) return 4;
            }else break;
        };

        for(int i=1;i<4;i++){ //top
            if(a-i>=0){
                if(e[a-i][b]==1) break;
                if(e[a-i][b]==0) return 1;
            }else break;
        };

        for(int i=1;i<4;i++){ //bottom
            if(a+i<=9){
                if(e[a+i][b]==1) break;
                if(e[a+i][b]==2) return 4;
            }else break;
        };
        return 5;
    };


    void initialize(){
        for (int i=0; i<10;i++){
            for (int j=0; j<10;j++){
                o[i][j]=0;
                e[i][j]=0;
            };
        };
        remx=-1;
        remy=-1;
        placeboat(4);
        updateo();
        placeboat(3);
        updateo();
        placeboat(3);
        updateo();
        placeboat(2);
        updateo();
        placeboat(2);
        updateo();
        placeboat(2);
        updateo();
        placeboat(1);
        updateo();
        placeboat(1);
        updateo();
        placeboat(1);
        updateo();
        placeboat(1);
        updateo();
        int wincon=0;
        for (int i=0;i<10;i++){
            for (int j=0;j<10;j++){
                std::cout << o[i][j] << " ";
            };
            std::cout << "\n";
        };
        int pmx, pmy, miss=1, x,y,inp,co,ce;
        do{
            std::cin >> pmx >> pmy; //player's turn
            pmx--;
            pmy--;
            if (o[pmx][pmy]==2){
                o[pmx][pmy]=3;
                if (boatcheck(pmx,pmy)==1)std::cout << "Hit!\n";
                else std::cout << "Destroyed!\n";
                miss=0;
                ce++;
            }else{
                o[pmx][pmy]=1;
                miss=1;
                std::cout << "Missed!\n";
            };
            while (miss==0){
                std::cin >> pmx >> pmy;
                pmx--;
                pmy--;
                if (o[pmx][pmy]==2){
                    o[pmx][pmy]=3;
                    if (boatcheck(pmx,pmy)==1)std::cout << "Hit!\n";
                    else std::cout << "Destroyed!\n";
                    co++;
                }else{
                    o[pmx][pmy]=1;
                    miss=1;
                    std::cout << "Missed!\n";
                };
            };

            while(true){
                if(remx==-1){
                    do{
                        x=rand()%10;
                        y=rand()%10;
                    } while (e[x][y]!=0);
                } else{
                    switch(whatdoidonow(remx,remy)){
                    case 1:
                        y=remy;
                        for(int i=1;i<4;i++) if(e[remx-i][remy]==0) {x=remx-i; break;};
                        break;
                    case 2:
                        x=remx;
                        for(int i=1;i<4;i++) if(e[remx][remy+i]==0) {y=remy+i; break;};
                        break;
                    case 3:
                        y=remy;
                        for(int i=1;i<4;i++) if(e[remx+i][remy]==0) {x=remx+i; break;};
                        break;
                    case 4:
                        x=remx;
                        for(int i=1;i<4;i++) if(e[remx][remy-i]==0) {y=remy-i; break;};
                        break;
                    default:
                        std::cout << "Uh, something is definitly wrong.\n";
                        wincon=3;
                        x=-1;
                        break;
                    };
                };
                if (x==-1) break;
                std::cout << "I pick " << x+1 << " and " << y+1 << ". Type 1 if i missed 2 if i hit or 3 if i destroyed ur ship \n";
                std::cin >> inp;
                if (inp==1){
                    std::cout << "Shit, your turn.\n";
                    e[x][y]=1;
                    break;
                };
                if(inp==2) {
                    std::cout << "Interesting.\n";
                    e[x][y]=3;
                    if (remx==-1) {
                        remx=x;
                        remy=y;
                    };
                    continue;
                };  
                if(inp==3){
                    std::cout << "Cry about it.\n";
                    e[x][y]=3;
                    remx=-1;
                    remy=-1;
                    updatee();
                };
            };
        } while (wincon==0);
        switch(wincon){
            case 1:
                std::cout << "Dang ur good. Down for a rematch?)";
                break;
            case 2:
                std::cout << "Skill issue LOL";
                break;
            default:
                std::cout << "Lets call it a draw, im too lazy to investigate what went wrong";
        };
    };
};


int main(){
    srand(time(NULL));
    seabattle a = seabattle();
    a.initialize();
};