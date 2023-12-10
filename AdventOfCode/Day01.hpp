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
struct ACString
{ const char* Start = nullptr; const char* End = nullptr;
	const char* begin() { return Start; }
	const char* end() { return End; }
	size_t Length() { return (size_t)(End - Start); }
};
ACString MakeACString( const char* Start);
bool ReadNextLine(ACString & Sz);
void PrintLine(ACString & sz);
void SkipWhitespace(ACString &sz);
bool Consume(ACString &sz, const char* String);
bool Consume(ACString &sz, int &Out);


//////////////////////////////
void Day03();
bool IsNumeric(char c);


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
	
	void Empty() { Length = 0; }
	
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

template<typename T>
void Consume(ACString&Sz, ACArray<T> &Target)
{
	T Temp;
	while (Consume(Sz, Temp))
		Target.Add(Temp);
}


//////////////////////////////
void Day07();
bool IsAlpha(char a);
bool Consume(ACString &Src, ACString &Dst);

template<typename T>
auto QuickSort_Internal(ACArray<T>& ToSort, int start, int end)
{
	if (end == start + 1)
	{
		if (ToSort[start] > ToSort[end])
			std::swap(ToSort[start], ToSort[end]);
		return;
	}
	
	int mid = (start + end) / 2;
	if (mid != end) std::swap(ToSort[mid], ToSort[end]);
	T &MidValue = ToSort[end];
	
	int send = end - 1;
	int sstart = start;
	
	while (send > sstart)
	{
		while (ToSort[send] > MidValue && send >= start)
			send--;
		
		while (ToSort[sstart] < MidValue && sstart <= end-1)
			sstart++;
		
		if (sstart < send)
			std::swap(ToSort[sstart], ToSort[send]);
		else
			break;
	}
	send++;
	if (end != send)
	{
		std::swap(ToSort[send], ToSort[end]);
	}
	
	sstart--;
	if (start < sstart)	QuickSort_Internal(ToSort, start, sstart);
	
	if (end > send)	QuickSort_Internal(ToSort, send, end);
};

template<typename T>
void Quicksort(ACArray<T> &ToSort)
{
	
	if (ToSort.GetLength() > 1)
	{
		QuickSort_Internal(ToSort, 0, ToSort.GetLength() - 1);
	}
}
