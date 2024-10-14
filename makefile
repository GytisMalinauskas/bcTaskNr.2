# Kompiliatoriaus nustatymas
CXX = g++
CXXFLAGS = -Wall -Iheaders -std=c++17

# Šaltinių ir antraščių katalogai
SRC_DIR = sources
HEADER_DIR = headers

# Tikslinis (output) failas
TARGET = program

# Surinkti visi .cpp failai iš sources katalogo
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Paversk .cpp failų vardus į .o failus
OBJS = $(SRCS:.cpp=.o)

# Pagrindinė taisyklė: kaip surinkti programą
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Taisyklė kaip surinkti .o failus iš .cpp failų
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Švarinimo taisyklė (šalina sugeneruotus failus)
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Tikriname pakeitimus antraštės failuose
.PHONY: clean
