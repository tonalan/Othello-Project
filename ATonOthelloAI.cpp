#include <ics46/factory/DynamicFactory.hpp>
#include "ATonOthelloAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, tona4::MyOthelloAI, "ATon's Othello AI (Required)");

int tona4::MyOthelloAI::eval(OthelloGameState &state, OthelloCell &turn)
{
    if (turn == OthelloCell::black)
    {
        return state.blackScore() - state.whiteScore();
    }
    else
    {
        return state.whiteScore() - state.blackScore();
    }
    
}

int tona4::MyOthelloAI::search(OthelloGameState &state, int depth)
{
    OthelloCell turn;  //keeps track of whose turn it is
    int max = -999;
    int min = 999;     //initialize the variables to be overwritten
    if (state.isBlackTurn())
    {
        turn = OthelloCell::black;
    }
    else
    {
        turn = OthelloCell::white;
    }
    if (depth == 0)
    {
        return eval(state, turn);
    }
    else
    {
        if (turn == OthelloCell::black)
        {
            for (int i = 0; i < state.board().width(); i++) 
            {
                for (int j = 0; j < state.board().height(); j++)
                {
                    if(state.isValidMove(i, j)) 
                    {
                        std::unique_ptr<OthelloGameState> anotherClone = state.clone();
                        anotherClone->makeMove(i, j);
                        int potentialMax = search(*anotherClone, depth - 1); //recurse until depth = 0
                        if (potentialMax > max)
                        {
                            max = potentialMax;
                            return max;
                        }
                    }
                }
            }
            return max;
        }
        else
        {
            for (int i = 0; i < state.board().width(); i++) 
            {
                for (int j = 0; j < state.board().height(); j++)
                {
                    if(state.isValidMove(i, j)) 
                    {
                        std::unique_ptr<OthelloGameState> anotherClone = state.clone();
                        anotherClone->makeMove(i, j);
                        int potentialMin = search(*anotherClone, depth - 1); //recurse until depth = 0
                        if (potentialMin < min)
                        {
                            min = potentialMin;
                            return min;
                        }
                    }
                }
            }
            return min;
        }
    }
}
std::pair<int, int> tona4::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    int bestValue = -9999;      //placeholder for searched values
    std::pair<int, int> final_pair;

    for (int i = 0; i < state.board().width(); i++) //iterate through the whole board
    {
        for (int j = 0; j < state.board().height(); j++)
        {
            if (state.isValidMove(i, j)) //check possible moves
            {
                std::unique_ptr<OthelloGameState> clonedState = state.clone(); //preserve previous state
                clonedState->makeMove(i, j);  //makes available move with clone
                int potentialBestValue = search(*clonedState, 5);
                if (potentialBestValue > bestValue)
                {
                    bestValue = potentialBestValue;  //change bestValue to the bew best move
                    final_pair.first = i;  //store the location of the best move
                    final_pair.second = j;
                }
            }
        }
    }
    return final_pair;
}