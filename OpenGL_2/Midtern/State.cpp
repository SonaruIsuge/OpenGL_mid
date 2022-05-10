
#include "State.h"


State::State(Character* owner)
{
	this->owner = owner;
}

State::~State() 
{
	if(owner != nullptr) delete owner;
}