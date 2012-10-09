//============================================================================
// Name        : fast_mentalAr.cpp
// Author      : John-David Wuarin
// Copyright (c) 2012 John-David Wuarin
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense,
// and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <ctime>

using namespace std;

class questionInfo{
	int qNumber;
	string question;
	int timeOnQu;

public:

	questionInfo(int _qNumber, string _question){
		qNumber = _qNumber;
		question = _question;
		timeOnQu = 0;
	}

	virtual ~questionInfo(){

	}

	void setQNumber (int _qNumber){
		qNumber = _qNumber;
	}
	void setQuestion (string _question){
		question = _question;
	}
	void setTimeOnQu (int _timeOnQu){
		timeOnQu = _timeOnQu;
	}

	virtual void setCorrAnswer(double _corrAnswer){
		cout << "Nothing to do here, wrong object called. " << endl;
	}
	virtual void setYourAnswer(double _yourAnswer){
		cout << "Nothing to do here, wrong object called. " << endl;
	}
	virtual void setCorrAnswer(string _corrAnswer){
		cout << "Nothing to do here, wrong object called. " << endl;
	}
	virtual void setYourAnswer(string _corrAnswer){
		cout << "Nothing to do here, wrong object called. " << endl;
	}

	void printQNumber(){
		string questNumber;
		questNumber = " " + static_cast<ostringstream*>( &(ostringstream() << qNumber) )->str() + ")";
		cout << questNumber;
	}

	void printQuestion(){
		cout << question;
	}

	void printTimeOnQu(){
		if (timeOnQu > 20)
			cout << timeOnQu << "s(!!!)";
		else if (timeOnQu > 15)
			cout << timeOnQu << "s(!!)";
		else if (timeOnQu > 8)
			cout << timeOnQu << "s(!)";
		else
			cout << timeOnQu << "s";
	}

	virtual void printCorrAnswer(){
		cout << "Nothing to do here, wrong object called. " << endl;
	}

	virtual void printYourAnswer(){
		cout << "Nothing to do here, wrong object called. " << endl;
	}



};

class questionDouble: public questionInfo{
	double corrAnswer;
	double yourAnswer;

public:
	questionDouble(int _qNumber, string _question,
			double _corrAnswer, double _yourAnswer = 0):questionInfo(_qNumber, _question){
		corrAnswer = _corrAnswer;
		yourAnswer = _yourAnswer;
	}

	void setCorrAnswer(double _corrAnswer){
		corrAnswer = _corrAnswer;
	}
	void setYourAnswer(double _yourAnswer){
		yourAnswer = _yourAnswer;
	}

	virtual void printCorrAnswer(){
		cout << corrAnswer;
	}

	virtual void printYourAnswer(){
		cout.width(13);
		if (yourAnswer != corrAnswer){
			cout << yourAnswer;
			cout.width(7);
			cout << "  W";
		}
		else{
			cout << yourAnswer;
			cout.width(7);
			cout << " R";
		}
	}


};

class questionString: public questionInfo{
	string corrAnswer;
	string yourAnswer;

public:
	questionString(int _qNumber, string _question,
			string _corrAnswer, string _yourAnswer = "0"):questionInfo(_qNumber, _question){
		corrAnswer = _corrAnswer;
		yourAnswer = _yourAnswer;
	}

	void setCorrAnswer(string _corrAnswer){
		corrAnswer = _corrAnswer;
	}
	void setYourAnswer(string _yourAnswer){
		yourAnswer = _yourAnswer;
	}

	virtual void printCorrAnswer(){
		cout << corrAnswer;
	}

	virtual void printYourAnswer(){
		cout.width(13);
		if (yourAnswer != corrAnswer){
			cout << yourAnswer;
			cout.width(7);
			cout << "  W";
		}
		else{
			cout << yourAnswer;
			cout.width(7);
			cout << " R";
		}
	}


};

vector<double> returnSimple(double corrAnswer, double divisor);
vector<string> returnFract(int ansNume, int ansDenom, string& strinAnswer);
vector<string> returnMixedFract(int ansNume, int ansDenom, int ansInteger, string& stringAnswer);
vector<double> simpleAdd(vector<questionInfo*>&allQuestions, int questionNum, double& answer);
vector<double> simpleMult(vector<questionInfo*>&allQuestions, int questionNum, double& answer);
vector<string> fractMult(vector<questionInfo*>&allQuestions, int questionNum, string& answer);
vector<string> fractAdd(vector<questionInfo*>&allQuestions, int questionNum, string& answer);

