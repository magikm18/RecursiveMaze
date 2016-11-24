#include <string>
#include <iostream>
#include <stack>
#include <list>

using namespace std;

enum pos {
    A0, A1, A2, A3,
    B0, B1, B2, B3,
    C0, C1, C2, C3,
    D0, D1, D2, D3,
};

enum maze {
    A, B, C
};

struct frame {
    maze _maze;
    pos _pos;
};

list<string> result {};
list<frame> frames {};
size_t level = 0;

void exit(pos);

void enter(maze _maze, pos _pos) {
    for (frame &f : frames)
        if (f._maze == _maze && f._pos == _pos)
            return;
    result.push_back(string("Enter ") + (char)(_maze + 'A') + ": " + (char)((_pos >> 2) + 'A') + to_string(_pos & 3));
    cout << result.back() << '\n';
    cout << result.size() << '\n';
    ++level;
    frames.push_back({_maze, _pos});
    switch(_pos){
        case A0:
            exit(D3);
            exit(D2);
            //enter(A, A0);
            break;
        case A1:
            enter(A, A3);
            break;
        case A2:
            enter(A, B0);
            enter(C, A0);
            enter(B, B2);
            break;
        case A3:
            enter(B, A0);
            break;
        case B0:
            enter(B, A3);
            break;
        case B1:
            enter(B, B3);
            break;
        case B2:
            enter(A, A2);
            enter(C, B1);
            break;
        case B3:
            exit(C1);
            exit(D0);
            enter(A, C2);
            break;
        case C0:
            enter(B, A2);
            break;
        case C1:
            exit(B3);
            exit(D0);
            enter(A, C2);
            break;
        case C2:
            exit(D1);
            enter(A, D1);
            break;
        case C3:
            enter(C, A0);
            enter(B, B2);
            enter(A, B0);
            exit(A2);
            break;
        case D0:
            enter(A, C2);
            exit(C1);
            exit(B3);
            break;
        case D1:
            exit(C2);
            //enter(A, D1);
            break;
        case D2:
            exit(D3);
            exit(A0);
            enter(A, A0);
            break;
        case D3:
            exit(D2);
            exit(A0);
            enter(A, A0);
            break;
    }
    frames.pop_back();
    --level;
    result.pop_back();
}

void exit(pos _pos) {
    if (!level)
        return;
    frame c = frames.back();
    result.push_back(string("Exit ") + (char)(c._maze + 'A') + ": " + (char)((_pos >> 2) + 'A') + to_string(_pos & 3));
    cout << result.back() << '\n';
    cout << result.size() << '\n';
    --level;
    frames.pop_back();
    switch(c._maze) {
        case A:
            switch(_pos) {
                case A0:
                    exit(A0);
                    exit(D2);
                    exit(D3);
                    break;
                case A2:
                    exit(B2);
                    enter(C, B1);
                    break;
                case A3:
                    exit(A1);
                    break;
                case B0:
                    exit(A2);
                    enter(C, A0);
                    enter(B, B2);
                    exit(C3);
                    break;
                case B3:
                    enter(B, D3);
                    break;
                case C0:
                    enter(C, D0);
                    break;
                case C1:
                    enter(A, D3);
                    break;
                case C2:
                    exit(D0);
                    exit(C1);
                    exit(B3);
                    break;
                case C3:
                    if (!level) {
                        cout << "SOLUTION:\n";
                        for (string &s : result)
                            cout << s << '\n';
                    }
                    break;
                case D1:
                    exit(D1);
                    exit(C2);
                    break;
                case D3:
                    enter(A, C1);
                    break;
            }
            break;
        case B:
            switch(_pos){
                case A0:
                    exit(A3);
                    break;
                case A2:
                    exit(C0);
                    break;
                case A3:
                    exit(B0);
                    break;
                case B2:
                    enter(C, A0);
                    exit(A2);
                    enter(A, B0);
                    exit(C3);
                    break;
                case B3:
                    exit(B1);
                    break;
                case C2:
                    enter(C, A3);
                    break;
                case D1:
                    enter(C, D2);
                    break;
                case D3:
                    enter(A, B3);
                    break;
            }
            break;
        case C:
            switch (_pos){
                case A0:
                    enter(B, B2);
                    enter(A, B0);
                    exit(A2);
                    exit(C3);
                    break;
                case A3:
                    enter(B, C2);
                    break;
                case B1:
                    exit(B2);
                    enter(A, A2);
                    break;
                case B2:
                    enter(C, B3);
                    break;
                case B3:
                    enter(C, B2);
                    break;
                case D0:
                    enter(A, C0);
                    break;
                case D2:
                    enter(B, D1);
                    break;
            }
            break;
    }
    frames.push_back(c);
    ++level;
    result.pop_back();
}

int main() {
    enter(C, C1);
    return 0;
}
