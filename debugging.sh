g++ -c -Wall -std=c++11 io_service.cpp -o io_service.o
g++ -c -Wall -std=c++11 pin_manager.cpp -o pin_manager.o
g++ -c -Wall -std=c++11 carg_filter.cpp -o carg_filter.o
g++ -c -Wall -std=c++11 data_packet.cpp -o data_packet.o
g++ -Wall -std=c++11 debugging.cpp pin_manager.o carg_filter.o data_packet.o io_service.o -o debugging.exec && ./debugging.exec
