#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED


class GameStats
{
public:
    GameStats()
        : p1_score(0), p2_score(0), tie(0) {}

    void clearStats()
    {
        p1_score  = 0;
        p2_score  = 0;
        tie       = 0;
    }

    Uint8 p1Score() { return p1_score; }
    Uint8 p2Score() { return p2_score; }
    Uint8 Tie()     { return tie;      }

    void incP1Score() { ++p1_score; }
    void incP2Score() { ++p2_score; }
    void incTie()     { ++tie;      }

private:
    Uint8 p1_score;
    Uint8 p2_score;
    Uint8 tie;
};


#endif // STATS_H_INCLUDED
