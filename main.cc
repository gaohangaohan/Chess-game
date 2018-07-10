#include <iostream>
#include <vector>
#include "board.h"
#include "piece.h"
#include "human.h"
#include "player.h"
#include "LevelTT.h"
#include "graphicsdisplay.h"
#include "computer.h"
using namespace std;

int main (){

    Board b;
    string s;
    int p = 0;
    bool valid = false;
    vector<unique_ptr<Player>> vp;
    Graphicsdisplay gd = Graphicsdisplay(&b);
    b.setdisplay(&gd);
    int whites = 0;
    int blacks = 0;
    bool presetup = false;
    b.init(0);
    while(cin>>s) {
        if (s == "game") {
            if(!presetup) {
                b.init(1);
            }
            vp.clear();
            for(int i = 0; i < 2; ++i) {
                string s;
                cin>>s;
                if (s == "human") {
                    vp.emplace_back(new Human(&b, 1 - i));
                } else if (s == "computer[1]") {
                    vp.emplace_back(new LevelOne(&b, 1 - i));
                } else if (s == "computer[2]") {
                    vp.emplace_back(new LevelTwo(&b, 1 - i));
                } else if (s == "computer[3]") {
                    vp.emplace_back(new LevelThree(&b, 1 - i));
                } else if (s == "computer[4]") {
                    vp.emplace_back(new LevelFour(&b, 1 - i));
                } else {
                    vp.emplace_back(new Level(&b, 1 - i));
                }
            }
            p = 0;
            valid = true;
            cout<<b<<endl;
            gd.Display();
        } else if (s == "resign" && valid) {
            if (p == 0) {
                cout<<"Black wins!"<<endl;
                blacks += 2;
            } else {
                cout<<"White wins!"<<endl;
                whites += 2;
            }
            presetup = false;
        } else if (s == "move" && valid) {
            try{
                vp[p]->move();
                p = (p + 1) % 2;
                cout<<b<<endl;
                if (vp[p]->isCheck() && !vp[p]->canMove()) {
                    cout<<"Checkmate! ";
                    if (p == 0) {
                        cout<<"Black wins!"<<endl;
                        blacks += 2;
                    } else {
                        cout<<"White wins!"<<endl;
                        whites += 2;
                    }
                    valid = false;
                    presetup = false;
                } else if (vp[p]->isCheck()) {
                    if (p == 1) {
                        cout<<"Black";
                    } else {
                        cout<<"White";
                    }
                    cout<<" is in check!"<<endl;
                } else if (!vp[p]->canMove()) {
                    cout<<"Stalement!"<<endl;
                    ++blacks;
                    ++whites;
                    valid = false;
                    presetup = false;
                }
            }
            catch(...) {cout<<"Invalid"<<endl;}
        } else if (s == "setup") {
            cout<<"Setup Mode"<<endl;
            string ss;
            while(cin>>ss) {
                if (ss == "+") {
                    try {
                        char type;
                        cin>>type;
                        char c;
                        cin>>c;
                        int i;
                        cin>>i;
                        b.setPiece(type, c, i, 1 - p);
                        if (type == 'K' && presetup) {
                            vp[p]->setK(c, i);
                        }
                    }
                    catch(...) {}
                    cout<<b<<endl;
                } else if (ss == "-") {
                    try{
                        char c;
                        cin>>c;
                        int i;
                        cin>>i;
                        b.removePiece(c, i);
                    }
                    catch(...) {}
                    cout<<b<<endl;      
                } else if (ss == "=") {
                    string col;
                    cin>>col;
                    if (col == "black") {
                        p = 1;
                    } else if (col == "white"){
                        p = 0;
                    } else {
                        cout<<"No Such Player!"<<endl;
                    }
                } else if (ss == "done") {
                    bool wk = false;
                    bool bk = false;
                    bool n = true;
                    bool ka = false;
                    for (int j = 0; j < 64; ++j) {
                        if(b.vb[j].getType() != ' ') {
                        if (b.vb[j].getType() == 'K') {
                            if (b.vb[j].getOwner() == 0 && bk) {
                                n = false;
                                break;
                            } else if (b.vb[j].getOwner() == 1 && wk) {
                                n = false;
                                break;
                            } else if (b.vb[j].getOwner() == 0) {
                                bk = true;
                            } else if (b.vb[j].getOwner() == 1) {
                                wk = true;
                            }
                            if(b.isAttacked(b.vb[j].getOwner(), j % 8 + 'a', 8 - j / 8)) {
                                ka = true;
                                break;
                            }
                        }
                        if (b.vb[j].getType() == 'P' && (j/8 == 0 || j/8 == 7)) {
                            n = false;
                            break;
                        } 
                        }
                    }
                    if(n && wk && bk && !ka) {
                        cout<<"Exit Setup Mode"<<endl;
                        presetup = true;
                        break;
                    } else if (ka){
                        cout<<"Is check!"<<endl;
                    } else {
                        cout<<"Invalid Board!"<<endl;
                    }
                }
            }
        }
    }
    cout<<"Final Score:"<<endl;
    cout<<"White: "<<whites / 2;
    if (whites % 2 != 0) {
        cout<<".5";
    }
    cout<<endl;
    cout<<"Black: "<<blacks/2;
    if (blacks % 2 != 0) {
        cout<<".5";
    }
    cout<<endl;
    return 0;
}
