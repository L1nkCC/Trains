---------------------------------------------------------------------------
	

				README


--------------------------------------------------------------------------
	Trains.cpp
		Author: Connor Leslie
		Date: 2/15/21
		Class: CS315
		Description: Run a simulation of a train station
			switching cars of a calculatable value.	
---------------------------------------------------------------------------

Struct: Car
	holds a set size and pointers to cars linked both before and after
Struct: Train
	holds a value calculated from the cars it holds and their position
	holds int length describing how many cars are in its list
	holds a pointer to the front of a linked list of struct: car
Func: makeCar()
	returns a car* with all of the passed information
Func: valueOfTrain()
	Calculates, sets, and returns the value of a passed train*
Func: makeTrain()
	returns a train* meeting the requirements of the start of the simulation
Func: insert()
	adds a given car* to the front of a given train*
Func: removeFront()
	returns and removes the front of given train*
Func: removeBack()
	returns and removes the back of given train*
Func: randNum()
	returns a value between 1 and given int inclusive by taking standard imput
Func: main()
	Runs simulation of car switching
	takes inital parameters
	creates a train*[]: station to hold all trains for the simulation
	loops (
		taking and adding cars to trains through standard input
		print the occurances of the loop and the values of each train
	)until a train is empty or a train is empty
	prints the simulation's results 

