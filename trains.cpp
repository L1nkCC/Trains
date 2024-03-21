//---------------------------------------------------------------------------------------------
//trains.cpp
//Author: Connor Leslie
//Date: 2/15/21
//Class: CS315
//Description: Run simulation of a train station switching cars of a calculatable value
//---------------------------------------------------------------------------------------------

#include <iostream>
using namespace std;




//Car struct
//holds a cars size and the pointers to the car before and after
struct car{
	int size;
	car* next;
	car* prev;
};

//Train struct
//holds the number of cars in the linked list of cars, their value and point
struct train{
	int value;
	int length;
	car* front;
};

//Car constuctor
//takes all held values of car and returns a car with those values
car* makeCar(int newSize, car* newNext, car* newLast)
{
	car* returnCar = (car*) malloc(sizeof(car));
	returnCar->size = newSize;
	returnCar->next = newNext;
	returnCar->prev = newLast;
	return returnCar;
}


//train value calc
//finds and sets the value of the passed train
int valueOfTrain(train* t)
{
	int val = 0;
	car* currCar = t->front;
	for(int i = 1; i < t->length+1; i++)//loop through cars
	{
		val += (currCar->size)*(i);
		currCar = currCar->next;//change cars
	}
	t->value = val;//set value
	return val;
}

//train constructor
//takes a number of cars and makes the inital conditions for a train
train* makeTrain(int numOfCars)
{	

	train* returnTrain = (train*)malloc(sizeof(train));
	//if given a number under 1 return a NULL train
	if(numOfCars < 1)
	{
		returnTrain->value = -1;
		returnTrain->length = -1;
		returnTrain->front = NULL;
		return returnTrain;
	}
	//make a car for returnTrain to hold as front
	car* iCar = makeCar(1, NULL, NULL);
	returnTrain->front = iCar;

	//set variables so that loop will run
	car* earlyCar = iCar;
	car* laterCar = (car*) malloc(sizeof(car)); 
	for(int i = 0; i < numOfCars-1; i++)
	{
		laterCar = makeCar(numOfCars-i, earlyCar, NULL);
	        earlyCar->prev = laterCar;
		earlyCar = laterCar;	
	}
	//set end coniditions so the last car points to the front and front points to rear
	laterCar->prev = iCar;
	iCar->next = laterCar;

	//set the rest of trains information
	returnTrain->length = numOfCars;
	valueOfTrain(returnTrain);
	return returnTrain;
}


//adds a car to the front of a train
void insert(train* t, car* c)
{
	//set variables for easy read
	car* lastFront = t->front;
	car* back = t->front->prev;
	t->front = c;//set given car as the front of given train

	//change pointers to car is added to the front
	back->next = c;
	lastFront->prev = c;
	c->next = lastFront;
	c->prev = back;

	//update train information
	t->length += 1;
	valueOfTrain(t);
}


//remove a car from the front of passed train
//return car* removed
car* removeFront(train* t)
{
	//change pointers to remove the front car
	t->front->next->prev = t->front->prev;
	t->front->prev->next = t->front->next;
	car* returnCar = t->front;//set trains front to the new fron
	t->front = t->front->next;

	//update train information
	t->length -= 1;
	valueOfTrain(t);
	return returnCar;
}

//remove a car from the back of passed train
//return car* removed
car* removeBack(train* t)
{
	//change pointers to remove last car
	car* returnCar = t->front->prev;
	t->front->prev->prev->next = t->front;
	t->front->prev = t->front->prev->prev;

	//update train information
	t->length -= 1;
	valueOfTrain(t);
	return returnCar;
}

//return a random int between 1 and max inclusive
int randNum(int max)
{
	int imput;
	cin >> imput;
	return (imput%max)+1;
}


//simulation of a trains chainging cars body
int main(int argc, char* argv[])
{
	//import parameters
	int numOfTrains = stoi(argv[1]);
	int numOfCars = stoi(argv[2]);
	int maxIter = stoi(argv[3]);
	
	//create station
	//station is an array of a given length that represents the compilation of all trains in the simulation
	train* station[numOfTrains];
	for(int i = 0; i < numOfTrains; i++)
	{
		station[i] = makeTrain(numOfCars);//make each train for station
	}

	bool noLengthZero = true;//check that no train is empty

	for(int iteration = 1; ( (iteration < maxIter) && (noLengthZero) ); iteration ++)//loop until given: MaxIterations is reached or a train is empty
	{
		int trainLosingIndex = randNum(numOfTrains)-1;
		int frontOrBack = randNum(2)-1; //0 is front
		int trainGainingIndex = randNum(numOfTrains)-1;
		
		//remove a car
		car* changingCar = (car*) malloc(sizeof(car));
		if(frontOrBack == 0)//front
		{
			changingCar = removeFront(station[trainLosingIndex]);
		}else{//back
			changingCar = removeBack(station[trainLosingIndex]);
		}

		//add car
		insert(station[trainGainingIndex], changingCar);


		//printing the turn and what occured
		cout << "Turn Iteration: " << iteration << ": train " << trainLosingIndex+1<< " sends a car to train " << trainGainingIndex+1 << ", from ";
		if(frontOrBack ==0)//front
		{
			cout << "front";
		}else{//back
			cout << "back";
		}
		cout << endl;
		
		//list all trains' values
		for(int currTrain = 0; currTrain < numOfTrains; currTrain++)
		{
			cout << "Train " << currTrain+1 << ": value: " << station[currTrain]->value << endl;
			if(station[currTrain]->value ==0)
				noLengthZero = false;
		}
	}

	int highestValueIndex = 0;
	int zeroIndex = -1;
	for(int currTrain = 1; currTrain < numOfTrains; currTrain++)//loop through all trains
	{
		if(station[highestValueIndex]->value < station[currTrain]->value)//find train with the higshest value
			highestValueIndex = currTrain;
		if(station[currTrain]->value==0)//find which train is empty
			zeroIndex = currTrain;
	}
	//print results
	cout << "The simulation has finished. Train " << highestValueIndex+1 << " has the highest value.";
	if(zeroIndex!=-1)//print which train hit zero if it occurs       	
	 	cout << " Train " << zeroIndex +1 << " hit zero.";
	cout<< endl;


	return 0;//end program softly
		
}