template <typename T>
int runCheckQ(vector<questionInfo*>&allQuestions, vector<T>&answers, T& answer, int _timeLeft){

	int answerNum = 0;
	T userAnswer;
	int userCorrect = 0;
	int quStartTime = 0;
	int timeOnQu = 0;
	string discard;

	cout.precision(10);
	cout << "1) " << answers[0] << endl << endl;
	cout << "2) " << answers[1] << endl << endl;
	cout << "3) " << answers[2] << endl << endl;
	cout << "4) " << answers[3] << endl << endl;

	cout <<"Your answer: type number 1-4, then ENTER: " << endl;

	quStartTime = time(0);
	while (answerNum == 0){
		cin >> answerNum;
		if (!cin){
			cout << "Bad input, please enter number between 1 and 4, no letters." << endl;
			cin.clear();
			getline(cin, discard);
		}
		else if ((answerNum < 1) || (answerNum > 4)){
			cout << "Bad input, please enter number between 1 and 4" << endl;
			answerNum = 0;
		}
		else //input is good
			break;
	}

	timeOnQu = time(0) - quStartTime;

	if (answerNum == 1)
		userAnswer = answers[0];
	else if (answerNum == 2)
		userAnswer = answers[1];
	else if (answerNum == 3)
		userAnswer = answers[2];
	else
		userAnswer = answers[3];

	if (timeOnQu > _timeLeft){
		userCorrect = -1;
		cout << "Time has expired before answer for question"; allQuestions.at(allQuestions.size()-1)->printQNumber();
				cout << " was input. Point will not be counted towards total." << endl << endl;
	}
	else if (userAnswer == answer)
		userCorrect = true;
	else
		userCorrect = false;

	allQuestions.at(allQuestions.size()-1)->setYourAnswer(userAnswer);
	allQuestions.at(allQuestions.size()-1)->setTimeOnQu(timeOnQu);

	return userCorrect;

}


int main() {

	int const numQuestions = 80;
	int const testTime = 480;
	int questionNum = 1;
	int const start = time(0);
	double questionType = 0;
	double answerNume = 0;
	int points = 0;
	int userCorrect = false;
	vector<double>answersNume;
	vector<string>answersString;
	string answerFract;
	vector<questionInfo*>allQuestions;


	int timeLeft = 0;

	srand(time(0));

	while ((time(0) - start < testTime) && (questionNum <= numQuestions)) {


		timeLeft = testTime - (time(0) - start);

		cout << endl << "Question " << questionNum << ")" << endl;
		if(timeLeft % 60 < 10){ //seconds remaining in current minute
			cout << "time left: " << int(timeLeft/60) << ":0"
					<< timeLeft % 60 << endl << endl;
		}
		else{
			cout << "time left: " << int(timeLeft/60) << ":"
					<< timeLeft % 60 << endl << endl;
		}



		questionType = rand() % 4; //assuming 4 tyes of question.

		if (questionType == 0) { //call simple addition/substraction

			answersNume = simpleAdd(allQuestions, questionNum, answerNume);
			userCorrect = runCheckQ<double>(allQuestions, answersNume, answerNume, timeLeft);

		}

		else if (questionType == 1) { //call fraction addition/substraction
			answersString = fractAdd(allQuestions, questionNum, answerFract);
			userCorrect = runCheckQ<string>(allQuestions, answersString, answerFract, timeLeft);

		}

		else if (questionType == 2) { //call simple multiplication/division

			answersNume = simpleMult(allQuestions, questionNum, answerNume);
			userCorrect = runCheckQ<double>(allQuestions, answersNume, answerNume, timeLeft);

		}

		else{ //call fraction multiplication/division

			answersString = fractMult(allQuestions, questionNum, answerFract);
			userCorrect = runCheckQ<string>(allQuestions, answersString, answerFract, timeLeft);

		}


		++questionNum;

		if (userCorrect == true)
			++points;
		else if (userCorrect == false)
			--points;
		else{} // does nothing when userCorrect = -1 (when time has expired)


	}

	cout << "Total number of points: " << points << endl;

	if (points > 53){
		cout << "You probably would have passed the real test. Well done!!!" << endl << endl;
	}
	else
		cout << "You would have failed the real test, try again..." << endl << endl;

	unsigned int i = 0;

	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(9);
	cout << "qNumber";
	cout.width(27);
	cout << "Question";
	cout.width(13);
	cout << "Corr answer";
	cout.width(13);
	cout << "Your answer";
	cout.width(7);
	cout << "Rt/Wg";
	cout << "Time spent" << endl << endl;

	for (i = 0; i < allQuestions.size(); ++i){
		cout.width(9);
		allQuestions[i]->printQNumber();
		cout.width(27);
		allQuestions[i]->printQuestion();
		cout.width(13);
		allQuestions[i]->printCorrAnswer();
		//width set in class from here.
		allQuestions[i]->printYourAnswer();
		allQuestions[i]->printTimeOnQu();
		cout << endl; //keep this

	}


	cout << endl << "Press any key then Enter to exit" << endl;
	int dontExit; //used mainly because windows console exits automatically.
	cin >> dontExit;

	return 0;
}


