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
  string eventLine;
  while(getline(eventFile, eventLine)){
    if(!eventLine.empty()){
      string eventCode;
      stringstream streamLine(eventLine);
      while(streamLine>>eventCode){
        if(!eventCode.empty()){
          ninjaEvent_t *newNinjaEvent = new ninjaEvent_t(eventCode);
          eList.push_back(*newNinjaEvent);
        }
      }
    }
  }
  eventFile.close();
}
