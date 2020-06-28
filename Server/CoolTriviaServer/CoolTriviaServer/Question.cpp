#include "Question.h"

string Question::getQuestion()
{
	return this->m_question;
}

string Question::getPossibleAnswers()
{
	string answers = "";
	for (auto& answer : this->m_possibleAnswers)
	{
		answers += answer;
		if (answer != this->m_possibleAnswers[this->m_possibleAnswers.size() - 1]) {
			answers += ",";
		}
	}
	return answers;
}

string Question::getCorrentAnswer()
{
	return this->m_possibleAnswers[0];
}
