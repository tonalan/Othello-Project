#include "OthelloAI.hpp"


namespace tona4
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
        int eval(OthelloGameState &state, OthelloCell &turn);
        int search(OthelloGameState &state, int depth);
    };
}