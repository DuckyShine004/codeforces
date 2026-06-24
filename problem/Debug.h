#ifndef DEBUG_H
#define DEBUG_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

inline int recur_depth = 0;

inline void __print(int x) {
    cerr << x;
}

inline void __print(long x) {
    cerr << x;
}

inline void __print(long long x) {
    cerr << x;
}

inline void __print(unsigned x) {
    cerr << x;
}

inline void __print(unsigned long x) {
    cerr << x;
}

inline void __print(unsigned long long x) {
    cerr << x;
}

inline void __print(float x) {
    cerr << x;
}

inline void __print(double x) {
    cerr << x;
}

inline void __print(long double x) {
    cerr << x;
}

inline void __print(char x) {
    cerr << '\'' << x << '\'';
}

inline void __print(const char *x) {
    cerr << '\"' << x << '\"';
}

inline void __print(const string &x) {
    cerr << '\"' << x << '\"';
}

inline void __print(bool x) {
    cerr << (x ? "true" : "false");
}

template <typename T, typename V> void __print(const pair<T, V> &x) {
    cerr << '{';
    __print(x.first);

    cerr << ", ";

    __print(x.second);
    cerr << '}';
}

template <typename T> void __print(const T &x) {
    int f = 0;

    cerr << '{';

    for (const auto &i : x) {
        if (f++)
            cerr << ", ";

        __print(i);
    }

    cerr << '}';
}

inline void _print() {
    cerr << "]" << endl;
}

template <typename T, typename... V> void _print(T t, V... v) {
    __print(t);

    if (sizeof...(v))
        cerr << ", ";

    _print(v...);
}

template <typename K, typename V> void __print(const map<K, V> &x) {
    int f = 0;

    cerr << '{';

    for (const auto &it : x) {
        if (f++)
            cerr << ", ";

        __print(it.first);
        cerr << ": ";
        __print(it.second);
    }

    cerr << '}';
}

template <typename K, typename V> void __print(const unordered_map<K, V> &x) {
    int f = 0;

    cerr << '{';

    for (const auto &it : x) {
        if (f++)
            cerr << ", ";

        __print(it.first);
        cerr << ": ";
        __print(it.second);
    }

    cerr << '}';
}

template <typename T, typename Container> void __print(const queue<T, Container> &q) {
    int f = 0;

    queue<T, Container> tmp = q;

    cerr << '{';

    while (!tmp.empty()) {
        if (f++)
            cerr << ", ";

        __print(tmp.front());

        tmp.pop();
    }

    cerr << '}';
}

template <typename T, typename Container> void __print(const stack<T, Container> &s) {
    int f = 0;

    stack<T, Container> tmp = s;

    cerr << '{';

    while (!tmp.empty()) {
        if (f++)
            cerr << ", ";

        __print(tmp.top());

        tmp.pop();
    }

    cerr << '}';
}

template <typename T, typename Container, typename Compare> void __print(const priority_queue<T, Container, Compare> &pq) {
    int f = 0;

    priority_queue<T, Container, Compare> tmp = pq;

    cerr << '{';

    while (!tmp.empty()) {
        if (f++)
            cerr << ", ";
        __print(tmp.top());

        tmp.pop();
    }

    cerr << '}';
}

inline vector<string> split_names(const string &names_str) {
    vector<string> names;

    size_t start = 0;
    size_t comma = names_str.find(',');

    while (comma != string::npos) {
        string name = names_str.substr(start, comma - start);

        size_t last = name.find_last_not_of(" \t");
        size_t first = name.find_first_not_of(" \t");

        if (first != string::npos && last != string::npos)
            name = name.substr(first, last - first + 1);
        else
            name = "";

        names.push_back(name);
        start = comma + 1;
        comma = names_str.find(',', start);
    }

    string name = names_str.substr(start);

    size_t last = name.find_last_not_of(" \t");
    size_t first = name.find_first_not_of(" \t");

    if (first != string::npos && last != string::npos)
        name = name.substr(first, last - first + 1);
    else
        name = "";

    names.push_back(name);

    return names;
}

template <typename T> inline string to_string_debug(const T &x) {
    ostringstream oss;
    streambuf *old_buf = cerr.rdbuf(oss.rdbuf());

    __print(x);
    cerr.rdbuf(old_buf);

    return oss.str();
}

namespace DebugImpl {
template <typename... Args> void debug_impl(const char *func, int line, const char *names_str, const Args &...args) {
    vector<string> names = split_names(names_str);
    vector<string> values{to_string_debug(args)...};

    if (names.empty())
        return;

    cerr << string(recur_depth, '\t') << "\033[91m" << func << ":" << line << " [";

    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0)
            cerr << ", ";
        cerr << names[i];
    }

    cerr << "] = ";

    for (size_t i = 0; i < values.size(); i++) {
        if (i > 0)
            cerr << " ";
        cerr << values[i];
    }

    cerr << "\033[39m" << endl;
}
} // namespace DebugImpl

#ifndef ONLINE_JUDGE
#define debug(...) (DebugImpl::debug_impl(__func__, __LINE__, #__VA_ARGS__, __VA_ARGS__))
#else
#define debug(...)
#endif

// clang-format off
#ifndef ONLINE_JUDGE
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        ( \
            cerr << string(recur_depth, '\t') << "\033[91m" << "Time: " << \
            fixed << setprecision(3) << \
            chrono::duration<double, milli>(chrono::high_resolution_clock::now() - blockTime.first).count() << " ms" << \
            "\033[39m" << endl, \
            blockTime.second = false \
        ) \
    )
#else
#define time__(d) for(; false;)
#endif
// clang-format on

#endif // DEBUG_H
