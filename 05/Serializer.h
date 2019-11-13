#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive
};


class Serializer {
    static constexpr char Separator = ' ';
    std::ostream &out_;
public:
    explicit Serializer(std::ostream& out): out_(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(std::forward<ArgsT>(args)...);
    }
private:
    Error process(uint64_t value) {
        out_ << value << Separator;
        return Error::NoError;
    }

    Error process(bool value) {
        out_ << (value ? "true" : "false") << Separator;
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args) {
        if (process(value) == Error::NoError) {
            return process(std::forward<ArgsT>(args)...);
        } else {
            return Error::CorruptedArchive;
        }
    }
};


class Deserializer {
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in) : in_(in) {}

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return load(std::forward<ArgsT>(args)...);
    }

private:
    Error load(uint64_t &value) {
        std::string text;
        in_ >> text;
        try {
            value = std::stoull(text);
        } catch (std::invalid_argument) {
            return Error::CorruptedArchive;
        } catch (std::out_of_range) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error load(bool &value) {
        std::string text;
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
            return load(std::forward<ArgsT>(args)...);
        } else {
            return Error::CorruptedArchive;
        }
    }
};
