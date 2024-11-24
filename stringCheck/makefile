# Nome del compilatore
CXX = g++

# Opzioni del compilatore
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Nome del file sorgente e dell'eseguibile
SRC = stringCheck.cpp
TARGET = stringCheck

# Regola di default
all: $(TARGET)

# Regola per compilare il target
$(TARGET): $(SRC) Parameters.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Regola per pulire i file generati
clean:
	rm -f $(TARGET)