vector<double> simpleAdd(vector<questionInfo*>&allQuestions, int questionNum, double& answer){
	double num1, num2;
	double divisor1, divisor2;
	bool addOrSub = 0;
	double unknLoc = 0;
	vector<double>answerS;

	stringstream toPrint;
	string question;

	//get two values for numbers to compute.

	num1 = (rand() % 100) + 4;

	num2 = (rand() % 100)+ 4; //set them to a random value 4-103

	divisor1 = pow(10.0, (rand() % 4)); divisor2 = divisor1*pow(10.0, (rand() % 3)-1); // get divisor, second close to first.

	num1 = num1/divisor1; //get real values for numbers.
	num2 = num2/divisor2; //get real values for numbers.

	if (rand() % 2 == 0) //numbers can be positive or negative.
		num1 = -num1;
	else{}

	if (rand() % 2 == 0)
		num2 = - num2;
	else{}

	addOrSub = (rand() % 2);

	if (addOrSub == 1){ //addition;
		//determine unknown
		unknLoc = rand() % 3;

		if(unknLoc == 0){ // ... + num1 = num2
			answer = num2-num1;
			toPrint << "... + " << num1 << " = " << num2;
		}
		else if(unknLoc == 1){ // num1 + ... = num2
			answer = num2-num1;
			toPrint << num1 << " + ... " << "= " << num2;
		}
		else{ // num1 + num2 = ...
			answer = num1 + num2;
			toPrint << num1 << " + " << num2 << " = ...";
		}
	}

	else{ //substraction
		unknLoc = rand() % 3;

		if(unknLoc == 0){ // ... - num1 = num2
			answer = num2 + num1;
			toPrint << "... - " << num1 << " = " << num2;
		}
		else if(unknLoc == 1){ // num1 - ... = num2
			answer = num1 - num2;
			toPrint << num1 << " - ... " << " = " << num2;
		}
		else{ // num1 - num2 = ...
			answer = num1 - num2;
			toPrint << num1 << " - " << num2 << " = ...";
		}
	}
	answerS = returnSimple(answer, divisor1);

	toPrint.seekg(0);
	getline(toPrint, question);

	allQuestions.push_back(new questionDouble(questionNum, question, answer));

	cout << question << endl << endl;

	return answerS;
}

vector<double> simpleMult(vector<questionInfo*>&allQuestions, int questionNum, double& answer){
	double num1, num2;
	double divisor1, divisor2;
	bool multOrDiv = 0;
	double unknLoc = 0;
	vector<double>answerS;

	stringstream toPrint;
	string question;

	//get two values for numbers to compute.

	num1 = (rand() % 30) + 2;
	if(num1 > 12)
		num2 = (rand() % 11) + 2;
	else
		num2 = (rand() % 30) + 2;


	divisor1 = pow(10.0, (rand() % 3)); divisor2 = divisor1*pow(10.0, (rand() % 3)-1); // get divisor, second close to first.

	num1 = num1/divisor1; //get real values for numbers.
	num2 = num2/divisor2; //get real values for numbers.

	if (rand() % 2 == 0)
		num1 = -num1;
	else{}

	if (rand() % 2 == 0)
		num2 = - num2;
	else{}

	multOrDiv = (rand() % 2);

	if (multOrDiv == 1){ //multiplication
		//determine unknown
		unknLoc = rand() % 3;

		if(unknLoc == 0){ // ... x num1 = num2
			answer = num1;
			num1 = num2;
			num2 = answer*num1;
			toPrint << "... x " << num1 << " = " << num2;
		}
		else if(unknLoc == 1){ // num1 x ... = num2
			answer = num2;
			num2 = num1*answer;
			toPrint << num1 << " x ... " << "= " << num2;
		}
		else{ // num1 x num2 = ...
			answer = num1*num2;
			toPrint << num1 << " x " << num2 << " = ...";
		}
	}

	else{ //division
		unknLoc = rand() % 3;

		if(unknLoc == 0){ // ... / num1 = num2
			answer = num1*num2;
			toPrint << "... : " << num1 << " = " << num2;
		}
		else if(unknLoc == 1){ // num1 : ... = num2 (num1 = num2*...)
			answer = num2;
			num2 = num1;
			num1 = num2*answer;
			toPrint << num1 << " : ... " << " = " << num2;
		}
		else{ // num1 / num2 = ...
			answer = num2;
			num2 = num1;
			num1 = num2*answer;
			toPrint << num1 << " : " << num2 << " = ...";
		}
	}

	answerS = returnSimple(answer, divisor1);

	toPrint.seekg(0);
	getline(toPrint, question);

	allQuestions.push_back(new questionDouble(questionNum, question, answer));

	cout << question << endl << endl;

	return answerS;
}

