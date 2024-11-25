# Nome dell'eseguibile
TARGET = edsToRaw

# Compilatore
CXX = g++

# Opzioni di compilazione
CXXFLAGS = -Wall -Wextra -std=c++11

# File sorgente
SRCS = edsToRaw.cpp

# File oggetto
OBJS = $(SRCS:.cpp=.o)

# Regola di default
all: $(TARGET)

# Regola per compilare l'eseguibile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regola per compilare i file sorgente in file oggetto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Regola per pulire i file oggetto e l'eseguibile
clean:
	rm -f $(OBJS) $(TARGET)

# Regola per eseguire il programma
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
