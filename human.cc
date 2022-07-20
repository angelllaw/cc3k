#include "human.h"
#include "info.h"
#include <memory>

Human::~Human() {}

Human::Human() : Player(Race::Human, Info{140, 20, 20, 0}) {}

