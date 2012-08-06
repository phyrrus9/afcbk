/********************************************************************
 AFC iPhone Backup Utility Copyright © 2012 Ethan Laur (phyrrus9)
 This will allow you to back up files and directories off of your
 iPhone, iPad, or iPod Touch. The following devices are supported:
 iPhone 3G[S]    5.0.1, 5.1.1
 iPhone 4[GSM]   5.0.1, 5.1.1
 iPhone 4[CDMA]  5.0.1, 5.1.1
 iPhone 4[S]     5.1.1
 iPod Touch 3G   5.0.1, 5.1.1 (possibly)
 iPod Touch 4G   5.0.1, 5.1.1
 iPad 2          5.0.1, 5.1.1
 iPad 3          5.1.1
 This program requires the cinject binary file to be in the same
 directory as this binary. Cinject is Copyright © 2012 Chronic dev
 Team LLC and is not for commercial use. I have not yet asked for
 permission to distribute this file yet so you will need to get it
 on your own and place it in this directory.
 This program is full copyright © 2012 by the following names
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> (source code)
 MOD Technologies LLC <http://modtech.co> (resources)
 Joshua Hill (p0sixninja) [chronic-dev team] (cinject)
 pod2g [chronic-dev team] (filesystem node bug-cinject)
 planetbeing [chronic-dev team] (cinject private resources)
 Jay Freeman (saurik) [SaurikIT] (Cydia--part of cinject payload)
 Nikias Bassen (pimskeks) [Chronic-dev team] (cinject GUI)
 MuscleNerd [iPhone Dev Team] (private resources)
 xvolks [freelance] (ROP code generator used in cinject payloads)
 This program is open source, meaning that you may use any of the
 code (however simple it is) in any way you wish at any time and
 distribute it under any open source lisence. This means that any
 distribution of this source code as a binary form must provide
 a simple method for the user of the program to obtain a copy of 
 the original source code as compiled in binary form. Along with
 the source code, any distribution of this code must contain at the
 bare minimum a copy of this comment block to maintain that the
 original authors are given credit for their works in the program.
 Any comments, questions, or concerns should not be sent to any
 of the chronic-dev members, MuscleNerd, or Saurik, they are far
 too busy to deal with my broken code. If you would like help with
 this program do the following checks before contacting me:
 1. Check your compiler, make sure it is set up properly
 2. Ensure you are compiling on a system that includes the libs used
    There is nothing worse than finding out it is all because you
    forgot that arm iphone does not have a compiler with sstream
    on it. Check to ensure that is all set up.
 3. Make sure your code is up to date.
    I do not release broken source code, so it must have been changed
    if it will not compile with the same commands I use.
 4. Do some googling. I wont even reply to you if I can see that your
    problem can be solved with a quick google search.
 5. Email Jerrick (lamaboy99@gmail.com) I probably will just fwd it
    to him anyways because I don't handle a lot of this stuff myself
 *******************************************************************/
#include <iostream>
#include <sstream>
using namespace std;
int strch(char * , char);
void display_help(void);
void jailbreak_err(void);
int main(int argc, char * argv[])
{
    char directory[50], output[50], image[50], restore[50];
    //make sure we have the info we need
    if (argc < 1)
        exit(-1);
    //parse some command line crap
    if (strch(argv[1], 'h')) //parse for help dialog
        display_help();
    int dir = strch(argv[1], 'd'); //parse for directory change
    if (dir)
        strcpy(directory, argv[dir+1]);
    int out = strch(argv[1], 'l');
    if (out)
        strcpy(output, argv[out+1]);
    int img = strch(argv[1], 'c');
    if (img)
        strcpy(image, argv[img+1]);;
    int res = strch(argv[1], 'r');
    if (res)
        strcpy(restore, argv[res+1]);
    system("mkdir /tmp/afcbk");
    chdir("/tmp/afcbk");
    ostringstream t;
    t << "./cinject -D ";
    if (img)
    {
        if (!strch(argv[1], 'j'))
            jailbreak_err();
        t << "/";
        system(t.str().c_str());
        ostringstream s;
        s << "zip -rq0 ./* ";
        s << image;
        system(t.str().c_str());
        //exit(0);
    }
    if (res)
    {
        cout << "Restore Comming soon" << endl;
        //exit(0);
    }
    if (dir)
    {
        if (!strch(argv[1], 'j'))
        {
            char location[15];
            strncpy(location, directory, 12);
            if (strcmp(location, "/var/mobile/"))
                jailbreak_err();
        }
        t << directory;
        cout << t.str() << endl;
        system(t.str().c_str());
    }
    if (out && dir)
    {
        ostringstream t;
        t << "cp -R /tmp/afcbk/* ";
        t << output;
        system(t.str().c_str());
    }
    if (!out && dir)
    {
        system("cp -R /tmp/afcbk/* ./");
    }
}
int strch(char * string, char character)
{
    int code = 0;
    for (int i = 1; i < strlen(string); i++)
        if (string[i] == character)
            code = i;
    return code;
}
void display_help(void)
{
    cout << "iPhone AFC Backup Utility" << endl
         << "Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>" << endl
         << "This app will back up all information on your iOS device," << endl
         << "including all applications, music, and other data. If you" << endl
         << "are not jailbroken, this cannot make a restore image for you." << endl
         << "Usage: afcbk -[options] <parameters>" << endl
         << "Options:" << endl
         << "-h Display this help, no parameters" << endl
         << "-d choose directory, directory to be backed up" << endl
         << "-l change location, location to be backed up to (default is ./)" << endl
         << "-j device is jailbroken, no parameters" << endl
         << "-c create restore image, path to image" << endl
         << "-r restore image, path to image" << endl
         << "Note: parameters must be passed in the same order as options" << endl
         << "options with no parameters MUST be passed after those with parameters" << endl
         << "do not use image with any other parameters" << endl;
    exit(0);
}
void jailbreak_err(void)
{
    cout << "Sorry, you are not jailbroken..." << endl
    << "All non-jailbroken paths must be backed up" << endl
    << "on the User partition (/var/mobile/). Try " << endl
    << "starting your path with \"/var/mobile/\"" << endl;
    exit(-1);
}

