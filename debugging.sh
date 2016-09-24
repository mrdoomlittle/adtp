g++ -c -Wall -std=c++11 io_service.cpp -o io_service.o
g++ -c -Wall -std=c++11 pin_manager.cpp -o pin_manager.o
g++ -Wall -std=c++11 debugging.cpp pin_manager.o io_service.o -o debugging.exec && ./debugging.exec
