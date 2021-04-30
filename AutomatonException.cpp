#include "AutomatonException.h"


AutomatonException::AutomatonException(const char* msg, const char* file, int line, const char* func, const char* info, const char* stateTry, const char* stateMarked):std::exception(msg){
	this->file = file;
	this->line = line;
	this->func = func;
	this->info = info;
	this->stateTry = stateTry;
	this->stateMarked = stateMarked;
}

const char* AutomatonException::getFile() const{
	return file;
}
int AutomatonException::getLine() const{
	return line;
}
const char* AutomatonException::getFunc() const{
	return func;
}
const char* AutomatonException::getInfo() const{
	return info;
}
const char* AutomatonException::getStateTry() const {
	return stateTry;
}
const char* AutomatonException::getStateMarked() const {
	return stateMarked;
}