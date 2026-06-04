CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -I include

SRCDIR = src
OBJS = $(SRCDIR)/main.o $(SRCDIR)/math.o $(SRCDIR)/operations.o $(SRCDIR)/statistics.o \
       $(SRCDIR)/geometry.o $(SRCDIR)/bigint.o $(SRCDIR)/finance.o $(SRCDIR)/hex.o $(SRCDIR)/cli.o

calc: $(OBJS)
	$(CXX) $(CXXFLAGS) -o calc $(OBJS)

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp include/cli.h include/operations.h include/statistics.h \
                  include/geometry.h include/bigint.h include/finance.h include/hex.h include/safeinput.hpp
$(SRCDIR)/math.o: $(SRCDIR)/math.cpp include/math.h
$(SRCDIR)/operations.o: $(SRCDIR)/operations.cpp include/operations.h include/math.h include/safeinput.hpp
$(SRCDIR)/statistics.o: $(SRCDIR)/statistics.cpp include/statistics.h include/math.h include/safeinput.hpp
$(SRCDIR)/geometry.o: $(SRCDIR)/geometry.cpp include/geometry.h include/math.h include/safeinput.hpp
$(SRCDIR)/bigint.o: $(SRCDIR)/bigint.cpp include/bigint.h include/math.h include/safeinput.hpp
$(SRCDIR)/finance.o: $(SRCDIR)/finance.cpp include/finance.h include/operations.h include/safeinput.hpp
$(SRCDIR)/hex.o: $(SRCDIR)/hex.cpp include/hex.h include/safeinput.hpp
$(SRCDIR)/cli.o: $(SRCDIR)/cli.cpp include/cli.h include/operations.h include/safeinput.hpp

.PHONY: clean
clean:
	rm -f calc $(SRCDIR)/*.o