vector<string> fractAdd(vector<questionInfo*>&allQuestions, int questionNum, string& answer){

	vector<string>answerS;

	stringstream toPrint;
	string question;

	if (rand() % 2 == 0){ //normal fraction additions and divisions.

		int nume1 = 0;
		int nume2 = 0;
		int ansNume  = 0; //contains answer numerator
		int denom1 = 0;
		int denom2 = 0; //has to be computed from denom1
		int ansDenom = 0; //contains answer denominator
		int commonDivisor1 = 0;
		int commonDivisor2 = 0;
		double unknLoc = 0;


		//get the two commonDivisors

		commonDivisor1 = (rand() % 11) + 2;
		if(commonDivisor1 > 4)
			commonDivisor2 = (rand() % 4) + 2;
		else
			commonDivisor2 = (rand() % 11) + 2;

		nume1 = (rand() % 7) + 1;
		while (nume2 == 0 || nume2 == nume1) //nume1 and nume2 must be different to avoid answer = 0
			nume2 = (rand() % 7) + 1;
		denom1 = (rand() % 7) + 1;
		denom2 = denom1;

		if (rand() % 2 == 0) //not allowing minus signs to denominators (too ugly on output)
			nume1 = -nume1;
		else{}

		if (rand() % 2 == 0)
			nume2 = - nume2;
		else{}

		int oSnume1 = nume1 * commonDivisor1; // on screen numbers
		int oSdenom1 = denom1 *commonDivisor1;
		int oSnume2  = nume2 * commonDivisor2;
		int oSdenom2 = denom2*commonDivisor2; //simplifiable to same denominator

		bool multOrDiv = (rand() % 2);

		//bogus multiplier used in ansDenom and ansNume to make the answer less obvious, as in real test.
		const int bogMult = (rand() % 5) + 1;

		ansDenom = denom1*bogMult; //ansNume also has to be multiplied by bogMult.

		if (multOrDiv == 1){ //addition
			//determine unknown
			unknLoc = rand() % 3;

			if(unknLoc == 0){ // ... + nume1/denom1 = nume2/denom2 => (nume2/denom2) - (nume1/denom1) = ...
				ansNume = (nume2-nume1)*bogMult;
				toPrint << "... + (" << oSnume1 << "/" << oSdenom1 << ") = (" << oSnume2 << "/" << oSdenom2 << ")";

			}
			else if(unknLoc == 1){ // nume1/denom1 + ... = nume2/denom2 => (nume2/denom2) - (denom1/nume1) = ...
				ansNume = (nume2-nume1)*bogMult;
				toPrint << "(" << oSnume1 << "/" << oSdenom1 << ") + ... = (" << oSnume2 << "/" << oSdenom2 << ")";

			}
			else{ // nume1/denom1 + nume2/denom2 = ...
				ansNume = (nume1+nume2)*bogMult;
				toPrint << "(" << oSnume1 << "/" << oSdenom1 << ") + (" << oSnume2 << "/" << oSdenom2 << ")" << " = ...";
			}
		}

		else{ //subtraction
			unknLoc = rand() % 3;

			if(unknLoc == 0){ // ... - nume1/denom1 = nume2/denom2 => (nume2/denom2) + (nume1/denom1) = ...
				ansNume = (nume1+nume2)*bogMult;
				toPrint << "... - (" << oSnume1 << "/" << oSdenom1 << ") = (" << oSnume2 << "/" << oSdenom2 << ")";
			}
			else if(unknLoc == 1){ // nume1/denom1 - ... = nume2/denom2 => (nume1/denom1) - (nume2/denom2) = ...
				ansNume = (nume1-nume2)*bogMult;
				toPrint << "(" << oSnume1 << "/" << oSdenom1 << ") - ... = (" << oSnume2 << "/" << oSdenom2 << ")";
			}

			else if(unknLoc == 2){ // nume1/denom1 - nume2/denom2 = ...
				ansNume = (nume1-nume2)*bogMult;
				toPrint << "(" << oSnume1 << "/" << oSdenom1 << ") - (" << oSnume2 << "/" << oSdenom2 << ")" << " = ...";
			}
		}

		answerS = returnFract(ansNume, ansDenom, answer);

	}

	else { //fraction addition and divisions with mixed numbers

		int integer1 = 0; //number that will be on screen as is
		int integer2 = 0;  //whole of second number.
		int denom = 0;  //rest of answer has same denom.
		int restNume  = 0;
		int ansInteger = 0; //contains whole of answer
		int ansRestNume = 0; //contains answer numerator for rest
		double unknLoc = 0;


		integer1 = (rand() % 89) + 11;
		//we note, there are no negative mixed numbers in test that I know of.
		integer2 = (rand() % 9) + 1;
		denom = (rand() % 7) + 3;
		restNume = (rand() % (denom-1)) + 1; //number from 1 to restDenom-1


		int oSnume = (integer2*denom) + restNume; //on screen numerator

		bool multOrDiv = (rand() % 2);


		if (multOrDiv == 1){ //addition
			//determine unknown
			unknLoc = rand() % 3;

			if(unknLoc == 0){ // ... + oSnume/denom = integer1 => integer1 - (integer2 restNume/restDenom) =...
				ansInteger = integer1 - (integer2 + 1); //because of rest
				ansRestNume = denom - restNume;
				toPrint << "... + (" << oSnume << "/" << denom << ") = " << integer1;

			}
			else if(unknLoc == 1){ // oSnume/denom + ... = integer1 => integer1 - (integer2 restNume/restDenom) =...
				ansInteger = integer1 - (integer2 + 1); //because of rest
				ansRestNume = denom - restNume;
				toPrint << "(" << oSnume << "/" << denom << ") + ... = " << integer1;

			}
			else{ // oSnume/denom + integer1 = ... => integer1 + (integer2 restNume/restDenom) =...
				ansInteger = integer1 + integer2;
				ansRestNume = restNume;
				toPrint << "(" << oSnume << "/" << denom << ") + " << integer1 << "  = ...";
			}
		}

		else{ //subtraction
			unknLoc = rand() % 3;

			if(unknLoc == 0){ // ... - oSnume/denom = integer1 => integer1 + (integer2 restNume/restDenom) =...
				ansInteger = integer1 + integer2;
				ansRestNume = restNume;
				toPrint << "... - (" << oSnume << "/" << denom << ") = " << integer1;

			}
			else if(unknLoc == 1){ // integer1 - ... = oSnume/denom => integer1 - (integer2 restNume/restDenom) =...
				ansInteger = integer1 - (integer2 + 1); //because of rest
				ansRestNume = denom - restNume;
				toPrint << integer1 << " - ..." << " = (" << oSnume << "/" << denom << ")";

			}
			else{ // integer1 - oSnume/denom = ... => integer1 - (integer2 restNume/restDenom) =...
				ansInteger = integer1 - (integer2 + 1); //because of rest
				ansRestNume = denom - restNume;
				toPrint << integer1 << " - " << "(" << oSnume << "/" << denom << ") = ...";
			}
		}

		answerS = returnMixedFract(ansRestNume, denom, ansInteger, answer);

	}

	toPrint.seekg(0);
	getline(toPrint, question);

	allQuestions.push_back(new questionString(questionNum, question, answer));

	cout << question << endl << endl;

	return answerS;

}

