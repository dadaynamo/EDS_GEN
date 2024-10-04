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
# Regola per eseguire il programma con parametri
run: $(TARGET)
	@read -p "Enter output name: " outputname; \
	read -p "Enter TOTsize: " totsize; \
	./$(TARGET) $$outputname $$totsize


# Pulire i file oggetto e l'eseguibile
clean:
	rm -f $(TARGET)
