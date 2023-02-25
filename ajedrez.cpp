#include <iostream>
#include <array>
using namespace std;

const int SIZE = 8; //Size of an usual chess board (8x8)

typedef array<char, SIZE> TColumn;
typedef array<TColumn, SIZE> Board;   //We build an 8x8 matrix as a chess board

const char white = char(178); //This represents white squares

const char black = char(176); //As background is black, gaps will represent our black squares

/*

Pieces will be represented by their initials:

Capital letter represent white pieces.

Pawns = p/P

Rooks = r/R

Knights = n/N

Bishops = b/B

Queen = q/Q

King = k/K

*/

const char PAWN = 'p';

const char ROOK = 'r';

const char KNIGHT = 'n';

const char BISHOP = 'b';

const char QUEEN = 'q';

const char KING = 'k';


void fillBoard (Board& b)  //Just for filling the board
{

    int color = 0;

    for (int i = 0; i < SIZE; i++)   // i represents rows and j columns
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i < 2)
            {
                color = 0;
            }
            else
            {
                color = -32;
            }
            if (i == 0 || i == 7)
            {
                if (j == 0 || j == 7)
                {
                    b[i][j] = ROOK + color;
                }
                else if (j == 1 || j == 6)
                {
                    b[i][j] = KNIGHT + color;
                }
                else if (j == 2 || j == 5)
                {
                    b[i][j] = BISHOP + color ;
                }
                else if (j == 3)
                {
                    b[i][j] = QUEEN + color;
                }
                else
                {
                    b[i][j] = KING + color;
                }

            }
            else if (i == 1 || i == 6)
            {
                b[i][j] = PAWN + color;
            }
            else if ((i + j)%2 == 0)
            {
                b[i][j] = white;
            }
            else
            {
                b[i][j] = black;
            }

        }
    }

}


void showBoard (const Board& b)   //Prints the board on screen
{


    for (int i = 0; i < SIZE; i++)
    {
        int t = 8 - i;
        cout<<t<<" ";
        for (int j = 0; j < SIZE; j++)
        {
            if ((i+j)%2 == 0)
            {
                cout<<white;
            }
            else
            {
                cout<<black;
            }
            cout<<b[i][j];
        }
        cout<<endl;
    }

    cout<<"  A B C D E F G H";
}



//--------------------------MOVEMENTS--------------------------//

//We define a void in order to move a piece to other square and replace it with a white or black square

void movPiece (Board& b, int row1, int col1, int row2, int col2)
{

    b[row2][col2]=b[row1][col1];

    if ((row1 + col1)%2 == 0)
    {
        b[row1][col1] = white;
    }
    else
    {
        b[row1][col1] = black;
    }

}

//--------------------------------------------------------------//

//-------------------MOVEMENT CONDITIONS------------------------//

//We are going to evaluate whether a move is possible or not

//------EMPTY SQUARE------//

//We evaluate if a square has a piece (false) on it or if it is empty (true)

