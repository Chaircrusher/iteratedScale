CXXFLAGS=-g -O0
iteratedScale: iteratedScale.cpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@

clean:
	rm -f iteratedScale *.o
