#include<iostream>
#include <string>
#include <math.h>
#include<fstream>
using namespace std;
void records();
void setting();
void display(int n,int m);
bool check(int a, int b, int n, int m, int p);
int drop(int b, char player);
int length = 7;
int width = 6;
int row = 4;
string filepath = "records.txt";
void start(int l, int w,int r);
char place[6][7];//available for whole program
int main()
{
    int x;

    while (true)
    {
        system("clear");
        cout << "\n     ****************************\n";
        cout << "\t1: Start \n";
        cout << "     ****************************\n";
        cout << "\t2: Setting \n";
        cout << "     ****************************\n";
        cout << "\t3: Records  \n";
        cout << "     ****************************\n";
        cout << "\t4: Exit  \n";
        cout << "     ****************************\n";
        cin >> x;
        switch (x)
        {
        case 1:
                  start(length,width, row);
                  break;
        case 2:
                  setting();
                  break;
        case 3:
                  records();
                      break;
        case 4:
                  exit(0);
        }

    }
    return 0;//Exit application
}
void start(int l,int w,int r)
{
    system("clear");
    string s1, s2;
    cout << "player 1 ?";
        cin >> s1;
        cout << "player 2 ?";
            cin >> s2;
    ofstream outfile(filepath, ios::app);
    if (!outfile){
        exit(1);
    }
    int one = 0, two = 0;
    for (int a = 0; a <w; a++){		//fill place with whitespace
        for (int b = 0; b <l; b++)
            place[a][b] = ' ';
    }
    display(l,w);//Displays for first time so players can see the board
    int hold;//Will house user row choice
    int hold2 = 0;//will hold drop value
    int charsPlaced = 0;//Number of peices dropped so can end game if a draw
    bool gamewon = false;//Will be changed to true when game is won and will exit while loop
    char player = 15;//start as player 2 will change back 2 player 1
    while (!gamewon){//will stop when game is won, ! means NOT makes the oppisite be checked
        if (hold2 != -1){//check if there was a error in the last drop
            if (player == 15){//if player 2 lasted dropped a piece so its player 1s turn
                cout << "player 1 drop where?";
                player = 254;//char of players piece
                one++;
            }
            else{
                cout << "player 2 drop where?";
                player = 15;//char of player piece
                two++;
            }
        }
        while (true){//will run untill 'break;'
            if (charsPlaced == w*l) break;//if draw
            cin >> hold;//get user input
            hold--;//take off 1 to account for arrays starting at 0 not 1
            if (hold <= l && hold >= 0) break;//if within valid range stop loop
            else cout << "\nplease enter a value :";//ask for input and loop again
            if (cin.fail())	//catch a non number
            {						//
                cin.clear();		//Stops cin trying to put its value in to hold
                char c;			//Try entering a non number without this, 2 see what this does
                cin >> c;			//
            }						//Catch a non number

        }
        if (charsPlaced == w*l) break;//if draw
        hold2 = drop(hold, player);//drop the player store the row in hold2
        if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number:";//if error -1 row is full
        else{
            gamewon = check(hold2, hold,l,w,r);//check if game is run
            charsPlaced++;//another character has been succesfully placed
            system("clear");//This clears the screen works with windows, not nesscery to run game
            display(l,w);//displayed updated board
        }
    }
    system("clear");//this clears the screen
    if (charsPlaced == w*l){//if draw
        cout << "No winner, Game was draw\n";
        system("pause");
        return;
    }
    if (player == 15)//if won by player 2
    {
        cout << "gamewon by : player 2   "<<s2<<"\n";
        int score = (pow(l, w) / two);
        outfile << s2 <<score << "\n";
    }

    else
    {
        cout << "gamewon by : player 1   "<<s1<<"\n";//Else won by player 1
        int score = (pow(l, w) / one);
        outfile << s1 <<score << "\n";
    }
    outfile.close();
    system("pause");//pauses before exit so players can see who won, works with windows

    return;
}
void setting()
{
    system("clear");
    cout << "\n     ****************************\n";
    cout << "\ta: length ="<<length<<"\n";
    cout << "     ****************************\n";
    cout << "\tb: width = " << width<<"\n";
    cout << "     ****************************\n";
    cout << "\tc: in row = " << row<<"\n";
    cout << "     ****************************\n";
    cout << "\t   enter 0 for return  \n";
    cout << "     ****************************\n";
    char x;
    cout << "choose? \n";
    cin >> x;
    while (x!='0')
    {
        switch (x)
        {
        case 'a':
        {
                    int a;
                    cin >> a;
                    length = a;
                    break;

        }
        case 'b':
        {
                    int a;
                    cin >> a;
                    width = a;
                    break;
        }
        case 'c':
        {
                    int a;
                    cin >> a;
                    row = a;
                    break;
        }
        }
        cout << "choose? \n";
        cin >> x;
    }
    return;
}
void records()
{
    system("clear");
    char ch;
    char a[20];
    ifstream infile(filepath);
    infile >> a;
    while (!infile.eof())
    {
        cout << a<<"\n";
        infile >> a;
    }
    infile.close();
    cout << "\n enter 0 for return \n";
        cin >> ch;
    if (ch == '0')
        return;
}
void display(int n,int m){
    for (int i = 1; i<= n; i++)
        cout << "   " << i;
    cout<<"\n";
    for (int a = 0; a <m; a++)
    {
        for (int b = 0; b <n; b++) cout << "|" << " " << " " << " ";
        cout << '\n';
        for (int b = 0; b <n; b++) cout << "|" << place[a][b] << " " << " ";
        cout << '\n';
        for (int b = 0; b <n; b++) cout << "|" << " " << " " << " ";
        cout << '\n';
    }
}
bool check(int a, int b,int n,int m,int p){
    int vertical = 1;//(|)
    int horizontal = 1;//(-)
    int diagonal1 = 1;//(\)
    int diagonal2 = 1;//(/)
    char player = place[a][b];
    int i;//vertical
    int ii;//horizontal
    //check for vertical(|)
    for (i = a + 1; place[i][b] == player && i <m; i++, vertical++);//Check down
    for (i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);//Check up
    if (vertical >= p)return true;
    //check for horizontal(-)
    for (ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
    for (ii = b + 1; place[a][ii] == player && ii <n; ii++, horizontal++);//Check right
    if (horizontal >= p) return true;
    //check for diagonal 1 (\)
    for (i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
    for (i = a + 1, ii = b + 1; place[i][ii] == player && i <m && ii <n; diagonal1++, i++, ii++);//down and right
    if (diagonal1 >= p) return true;
    //check for diagonal 2(/)
    for (i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <n; diagonal2++, i--, ii++);//up and right
    for (i = a + 1, ii = b - 1; place[i][ii] == player && i <m && ii >= 0; diagonal2++, i++, ii--);//up and left
    if (diagonal2 >= p) return true;
    return false;
}
int drop(int b, char player){
    if (b >= 0 && b <= length)
    {
        if (place[0][b] == ' '){
            int i;
            for (i = 0; place[i][b] == ' '; i++)
            if (i == width - 1){
                place[i][b] = player;
                return i;
            }
            i--;
            place[i][b] = player;
            return i;

        }
        else{
            return -1;
        }

    }
    else{
        return -1;
    }

}
