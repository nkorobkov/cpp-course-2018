class Pair {
public:

    float x;
    float y;

    Pair(float x, float y) : x(x), y(y) {};
};

Pair rotate(Pair p, int degree) {
    degree = degree%4;
    if (degree == 0) return p;
    if (degree == 2) return {-p.x, -p.y};
    if (degree == 1) return {-p.y, p.x};
    return {p.y, -p.x};

}