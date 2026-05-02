PC_TARGET  = noise_suppression_pc
CXX = C:/msys64/mingw64/bin/g++
CFLAGS     = -std=c++17 -O2 -Icommon

SOURCES    = common/pc_main.cpp \
             common/noise_suppression.cpp \
             common/fft_wrapper_pc.cpp

$(PC_TARGET): $(SOURCES)
	$(CXX) $(CFLAGS) $(SOURCES) -o $(PC_TARGET)

run: $(PC_TARGET)
	./$(PC_TARGET)

clean:
	rm -f $(PC_TARGET)