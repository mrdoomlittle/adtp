g++ -c -Wall -std=c++11 pin_manager.cpp -o pin_manager.o
g++ -c -Wall -std=c++11 tmp_config.cpp -o tmp_config.o
g++ -Wall -std=c++11 sdebugging.cpp tmp_config.o pin_manager.o -o sdebugging.exec && ./sdebugging.exec
