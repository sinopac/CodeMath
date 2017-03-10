#include "stdafx.h"
#include "iostream"
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>


int totalTry = 0;

int getSum(std::vector<int> scores)
{
	int total = 0;

	for (int i = 0; i < scores.size(); i++)
		total = total + scores.at(i);

	return total;
}

std::vector<int> GetPossibleScores(std::vector<int> currentScores)
{
	std::vector<int> allScores = { 1, 2, 3, 4, 6, 7, 8, 9, 10 };
	std::set<int> set1(allScores.begin(), allScores.end());
	std::set<int> set2(currentScores.begin(), currentScores.end());
	std::vector<int> availableScores;
	std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(availableScores));

	return availableScores;
}

void printAnswer(std::vector<int> scores)
{
	int total = 5;
	for each (int s in scores)
	{
		total = total + s;
		std::cout << s + 90 << ", ";
	}
	std::cout << "95" << '\n';
}

bool verify1(std::vector<int> scores, int nextScore)
{
	totalTry++;

	// tn != 5
	if (nextScore == 5) return false;

	// t1 != t2 != t3 != t4 != t5 != t6
	for (int i = 0; i < scores.size(); i++) {
		if (nextScore == scores.at(i))
			return false;
	}

	// the average of test scores is an integer
	int sum = getSum(scores);
	bool isAvgInt = (sum + nextScore) % (scores.size() + 1) == 0;

	return isAvgInt;
}

std::vector<int> verify2(std::vector<int> scores, int nextScore)
{
	totalTry++;

	// tn != 5
	if (nextScore == 5) return std::vector<int>();

	// t1 != t2 != t3 != t4 != t5 != t6
	for (int i = 0; i < scores.size(); i++)
		if (nextScore == scores.at(i)) return std::vector<int>();

	// the average of test scores is an integer
	scores.push_back(nextScore);
	int sum = getSum(scores);
	bool isAvgInt = sum % scores.size() == 0;
	return isAvgInt ? scores : std::vector<int>();
}

void ExhaustTry1()
{
	for (int t1 = 1; t1 <= 10; t1++) {
		for (int t2 = 1; t2 <= 10; t2++) {
			if (t1 != 5 && t2 != 5 && t1 != t2 && (t1 + t2) % 2 == 0) {
				for (int t3 = 1; t3 <= 10; t3++) {
					if (t3 != 5 && t3 != t2 && t3 != t1 && (t1 + t2 + t3) % 3 == 0) {
						for (int t4 = 1; t4 <= 10; t4++) {
							if (t4 != 5 && t4 != t3 && t4 != t2 && t4 != t1 && (t1 + t2 + t3 + t4) % 4 == 0) {
								for (int t5 = 1; t5 <= 10; t5++) {
									if (t5 != 5 && t5 != t4 && t5 != t3 && t5 != t2 && t5 != t1 && (t1 + t2 + t3 + t4 + t5) % 5 == 0) {
										for (int t6 = 1; t6 <= 10; t6++) {
											if (t6 != 5 && t6 != t5 && t6 != t4 && t6 != t3 && t6 != t2 && t6 != t1 && (t1 + t2 + t3 + t4 + t5 + t6) % 6 == 0) {
												if ((t1 + t2 + t3 + t4 + t5 + t6 + 5) % 7 == 0)
													std::cout << t1 + 90 << ", " << t2 + 90 << ", " << t3 + 90 << ", " << t4 + 90 << ", " << t5 + 90 << ", " << t6 + 90 << ", 95" << '\n';
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void ExhaustTry2()
{
	for (int t1 = 1; t1 <= 10; t1++) {
		if (verify1({}, t1)) {
			for (int t2 = 1; t2 <= 10; t2++) {
				if (verify1({ t1 }, t2)) {
					for (int t3 = 1; t3 <= 10; t3++) {
						if (verify1({ t1, t2 }, t3)) {
							for (int t4 = 1; t4 <= 10; t4++) {
								if (verify1({ t1, t2, t3 }, t4)) {
									for (int t5 = 1; t5 <= 10; t5++) {
										if (verify1({ t1, t2, t3, t4 }, t5)) {
											for (int t6 = 1; t6 <= 10; t6++) {
												if (verify1({ t1, t2, t3, t4, t5 }, t6)) {
													if ((t1 + t2 + t3 + t4 + t5 + t6 + 5) % 7 == 0)
														std::cout << t1 + 90 << ", " << t2 + 90 << ", " << t3 + 90 << ", " << t4 + 90 << ", " << t5 + 90 << ", " << t6 + 90 << ", 95" << '\n';
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void ExhaustTry(std::vector<int> scores)
{
	for (int t = 1; t <= 10; t++) {
		std::vector<int> newscores = verify2(scores, t);
		if (newscores.size() == 6) {
			int s = getSum(newscores);
			if ((s + 5) % 7 == 0)
				printAnswer(newscores);
		}
		else if (newscores.size() != 0) {
			ExhaustTry(newscores);
		}
	}
}

void SmartTry(std::vector<int> scores)
{
	std::vector<int> possibleScores = GetPossibleScores(scores);

	for each (int s in possibleScores) {
		std::vector<int> newscores = verify2(scores, s);
		if (newscores.size() == 6) {
			int s = getSum(newscores);
			if ((s + 5) % 7 == 0)
				printAnswer(newscores);
		}
		else if (newscores.size() != 0) {
			SmartTry(newscores);
		}
	}
}

int main() {
	std::cout << "ExhaustTry:" << '\n';
	ExhaustTry({});
	std::cout << "Total try: " << totalTry << '\n';

	totalTry = 0;
	std::cout << '\n' << "SmartTry:" << '\n';
	SmartTry({});
	std::cout << "Total try: " << totalTry << '\n';

	return 0;
}

