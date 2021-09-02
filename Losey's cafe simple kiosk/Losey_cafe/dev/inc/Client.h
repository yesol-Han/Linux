#ifndef CLIENT_H
#define CLIENT_H
#include "../inc/Manager.h"
#include <string>
using namespace std;

class Client {
	int people = 1;					//Count People for giveCoupon event.
public:
	bool order();
};

#endif
