/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {
    tm *pTime = gmtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}



void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
    ifstream ninjaFile(fName);
    double sizeMove;
    double timeMove;
    if(ninjaFile.fail()){
        cout << "The file is not found!";
        return;
    }
    string ninjaLine;
    // ignore first line in csv file
    getline(ninjaFile, ninjaLine,'\n');
    while(getline(ninjaFile,ninjaLine,',')){
      if(!ninjaLine.empty()){
        NinjaInfo_t *newNode = new NinjaInfo_t();
        L1Item<NinjaInfo_t> *myItem  = new L1Item<NinjaInfo_t>();
  
        // read report time
        getline(ninjaFile,ninjaLine,',');
        struct tm tm;
        strptime(ninjaLine.c_str(), "%m/%d/%Y %H:%M:%S" , &tm);
        newNode->timestamp = myItem->data.timestamp = timegm(&tm);
  
        // read ninjaTag
        getline(ninjaFile,ninjaLine,',');
        if(ninjaLine.size()<4){
          for(int i=0; i<4-ninjaLine.size(); i++){
            newNode->id[i] = myItem->data.id[i] = '0';
          }
          strncpy(myItem->data.id+4-ninjaLine.size(),ninjaLine.data(), ID_MAX_LENGTH - 1 - 4 + ninjaLine.size());
          strncpy(newNode->id+4-ninjaLine.size(),ninjaLine.data(), ID_MAX_LENGTH - 1 - 4 + ninjaLine.size());
        } else{
          strncpy(myItem->data.id, ninjaLine.data(), ID_MAX_LENGTH - 1);
          strncpy(newNode->id, ninjaLine.data(), ID_MAX_LENGTH - 1);
        }
  
        // read longitude
        getline(ninjaFile,ninjaLine,',');
        newNode->longitude = myItem->data.longitude = stod(ninjaLine);
  
        // read latitude
        getline(ninjaFile,ninjaLine,',');
        newNode->latitude = myItem->data.latitude = stod(ninjaLine);
  
        db.push_back(*newNode);

        if(db.listSize==0){
            db.list = myItem;
            strncpy(db.maxId, myItem->data.id, ID_MAX_LENGTH - 1);
            db.listSize++;
        } else{
            L1Item<NinjaInfo_t> *tempNode = db.list;
            while(tempNode!=NULL){
                if(strcmp(tempNode->data.id,myItem->data.id)==0){
                    sizeMove=distanceEarth(tempNode->data.la,tempNode->data.lo, myItem->data.latitude,myItem->data.longitude);
                    tempNode->data.dMove+=distanceEarth(tempNode->data.latitude,tempNode->data.longitude, myItem->data.latitude,myItem->data.longitude);
                    tempNode->data.latitude = myItem->data.latitude;
                    tempNode->data.longitude = myItem->data.longitude;
                    if(sizeMove>0.005){
                        tempNode->data.moving = true;
                        tempNode->data.tMove += (myItem->data.timestamp -tempNode->data.timestamp);
                        tempNode->data.la = myItem->data.latitude;
                        tempNode->data.lo = myItem->data.longitude;
                    } else{
                        if(tempNode->data.moving){
                            tempNode->data.numStand++;
                        }
                        tempNode->data.moving = false;
                        tempNode->data.tStand += (myItem->data.timestamp -tempNode->data.timestamp);
                    }
                    tempNode->data.timestamp = myItem->data.timestamp;
                    goto readData1;                
                }
                tempNode=tempNode->pNext;
            }
            if(strcmp(db.maxId,myItem->data.id)<0){
                strncpy(db.maxId, myItem->data.id, ID_MAX_LENGTH - 1);
            }
            myItem->pNext = db.list;
            db.list->data.lo = db.list->data.longitude;
            db.list->data.la = db.list->data.latitude;
            db.list = myItem;
            db.listSize++;

        }

        readData1:
        // goto endline
        getline(ninjaFile,ninjaLine,'\n');
      }
    }
    ninjaFile.close();
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
    // TODO: write code to parse information from a string buffer, ignore if you don't use it
    return true;
}

void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
    void*   pGData = NULL;
    initNinjaGlobalData(&pGData);
    pGData = eventList.getHead();

    while (!eventList.isEmpty()) {
        if(!processEvent(eventList[0], bList, pGData))
            cout << eventList[0].code << " is an invalid event\n";
        eventList.removeHead();
    }

    releaseNinjaGlobalData(pGData);
}


bool initNinjaGlobalData(void** pGData) {
    return true;
}

void releaseNinjaGlobalData(void* pGData) {
    /// TODO: You should define this function if you allocated extra data at initialization stage
    /// The data pointed by pGData should be released
}




void printNinjaInfo(NinjaInfo_t& b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
inline double deg2rad(double deg) {
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
inline double rad2deg(double rad) {
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
inline double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
