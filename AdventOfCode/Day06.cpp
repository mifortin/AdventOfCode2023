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

bool ConsumeSkipWhitespace(ACString &sz, int64_t &Out)
{
	SkipWhitespace(sz);
	
	Out = 0;
	if (sz.Start == sz.End)	return false;
	
	if (*sz.Start < '0' || *sz.Start > '9')	return false;
	
	while (*sz.Start >= '0' && *sz.Start <= '9')
	{
		Out *= 10;
		Out += *sz.Start - '0';
		sz.Start++;
		
		SkipWhitespace(sz);
	}
	
	return true;
}


void ComputeRace(int64_t Time, int64_t Distance, int64_t& OutResMin, int64_t &OutResMax)
{
	// We have a relation of:
	//	PlayerDistance = (Time - Hold) * (Hold) > Distance
	//				   = (Time - Hold) * Hold - Distance = 0
	//				   = - Hold*Hold + Time * Hold  - Distance = 0
	
	// ~oooo; quadratic!
	
	int64_t ToRoot =Time*Time - 4 * Distance;
	assert(ToRoot >= 0);
	
	double A = (double)(-Time + sqrt(ToRoot)) / (double)(-2);
	double B = (double)(-Time - sqrt(ToRoot)) / (double)(-2);
	
	OutResMin = (int64_t)std::ceil(A+0.00001f);
	OutResMax = (int64_t)std::floor(B-0.00001f);
}


void Day06()
{
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
		int64_t ResMin, ResMax;
		
		int64_t Answer01 = 1;
		for (int i=0; i<Distances.GetLength(); i++)
		{
			int64_t Time = Times[i];
			int64_t Distance = Distances[i];
			
			ComputeRace(Time, Distance, ResMin, ResMax);
			
			Answer01 *= (ResMax - ResMin + 1);
		}
		
		printf("Day 6 Part 1: %lli\n", Answer01);
	}
	
	{
		ACString Sz = MakeACString(Puzzle);
		
		int64_t Time;
		ReadNextLine(Sz);
		Consume(Sz, "Time:");
		ConsumeSkipWhitespace(Sz, Time);
		
		ReadNextLine(Sz);
		int64_t Distance;
		Consume(Sz, "Distance:");
		ConsumeSkipWhitespace(Sz, Distance);
		int64_t ResMin, ResMax;
		
		ComputeRace(Time, Distance, ResMin, ResMax);
		
		printf("Day 6 Part 2: %lli\n", ResMax - ResMin + 1);
	}
}
