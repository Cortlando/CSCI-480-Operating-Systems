/********************************************************************
CSCI 480 - Assignment 1- Spring 2021

Progammer: Cortland Ervins
Section:   0001
Date Due:  1/29/21

Purpose: Reads various /proc/ files and gathers information from them

*********************************************************************/

#include <iostream>
#include <string>
#include <fstream>
/****************************************************************

   FUNCTION:   OS_Questions

   ARGUMENTS:  N/A

   RETURNS:    N/A

   NOTES:      Reads several files and 
               pulls information about the OS.
****************************************************************/
void OS_Questions(){
    //Opens file
    std::ifstream file("/proc/sys/kernel/ostype", std::ios::in);

    std::string answer = " "; //Stores what is gotten from getline()

    std::cout << "A: Questions about turing's OS: " << std::endl;

    //Checks if file opened properly
    if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    //Gets answer to question
    std::getline(file, answer);

    //Prints it
    std::cout << "1. The type of turning's OS is " << answer << std::endl;

    //Closes file
    file.close();
    //Pattern repeats for rest of function

    file.open("/proc/sys/kernel/hostname", std::ios::in);

     if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    std::getline(file, answer);

    std::cout << "2. The hostname is " << answer << std::endl;
    
    file.close();

    file.open("/proc/sys/kernel/osrelease", std::ios::in);

     if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    std::getline(file, answer);

    std::cout << "3. The osrelease is " << answer << std::endl;
    
    file.close();

    file.open("/proc/sys/kernel/version", std::ios::in);

     if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    std::getline(file, answer);

    std::cout << "4. The version is " << answer << std::endl;
    
    file.close();
}

