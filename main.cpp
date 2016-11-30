#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

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

struct node {
    bool exit;
    maze _maze;
    pos _pos;
    node *parent;
};

bool operator==(const frame a, const frame b) {
    return a._maze == b._maze && a._pos == b._pos;
}

typedef vector<pos> vp;
typedef vector<frame> vf;
typedef vector<node> vn;

void exit(pos);

vp enter(maze _maze, pos _pos);

inline vf T(maze _maze, pos _pos) {
    vp in(enter(_maze, _pos));
    vf out(in.size());
    transform(in.begin(), in.end(), out.end(), [_maze](pos &_) { return frame{_maze, _}; });
    return out;
}

#define E(m, p) { vp v = map(m, enter(m, p)); copy(v.begin(), v.end(), back_inserter(r)); }
#define V(m, p) { vf v = T(m, p); copy(v.begin(), v.end(), back_inserter(cont)); }
#define R1(n) vp r(v1.size() + n); A(1);
#define R2(n) vp r(v1.size() + v2.size() + n); A(1); A(2);
#define R3(n) vp r(v1.size() + v2.size() + v3.size() + n); A(1); A(2); A(3);
#define X frames.pop_back(); --level; result.pop_back()
#define A(n) copy(v##n.begin(), v##n.end(), back_inserter(r))

list<string> result {};
list<frame> frames {};
size_t level = 0, max_level;

