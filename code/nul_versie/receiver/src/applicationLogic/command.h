//
// Created by endargon on 10/26/16.
//

#ifndef CODE_COMMAND_H
#define CODE_COMMAND_H

#include "../../../libs/hwlib/hwlib.hpp"
#include "../../../libs/rtos/rtos.hpp"

/**
 * \Class Command
 * \brief Command that handles decoding and encoding of the IR commands
 * This class can be instantiated with a short
 * If this happens it will automatically decode the short into readable data like the sender and the actual data
 *
 * It will also generate en validate checksums for the commands
 */
class Command {
    /** \brief  the sender of the command **/
    int sender;
    /** \brief  the actual data part of the command **/
    int data;
    /** \brief If the command decoded successfully */
    bool error = false;

    /**
     * \brief decodes short into sender and data
     * Takes the short bits and reads them like binary in MSB
     * The protocol is defined at https://cursussen.sharepoint.hu.nl/fnt/36/TCTI-V2THDE-16/Studiemateriaal/V2THDE%20-%20Casus%20lasertag%202016-2017.pdf PAGE 4
     *
     * from left to right the first bit is the start bit
     * Then the next 5 bits is the actual sender ID
     * After that the next 5 bits is the actual data part.
     * The remaining bits become the checksum
     */
    void decode(short bits);

    /**
     * \brief Validates the checksum of the given bits
     * The last 5 bits become the checksum
     * The checksum is valid when the XOR of the first till last bit from the id and the first til last bit from the data are equal to the first bit of the checksum.
     *
     * Example       ID    DATA CHECKSUM
     *            1 00100 10100 10000
     * 00100
     * 10100 XOR
     * 10000
     *
     */
    bool valid_checksum(short bits);;

public:
    /**
     * /brief helper that prints out a decoded version and encoded version of the command
     */
    void print_command();

    /**
     * \brief Takes the sender and data and turns it into a short encoded with the data
     * Adds a startbit to a 0 initialized short
     *
     * Decodes the int from sender into a binary value and adds it next to the short startbit
     *
     * Decodes the int from the data into binary value and add it next to the short sender bits
     *
     * Generates a checksum based on the binary XOR of sender and data and add it nex to the short data bits
     *
     * Checksum generation sources https://cursussen.sharepoint.hu.nl/fnt/36/TCTI-V2THDE-16/Studiemateriaal/V2THDE%20-%20Casus%20lasertag%202016-2017.pdf
     */
    short encode();

    /**
     * \brief  returns error value
     */
    bool get_error();

    /**
     * \brief  returns the sender value
     */
    int get_sender();

    /**
     * \brief  sets sender value
     */
    void set_sender(int sender);

    /**
     * \brief  returns the data value
     */
    int get_data();

    /**
     * \brief  sets the data value
     */
    void set_data(int data);

    /**
     * \brief empty constructor for Command
     * Empty constructor that initializes sender and data with -1
     */
    Command();

    /**
     * \brief Constructor with short decode the bits param into logical sender and data values
     * \param bits The short that will be decoded into usable data
     */
    Command(short bits) {
        decode(bits);
    }

    /**
     * \brief Constructor that takes a data and a sender
     * \param sender the sender part of the command
     * \param data the data part of the command
     */
    Command(int sender, int data);
};

#endif //CODE_COMMAND_H
