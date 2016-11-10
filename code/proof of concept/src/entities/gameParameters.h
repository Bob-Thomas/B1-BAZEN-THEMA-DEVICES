//
// Created by robbie on 9-11-2016.
//

#ifndef CODE_GAMEPARAMETERS_H
#define CODE_GAMEPARAMETERS_H

// struct for shot taken information.
// each shot can be registered in an array.

/**
 * \struct receive_shot
 * \brief receive_shot structure. Will be used for class GameParameters. Each structure contains the player id and weapon id from the received hit
 */

struct receive_shot {
    /**
     * play id from the received hit
     */
    int player_id;
    /**
     * weapon id from the received hit
     */
    int weapon_id;

};


/**
 * \class GameParameters
 * \brief GameParameters entity object will contain the player data.
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
    void add_received_shot(int player_id, int weapon_id);

    /**
     * int player id
     */
    int id;

    /**
     * int health
     */
    int health = 100;

    /**
     * weapon id
     */
    int weapon;

    /**
     * game time
     */
    int game_time;
};


#endif //CODE_GAMEPARAMETERS_H
