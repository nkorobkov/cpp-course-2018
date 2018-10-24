
#include <iostream>
#include <sstream>


class LineNumberBuffer : public std::streambuf {
    std::streambuf *old;
    std::string str;
    int ln = 2;
public:
    explicit LineNumberBuffer(std::streambuf *b) : old(b) {
        sputc('1');
        sputc(' ');
    }

protected:

    int_type overflow(int_type c) override {
        if ((c) == '\n') {
            old->sputc(c);
            for (char ch : std::to_string(ln)) {
                old->sputc(ch);
            }
            ln++;
            return old->sputc(' ');
        }else{
            return old->sputc(c);
        }

    }

    std::streamsize xsputn(const char *s, std::streamsize n) override {
        for (int i = 0; i < n; i++) {
            str += (*(s + i));
            if (*(s + i) == '\n') {
                str.append(std::to_string(ln));
                ln++;
            }
        }
        return old->sputn(str.data(), n);
    }
};