#include <string>
#include <iostream>
#include <vector>
#include <stack>
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

    node(bool exit, maze _maze, pos _pos, node *parent) : exit(exit), _maze(_maze), _pos(_pos), parent(parent) {}
};

bool operator==(const frame a, const frame b) {
    return a._maze == b._maze && a._pos == b._pos;
}

typedef pair<frame, node *> x;
typedef vector<pos> vp;
typedef vector<frame> vf;
typedef vector<node *> vn;
typedef vector<x> vx;

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

//list<string> result {};
//list<frame> frames {};
size_t level = 0, max_level;

/*
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
*/
vn enter(maze _maze, pos _pos, node *parent) {
    if (level >= max_level)
        return {};
    node *base = new node(false, _maze, _pos, parent);
    //result.push_back(string("Enter ") + (char) (_maze + 'A') + ": " + (char) ((_pos >> 2) + 'A') + to_string(_pos & 3));
    ++level;
    //frames.push_back({_maze, _pos});
    vp base_out{}; // The final result
    vf base_cont{}; // The possible places to enter
    switch (_pos) {
        case A0:
            base_cont = {{A, A0}};
            base_out = {D2, D3};
            break;
        case A1:
            base_cont = {{A, A3}};
            break;
        case A2:
            base_cont = {{A, B0},
                         {C, A0},
                         {B, B2}};
            break;
        case A3:
            base_cont = {{B, A0}};
            break;
        case B0:
            base_cont = {{B, A3}};
            break;
        case B1:
            base_cont = {{B, B3}};
            break;
        case B2:
            base_cont = {{A, A2},
                         {C, B1}};
            break;
        case B3:
            base_cont = {{A, C2}};
            base_out = {C1, D0};
            break;
        case C0:
            base_cont = {{B, A2}};
            break;
        case C1:
            base_cont = {{A, C2}};
            base_out = {D0, B3};
            break;
        case C2:
            base_cont = {{A, D1}};
            base_out = {D1};
            break;
        case C3:
            base_cont = {{C, A0},
                         {B, B2},
                         {A, B0}};
            base_out = {A2};
            break;
        case D0:
            base_cont = {{A, C2}};
            base_out = {C1, B3};
            break;
        case D1:
            base_cont = {{A, D1}};
            base_out = {C2};
            break;
        case D2:
            base_cont = {{A, A0}};
            base_out = {D3, A0};
            break;
        case D3:
            base_out = {D2, A0};
            break;
    }
    vx out{};
    if (!base_cont.empty()) {
        vf used = base_cont;
        vx cont;
        cont.reserve(base_cont.size());
        vx next{};
        transform(base_cont.begin(), base_cont.end(), back_inserter(cont), [&](frame f) { return x {f, base}; });
        while (true) {
            for (x &_x : cont)
                for (node *n : enter(_x.first._maze, _x.first._pos, _x.second)) {
                    switch (_x.first._maze) {
                        case A:
                            switch (n->_pos) {
                                case A0:
                                    out.push_back({{A, A0}, n});
                                    out.push_back({{A, D2}, n});
                                    out.push_back({{A, D3}, n});
                                    break;
                                case A2:
                                    out.push_back({{A, B2}, n});
                                    next.push_back({{C, B1}, n});
                                    break;
                                case A3:
                                    out.push_back({{A, A1}, n});
                                    break;
                                case B0:
                                    out.push_back({{A, A2}, n});
                                    next.push_back({{C, A0}, n});
                                    next.push_back({{B, B2}, n});
                                    out.push_back({{A, C3}, n});
                                    break;
                                case B3:
                                    next.push_back({{B, D3}, n});
                                    break;
                                case C0:
                                    next.push_back({{C, D0}, n});
                                    break;
                                case C1:
                                    next.push_back({{A, D3}, n});
                                    break;
                                case C2:
                                    out.push_back({{A, D0}, n});
                                    out.push_back({{A, C1}, n});
                                    out.push_back({{A, B3}, n});
                                    break;
                                case D1:
                                    out.push_back({{A, D1}, n});
                                    out.push_back({{A, C2}, n});
                                    break;
                                case D3:
                                    next.push_back({{A, C1}, n});
                                    break;
                            }
                            break;
                        case B:
                            switch (n->_pos) {
                                case A0:
                                    out.push_back({{B, A3}, n});
                                    break;
                                case A2:
                                    out.push_back({{B, C0}, n});
                                    break;
                                case A3:
                                    out.push_back({{B, B0}, n});
                                    break;
                                case B2:
                                    next.push_back({{C, A0}, n});
                                    out.push_back({{B, A2}, n});
                                    next.push_back({{A, B0}, n});
                                    out.push_back({{B, C3}, n});
                                    break;
                                case B3:
                                    out.push_back({{B, B1}, n});
                                    break;
                                case C2:
                                    next.push_back({{C, A3}, n});
                                    break;
                                case D1:
                                    next.push_back({{C, D2}, n});
                                    break;
                                case D3:
                                    next.push_back({{A, B3}, n});
                                    break;
                            }
                            break;
                        case C:
                            switch (n->_pos) {
                                case A0:
                                    next.push_back({{B, B2}, n});
                                    next.push_back({{A, B0}, n});
                                    out.push_back({{C, A2}, n});
                                    out.push_back({{C, C3}, n});
                                    break;
                                case A3:
                                    next.push_back({{B, C2}, n});
                                    break;
                                case B1:
                                    out.push_back({{C, B2}, n});
                                    next.push_back({{A, A2}, n});
                                    break;
                                case B2:
                                    next.push_back({{C, B3}, n});
                                    break;
                                case B3:
                                    next.push_back({{C, B2}, n});
                                    break;
                                case D0:
                                    next.push_back({{A, C0}, n});
                                    break;
                                case D2:
                                    next.push_back({{B, D1}, n});
                                    break;
                            }
                            break;
                    }
                }
            if (next.empty())
                break;
            for (x &_x : cont)
                if (find(used.begin(), used.end(), _x.first) == used.end())
                    used.push_back(_x.first);
            cont.clear();
            copy_if(next.begin(), next.end(), back_inserter(cont), [&used](x _x) { return find(used.begin(), used.end(), _x.first) == used.end(); });
            next.clear();
        }
    }
    --level;
    /*
    cout << string(level, '-') << (char) (_maze + 'A') << (char) ((_pos >> 2) + 'A') << (char) ((_pos & 0b11) + '0') << ':';
    for (pos p : base_out)
        cout << ' ' << (char) ((p >> 2) + 'A') << (char) ((p & 0b11) + '0');
    cout << '\n';
     */
    if (out.empty() && base_out.empty()) {
        delete base;
        return {};
    }
    vn _out;
    _out.reserve(out.size() + base_out.size());
    transform(out.begin(), out.end(), back_inserter(_out), [_maze](x _x) { return new node(true, _maze, _x.first._pos, _x.second); });
    transform(base_out.begin(), base_out.end(), back_inserter(_out), [&](pos p) { return new node(true, _maze, p, base); });
    return _out;
}

