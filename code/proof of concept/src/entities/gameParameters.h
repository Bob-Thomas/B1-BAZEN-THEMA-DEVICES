//
// Created by robbie on 9-11-2016.
//

#ifndef CODE_GAMEPARAMETERS_H
#define CODE_GAMEPARAMETERS_H

// struct for shot taken information.
// each shot can be registered in an array.

struct receive_shot {
    int player_id;
    int weapon_id;

};

class GameParameters {
private:

    // i hope everybody dies at 20 shots in a game...
    int shots_taken;
    receive_shot shots[20];

public:

    GameParameters();

    //add shot to array
    void add_recieved_shot(int player_id, int weapon_id);

    // player information
    int id;
    int health;
    int weapon;
};


#endif //CODE_GAMEPARAMETERS_H