vector<string> fractMult(vector<questionInfo*>&allQuestions, int questionNum, string& answer){
	int nume1 = 0;
	int nume2 = 0;
	int ansNume  = 0; //conains answer numerator
	int denom1 = 0;
	int denom2 = 0;
	int ansDenom = 0; //contains answer denominator
	int commonDivisor1 = 0;
	int commonDivisor2 = 0;
	int multWhat = 0; // what to multiply by common divisor
	bool multOrDiv = 0;
	double unknLoc = 0;
	vector<string>answerS;

	stringstream toPrint;
	string question;

	//get two values for numbers to compute.

	commonDivisor1 = (rand() % 15) + 2;
	if(commonDivisor1 > 4)
		commonDivisor2 = (rand() % 4) + 2;
	else
		commonDivisor2 = (rand() % 15) + 2;

	if (commonDivisor1 > 12 || commonDivisor2 > 12){ //if divisors are big, numbers are small
		nume1 = (rand() % 4) + 1;
		nume2 = (rand() % 4) + 1;
		denom1 = (rand() % 4) + 1;
		denom2 = (rand() % 4) + 1;
	}
	else{ //give lightly larger random numbers to 4 terms
		nume1 = (rand() % 6) + 1;
		nume2 = (rand() % 6) + 1;
		denom1 = (rand() % 6) + 1;
		denom2 = (rand() % 6) + 1;
	}


	if (rand() % 2 == 0) //not allowing minus signs to denominators (too ugly on output)
		nume1 = -nume1;
	else{}

	if (rand() % 2 == 0)
		nume2 = - nume2;
	else{}

	multOrDiv = (rand() % 2);
	multWhat = rand() % 4;

	if (multOrDiv == 1){ //multiplication
		//determine unknown
		unknLoc = rand() % 3;

		if(unknLoc == 0){ // ... x nume1/denom1 = nume2/denom2 => (nume2/denom2) * (denom1/nume1) = ...
			ansNume = nume2 * denom1;
			ansDenom = denom2 * nume1;
			if(multWhat == 0){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			else if (multWhat == 1){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 2){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 3){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			toPrint << "... x (" << nume1 << "/" << denom1 << ") = (" << nume2 << "/" << denom2 << ")";
		}
		else if(unknLoc == 1){ // nume1/denom1 x ... = nume2/denom2 => (nume2/denom2) * (denom1/nume1) = ...
			ansNume = nume2 * denom1;
			ansDenom = denom2 * nume1;
			if(multWhat == 0){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			else if (multWhat == 1){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 2){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 3){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			toPrint << "(" << nume1 << "/" << denom1 << ") x ... = (" << nume2 << "/" << denom2 << ")";

		}
		else{ // nume1/denom1 x nume2/denom2 = ...
			ansNume = nume1 * nume2;
			ansDenom = denom1 * denom2;
			if(multWhat == 0){
				nume1 *= commonDivisor1; nume2 *= commonDivisor2;
				denom1 *= commonDivisor2; denom2 *= commonDivisor1;
			}

			else if (multWhat == 1){
				nume1 *= commonDivisor2; nume2 *= commonDivisor1;
				denom1 *= commonDivisor1; denom2 *= commonDivisor2;
			}

			else if (multWhat == 2){
				nume1 *= commonDivisor1; nume2 *= commonDivisor2;
				denom1 *= commonDivisor1; denom2 *= commonDivisor2;
			}

			else if (multWhat == 3){
				nume1 *= commonDivisor2; nume2 *= commonDivisor1;
				denom1 *= commonDivisor2; denom2 *= commonDivisor1;
			}

			toPrint << "(" << nume1 << "/" << denom1 << ") x (" << nume2 << "/" << denom2 << ")" << " = ...";
		}
	}

	else{ //division
		unknLoc = rand() % 3;

		if(unknLoc == 0){ // ... / nume1/denom1 = nume2/denom2 => (nume2/denom2) * (nume1/denom1) = ...
			ansNume = nume1 * nume2;
			ansDenom = denom1 * denom2;
			if(multWhat == 0){
				nume1 *= commonDivisor1; nume2 *= commonDivisor2;
				denom1 *= commonDivisor2; denom2 *= commonDivisor1;
			}

			else if (multWhat == 1){
				nume1 *= commonDivisor2; nume2 *= commonDivisor1;
				denom1 *= commonDivisor1; denom2 *= commonDivisor2;
			}

			else if (multWhat == 2){
				nume1 *= commonDivisor1; nume2 *= commonDivisor2;
				denom1 *= commonDivisor1; denom2 *= commonDivisor2;
			}

			else if (multWhat == 3){
				nume1 *= commonDivisor2; nume2 *= commonDivisor1;
				denom1 *= commonDivisor2; denom2 *= commonDivisor1;
			}

			toPrint << "... : (" << nume1 << "/" << denom1 << ") = (" << nume2 << "/" << denom2 << ")";
		}
		else if(unknLoc == 1){ // nume1/denom1 / ... = nume2/denom2 => (denom2/nume2) * (nume1/denom1) = ...
			ansNume = denom2 * nume1;
			ansDenom = nume2 * denom1;
			if(multWhat == 0){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			else if (multWhat == 1){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 2){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 3){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			toPrint << "(" << nume1 << "/" << denom1 << ") : ... = (" << nume2 << "/" << denom2 << ")";
		}

		else if(unknLoc == 2){ // nume1/denom1 / nume2/denom2 = ... => (denom2/nume2) * (nume1/denom1) = ...
			ansNume = denom2 * nume1;
			ansDenom = nume2 * denom1;
			if(multWhat == 0){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			else if (multWhat == 1){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 2){
				nume2 *= commonDivisor1; denom1 *= commonDivisor2;
				denom2 *= commonDivisor1; nume1 *= commonDivisor2;
			}

			else if (multWhat == 3){
				nume2 *= commonDivisor2; denom1 *= commonDivisor1;
				denom2 *= commonDivisor2; nume1 *= commonDivisor1;
			}

			toPrint << "(" << nume1 << "/" << denom1 << ") : (" << nume2 << "/" << denom2 << ")" << " = ...";
		}
	}

	answerS = returnFract(ansNume, ansDenom, answer);

	toPrint.seekg(0);
	getline(toPrint, question);

	allQuestions.push_back(new questionString(questionNum, question, answer));

	cout << question << endl << endl;

	return answerS;
}

vector<double> returnSimple(double corrAnswer, double divisor){

	vector<double>answers(4);
	unsigned int i;
	int bogAnswerType;
	double bogAnswer = 0; //saves bogus answer
	double corrPos = 0;
	double divisor1 = pow(10.0, (rand() % 2)+1);

	for (i = 0; i < answers.size(); ++i){ //get all wrong value in vector

		bogAnswer = 0;
		while ((bogAnswer == 0) || (find(answers.begin(), answers.end(), bogAnswer) != answers.end())
				|| (bogAnswer == corrAnswer)){ //answer already input



			if((corrAnswer < 0.1 && corrAnswer > 0.0)
					|| (corrAnswer > -0.1 && corrAnswer < 0.0)){ //absolute value of answer is small

			}

			bogAnswerType = (rand() % 5);
			divisor1 = pow(10.0, (rand() % 2)+1);
			if ((bogAnswerType == 0) && ((corrAnswer < 0.1 && corrAnswer > 0.0)
					|| (corrAnswer > -0.1 && corrAnswer < 0.0))){
				if(rand() % 2 == 0)
					bogAnswer = (corrAnswer + ((rand() % 5)+1)/divisor)/divisor1;
				else
					bogAnswer = -(corrAnswer + ((rand() % 9)+1)/divisor)/divisor1;
			}
			else if (bogAnswerType == 1 && ((corrAnswer < 0.1 && corrAnswer > 0.0)
					|| (corrAnswer > -0.1 && corrAnswer < 0.0))){
				if(rand() % 2 == 0)
					bogAnswer = (corrAnswer - ((rand() % 5)+1)/divisor)/divisor1;
				else
					bogAnswer = -(corrAnswer - ((rand() % 5)+1)/divisor)/divisor1;
			}
			else if (bogAnswerType == 2){ //induce in error.

				if(rand() % 3 == 0 && ((corrAnswer < 0.1 && corrAnswer > 0.0)
						|| (corrAnswer > -0.1 && corrAnswer < 0.0))){
					if(rand() % 2 == 0)
						bogAnswer = corrAnswer/divisor1;
					else
						bogAnswer = -corrAnswer/divisor1;
				}
				else if(rand() % 2  == 0 && ((corrAnswer < 0.1 && corrAnswer > 0.0)
						|| (corrAnswer > -0.1 && corrAnswer < 0.0))){
					if(rand() == 0)
						bogAnswer = corrAnswer*divisor1;
					else
						bogAnswer = -corrAnswer*divisor1;
				}
				else
					if (rand() % 3 == 0) // so that it doesn't occur too often
						bogAnswer = -corrAnswer;
			}
			else if (bogAnswerType == 3){
				if(rand() % 2 == 0)
					bogAnswer = corrAnswer + ((rand() % 5)+1)/divisor;
				else
					bogAnswer = -(corrAnswer + ((rand() % 5)+1)/divisor);
			}
			else{
				if(rand() % 2 == 0)
					bogAnswer = corrAnswer - ((rand() % 5)+1)/divisor;
				else
					bogAnswer = -(corrAnswer - ((rand() % 5)+1)/divisor);
			}
		}
		answers[i] = bogAnswer;

	}

	corrPos = rand() % 4; //position between 1 and 4

	if (corrPos == 0)
		answers[0] = corrAnswer;
	else if (corrPos ==1)
		answers[1] = corrAnswer;
	else if (corrPos == 2)
		answers[2] = corrAnswer;
	else
		answers[3] = corrAnswer;

	return answers;


}

vector<string> returnFract(int ansNume, int ansDenom, string& stringAnswer){


	vector<string>answers(4);
	unsigned int i;

	stringstream wAToPrint; //wrong answer to print
	string bogAnswer;
	int bogAnswerType;

	if (ansDenom < 0){ //to make it more readable
		ansDenom = -ansDenom;
		ansNume = -ansNume;
	}
	else{}

	wAToPrint << ansNume << "/" << ansDenom << endl;
	getline(wAToPrint, stringAnswer);

	for (i = 0; i < answers.size(); ++i){ //get all wrong value in vector
		bogAnswer = "\0";
		while ((bogAnswer == "\0") || (find(answers.begin(), answers.end(), bogAnswer) != answers.end())
				|| (bogAnswer == stringAnswer)){ //answer already input
			wAToPrint.str("\0"); //replace what is in wAToPrint with the null string
			wAToPrint.clear();
			if (ansDenom < 0){ //reset signs to assure cohesion
				ansDenom = -ansDenom;
				ansNume = -ansNume;
			}
			bogAnswerType = (rand() % 4);
			if (bogAnswerType == 0){ //inverse numerator and denominator
				if(rand() % 2 == 0){
					if (ansNume != ansDenom){
						if (ansNume < 0){ //cohesion again
							ansDenom = -ansDenom;
							ansNume = -ansNume;
						}
						wAToPrint << ansDenom << "/" << ansNume << endl;
					}
					else
						if (ansDenom > 5)
							wAToPrint << ansNume +((rand() % 5) + 1) << "/" << ansDenom - ((rand() % 5) + 1) << endl;

				}
				else{
					if (ansNume != ansDenom){
						if (ansNume < 0){ //cohesion again
							ansDenom = -ansDenom;
							ansNume = -ansNume;
						}
						else{}
						wAToPrint << -ansDenom << "/" << ansNume << endl;
					}
					else
						if(ansNume > 5)
							wAToPrint << ansNume -((rand() % 5) + 1) << "/" << ansDenom +((rand() % 5) + 1)<< endl;
				}

			}
			else if (bogAnswerType == 1){
				if(rand() % 2 == 0){
					if ((ansNume > 5) || (ansNume < -5)){
						if (ansNume < 0){
							ansDenom = -ansDenom;
							ansNume = -ansNume;
						}
						if (ansDenom > 0) //look at what absolute values do to understand why condition.
							wAToPrint << ansDenom +((rand() % 5) + 1) << "/" << ansNume - ((rand() % 5) + 1) << endl;
						else
							wAToPrint << ansDenom -((rand() % 5) + 1) << "/" << ansNume - ((rand() % 5) + 1) << endl;
					}
					else
						wAToPrint << ansNume *((rand() % 5) + 1) << "/" << ansDenom *((rand() % 4) + 6) << endl;
				}
				else{
					if (ansNume < 0)
						wAToPrint << -ansNume +((rand() % 2) + 1) << "/" << ansDenom +((rand() % 5) + 1)<< endl;
					else
						wAToPrint << -ansNume -((rand() % 5) + 1) << "/" << ansDenom +((rand() % 5) + 1)<< endl;
				}

			}
			else if (bogAnswerType == 2){ //induce in error.
				if(rand() % 2 == 0)
					wAToPrint << -ansNume *((rand() % 5) + 1) << "/" << ansDenom *((rand() % 4) + 6) << endl;
				else{
					if (ansDenom > 5){
						if (ansNume < 0){
							ansDenom = -ansDenom;
							ansNume = -ansNume;
							if(ansDenom < 0)
								wAToPrint << ansDenom + ((rand() % 5) + 1) << "/" << ansNume + ((rand() % 5) + 1) << endl; //if negative/positive
							else
								wAToPrint << ansDenom - ((rand() % 5) + 1) << "/" << ansNume + ((rand() % 5) + 1) << endl; //if positive/positive
						}

					}
					else
						wAToPrint << ansNume *((rand() % 5) + 6) << "/" << ansDenom *((rand() % 5) + 1) << endl;
				}
			}
			else if (bogAnswerType == 3){
				if(rand() % 2 == 0){
					if (ansNume != ansDenom){
						if (ansNume < 0){
							ansDenom = -ansDenom;
							ansNume = -ansNume;
						}
					wAToPrint << -ansDenom *((rand() % 5) + 3) <<"/" <<  ansNume + 1 << endl;
					}
				}
				else{
					if (ansNume != ansDenom){
						if (ansNume < 0){
							ansDenom = -ansDenom;
							ansNume = -ansNume;
						}
					wAToPrint << ansDenom *((rand() % 5) + 1) << "/" << ansNume *((rand() % 4) + 6) << endl;
					}
				}
			}


			getline(wAToPrint, bogAnswer);
		}
		answers[i] = bogAnswer;
	}


	int corrPos = rand() % 4; //position between 1 and 4

	if (corrPos == 0)
		answers[0] = stringAnswer;
	else if (corrPos ==1)
		answers[1] = stringAnswer;
	else if (corrPos == 2)
		answers[2] = stringAnswer;
	else
		answers[3] = stringAnswer;


	return answers;


}

vector<string> returnMixedFract(int ansNume, int ansDenom, int ansInteger, string& stringAnswer){


	vector<string>answers(4);
	unsigned int i;

	stringstream wAToPrint; //wrong answer to print
	string bogAnswer;
	int bogAnswerType;

	wAToPrint << ansInteger << " " << ansNume << "/" << ansDenom << endl;
	getline(wAToPrint, stringAnswer);

	for (i = 0; i < answers.size(); ++i){ //get all wrong value in vector
		bogAnswer = "\0";
		while ((bogAnswer == "\0") || (find(answers.begin(), answers.end(), bogAnswer) != answers.end())
				|| (bogAnswer == stringAnswer)){ //look for actual new wrong answer
			wAToPrint.str("\0"); //replace what is in wAToPrint with the null string
			wAToPrint.clear(); //clear potential bad of failbit
			bogAnswerType = (rand() % 3);
			if (bogAnswerType == 0){
				if(rand() % 2 == 0){ //ansDenom - ansNume
					if(ansDenom/ansNume != 2)
						wAToPrint << ansInteger << " " << ansDenom-ansNume << "/" << ansDenom << endl;
				}

				else{
					if (rand() % 2 == 0){ //rest stays correct. larger whole number
						wAToPrint << ansInteger + (rand() % 5) + 1 << " " << ansNume << "/" << ansDenom << endl;
					}
					else{ //rest stays correct. Smaller whole number
						if(ansInteger > 5)
							wAToPrint << ansInteger - (rand() % 5) + 1 << " " << ansNume << "/" << ansDenom << endl;
						else
							wAToPrint << ansInteger - (rand() % ansInteger) + 1 << " " << ansNume << "/" << ansDenom << endl;
					}

				}

			}
			else if ((bogAnswerType == 1) && (ansDenom - ansNume > 1)){ //larger rest (only if possible)
				if(rand() % 2 == 0) //smaller whole, larger rest
					if(ansInteger > 5){
						wAToPrint << ansInteger - (rand() % 5) + 1 << " "
						<< ansNume + ((rand() % (ansDenom-ansNume)-1) + 1) << "/" << ansDenom << endl;
					}
					else
						wAToPrint << ansInteger - (rand() % ansInteger) + 1 << " "
						<< ansNume + (rand() % (ansDenom-ansNume)-1) + 1 << "/" << ansDenom << endl;
				else //larger whole, larger rest
					wAToPrint << ansInteger + (rand() % 5) + 1 << " "
					<< ansNume + ((rand() % (ansDenom-ansNume)-1) + 1) << "/" << ansDenom << endl;

			}
			else if ((bogAnswerType == 2) && (ansNume > 1)){
				if(rand() % 2 == 0) //smaller whole, smaller rest
					if(ansInteger > 5)
						wAToPrint << ansInteger - (rand() % 5) + 1 << " "
						<< ansNume - ((rand() % (ansNume)-1) + 1) << "/" << ansDenom << endl;
					else
							wAToPrint << ansInteger - (rand() % ansInteger) + 1 << " "
							<< ansNume - (rand() % (ansNume)-1) + 1 << "/" << ansDenom << endl;
				else //larger whole, smaller rest
						wAToPrint << ansInteger + (rand() % 5) + 1 << " "
						<< ansNume - ((rand() % (ansNume)-1) + 1) << "/" << ansDenom << endl;
			}

			getline(wAToPrint, bogAnswer);
		}
		answers[i] = bogAnswer;
	}


	int corrPos = rand() % 4; //position between 1 and 4

	if (corrPos == 0)
		answers[0] = stringAnswer;
	else if (corrPos ==1)
		answers[1] = stringAnswer;
	else if (corrPos == 2)
		answers[2] = stringAnswer;
	else
		answers[3] = stringAnswer;


	return answers;


}


