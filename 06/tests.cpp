#include <iostream>
#include <sstream>
#include "format.h"
using namespace std;


int main(int argc, const char *argv[]) {
    if (argc > 1) {
        switch (atoi(argv[1])) {
            case 1: {
    			cout << format("1");
                break;
            }
            case 2: {
                cout << format("{1}+{1} = {0}", 2, "one");
                break;
            }
            case 3: {
            	cout << format("{1}+{1}", 777, "one");
            	break;
            }
            case 4: {
            	try {
            		cout << format("{2}+{2}", 777);
            	} catch (std::runtime_error& e) {
            		cout << e.what();
            	}
            	break;
            }
            case 5: {
            	try {
            		cout << format("{{{}}}");
            	} catch (std::runtime_error& e) {
            		cout << e.what();
            	}
            	break;
            }
            case 6: {
	            try {
	          		cout << format("777{");
	            } catch (std::runtime_error& e) {
	            		cout << e.what();
	            }
	            break;
	        }
	        case 7: {
	        	cout << format("{0}{1}{2}{3}", 777, "one", "two", 3);
	        	break;
	        }
	        case 8: {
                try {
	          	    cout << format("777{");
                } catch (std::runtime_error& e) {
                        cout << e.what();
                }
	        }
            default: {
                break;
            }
        }
        cout << "done" << endl;
    } else {
        auto text = format("{1}+{1} = {0}", 2, "one");
        cout << text << endl;
        assert(text == "one+one = 2");
    }
    return 0;
}