/****************************************************************

   FUNCTION:   Processor_0_Questions

   ARGUMENTS:  1. file : an ifstream& that is "/proc/cpuinfo".

   RETURNS:    N/A

   NOTES:      Answers the questions about processor 0 using 
               the stat file.
****************************************************************/
void Processor_0_Questions(std::ifstream& file){
    //Holds what string.find() returns
    std::size_t found = 0;

    //Holds what getline returns
    std::string answer = " ";

    std::string vendor = " ";

    std::string model_name = " ";

    std::string physical_size = " ";

    std::string virtual_size = " ";

    if(!file.is_open()){
		std::cout << "Can't open file'" ;
        std::cout << "AAAAAAAAAAAAAAAAAAAA";
		file.close();
	}


    //Reads all relevent information about the first processor and then stops
    while(!file.eof() && answer.empty() == 0){
        std::getline(file, answer);
        found = answer.find("vendor_id", 0);

        if(found!=std::string::npos){
            vendor = answer.substr(12,answer.back());
        }

        found = answer.find("model name", 0);

        if(found!=std::string::npos){
            model_name = answer.substr(12,answer.back());
        }

        found = answer.find("address sizes", 0);

        if(found!=std::string::npos){
            physical_size = answer.substr(16,7);
            virtual_size = answer.substr(34, 7);

        }
            
    }

    std::cout << "\n" << "C: Questions about processor 0" << std::endl;
    std::cout << "1. The vendor for processor 0 is " << vendor  << std::endl;
    std::cout << "2. The model name of processor 0 is " << model_name  << std::endl;
    std::cout << "3. The physical size of processor 0 is " << physical_size  << std::endl;
    std::cout << "4. The virtual size of processor 0 is " << virtual_size  << std::endl;

}
/****************************************************************

   FUNCTION:   Processor_1_Questions

   ARGUMENTS:  1. file : an ifstream& that is "/proc/stat".

   RETURNS:    N/A

   NOTES:      Answers the questions about processor 0 using 
               the stat file.
****************************************************************/
void Processor_1_Questions(){
    std::ifstream file("/proc/stat", std::ios::in);


    //Used to store what find returns
    std::size_t found = 0;

    //Used for counting the number of spaces
    //which lets me know which numbers I need to save 
    //in a variable
    int space_locations [10] = { };
    int space_counter = 0;
    
    //Integer version of user mode time, system mode time,
    // and idle_seconds
    int i_user_mode_time = 0;
    int i_system_mode_time = 0;
    int i_idle_seconds = 0;

    //Used for time output
    int days, hours, minutes = 0;

    float seconds = 0;

    //String version of user mode time, system mode time,
    // and idle_seconds
    std::string user_mode_time = "";
    std::string system_mode_time = "";
    std::string idle_seconds = "";

    
    //Holds what getline returns
    std::string answer = " ";
     

     if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    
    while(!file.eof()){
        std::getline(file, answer);
        found = answer.find("cpu1", 0);
        
        
        if(found!=std::string::npos){
            for(size_t i = 0; i < answer.length(); i++){
                //If it finds a space, save the location of it in the space_locations array
                if(answer[i] == ' '){
                space_locations [space_counter] =  i; 
                space_counter++;
                }
            }
            //The for loops use the space locations to know which number to put into the variables
            for(int i = 0, p = space_locations[0]; i < ((space_locations[1] + 1) - space_locations[0]); i++,p++){
                user_mode_time.push_back(answer.at(p));
            }

            for(int i = 0, p = space_locations[2]; i < ((space_locations[3] + 1) - space_locations[2]); i++,p++){
                system_mode_time.push_back(answer.at(p));
            }

            for(int i = 0, p = space_locations[3]; i < ((space_locations[4] ) - space_locations[3]); i++,p++){
                idle_seconds.push_back(answer.at(p));
            }
            //Multiplies them by 100 to convert them from jiffies to seconds
            i_user_mode_time = stoi(user_mode_time) * 100; 
            i_system_mode_time = stoi(system_mode_time) * 100;     
            i_idle_seconds = stoi(idle_seconds) / 100;

            
        }    
    }

    //Numbers were inconsistant if not there absolute value for some reason
    //Probably overflow
    days = abs(i_idle_seconds) / 60 / 60 / 24;

    hours = (abs(i_idle_seconds) / 60 / 60) % 24;

    minutes = (abs(i_idle_seconds) / 60) % 60;

    seconds = abs(i_idle_seconds) % 60;

    std::cout << "\n" << "D: Questions about processor 1" << std::endl;
    std::cout << "1. This cpu has been in user mode for " << i_user_mode_time << " seconds" << std::endl;
    std::cout << "2. This cpu has been in system mode for " << i_system_mode_time <<" seconds" << std::endl; 
    std::cout << "3. This cpu has been idle for  " << abs(i_idle_seconds) << " seconds" << std::endl; 
    std::cout << "4. The system has been idle for " << days << " days, "
    << hours  << " hours, " << minutes << " minutes, and "
    << seconds << " seconds. " << std::endl;  

    file.close();
}
/****************************************************************

   FUNCTION:   Swap_Question

   ARGUMENTS:  N/A

   RETURNS:    N/A

   NOTES:      Answers the question about the swap drive
****************************************************************/
void Swap_Question(){
    std::ifstream file("/proc/swaps", std::ios::in);

    //Holds what getline returns
    std::string answer = "";

    //Holds the name of swap device
    std::string part_size = "";

    //Holds the name of swap device as an int
    int i_part_size = 0;


    if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    std::getline(file, answer);
    std::getline(file, answer);

    //Used to skip irelevant fields
    size_t i = answer.find_first_of(" ", 0);

    while(i < answer.length()){
        //Checks if its a number to know when its reached the relevant field
        if(!isdigit(answer[i]) ){
            i++;
        }
        else
            //Once it hits a number, adds it to string
            while(isdigit(answer[i])){
                part_size.push_back(answer[i]);
                i++;

                if(!isdigit(answer[i])){
                    i = answer.length();
                }
            }

    }
    //Converts it to MB
    i_part_size = stoi(part_size) / 1000;

    std::cout << "\n" << "E: What is the size of turing's swap device in MB" << std::endl;
    std::cout << "1. The swap size is: " << i_part_size << "MB" << std::endl;
    
    file.close();
}
/****************************************************************

   FUNCTION:   Processor_Questions

   ARGUMENTS:  N/A

   RETURNS:    N/A

   NOTES:      Answers general questions about the processors
****************************************************************/
void Processor_Questions(){
    std::ifstream file("/proc/cpuinfo", std::ios::in);
    //Used to store what find returns
    std::size_t found = 0;

    //Holds number of processors
    int num_processors = 0;

    //Holds number of physical chips
    char num_chips = '0';

    std::string uptime = " ";

    int uptime_int = 0;

    //Used for time output
    int days, hours, minutes = 0;

    float seconds = 0;

    //Holds what getline returns
    std::string answer = " ";

    if(!file.is_open()){
		std::cout << "Can't open file'" ;
		file.close();
	}

    while(!file.eof()){
        std::getline(file, answer);
        found = answer.find("physical id", 0);

        //When it finds the physical id section
        //Checks increments the number of processors
        //and checks to see if physical id is different
        //if it is, it increments num_chips

        if(found!=std::string::npos){
            num_processors++;
            if(num_chips == answer.back()){
               num_chips = (int)num_chips + 1;
            }
        }    
    }

    //Opens file for uptime
    std::ifstream file2("/proc/uptime", std::ios::in);

    if(!file2.is_open()){
		std::cout << "Can't open file'" ;
		file2.close();
	}
    
    //Gets uptime
    std::getline(file2, answer);


    uptime = answer.substr(0, answer.find_first_of(" ", 0));

    uptime_int = stoi(uptime);

    days = uptime_int / 60 / 60 / 24;

    hours = (uptime_int / 60 / 60) % 24;

    minutes = (uptime_int / 60) % 60;

    seconds = uptime_int % 60;

    std::cout << "\n" << "B: Questions about turing's processors" << std::endl;
    std::cout << "1. Turing has " << num_processors << " processors." << std::endl;   
    std::cout << "2. Turing has " << num_chips << " physical multi-core chips." << std::endl;
    std::cout << "3. Turing has been up for " << uptime << " seconds." << std::endl;
    std::cout << "4. Turing has been up for " << days << " days, " << hours << " hours, "
              << minutes << " minutes, and " << seconds << " seconds." << std::endl;

    file.clear();
    file.seekg(0);

    //Passes cpuinfo file
    Processor_0_Questions(file);

    file.close();
    file2.close();

}
/****************************************************************

   FUNCTION:   main

   ARGUMENTS:  N/A

   RETURNS:    N/A

   NOTES:      Calls functions to answer various questions
****************************************************************/
int main(){
    OS_Questions();

    Processor_Questions();
    
    Processor_1_Questions();

    Swap_Question();

    return 0;
}