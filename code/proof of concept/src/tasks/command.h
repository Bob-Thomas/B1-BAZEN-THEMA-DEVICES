//
// Created by endargon on 10/26/16.
//

#ifndef CODE_COMMAND_H
#define CODE_COMMAND_H
class Command {
    int sender;
    int data;

    char * encode(int sender , int data);
    void decode(char bits[16]);

public:
    int get_sender();
    void set_sender(int sender);
    int get_data();

    void set_data(int data);
    Command(): sender(0), data(0){}
    Command(char bits[16]){
        decode(bits);
    }
    Command(int sender, int data) : sender(sender), data(data){}
};
#endif //CODE_COMMAND_H
