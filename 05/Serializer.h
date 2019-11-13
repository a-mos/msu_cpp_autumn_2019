#include <sstream>
using namespace std;

enum class Error {
    NoError,
    CorruptedArchive
};


class Serializer {
    static constexpr char Separator = ' ';
    ostream &out_;
public:
    explicit Serializer(ostream& out): out_(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }
private:
    Error process(uint64_t &value) {
        out_ << value << Separator;
        return Error::NoError;
    }

    Error process(bool &value) {
        out_ << (value ? "true" : "false") << Separator;
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args) {
        if (process(value) == Error::NoError) {
            return process(forward<ArgsT>(args)...);
        } else {
            return Error::CorruptedArchive;
        }
    }
};


class Deserializer {
    istream& in_;
public:
    explicit Deserializer(istream& in) : in_(in) {}

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return load(forward<ArgsT>(args)...);
    }

private:
    Error load(uint64_t &value) {
        string text;
        in_ >> text;
        try {
            value = stoull(text);
        } catch (...) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error load(bool &value) {
        string text;
        in_ >> text;
        if (text == "true") {
            value = true;
        } else if (text == "false") {
            value = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error load(T&& value, ArgsT&&... args) {
        if (load(value) == Error::NoError) {
            return load(forward<ArgsT>(args)...);
        } else {
            return Error::CorruptedArchive;
        }
    }
};