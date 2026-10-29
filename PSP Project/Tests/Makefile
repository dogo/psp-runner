SRC = sim.cpp ../Src/GameScreen.cpp ../Src/Runner.cpp ../Src/Obstacles.cpp ../Src/Ranking.cpp

test: sim
	cd .. && Tests/sim

sim: $(SRC) oslib/oslib.h $(wildcard ../Include/*.h)
	c++ -O2 -Wall -I. -o sim $(SRC)

clean:
	rm -f sim
