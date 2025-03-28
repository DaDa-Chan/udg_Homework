#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <random>

using namespace std;

class room{
private:
    string name;
    string description;
    map<string,room*> exits; //map为键值对容器，存放room的出口。出口方向：出口房间的指针
    //int exits_num;
    bool find_Princess;
    bool find_Monster;

public:
    // Constructor
    room(const string& room_Name, const string& room_descp )
        : name(room_Name),description(room_descp),find_Princess(false),find_Monster(false) {}

    // get room's name
    string get_name() const {
        return name;
    }

/*

    int get_exits_num() const{
        return exits_num;
    }
*/
    // Get room's description
    string get_description() const{
        return description;
    }

    //add a exit to ohter room
    void add_exit(const string& direction, room* roomptr){
        exits[direction] = roomptr;
        //exits_num += 1;
    }

    //get all the exits of the room
    vector<string> get_exits() const{
        vector<string> room_exits;
        for (const auto& exit : exits){
            room_exits.push_back(exit.first);//获取键值，即出口
        }
        return room_exits;
    }

    // check if the monster is in the room
    bool check_Monster() const {
        return find_Monster;
    }

    //set the monster
    void set_Monster(bool T){
        find_Monster = T;
    } 

    // check if the princess is in the room
    bool check_princess() const {
        return find_Princess;
    }

    //set the princess
    void set_Princess(bool T){
        find_Princess = T;
    }

    //get into the exit
    room* getin(const string& direction){
        if (exits.find(direction) != exits.end()){
            return exits[direction];
        }
        else return nullptr;
    }

};


class Castle {
private:
    vector<room*> rooms;
    room* cur_room;
    room* lobby;
    bool Princess_found;

public:
    // constructor
    Castle():cur_room(nullptr),lobby(nullptr),Princess_found(false) {
        create_rooms();

        cur_room = lobby;

        random_place();
    }

    //Destructor
    ~Castle(){
        for(room* room : rooms){
            delete room;
        }
    }

    // create all the rooms
    void create_rooms(){

        lobby  = new room("lobby","Welcome to the lobby.");
        rooms.push_back(lobby);

        room*living_room = new room("living_room","Welcome to the living room.");
        rooms.push_back(living_room);

        room* canteen  = new room("canteen","Welcome to the canteen.");
        rooms.push_back(canteen);

        room* kitchen  = new room("kitchen","Welcome to the kitchen.");
        rooms.push_back(kitchen);

        room* cinema  = new room("cinema","Welcome to the cinema.");
        rooms.push_back(cinema);

        room* wareroom  = new room("wareroom","Welcome to the wareroom.");
        rooms.push_back(wareroom);

        room* bedroom = new room("bedroom","Welcome to the bedroom.");
        rooms.push_back(bedroom);

        room* cage = new room("cage","welcome to the cage.");


        //build the map
        lobby->add_exit("east",living_room);
        lobby->add_exit("west",cinema);
        lobby->add_exit("up",bedroom);

        bedroom->add_exit("down",lobby);

        cinema->add_exit("east",lobby);

        living_room->add_exit("west",lobby);
        living_room->add_exit("south",wareroom);
        living_room->add_exit("east",kitchen);

        wareroom->add_exit("north",living_room);

        kitchen->add_exit("west",living_room);
        kitchen->add_exit("down",canteen);

        canteen->add_exit("up",kitchen);
        canteen->add_exit("east",cage);

        cage->add_exit("west",canteen);


    }

    // set Monster and Princess randomly
    void random_place(){
        vector<room*> shuffle_rooms = rooms;
        //use time as seed
        shuffle(shuffle_rooms.begin(),shuffle_rooms.end(),default_random_engine(time(nullptr)));

        //set Monster
        for (room* room : shuffle_rooms) {
            if(room == lobby || room->check_Monster() || room->check_princess() ){
                continue;
            }
            else {
                room->set_Monster(true);
                break;
            }
        }

        //set Princess
        for (room* room : shuffle_rooms) {
            if(room == lobby || room->check_Monster() || room->check_princess() ){
                continue;
            }
            else {
                room->set_Princess(true);
                break;
            }
        }
    }

    //get current location
    room* get_currentroom() const{
        return cur_room;
    }

    //go under command
    bool under_command(const string& command, const string& direction){
        if (command == "go"){
            room* nextroom = cur_room->getin(direction);
            if(nextroom != nullptr){
                cur_room = nextroom;
                return true;
            }
            else{
                cout<< "There is no exit in that direction!" << endl;
            }
        }
        else{
            cout << "Invalid command. plz use 'go <dierection>'." << endl;
        }
        return false;
    }

    //to judge if the princess has been found
    bool princess_is_found() const{
        return Princess_found;
    }

    //if find ,change the state of the Castle
    void set_princess_found(bool T) {
        Princess_found = T;
    }

    bool in_lobby() const{
        return cur_room == lobby;
    }
    
};


class Game{

private:
    Castle castle;
    bool over;
    bool win;

    void showroominfo(room* room){
        vector<string> exits = room->get_exits();
        cout << room->get_description() << " ";
        cout << "There are " << exits.size() << " exits:";
        for(int i = 0 ; i < exits.size();++i){
            cout << exits[i];
            if( i != exits.size()-1){
                cout << ",";
            }
        }
        cout << "." << endl;
    }

    void process_command(const string& playinput){

        size_t i = playinput.find(' ');

        if (i == string::npos){
            cout << "Invalid command. plz use 'go <dierection>'." << endl;
            return;
        }

        string command = playinput.substr(0,i);
        string direction = playinput.substr(i+1);

        castle.under_command(command,direction);


    }
public:
    // constructor
    Game(): over(false),win(false){}

    void run(istream& Input = cin){
        cout << "Welcome to a new world!"<<endl;
        cout << "Your task here is to save the PRINCESS and avoid to be catched by the MONSTER" << endl;

        while(!over){
            room* currentroom = castle.get_currentroom();
            
            if(!castle.in_lobby()){  //这步多余了。。。懒得改了
                if(currentroom->check_princess() && ! castle.princess_is_found()){
                    castle.set_princess_found(true);
                    cout << "Wow! You've found the princess in the "<< currentroom->get_name()<<"!"<<endl; 
                    cout << "Trigger the Hide plot."<<endl;
                    cout << "Princess: 'Oh my god! Save me ,plz.'" << endl;
                    cout << "You:'It's my pleasure.I will do my best'" << endl;
                }                
            }

            if(currentroom->check_Monster()){
                cout << "Oh nooo! You've bothered the Monster!" << endl;
                cout << "KILLED! GAME OVER" <<endl;
                over = true;
                break;
            }

            if(castle.princess_is_found() && castle.in_lobby()){
                cout<<"Congratulations! You've escaped the castle with the princess!"<<endl;
                cout<<"WIN WIN WIN"<<endl;
                over = true;
                win = true;
                break;
            }

            showroominfo(currentroom);

            string play_input;
            cout << "Enter your command:" << endl;
            getline(Input,play_input);

            process_command(play_input);
        }
    }

};

int main(int argc, char* argv[]){

    Game game;

    if(argc > 1){
        ifstream file(argv[1]);
        if(file){
            game.run(file);
        }
        else{
            cout<<"open file failed."<<endl;
            return 1 ;
        }
    }
    else{
        game.run();
    }

    return 0;
}
