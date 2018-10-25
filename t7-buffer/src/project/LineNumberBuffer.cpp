
#include <iostream>
#include <sstream>


class LineNumberBuffer : public std::streambuf {
    std::streambuf *old;
    std::string str;
    int ln = 1;
    bool f = false;
public:
    explicit LineNumberBuffer(std::streambuf *b) : old(b) {}

protected:

    int_type overflow(int_type c) override {
        if (ln == 1) {
            str = std::to_string(ln);
            for (char ch : std::to_string(ln)) {
                old->sputc(ch);
            }
            old->sputc(' ');
            ln++;
        }
        if (f) {
            for (char ch : std::to_string(ln)) {
                old->sputc(ch);
            }
            ln++;
            old->sputc(' ');
            f = false;
        }
        if ((c) == '\n') {
            f = true;
        }
        return old->sputc(c);
    }

    std::streamsize xsputn(const char *s, std::streamsize n) override {
        for (int i = 0; i < n; i++) {
            str += (*(s + i));
            if (*(s + i) == '\n') {
                str.append(std::to_string(ln));
                ln++;
            }
        }
        return old->sputn(str.data(), str.size());
    }
};