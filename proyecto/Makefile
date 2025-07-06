CXX = g++
CXXFLAGS = -Wall -std=c++17
INCLUDES = -I./Core -I./UI -I./Utils

SRC = \
    main.cpp \
    Core/scheduler.cpp \
    Core/process.cpp \
    Core/metrics.cpp \
    Core/algorithms/fcfs.cpp \
    UI/interface.cpp \
    Utils/file_handler.cpp \
    Core/algorithms/sjf.cpp \
    Core/algorithms/round_robin.cpp \
    Core/algorithms/priority.cpp



OBJ = $(SRC:.cpp=.o)
TARGET = simulador

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
