#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// a A star Node
struct Node {
    int i, j, state;
    int F, G, H;
    Node *parent;
};

int main(int argc, char **argv)
{
    Node map[5][7] = {0};
    for (int i=0; i != 5; ++i)
        for (int j=0; j != 7; ++j) {
            map[i][j].i = i, map[i][j].j = j;
            Node &n = map[i][j];
            std::cout << n.i << " " << n.j << " " << n.state << " " << n.F  << " " << n.G << " " << n.H << endl; 
        }
    Node *start = &map[2][1];
    start->H = 4*10;
    start->F = start->H;
    Node *end = &map[2][5];
    map[1][3].state = 1;
    map[2][3].state = 1;
    map[3][3].state = 1;
   
    vector<Node*> openList, closeList;
    openList.push_back(start);
    while (!openList.empty()) {
        // find the lowset F node     
        Node *n = NULL;
        vector<Node*>::iterator bit;
        for (vector<Node*>::iterator it = openList.begin(); it != openList.end(); ++it) {
            if (NULL == n) {     
                n = *it;
                bit = it;
            } else {
                if ((*it)->F < n->F) {    
                    n = *it;
                    bit = it;
                }
            }
        }
        // remove from openList
        openList.erase(bit);
        // put it to closeList
        closeList.push_back(n);
        if (n == end) {
            //find it!
            break;     
        }
        cout << "deal node " << n << " i " << n->i << " j " << n->j << endl;
        // a find loop
        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                sleep(1);
                int ti = n->i+i, tj = n->j+j;  
                if (ti>=0 && tj >= 0 && ti < 5 && tj < 7 && (ti != n->i || tj != n->j)) { // can put
                    Node *tn = &map[ti][tj]; 
                    if (1 == tn->state) {
                        continue;     
                    }
                    //orthogonal check 
                    if (ti != n->i && tj != n->j) {
                        int di = ti - n->i, dj = tj - n->j;
                        // whatever must check this one
                        if (1 == map[ti][n->j].state) {
                            continue;     
                        } 
                        if (1 == map[n->i][n->j+dj].state) {
                            continue;     
                        }
                        /*
                        if (di == 1) {
                            // whatever must check this one
                            if (1 == map[ti][n->j].state) {
                                continue;     
                            } 
                            if (1 == map[n->i][n->j+dj].state) {
                                    continue;     
                            }
                        } else if (-1 == di) {
                            // whatever must check this one
                            if (1 == map[ti][n->j].state) {
                                continue;     
                            }
                            if (1 == map[n->i][n->j+dj].state) {
                                continue;     
                            }
                        } 
                        */
                    }
                    // in the closeList
                    bool bf = false;
                    for (vector<Node*>::iterator it = closeList.begin(); it != closeList.end(); ++it) {
                        if (*it == tn) {
                            bf = true;
                            break;     
                        }     
                    } 
                    if (bf) {
                        continue;     
                    }
                    bf = false;
                    // find tn in openList or not
                    for (vector<Node*>::iterator it = openList.begin(); it != openList.end(); ++it) {
                        if (*it == tn) {
                            bf = true;     
                            break;
                        }     
                    }
                    if (bf) {
                        // can change it or not 
                        int tadd = 10; 
                        if (tn->i != n->i && tn->j != n->j) {
                            tadd = 14;     
                        }
                        if (tadd + n->G < tn->G) { // a better path
                            tn->parent = n;
                            tn->G = tadd + n->G; 
                            int mi = tn->i - end->i, mj = tn->j - end->j;
                            tn->H = ((mi > 0 ? mi : -mi) + (mj > 0 ? mj : -mj))*10;
                            tn->F = tn->G + tn->H;
                            cout << "change node bf " << (bf ? 1:0) << " " << tn << " i " << tn->i << " j " 
                                    << tn->j << " to parent i " << n->i << " j " << n->j << endl;
                        }
                    } else {
                        // add it 
                        tn->parent = n;
                        tn->G = n->G+10;
                        // orthogonal is 14
                        if (tn->i != n->i && tn->j != n->j) {
                            tn->G += 4;     
                        }
                        int mi = tn->i - end->i, mj = tn->j - end->j;
                        tn->H = ((mi > 0 ? mi : -mi) + (mj > 0 ? mj : -mj))*10;
                        tn->F = tn->G + tn->H;
                        openList.push_back(tn);
                        cout << "put node bf " << (bf ? 1:0) << " "  << tn << " i " << tn->i << " j " << tn->j << endl;
                    }
                }
            }
        }
    }
    if (NULL == end->parent) {
        cout << "not find" << endl;     
    } else {
        Node *path = end;
        cout << "find it" << endl;
        while (path) {
            cout << "i " << path->i << " j " << path->j << " F " << path->F << " G " << path->G << " H " << path->H << endl;
            path = path->parent;
        }
    }
    return 0;
}

