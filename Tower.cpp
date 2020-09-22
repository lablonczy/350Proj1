#include <iostream>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

class Tower {

    struct Disk {
        string color, name;

        Disk(){
            color = "";
            name = "";
        }

        Disk(string aColor, string aName){
            color = aColor;
            name = aName;
        }
    };

    public:
        Tower(int n){
            size = n, move = 0;

            string letters = "abcdefghijklmnopqrstuvwxyz";
            strcpy(alphabet, letters.c_str());

            for(int i=0;i<size;i++){
                Disk tempRedNum;
                tempRedNum.color = "red";
                tempRedNum.name = to_string(i+1);

                Disk tempBlack;
                tempBlack.color = "black";
                tempBlack.name = alphabet[i];

                pegs[0].push(tempRedNum);
                //cout << "creating new red color: " << tempRedNum.color << " name " << tempRedNum.name << endl;
                //cout << "creating new black color: " << tempBlack.color << " name " << tempBlack.name << endl;

                pegs[0].push(tempBlack);
            }

            cout << "Starting position" << endl;
            //cout << "there are " << pegs[0].size() << " blocks\n";
            printPegs();

        }

        void solveHuger(int n, stack<Disk> &a, stack<Disk> &b, stack<Disk> &c){
            if(n < 2){
                moveBlocks(a,c,0,2);
                moveBlocks(a,b,0,1);
            } else  {
                moveStackOfPairs(n-1,a,b,c);
                moveBlocks(a,c,0,2);
                moveBlocks(a,c,0,2);
                moveStackOfPairs(n-1,b,a,c);
                moveBlocks(c,b,2,1);
                solveHuger(n-1,a,b,c);
            }
        }

        void moveStackOfPairs(int n, stack<Disk> &a, stack<Disk> &b, stack<Disk> &c){
            if(n<2){
                moveBlocks(a,c,0,2);
                moveBlocks(a,b,0,1);
                moveBlocks(c,b,2,1);
            } else  {
                moveStackOfPairs(n-1,a,b,c);
                moveBlocks(a,c,0,2);
                moveBlocks(a,c,0,2);
                moveStackOfPairs(n-1,b,a,c);
                moveBlocks(c,b,2,1);
                moveBlocks(c,b,2,1);
                moveStackOfPairs(n-1,a,b,c);
            }

        }

        void start(int n){
            size = n;
            solveHuger(n,this->pegs[0],this->pegs[1],this->pegs[2]);
            cout << "done!\n";
        }

    private:
        stack<Disk> pegs[3];
        char alphabet[26];
        int move, size;

        void moveBlocks(stack<Disk> &toPop, stack<Disk> &toPush, int firstStackNum, int secondStackNum){
            Disk toMove = toPop.top();
            toPush.push(toMove);
            toPop.pop();

            printMove(firstStackNum, secondStackNum, toMove);
        }

        void printMove(int firstStack, int secondStack, Disk &disk){
            move++;
            cout << "Step " << move << ": Move disk " + disk.name + " from peg " << firstStack << " to peg " << secondStack << endl;
            printPegs();
        }

        void printPegs(){
            for(int i=0;i<3;i++){
                cout << i << ":";
                printPeg(pegs[i]);
                cout << endl;
            }
            cout << endl;
        }

        void printPeg(stack<Disk> peg){
            stack<Disk> reversed;
            //cout << "peg size " << peg.size() << endl;

            int originalSize = peg.size();
            for(int i=0;i<originalSize;i++){
                reversed.push(peg.top());
                peg.pop();
            }

            //cout << "reversed peg size " << reversed.size() << endl;
            for(int i=0;i<originalSize;i++){
                cout << reversed.top().name;
                if(i!=(originalSize - 1))
                    cout << ",";
                reversed.pop();
            }


        }



};

int main(int argc, char* argv[]){

    string line;
    while(getline(cin,line)){
        int numPoints = stoi(line);
        Tower t(numPoints);
        t.start(numPoints);
    }



    return 0;
}
