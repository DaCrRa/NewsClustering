/*
 * NoticiaParser.h
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#ifndef NOTICIAPARSER_H_
#define NOTICIAPARSER_H_

#include <algorithm>

class NoticiaInvalidaException : public std::exception {
public:
	const char* what() const throw() {
		return "No puede instanciarse una noticia a partir de la entrada especificada";
	}
};

class NoticiaParser {
protected:
	std::istream& input;
	std::string stopListFilename;

	// trim from beginning
	inline std::string& ltrim(std::string &s) {
	    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
	            std::not1(std::ptr_fun<int, int>(std::isspace))));
	    return s;
	}

	// trim from end
	inline std::string& rtrim(std::string &s) {
	    s.erase(std::find_if(s.rbegin(), s.rend(),
	            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	    return s;
	}

	// trim from both ends
	inline std::string& trim(std::string &s) {
	    return ltrim(rtrim(s));
	}
public:
	NoticiaParser(std::istream& inputStream, const std::string& stopListFile) :
		input(inputStream),
		stopListFilename(stopListFile) {};
	virtual Noticia parse() = 0;
	virtual ~NoticiaParser() {};
};

#endif /* NOTICIAPARSER_H_ */
