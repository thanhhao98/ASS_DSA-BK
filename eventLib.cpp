/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"


/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
  ifstream eventFile(fName);
  if(eventFile.fail()){
    cout << "The file i not fount!";
    return;
  }
  string eventLine;
  while(getline(eventFile, eventLine)){
    if(!eventLine.empty()){
      string eventCode;
      stringstream streamLine(eventLine);
      while(streamLine>>eventCode){
        if(!eventCode.empty()){
          ninjaEvent_t *newNinjaEvent = new ninjaEvent_t(eventCode);
          int i=0;
          while(newNinjaEvent->code[i]!='\0'){
            if(newNinjaEvent->code[i]==';' && newNinjaEvent->code[i+1]=='\0'){
              newNinjaEvent->code[i]='\0';
            }
            i++;
          }
          eList.push_back(*newNinjaEvent);
        }
      }
    }
  }
  eventFile.close();
}
