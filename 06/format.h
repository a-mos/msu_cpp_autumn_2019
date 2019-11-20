#include <iostream>
#include <sstream>
#include <vector>

template <class T>
std::string arg_to_string(const T& arg) {
    std::stringstream tmp;
    tmp << arg;
    return tmp.str();
}

template <class ...ArgsT>
std::string format(const std::string &s, ArgsT&&... args) {
    std::stringstream ans;
    std::vector<std::string> args_vec {arg_to_string(std::forward<ArgsT>(args))...};
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '}') {
            throw std::runtime_error("err");
        } else if (s[i] == '{') {
            size_t num, next_idx;
            try {
                num = std::stoull(s.substr(++i), &next_idx);
            } catch (std::logic_error &e) {
                throw std::runtime_error("err");
            }
            if (s[i += next_idx] != '}' || num >= args_vec.size()) {
                throw std::runtime_error("err");
            }
            ans << args_vec[num];
        } else {
            ans << s[i];
        }
    }
    return ans.str();
}