int main() {
    cout << "Max levels: ";
    cin >> max_level;
    size_t solutions = 0;
    vx cont{{{C, C1}, nullptr}};
    vx next{};
    vf used{{C, C1}};
    while (true) {
        for (x &_x : cont)
            for (node *n : enter(_x.first._maze, _x.first._pos, _x.second))
                switch (_x.first._maze) {
                    case A:
                        switch (n->_pos) {
                            case A0:
                                break;
                            case A2:
                                next.push_back({{C, B1}, n});
                                break;
                            case B0:
                                next.push_back({{C, A0}, n});
                                next.push_back({{B, B2}, n});
                                break;
                            case B3:
                                next.push_back({{B, D3}, n});
                                break;
                            case C0:
                                next.push_back({{C, D0}, n});
                                break;
                            case C1:
                                next.push_back({{A, D3}, n});
                                break;
                            case C3: {
                                cout << "Solution:\n";
                                stack<node *> nodes;
                                node *c = n;
                                while (c) {
                                    nodes.push(c);
                                    c = c->parent;
                                }
                                while (!nodes.empty()) {
                                    c = nodes.top();
                                    nodes.pop();
                                    cout << (c->exit ? "\tExit " : "\tEnter ") << (char) (c->_maze + 'A') << " at " << (char) ((c->_pos >> 2) + 'A') << (char) ((c->_pos & 0b11) + '0') << '\n';
                                }
                                ++solutions;
                                break;
                            }
                            case D3:
                                next.push_back({{A, C1}, n});
                                break;
                        }
                        break;
                    case B:
                        switch (n->_pos) {
                            case B2:
                                next.push_back({{C, A0}, n});
                                next.push_back({{A, B0}, n});
                                break;
                            case C2:
                                next.push_back({{C, A3}, n});
                                break;
                            case D1:
                                next.push_back({{C, D2}, n});
                                break;
                            case D3:
                                next.push_back({{A, B3}, n});
                                break;
                        }
                        break;
                    case C:
                        switch (n->_pos) {
                            case A0:
                                next.push_back({{B, B2}, n});
                                next.push_back({{A, B0}, n});
                                break;
                            case A3:
                                next.push_back({{B, C2}, n});
                                break;
                            case B1:
                                next.push_back({{A, A2}, n});
                                break;
                            case B2:
                                next.push_back({{C, B3}, n});
                                break;
                            case B3:
                                next.push_back({{C, B2}, n});
                                break;
                            case D0:
                                next.push_back({{A, C0}, n});
                                break;
                            case D2:
                                next.push_back({{B, D1}, n});
                                break;
                        }
                        break;
                }
        if (next.empty())
            break;
        for (x &_x : cont)
            if (find(used.begin(), used.end(), _x.first) == used.end())
                used.push_back(_x.first);
        cont.clear();
        copy_if(next.begin(), next.end(), back_inserter(cont), [&used](x _x) { return find(used.begin(), used.end(), _x.first) == used.end(); });
        next.clear();
    }
    cerr << solutions << " solutions\n";
    return 0;
}
