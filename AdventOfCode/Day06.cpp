//
//  Day06.cpp
//  AdventOfCode
//
//  Created by Michael Fortin on 2023-12-10.
//

#include "Day01.hpp"

static const char* Sample =
R"MEOW(Time:      7  15   30
Distance:  9  40  200)MEOW";

static const char* Puzzle =
R"MEOW(Time:        62     64     91     90
Distance:   553   1010   1473   1074)MEOW";


template<typename T>
void Consume(ACString&Sz, ACArray<T> &Target)
{
	T Temp;
	while (Consume(Sz, Temp))
		Target.Add(Temp);
}


void Day06()
{
	ACString Sz = MakeACString(Puzzle);
	
	auto Times = ACArray<int>(6);
	ReadNextLine(Sz);
	Consume(Sz, "Time:");
	Consume(Sz, Times);
	
	ReadNextLine(Sz);
	auto Distances = ACArray<int>(6);
	Consume(Sz, "Distance:");
	Consume(Sz, Distances);
	
	assert(Distances.GetLength() == Times.GetLength());
	
	int Answer01 = 1;
	for (int i=0; i<Distances.GetLength(); i++)
	{
		int Time = Times[i];
		int Distance = Distances[i];
		
		// We have a relation of:
		//	PlayerDistance = (Time - Hold) * (Hold) > Distance
		//				   = (Time - Hold) * Hold - Distance = 0
		//				   = - Hold*Hold + Time * Hold  - Distance = 0
		
		// ~oooo; quadratic!
		
		assert(Time*Time - 4 * Distance >= 0);
		
		float A = (float)(-Time + sqrt(Time*Time - 4 * Distance)) / (float)(-2);
		float B = (float)(-Time - sqrt(Time*Time - 4 * Distance)) / (float)(-2);
		
		int ResMin = (int)std::ceil(A+0.001f);
		int ResMax = (int)std::floor(B-0.001f);
		
		Answer01 *= (ResMax - ResMin + 1);
	}
	
	printf("Day 6 Part 1: %i\n", Answer01);
}
