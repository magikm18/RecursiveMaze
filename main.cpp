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

size_t level = 0, max_level;

vn enter(maze _maze, pos _pos, node *parent) {
    if (level >= max_level)
        return {};
    node *base = new node(false, _maze, _pos, parent);
    ++level;
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
    cout << solutions << " solutions\n";
    return 0;
}