vp map(maze _maze, vp result) {
    vp r;
    switch (_maze) {
        case A:
            for (pos _pos : result)
                switch (_pos) {
                    case A0:
                        r.push_back(A0);
                        r.push_back(D2);
                        r.push_back(D3);
                        break;
                    case A2:
                        r.push_back(B2);
                        E(C, B1);
                        break;
                    case A3:
                        r.push_back(A1);
                        break;
                    case B0:
                        r.push_back(A2);
                        r.push_back(C3);
                        E(C, A0);
                        E(B, B2);
                        break;
                    case B3: E(B, D3);
                        break;
                    case C0: E(C, D0);
                        break;
                    case C1: E(A, D3);
                        break;
                    case C2:
                        r.push_back(D0);
                        r.push_back(C1);
                        r.push_back(B3);
                        break;
                    case C3:
                        if (!level) {
                            cout << "SOLUTION:\n";
                        }
                        break;
                    case D1:
                        r.push_back(D1);
                        r.push_back(C2);
                        break;
                    case D3: E(A, C1);
                        break;
                }
            break;
        case B:
            for (pos _pos : result)
                switch (_pos) {
                    case A0:
                        r.push_back(A3);
                        break;
                    case A2:
                        r.push_back(C0);
                        break;
                    case A3:
                        r.push_back(B0);
                        break;
                    case B2: E(C, A0);
                        r.push_back(A2);
                        E(A, B0);
                        r.push_back(C3);
                        break;
                    case B3:
                        r.push_back(B1);
                        break;
                    case C2: E(C, A3);
                        break;
                    case D1: E(C, D2);
                        break;
                    case D3: E(A, B3);
                        break;
                }
            break;
        case C:
            for (pos _pos : result)
                switch (_pos) {
                    case A0: E(B, B2);
                        E(A, B0);
                        r.push_back(A2);
                        r.push_back(C3);
                        break;
                    case A3: E(B, C2);
                        break;
                    case B1:
                        r.push_back(B2);
                        E(A, A2);
                        break;
                    case B2: E(C, B3);
                        break;
                    case B3: E(C, B2);
                        break;
                    case D0: E(A, C0);
                        break;
                    case D2: E(B, D1);
                        break;
                }
            break;
    }
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

vp enter(maze _maze, pos _pos) {
    if (level > max_level)
        return {};
    result.push_back(string("Enter ") + (char) (_maze + 'A') + ": " + (char) ((_pos >> 2) + 'A') + to_string(_pos & 3));
    ++level;
    frames.push_back({_maze, _pos});
    vp out{}; // The final result
    vf cont{}; // The possible places to enter
    vf next{}; // Next values of cont
    vf used{}; // The places that have been entered
    switch (_pos) {
        case A0:
            cont = {{A, A0}};
            out = {D2, D3};
            break;
        case A1:
            cont = {{A, A3}};
            break;
        case A2:
            cont = {{A, B0},
                    {C, A0},
                    {B, B2}};
            break;
        case A3:
            cont = {{B, A0}};
            break;
        case B0:
            cont = {{B, A3}};
            break;
        case B1:
            cont = {{B, B3}};
            break;
        case B2:
            cont = {{A, A2},
                    {C, B1}};
            break;
        case B3:
            cont = {{A, C2}};
            out = {C1, D0};
            break;
        case C0:
            cont = {{B, A2}};
            break;
        case C1:
            cont = {{A, C2}};
            out = {D0, B3};
            break;
        case C2:
            cont = {{A, D1}};
            out = {D1};
            break;
        case C3:
            cont = {{C, A0},
                    {B, B2},
                    {A, B0}};
            out = {A2};
            break;
        case D0:
            cont = {{A, C2}};
            out = {C1, B3};
            break;
        case D1:
            cont = {{A, D1}};
            out = {C2};
            break;
        case D2:
            cont = {{A, A0}};
            out = {D3, A0};
            break;
        case D3:
            out = {D2, A0};
            break;
    }
    used = cont;
    while (true) {
        for (frame f : cont)
            for (pos p : enter(f._maze, f._pos)) {
                switch (f._maze) {
                    case A:
                        switch (p) {
                            case A0:
                                out.push_back(A0);
                                out.push_back(D2);
                                out.push_back(D3);
                                break;
                            case A2:
                                out.push_back(B2);
                                next.push_back({C, B1});
                                break;
                            case A3:
                                out.push_back(A1);
                                break;
                            case B0:
                                out.push_back(A2);
                                next.push_back({C, A0});
                                next.push_back({B, B2});
                                out.push_back(C3);
                                break;
                            case B3:
                                next.push_back({B, D3});
                                break;
                            case C0:
                                next.push_back({C, D0});
                                break;
                            case C1:
                                next.push_back({A, D3});
                                break;
                            case C2:
                                out.push_back(D0);
                                out.push_back(C1);
                                out.push_back(B3);
                                break;
                            case D1:
                                out.push_back(D1);
                                out.push_back(C2);
                                break;
                            case D3:
                                next.push_back({A, C1});
                                break;
                        }
                        break;
                    case B:
                        switch (p) {
                            case A0:
                                out.push_back(A3);
                                break;
                            case A2:
                                out.push_back(C0);
                                break;
                            case A3:
                                out.push_back(B0);
                                break;
                            case B2:
                                next.push_back({C, A0});
                                out.push_back(A2);
                                next.push_back({A, B0});
                                out.push_back(C3);
                                break;
                            case B3:
                                out.push_back(B1);
                                break;
                            case C2:
                                next.push_back({C, A3});
                                break;
                            case D1:
                                next.push_back({C, D2});
                                break;
                            case D3:
                                next.push_back({A, B3});
                                break;
                        }
                        break;
                    case C:
                        switch (p) {
                            case A0:
                                next.push_back({B, B2});
                                next.push_back({A, B0});
                                out.push_back(A2);
                                out.push_back(C3);
                                break;
                            case A3:
                                next.push_back({B, C2});
                                break;
                            case B1:
                                out.push_back(B2);
                                next.push_back({A, A2});
                                break;
                            case B2:
                                next.push_back({C, B3});
                                break;
                            case B3:
                                next.push_back({C, B2});
                                break;
                            case D0:
                                next.push_back({A, C0});
                                break;
                            case D2:
                                next.push_back({B, D1});
                                break;
                        }
                        break;
                }
            }
        if (next.empty())
            break;
        copy_if(cont.begin(), cont.end(), back_inserter(used), [&used](frame f) { return find(used.begin(), used.end(), f) == used.end(); });
        cont.clear();
        copy_if(next.begin(), next.end(), back_inserter(cont), [&used](frame f) { return find(used.begin(), used.end(), f) == used.end(); });
        next.clear();
    }
    X;
    cout << string(level, '-') << (char) (_maze + 'A') << (char) ((_pos >> 2) + 'A') << (char) ((_pos & 0b11) + '0') << ':';
    for (pos p : out)
        cout << ' ' << (char) ((p >> 2) + 'A') << (char) ((p & 0b11) + '0');
    cout << '\n';
    return out;
}

int main() {
    cout << "Max levels: ";
    cin >> max_level;

    vf cont{{C, C1}};
    vf next{};
    vf used(cont);
    while (true) {
        for (frame f : cont)
            for (pos p : enter(f._maze, f._pos))
                switch (f._maze) {
                    case A:
                        switch (p) {
                            case A0:
                                break;
                            case A2:
                                next.push_back({C, B1});
                                break;
                            case B0:
                                next.push_back({C, A0});
                                next.push_back({B, B2});
                                break;
                            case B3:
                                next.push_back({B, D3});
                                break;
                            case C0:
                                next.push_back({C, D0});
                                break;
                            case C1:
                                next.push_back({A, D3});
                                break;
                            case C3:
                                cout << "SOLUTION!\n";
                                break;
                            case D3:
                                next.push_back({A, C1});
                                break;
                        }
                        break;
                    case B:
                        switch (p) {
                            case B2:
                                next.push_back({C, A0});
                                next.push_back({A, B0});
                                break;
                            case C2:
                                next.push_back({C, A3});
                                break;
                            case D1:
                                next.push_back({C, D2});
                                break;
                            case D3:
                                next.push_back({A, B3});
                                break;
                        }
                        break;
                    case C:
                        switch (p) {
                            case A0:
                                next.push_back({B, B2});
                                next.push_back({A, B0});
                                break;
                            case A3:
                                next.push_back({B, C2});
                                break;
                            case B1:
                                next.push_back({A, A2});
                                break;
                            case B2:
                                next.push_back({C, B3});
                                break;
                            case B3:
                                next.push_back({C, B2});
                                break;
                            case D0:
                                next.push_back({A, C0});
                                break;
                            case D2:
                                next.push_back({B, D1});
                                break;
                        }
                        break;
                }
        if (next.empty())
            break;
        copy_if(cont.begin(), cont.end(), back_inserter(used), [&used](frame f) { return find(used.begin(), used.end(), f) == used.end(); });
        cont.clear();
        copy_if(next.begin(), next.end(), back_inserter(cont), [&used](frame f) { return find(used.begin(), used.end(), f) == used.end(); });
        next.clear();
    }
    return 0;
}
