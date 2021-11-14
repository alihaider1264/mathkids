#ifndef _SCORE_
#define _SCORE_

class Score{
    int correct;
    int total;
public:
    Score(): correct(0), total(0) {}

    float getScore(){ return correct/(float)total; }
    void inc_correct() { correct++; }
    void dec_correct() { correct--; }
    void inc_total() { total++; }
    int getCorrect() { return correct; }
    int getTotal() { return total; }

    ~Score(){}
};


#endif