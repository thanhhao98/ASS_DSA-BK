/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"

int getEndEvent(char* code){
  for(int i=0; i< EVENT_CODE_SIZE; i++){
    if(code[i]=='\0'){
      return i;
    }
  }
  return -1;
}


int switchEvent(ninjaEvent_t event){
  switch(event.code[0]){
    case '0':{
      if(event.code[1]=='\0'){
        return 0;
      } else{
        return -1;
      }
    }
    case '1':{
      switch(event.code[1]){
        case '\0':{
          return 1;
        }
        case '0':{
          if(event.code[2]=='\0'){
            return 10;
          } else{
            return -1;
          }
        }
        case '1':{
          if(5<getEndEvent(event.code)){
            return 11;
          }else{
            return -1;
          }
        }
        case '2':{
          if(event.code[2]=='\0'){
            return 12;
          } else{
            return -1;
          }
        }
        case '3':{
          return -1;
        }
        case '4':{
          if(event.code[2]=='\0'){
            return 14;
          } else{
            return -1;
          }
        }
      }
    }
    case '2':{
      if(event.code[1]=='\0'){
        return 2;
      } else{
        return -1;
      }
    }
    case '3':{
      if(event.code[1]=='\0'){
        return 3;
      } else{
        return -1;
      }
    }
    case '4':{
      if(event.code[1]=='\0'){
        return 4;
      } else{
        return -1;
      }
    }
    case '5':{
      if(4<getEndEvent(event.code)){
        return 5;
      }else{
        return -1;
      }
    }
    case '6':{
      if(4<getEndEvent(event.code)){
        return 6;
      }else{
        return -1;
      }
    }
    case '7':{
      if(4<getEndEvent(event.code)){
        return 7;
      }else{
        return -1;
      }
    }
    case '8':{
      if(4<getEndEvent(event.code)){
        return 8;
      }else{
        return -1;
      }
    }
    case '9':{
      if(event.code[1]=='\0'){
        return 9;
      } else{
        return -1;
      }
    }
    default: {
      return -1;
    }
  }
}


