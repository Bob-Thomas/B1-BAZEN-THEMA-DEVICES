//
// Created by robbie on 9-11-2016.
//

#ifndef CODE_GAMEPARAMETERS_H
#define CODE_GAMEPARAMETERS_H

// struct for shot taken information.
// each shot can be registered in an array.

/**
 *  receive_shot structure. Will be used for class GameParameters. Each structure contains the player id and weapon id from the received hit
 */
struct receive_shot {
    /**
     * play id from the received hit
     */
    int player_id;
    int weapon_id;

};

/**
 * GameParameters entity object will contain the player data
 */
class GameParameters {
private:

    /**
     * amount of shot taken
     */
    int shots_taken;

    /**
     * received shots array
     */
    receive_shot shots[20];

public:

    /**
     * GameParameter Constructor
     */
    GameParameters();

    /**
     * function to store the received shot data
     * /param player_id int for player id
     * /param weapon_id int for weapon id
     */
    void add_recieved_shot(int player_id, int weapon_id);

    /**
     * int player id
     */
    int id;

    /**
     * int health
     */
    int health;

    /**
     * weapon id
     */
    int weapon;
};


#endif //CODE_GAMEPARAMETERS_H
