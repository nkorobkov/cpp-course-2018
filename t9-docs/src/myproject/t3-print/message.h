#include <iostream>

template <class Head>
void message(std::ostream& stream,const char* string, Head head) {
    if (*string == '\0'){
        return;
    }
    if (*string == '%'){
        stream << head;
        string++;
        stream << string;
    }else{
        stream << string[0];
        string++;
        message(stream, string, head); // рекурсия
    }
}

/**
\brief
Выводит сообщение в поток заменяя символы процента на аргументы начиная со третьего.
\date 2018-12-14
\param[in] stream поток, в который записывается сообщение
\param[in] string строка которую нужно вывести в поток
\param[in] args... значения которые нужно подставить в строку вместо символов %
*/
template <class Head, class ... Tail>
void message(std::ostream& stream, const char* string, Head head, Tail ... tail) {
    if (*string == '\0'){
        return;
    }
    if (*string == '%'){
        stream << head;
        string++;
        message(stream, string, tail...); // рекурсия
    }else{
        stream << string[0];
        string++;
        message(stream, string, head, tail...); // рекурсия
    }


}
