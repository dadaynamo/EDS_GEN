# Nome del programma eseguibile
TARGET = my_program

# Compilatore
CXX = g++

# Opzioni di compilazione
CXXFLAGS = -Wall -Wextra -std=c++11

# File sorgente
SRCS = mainEDS-GEN.cpp

# Regola di compilazione
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regola per eseguire il programma con parametri passati
run: $(TARGET)
	./$(TARGET) $(PARAM1) $(PARAM2)

# Pulire i file oggetto e l'eseguibile
clean:
	rm -f $(TARGET)
