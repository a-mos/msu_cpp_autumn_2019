#include <iostream>
#include <sstream>
#include "Serializer.h"
using namespace std;


struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }
};


int main(int argc, const char *argv[]) {
    if (argc > 1) {
        switch (atoi(argv[1])) {
            case 1: {
    	        Data x { 1, true, 2 };
                std::stringstream stream;
                Serializer serializer(stream);
                serializer.save(x);
                cout << stream.str() << endl;
                break;
            }
            case 2: {
                Data x { 1, true, 2 };

                std::stringstream stream;
                Serializer serializer(stream);
                serializer.save(x);

                Data y { 0, false, 0 };

                Deserializer deserializer(stream);
                const Error err = deserializer.load(y);

                assert(err == Error::NoError);
                assert(x.a == y.a);
                assert(x.b == y.b);
                assert(x.c == y.c);
                break;
            }
            default: {
                break;
            }
        }
        cout << "done" << endl;
    } else {
        Data x { 1, true, 2 };
        stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);
        cout << stream.str() << endl;
    }
    return 0;
}
