#include <iostream>
#include <vector>

enum {UP = 0, DOWN = 1, UNCHANGE = 2};

using namespace std;

vector< vector<string> > outstr(3, vector<string>(7, ""));
vector<string> optstr(7, "");
int biggest = 0;
int noofseq[3] = {0, 0, 0};

double max(double a, double b, double c) {
    if(a >= b && a >= c) {
        biggest = 0;
        return a;
    }
    if(b >= a && b >= c) {
        biggest = 1;
        return b;
    }
    if(c >= a && c >= b) {
        biggest = 2;
        return c;
    }
}

int main()
{
    int observe[7] = {UP, UP, UNCHANGE, DOWN, UNCHANGE, DOWN, UP};
    int times = 7;

    double answer;

    double initia[3]    =  {0.5, 0.2, 0.3}; /// no use in this code.

    double forwar[2][3] = {{0.5, 0.2, 0.3},
                           {0.0, 0.0, 0.0}};

    double stateM[3][3] = {{0.7, 0.1, 0.2},
                           {0.1, 0.6, 0.3},
                           {0.3, 0.3, 0.4}};

    double transM[3][3] = {{0.6, 0.2, 0.2},
                           {0.5, 0.3, 0.2},
                           {0.4, 0.1, 0.5}};

    for(int i = 1; i < times; ++i) {

        for(int j = 0; j < 3; ++j) {
            forwar[0][j] = forwar[0][j] * stateM[j][observe[i-1]];
        }

        for(int j = 0; j < 3; ++j) {
            forwar[1][j] = forwar[0][0] * transM[0][j] + forwar[0][1] * transM[1][j] + forwar[0][2] * transM[2][j];
        }

        for(int j = 0; j < 3; ++j) {
            forwar[0][j] = forwar[1][j];
        }
    }

    for(int j = 0; j < 3; ++j) {
        forwar[0][j] = forwar[0][j] * stateM[j][observe[times-1]];
    }

    cout << "Observation Length: " << times << endl << endl;
    cout << "Observation { ";
    for(int i = 0; i < times; ++i) {
        switch(observe[i]) {
            case 0:
                cout << "UP ";
                break;
            case 1:
                cout << "DOWN ";
                break;
            case 2:
                cout << "UNCHANGE ";
                break;
        }
    }
    cout << "}" << endl << endl;


    cout << "HW1-1: Probability" << endl << endl;

    answer = forwar[0][0]+forwar[0][1]+forwar[0][2];
    cout << answer << endl << endl;



    ///--- Viterbi Algorithm. ---///
    cout << "HW1-2: Optimal State Sequence" << endl << endl;

    string states[3] = {"S1", "S2", "S3"};

    double viterbi[2][3] = {{0.5, 0.2, 0.3},
                            {0.0, 0.0, 0.0}};
    biggest = 0;

    for(int i = 0; i < times; ++i) {
        if ( i == 0 ) {
            for(int j = 0; j < 3; ++j) {
                viterbi[0][j] = viterbi[0][j] * stateM[j][observe[i]];
            }
        } else {
            for(int j = 0; j < 3; ++j) {
                /// max(a, b, c): return the value a/b/c, also set the "biggest" to 0/1/2, when return a/b/c.
                viterbi[1][j]  = max(viterbi[0][0]*transM[0][j],
                                     viterbi[0][1]*transM[1][j],
                                     viterbi[0][2]*transM[2][j])*stateM[j][observe[i]];
                noofseq[j] = biggest; /// record the NODE that is the most probable come from.
                outstr [j][i-1] = states[biggest]; /// record the path.
                outstr [j][i]   = states[j];       /// target NODE. ( to S1/S2/S3 )
            }
            /// get the the most probable target NODE. ( use "biggest" to get )
            max(viterbi[1][0], viterbi[1][1], viterbi[1][2]);
            for(int k = 0; k < i; ++k) {
                cout << outstr[noofseq[biggest]][k] << ", ";
            }
            cout << outstr[biggest][i];
            cout << endl;
            for(int j = 0; j < 3; ++j) {
                viterbi[0][j] = viterbi[1][j];
            }
        }
    }
    cout << "           ----->  final seq." << endl << endl;

    /// print the record path.
    for(int k = 0; k < 3; ++k) {
        for(int l = 0; l < times; ++l) {
            cout << outstr[k][l] << ", ";
        }
        cout << endl;
    }


    return 0;
}