bool idExist(char* idCheck, L1Item<NinjaInfo_t> *pHead){
  L1Item<NinjaInfo_t> *temp = pHead;
  while(temp!=NULL){
    if(strcmp(idCheck,temp->data.id)==0){
      return true;
    }
    temp=temp->pNext;
  }
  return false;
}

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {
    int eventProcess = switchEvent(event);
    if(eventProcess<0){
      return false;
    } else{
      cout << event.code << ": ";
    }

    switch(eventProcess){
      case 0:{
        L1Item<ninjaEvent_t> *temp = static_cast<L1Item<ninjaEvent_t> *>(pGData);
        while(temp!=NULL){
          if(temp->pNext==NULL){
            cout << temp->data.code;
          }else{
            cout << temp->data.code << " ";
          }
          temp=temp->pNext;
        }
        break;
      }
      case 1:{
        cout << nList.getHead()->data.id;
        break;
      }
      case 2:{
        cout << nList.getTail()->data.id;
        break;
      }
      case 3:{
        cout << nList.listSize;
        break;
      }
      case 4:{
        cout << nList.maxId;
        break;
      }
      case 5:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        time_t timeMove;
        bool exist = false;
        double longitude;
        double latitude;
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        if(idExist(id,nList.list)){
          while(temp!=NULL){
            if(strcmp(id,temp->data.id)==0){
              if(!exist){
                exist = true;
                longitude = temp->data.longitude;
                latitude = temp->data.latitude;
              } else {
                if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)>0.005){
                  timeMove = temp->data.timestamp;
                  break;
                }
              }
            }
            temp=temp->pNext;
          }
          outCase5:
          if(exist){
            char timeChar[26];
            strPrintTime(timeChar,timeMove);
            cout << timeChar;
          }
        }else {
          cout << -1;
        }
        break;
      }
      case 6:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        if(idExist(id,nList.list)){
          time_t timeNotMove;
          time_t justMove;
          bool exist = false;
          bool moving = false;
          double longitude;
          double latitude;
          while(temp!=NULL){
            if(strcmp(id,temp->data.id)==0){
              if(!exist){
                exist = true;
                longitude = temp->data.longitude;
                latitude = temp->data.latitude;
                timeNotMove = temp->data.timestamp;
              } else {
                if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)>0.005){
                  longitude = temp->data.longitude;
                  latitude = temp->data.latitude;
                  justMove = temp->data.timestamp;
                  moving = true;
                } else{
                  if(moving){
                    timeNotMove = justMove;
                  }
                  moving = false;
                }
              }
            }
            temp=temp->pNext;
          }
          if(exist){
            char timeChar[26];
            strPrintTime(timeChar,timeNotMove);
            cout << timeChar;
          }
        } else {
          cout << -1;
        }
        break;
      }
      case 7:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        if(idExist(id,nList.list)){
          int count=0;
          bool exist = false;
          bool moving = true;
          double longitude;
          double latitude;
          while(temp!=NULL){
            if(strcmp(id,temp->data.id)==0){
              if(!exist){
                exist = true;
                longitude = temp->data.longitude;
                latitude = temp->data.latitude;
              } else {
                if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)<=0.005){
                  if(moving){
                    count++;
                  }
                  moving = false;
                }else{
                  moving =true;
                  longitude = temp->data.longitude;
                  latitude = temp->data.latitude;
                }
              }
            }
            temp=temp->pNext;
          }
          if(exist){
            cout << count;
          }
        }else{
          cout << -1;
        }
        break;
      }
      case 8:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        if(idExist(id,nList.list)){
          double distanceMove=0;
          bool exist = false;
          double longitude;
          double latitude;
          while(temp!=NULL){
            if(strcmp(id,temp->data.id)==0){
              if(!exist){
                exist = true;
                longitude = temp->data.longitude;
                latitude = temp->data.latitude;
              } else {
                distanceMove += distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude);
                longitude = temp->data.longitude;
                latitude = temp->data.latitude;
              }
            }
            temp=temp->pNext;
          }
          if(exist){
            cout << distanceMove;
          }
        } else{
          cout << -1;
        }
        break;
      }
      case 9:{
        char idDisMoveMax[ID_MAX_LENGTH];
        double distanceMoveMax = -1;
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.dMove>distanceMoveMax&&temp->data.id[0]!='\0'){
            distanceMoveMax = temp->data.dMove;
            strncpy(idDisMoveMax, temp->data.id, ID_MAX_LENGTH - 1);
          }
          temp=temp->pNext;
        }
        cout << idDisMoveMax ;
        break;
      }
      case 10:{
        char idTimeMoveMax[ID_MAX_LENGTH];
        double timeMoveMax = -1;
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.tMove>timeMoveMax&&temp->data.id[0]!='\0'){
            timeMoveMax = temp->data.tMove;
            strncpy(idTimeMoveMax, temp->data.id, ID_MAX_LENGTH - 1);
          }
          temp=temp->pNext;
        }
        cout << idTimeMoveMax ;
        break;
      }
      case 11:{
        char id[ID_MAX_LENGTH];
        bool exist = false;
        strncpy(id, event.code+2 , ID_MAX_LENGTH - 1);
        char idChose[ID_MAX_LENGTH];
        for(int i=0;i<ID_MAX_LENGTH-2;i++){
          idChose[i] = '0';
        }
        idChose[ID_MAX_LENGTH-1] = '\0';
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(strcmp(temp->data.id,id)==0){
            goto case11_gate;
          } else if(strcmp(temp->data.id,id)>0||strcmp(temp->data.id,idChose)<0){
            goto case11_gate;
          }
          exist=true;
          strncpy(idChose,temp->data.id,ID_MAX_LENGTH-1);
          case11_gate:
          temp=temp->pNext;
        }
        if(exist){
          temp = nList.list;
          while(temp!=NULL){
            if(strcmp(temp->data.id,idChose)==0){
              temp->data.id[0]= '\0';
              break;
            }
            temp=temp->pNext;
          }
          cout << idChose;
          nList.listSize--;
        } else {
          cout << -1;
        }

        break;
      }
      case 12:{
        char idTimeStandMax[ID_MAX_LENGTH];
        double timeStandMax = -1;
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.tStand>timeStandMax&&temp->data.id[0]!='\0'){
            timeStandMax = temp->data.tStand;
            strncpy(idTimeStandMax, temp->data.id, ID_MAX_LENGTH - 1);
          }
          temp=temp->pNext;
        }
        cout << idTimeStandMax ;
        break;
      }
      case 13:{
        break;
      }
      case 14:{
        break;
      }
    }


    cout << endl;
    return true;
}
