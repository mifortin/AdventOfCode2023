//
//  Day01.hpp
//  AdventOfCode
//
//  Created by Michael Fortin on 2023-12-05.
//

#pragma once
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cstdint>

#define ARRAY_LEN(X)	(sizeof(X) / sizeof(X[0]))


void Day01();

void GenRevDigits();
bool ReadNextLine(const char** Start, const char** End);
void PrintLine(const char* Start, const char* End);
int FirstDigit(const char* Start);
int LastDigit(const char* End);
bool EqualsFront(const char*Start, const char* Cmp);
bool EqualsFront(const char*Start, const char* Cmp);
bool EqualsBack(const char*Start, const char* CmpStart, const char* CmpEnd);


//////////////////////////////
void Day02();
struct ACString { const char* Start = nullptr; const char* End = nullptr; };
ACString MakeACString( const char* Start);
bool ReadNextLine(ACString & Sz);
void PrintLine(ACString & sz);
void SkipWhitespace(ACString &sz);
bool Consume(ACString &sz, const char* String);
bool Consume(ACString &sz, int &Out);


//////////////////////////////
void Day03();


//////////////////////////////
void Day04();
void SetBit(char* BitField, int Index, bool Value);
bool IsBitSet(const char* BitField, int Index);


//////////////////////////////
void Day05();
bool Consume(ACString &sz, int64_t &Out);
struct ACRange {
	static ACRange FromStartLength(int64_t Start, int64_t Length);
	static ACRange Intersect(const ACRange& A, const ACRange&B);
	static ACRange Left(const ACRange& A, const ACRange&B);
	static ACRange Right(const ACRange& A, const ACRange&B);
	static ACRange Union(const ACRange &A, const ACRange&B);
	
	bool IsValid();
	
	int64_t Start;
	int64_t End;
};

template<typename T>
struct ACArray
{
	ACArray(int InMax)
	{
		Max = InMax;
		Length = 0;
		Data = new T[Max];
		memset(Data, 0, Max*sizeof(T));	// Maybe I shouldn't, but convenient.
	}
	
	ACArray(ACArray&) = delete;
	~ACArray()
	{
		delete[] Data;
	}
	
	int GetLength() { return Length; }
	
	T&operator[](int i)
	{
		assert(i >= 0 && i < Length);
		return Data[i];
	}
	
	void Add(const T&Value)
	{
		assert(Length < Max);
		Data[Length] = Value;
		Length++;
	}
	
	void Delete(int index)
	{
		assert(index >=0 && index < Length);
		Length--;
		for (int i=index; i<Length; i++)
		{
			Data[i] = Data[i+1];
		}
	}
	
	T*begin() { return Data; }
	T*end() { return Data + Length; }
	
	static void swap(ACArray<T> & A, ACArray<T> &B)
	{
		std::swap(A.Length, B.Length);
		std::swap(A.Max, B.Max);
		std::swap(A.Data, B.Data);
	}
	
protected:
	
	int Length;
	int Max;
	
	T *Data;
};

namespace std {
	template<typename T>
	void swap(ACArray<T> & A, ACArray<T> &B)
	{
		ACArray<T>::swap(A, B);
	}
}


struct ACRangeArray : public ACArray<ACRange>
{
	ACRangeArray(int MaxSize) : ACArray<ACRange>(MaxSize) {}
	
	void AddRange(ACRange Range)
	{
		Add(Range);
		
		int CurIndex = GetLength() - 1;
		while (CurIndex > 0)
		{
			ACRange Merged = ACRange::Union(Data[CurIndex], Data[CurIndex-1]);
			
			if (Merged.IsValid())
			{
				Data[CurIndex-1] = Merged;
				Delete(CurIndex);
			}
			else if (Data[CurIndex-1].Start < Data[CurIndex].Start)
				return;
			
			std::swap(Data[CurIndex-1], Data[CurIndex]);
			
			CurIndex--;
		}
	}
};


//////////////////////////////
void Day06();
bool ConsumeSkipWhitespace(ACString &sz, int64_t &Out);
