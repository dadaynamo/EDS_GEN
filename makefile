# Nome del programma eseguibile
TARGET = mainEDS-GEN

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
raw: $(TARGET)
	@read -p "Enter output name: " outputname; \
	read -p "Enter TOTsize: " totSize; \
	./$(TARGET) --outputName $$outputname --totSize $$totSize --type R

eds: $(TARGET)
	@read -p "Enter output name: " outputname; \
	read -p "Enter TOTsize: " totsize; \
	read -p "Enter maxPerDeg: " maxPerDeg; \
	read -p "Enter numDeg: " numDeg; \
	./$(TARGET) --outputName $$outputname --totSize $$totsize --maxPerDeg $$maxPerDeg --numDeg $$numDeg --type E


# Pulire i file oggetto e l'eseguibile
clean:
	rm -f $(TARGET)
