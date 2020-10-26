#pragma once
#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H
#include <string>

namespace {

	template <typename Iter>
	Iter next_iteration(Iter iter)
	{
		return ++iter;
	}

	template <typename T>
	bool concatenate_list(std::list <T> list_a, std::list <T> &list_b) {
		std::list<T>::iterator it;
		for (it = list_a.begin(); it != list_a.end(); ++it) {
			list_b.push_back(*it)
		}
		return true;
	}

	template <typename T>
	void reverse_list(std::list <T> &list_a) {
		list_a.reverse();
	}

	bool concatenate_reverse_list(std::list <Point*> &list_a) {
		Point* new_input;
		std::list <Point*> list_b;
		for (std::list<Point*>::reverse_iterator rit = list_a.rbegin(); rit != list_a.rend(); ++rit){
			new_input = new Point();
			new_input->set_x((*rit)->x());
			new_input->set_y((*rit)->y());
			new_input->set_z((*rit)->z());
			list_b.push_back(new_input);
		}

		for (std::list<Point*>::iterator it = list_b.begin(); it != list_b.end(); ++it) {
			list_a.push_back(*it);
		}
		return true;
	}
	
	std::string double_to_string(double input) {
		std::ostringstream strs;
		strs << input;
		std::string str = strs.str();
		return str;
	}

	std::string delSpaces(std::string &str)
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
		return str;
	}

	std::string split_string_by_delemeter(std::string sentence, char del, int possition) {
		std::string empty = " ";
		try {
			if (sentence.back() == ':') {
				return empty;
			}
			std::istringstream iss(sentence);
			std::vector<std::string> tokens;
			std::string token;
			while (std::getline(iss, token, del)) {
				if (!token.empty())
					tokens.push_back(token);
			}
			return delSpaces(tokens[possition]);
		}
		catch (std::exception e) {
			return empty;
		}
	}

		

}

#endif