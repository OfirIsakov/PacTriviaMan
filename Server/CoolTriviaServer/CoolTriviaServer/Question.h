#pragma once
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Question
{
	string m_question;
	vector<string> m_possibleAnswers;
public:
	string getQuestion();
	string getPossibleAnswers();
	string getCorrentAnswer();
};

