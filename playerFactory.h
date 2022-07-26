#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include <memory>

class Player;

class PlayerFactory {
    
    public:
    std::shared_ptr<Player> generatePlayer(char race);

};

#endif
