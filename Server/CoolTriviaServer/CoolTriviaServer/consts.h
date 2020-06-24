#pragma once

// server settings
#define PORT 8820
#define IP "127.0.0.1"

// DATABASE

// Database general
#define ERROR -1

// Database settings
#define DB_FILE_NAME "triviaDB.sqlite"

// Database questions
#define NUM_OF_Q 10
#define NUM_OF_DETAILS 5
#define NUM_OF_COMMANDS 4

const string QUES_ANS[NUM_OF_Q][NUM_OF_DETAILS] = { {"Ques1", "correct_Ans1", "ans1-1", "ans2-1", "ans3-1"},
													{"Ques2", "correct_Ans2", "ans1-2", "ans2-2", "ans3-2"},
													{"Ques3", "correct_Ans3", "ans1-3", "ans2-3", "ans3-3"},
													{"Ques4", "correct_Ans4", "ans1-4", "ans2-4", "ans3-4"},
													{"Ques5", "correct_Ans5", "ans1-5", "ans2-5", "ans3-5"},
													{"Ques6", "correct_Ans6", "ans1-6", "ans2-6", "ans3-6"},
													{"Ques7", "correct_Ans7", "ans1-7", "ans2-7", "ans3-7"},
													{"Ques8", "correct_Ans8", "ans1-8", "ans2-8", "ans3-8"},
													{"Ques9", "correct_Ans9", "ans1-9", "ans2-9", "ans3-9"},
													{"Ques10", "correct_Ans10", "ans1-10", "ans2-10", "ans3-10"} };

const string SET_DB[NUM_OF_COMMANDS] = { "CREATE TABLE Users (id integer PRIMARY KEY AUTOINCREMENT NOT NULL, username text NOT NULL, password text NOT NULL, mail text NOT NULL);",
										 "CREATE TABLE Questions (id integer PRIMARY KEY AUTOINCREMENT NOT NULL, question text NOT NULL, correct_ans text NOT NULL, ans1 text NOT NULL, ans2 text NOT NULL, ans3 text NOT NULL);",
										 "CREATE TABLE Games (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, status integer NOT NULL, start_time	DATETIME NOT NULL, end_time	DATETIME);",
										 "CREATE TABLE Data (game_id integer NOT NULL, username text NOT NULL, question_id integer NOT NULL, player_answer text NOT NULL, is_correct integer NOT NULL, answer_time integer NOT NULL, PRIMARY KEY(game_id,username,question_id), FOREIGN KEY(game_id) REFERENCES Games(id), FOREIGN KEY(username) REFERENCES Users(username), FOREIGN KEY(question_id) REFERENCES Questions(id));" };

// message codes
enum messageCodes
{
	signupCode = 1,
	loginCode = 2,
	errorCode = 3,
	createRoomCode = 4,
	getRoomsCode = 5,
	getPlayersInRoomCode = 6,
	joinRoomCode = 7,
	getStatisticsCode = 8,
	logoutCode = 9
};

// answer statuses
enum answerStatuses
{
	successStatus = 1,
	wrongDataStatus = 2,
	alreadyConnectedStatus = 3,
	roomIsFullStatus = 4
};

// room states
enum roomStates
{
	waitingForPlayersRoom = 1,
	alreadyStartedRoom = 2
};

// protocol consts
enum protocolParts
{
	partCode = 1,
	partJsonLength = 4
};

