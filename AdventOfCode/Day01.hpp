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

