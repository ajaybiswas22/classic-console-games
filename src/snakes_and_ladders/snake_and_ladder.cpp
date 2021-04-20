#include<bits/stdc++.h>

class SnakeLadder {

    // the board
    std::vector<std::vector<int> > board;

    // snake and ladder
    std::vector<std::vector<int> > snake_ladder;

    // player position
    std::pair<int,int> player1;
    std::pair<int,int> player2;

public:

    SnakeLadder() {
        std::vector<std::vector<int> > b = { {100,99,98,97,96,95,94,93,92,91},
                                        {81,82,83,84,85,86,87,88,89,90},
                                        {80,79,78,77,76,75,74,73,72,71},
                                        {61,62,63,64,65,66,67,68,69,70},
                                        {60,59,58,57,56,55,54,53,52,51},
                                        {41,42,43,44,45,46,47,48,49,50},
                                        {40,39,38,37,36,35,34,33,32,31},
                                        {21,22,23,24,25,26,27,28,29,30},
                                        {20,19,18,17,16,15,14,13,12,11},
                                        {1,2,3,4,5,6,7,8,9,10},
                                      };

        std::vector<std::vector<int> > s = { {100,99,98,78,96,56,94,93,92,91},
                                        {81,82,83,84,85,86,87,24,89,90},
                                        {99,79,78,77,76,75,74,73,72,92},
                                        {61,18,63,64,65,66,67,68,69,70},
                                        {60,59,58,57,56,55,54,53,52,51},
                                        {41,42,43,44,45,46,47,26,49,67},
                                        {40,39,38,37,6,35,34,33,10,31},
                                        {42,22,23,24,25,26,27,76,29,30},
                                        {20,19,18,17,16,15,14,13,12,11},
                                        {1,38,3,14,5,6,7,30,9,10},
                                      };

        // setting board
        board = b;
        snake_ladder = s;

        // setting players
        player1.first = 9; player1.second = 0;
        player2.first = 9; player2.second = 0;

    }

    void display_board()
    {
        std::cout<<"BOARD"<<std::endl;
        for(int i=0;i<board.size();i++)
        {
            for(int j=0;j<board[0].size();j++) {
                if(board[i][j] < 10) {                         // padding
                    std::cout<<"  ";
                }
                else if(board[i][j] < 100) {                  // padding
                    std::cout<<" ";
                }
                std::cout<<board[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"SNAKES AND LADDERS"<<std::endl;
        for(int i=0;i<board.size();i++)
        {
            for(int j=0;j<board[0].size();j++) {
                if(board[i][j] != snake_ladder[i][j]) {
                    if(snake_ladder[i][j] < 10) {              // padding
                        std::cout<<"  ";
                    }
                    else if(snake_ladder[i][j] < 100) {        // padding
                        std::cout<<" ";
                    }
                    std::cout<<snake_ladder[i][j]<<" ";
                }
                else {
                    std::cout<<"*** ";
                }
                
            }
            std::cout<<std::endl;
        }
    }

    void moves(int player, int amount)
    {
        int r,c, moves = 0;
        
        if(player == 1) {
            r = player1.first;
            c = player1.second;
        }
        else if(player == 2) {
            r = player2.first;
            c = player2.second;
        }
        else {
            r = player2.first;
            c = player2.second;
        }
        int old_r = r;
        int old_c = c;

        while(moves < amount) {
            if(r%2 == 1) {
                // move right
                
                if(c == 9) {
                    c = 9;
                    r--;
                } 
                else {
                    c++;
                }
                
            }
            else {
                // move left

                if(c == 0) {
                    c = 0;
                    r--;
                }
                else {
                    c--;
                }
            }

            moves++;
        }

        if(r < 0 || c < 0 || r > 9 || c > 9) {      // overflow or underflow condition
            r = old_r;
            c = old_c;
        }

        // check for snake or ladder after moves have completed
        if(snake_ladder[r][c] != board[r][c]) {
                
                int newPos = snake_ladder[r][c];

                r = (int) (10.0 - ceil(newPos / 10.0) );

                if(r%2 == 1) {
                    c = newPos%10 - 1;
                } 
                else
                {
                    c = 10 - newPos%10;
                }
            }

        if(player == 1) {
            player1.first = r;
            player1.second = c;
        }
        else if(player == 2) {
            player2.first = r;
            player2.second = c;
        }
        else {
            player2.first = r;
            player2.second = c;
        }
    }

    std::pair<int,int> player_pos(int player)
    {
        if(player == 1) {
            return player1;
        }
        else if(player == 2) {
            return player2;
        }
        else {
            return player2;
        }
    }

    int random_move() {
        int iSecret;

        /* generate secret number between 1 and 6: */
        iSecret = rand() % 6 + 1;
        return iSecret;
    }

};

int main()
{
    using namespace std;
    srand (time(NULL));

    int end = 0;
    int mv;
    string winner;

    SnakeLadder s;
    s.display_board();
    
    cout<<"\nGAME\n";
    cout<<"Player 1: "<<s.player_pos(1).first<<" "<<s.player_pos(1).second<<endl;
    cout<<"Player 2: "<<s.player_pos(2).first<<" "<<s.player_pos(2).second<<endl;
    
    while(!end) {

        mv = s.random_move();
        s.moves(1,mv);
        cout<<"Dice: "<<mv<<endl;
        cout<<"Player 1: "<<s.player_pos(1).first<<" "<<s.player_pos(1).second<<endl;
        
        mv = s.random_move();
        s.moves(2,mv);
        cout<<"Dice: "<<mv<<endl;
        cout<<"Player 2: "<<s.player_pos(2).first<<" "<<s.player_pos(2).second<<endl;

        if(s.player_pos(1).first == 0 && s.player_pos(1).second == 0 &&
           s.player_pos(1).first == 0 && s.player_pos(2).second == 0) {
            winner = "Draw";
            end = 1;
        }
        else if(s.player_pos(1).first == 0 && s.player_pos(1).second == 0) {
            winner = "Player 1";
            end = 1;
        }
        else if(s.player_pos(2).first == 0 && s.player_pos(2).second == 0) {
            winner = "Player 2";
            end = 1;
        }

    }

    cout<<"Winner: "<<winner<<endl;

    return 0;
}