bool emptySquare (const Board& b, int row, int col)
{

    if ((b[row][col] == white) || (b[row][col] == black))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------//

//------COLOR PIECE-------//

//Just to know the color of the piece on a square

//True if it is its color, false if it is not its color

bool colorPiece (const Board& b,const int row,const int col, bool whiteturn)
{

    if (whiteturn)
    {
        if (('A' <= b[row][col])&&('Z' >= b[row][col]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (('A' <= b[row][col])&&('Z' >= b[row][col]))
        {
            return false;
        }
        else
        {
            return true;
        }
    }


}

//------------------------//

//---------PAWN-----------//

bool movPawn (const Board& b, int row1, int col1, int row2, int col2, bool whiteturn)
{

    if (whiteturn)
    {

        if (row1 >= row2)  //Only move forwards
        {
            return false;
        }
        else if (((col1-col2) > 1) || ((col2-col1) > 1))  //Adjacent columns
        {
            return false;
        }
        else if ((col1!=col2)&&(emptySquare(b, row2, col2)))  //Adjacent columns where there is a piece
        {
            return false;
        }
        else if ((row2 - row1 >= 2)&&(row1 != 6))  //Only one square
        {
            return false;
        }
        else if ((row2 - row1 > 2)&&(row1 == 6))  //Initial position
        {
            return false;
        }
        else if ((col1!=col2)&&(row1 == 6)&&(row2 - row1 == 2))  //Initial position diagonal move 2 squares
        {
            return false;
        }
        else if ((col1 != col2)&&(!emptySquare(b, row2, col2))&& colorPiece(b, row2, col2, whiteturn))  //Only move diagonally if there is a piece on arrival square
        {
            return false;
        }
        else if ((col1==col2)&&(!emptySquare(b, row2, col2)))  //Piece on arrival square
        {
            return false;
        }
        else
        {
            return true;
        }
    }                                       //Permutar row1, row2 si se hace con blancas o con negras//
    else
    {
        if (row1 <= row2)  //Only move forwards
        {
            return false;
        }
        else if (((col1 - col2) > 1) || ((col2 - col1) > 1))  //Adjacent columns
        {
            return false;
        }
        else if ((col1 != col2)&&(emptySquare(b, row2, col2)))  //Adjacent columns where there is a piece
        {
            return false;
        }
        else if ((row1 - row2 >= 2)&&(row1 != 1))  //Only one square
        {
            return false;
        }
        else if ((row1 - row2 > 2)&&(row1 == 1))  //Initial position
        {
            return false;
        }
        else if ((col1 != col2)&&(row1 == 1)&&(row1 - row2 == 2))  //Initial position diagonal move 2 squares
        {
            return false;
        }
        else if ((col1 != col2)&&(!emptySquare(b, row2, col2)) && colorPiece(b, row2, col2, whiteturn))  //Only move diagonally if there is a piece on arrival square
        {
            return false;
        }
        else if ((col1 == col2)&&(!emptySquare(b, row2, col2)))  //Piece on arrival square
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
//En passant still needed to be added

//------------------------//

//---------KING-----------//
/*
bool movKing (const Board& b, int row1, int col1, int row2, int col2){

if (){

}

}
*/
//--------------------------------------------------------------//

//------------------------CHECKS AND STUFF----------------------//

//--------------------------------------------------------------//

//---------------------------GAMEPLAY---------------------------//

//-------LOCATE PIECE-------//

void correctColumn (char& col, int& c){

    bool correct = false;

    do
            {
                cout<<"Column: (CAPITAL LETTER)"<<endl;
                cin>>col;


                if (col == 'A')
                {
                    c = 0;
                    correct = true;
                }
                else if (col == 'B')
                {
                    c = 1;
                    correct = true;
                }
                else if (col == 'C')
                {
                    c = 2;
                    correct = true;
                }
                else if (col == 'D')
                {
                    c = 3;
                    correct = true;
                }
                else if (col == 'E')
                {
                    c = 4;
                    correct = true;
                }
                else if (col == 'F')
                {
                    c = 5;
                    correct = true;
                }
                else if (col == 'G')
                {
                    c = 6;
                    correct = true;
                }
                else if (col == 'H')
                {
                    c = 7;
                    correct = true;
                }
                else
                {
                    cout<<"You might be wrong, please try again: "<<endl;
                }
            }
            while (!correct);


}

void correctRow (char& row, int& r){

    bool correct = false;

    do
            {

                cout<<"Row: "<<endl;
                cin>>row;
                if (row == '1')
                {
                    r = 7;
                    correct = true;
                }
                else if (row == '2')
                {
                    r = 6;
                    correct = true;
                }
                else if (row == '3')
                {
                    r = 5;
                    correct = true;
                }
                else if (row == '4')
                {
                    r = 4;
                    correct = true;
                }
                else if (row == '5')
                {
                    r = 3;
                    correct = true;
                }
                else if (row == '6')
                {
                    r = 2;
                    correct = true;
                }
                else if (row == '7')
                {
                    r = 1;
                    correct = true;
                }
                else if (row == '8')
                {
                    r = 0;
                    correct = true;
                }
                else
                {
                    cout<<"You might be wrong, please try again: "<<endl;
                }
            }
            while (!correct);



}



//--------------------------//

void gamePlay (Board& b, bool whiteturn)
{

    cout<<endl<<endl;

    char letter;
    int p;
    bool correct = false; //false until correct data is introduced
    char col, row;
    int r1, c1, r2, c2;
    bool correct2 = false; //to see if piece selected is the right color;

    if (whiteturn)
    {

        cout<<"WHITE'S TURN: "<<endl;
        do
        {
            /*do
            {
                cout<<"SELECT PIECE TO MOVE: (FIRST LETTER IN UPPERCASE)"<<endl;
                cin>>letter;
                cout<<endl;

                if (letter == 'P')
                {
                    p = 0;
                    correct = true;
                }
                else if (letter == 'R')
                {
                    p = 1;
                    correct = true;
                }
                else if (letter == 'N')
                {
                    p = 2;
                    correct = true;
                }
                else if (letter == 'B')
                {
                    p = 3;
                    correct = true;
                }
                else if (letter == 'Q')
                {
                    p = 4;
                    correct = true;
                }
                else if (letter == 'K')
                {
                    p = 5;
                    correct = true;
                }
                else
                {
                    cout<<"You might be wrong, please try again: "<<endl;
                }
            }
            while (!correct);*/

            correct = false;

            cout<<"Where is your piece?"<<endl;

            correctColumn (col, c1);

            correctRow (row, r1);

            cout<<endl;

            if ((b[r1][c1] >= 'A')&&(b[r1][c1] <= 'Z'))
            {
                correct2 = true;
            }
            else
            {
                cout<<"There is no piece on that square/The piece is not yours. Please enter another piece: "<<endl;
            }

        }
        while (!correct2);

        cout<<"Where do you want to move the piece?"<<endl;

        correctColumn(col, c2);
        correctRow(row, r2);

        movPiece (b, r1, c1, r2, c2);

    }
    else
    {

        cout<<"BLACK'S TURN: "<<endl;
        do
        {
           /* do
            {
                cout<<"SELECT PIECE TO MOVE: (FIRST LETTER IN UPPERCASE)"<<endl;
                cin>>letter;
                cout<<endl;

                if (letter == 'P')
                {
                    p = 0;
                    correct = true;
                }
                else if (letter == 'R')
                {
                    p = 1;
                    correct = true;
                }
                else if (letter == 'N')
                {
                    p = 2;
                    correct = true;
                }
                else if (letter == 'B')
                {
                    p = 3;
                    correct = true;
                }
                else if (letter == 'Q')
                {
                    p = 4;
                    correct = true;
                }
                else if (letter == 'K')
                {
                    p = 5;
                    correct = true;
                }
                else
                {
                    cout<<"You might be wrong, please try again: "<<endl;
                }
            }
            while (!correct);*/

            correct = false;

            cout<<"Where is your piece?"<<endl;

            correctColumn (col, c1);

            correctRow (row, r1);


            cout<<endl;

            if ((b[r1][c1] >= 'a')&&(b[r1][c1] <= 'z'))
            {
                correct2 = true;
            }
            else
            {
                cout<<"There is no piece on that square/The piece is not yours. Please enter another piece: "<<endl;
            }

        }
        while (!correct2);

        cout<<"Where do you want to move the piece?"<<endl;

        correctColumn(col, c2);
        correctRow(row, r2);

        movPiece (b, r1, c1, r2, c2);



    }

}

//--------------------------------------------------------------//



int main()
{

    bool whiteturn = true;

    bool checkMate = false;

    Board board;

    fillBoard (board);

    while (!checkMate)
    {
        showBoard (board);

        gamePlay (board, whiteturn);

        if(whiteturn)
        {
            whiteturn = false;
        }
        else
        {
            whiteturn = true;
        }
    }

    return 0;
}


