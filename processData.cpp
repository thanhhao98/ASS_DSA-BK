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

bool checkAdd(NinjaInfo_t data, L1List<NinjaInfo_t> &list){
  L1Item<NinjaInfo_t> *temp = list.getHead();
  while(temp!=NULL){
    if(strcmp(data.id, temp->data.id) == 0){
        return false;
    }
    temp=temp->pNext;
  }
  list.push_back(data);
  return true;
}

void event_3(L1Item<NinjaInfo_t> *pHead){
  L1Item<NinjaInfo_t> *temp = pHead;
  L1Item<NinjaInfo_t> *tempList = new L1Item<NinjaInfo_t>();
  strncpy(tempList->data.id, pHead->data.id, ID_MAX_LENGTH - 1);
  L1Item<NinjaInfo_t> *other = new L1Item<NinjaInfo_t>();
  temp = temp->pNext;
  while(temp!=NULL){
    other = tempList;
    while(other!=NULL){
      if(strcmp(other->data.id,temp->data.id)==0){
        goto event_3_1;
      }
      other=other->pNext;
    }
    
    event_3_1:
    temp = temp->pNext;
  }
  cout << tempList.getSize();
}

double distanceMove(char *code, L1Item<NinjaInfo_t> *pHead){
  double distanceMove=0;
  L1Item<NinjaInfo_t> *temp = pHead;
  double longitude;
  double latitude;
  longitude = temp->data.longitude;
  latitude = temp->data.latitude;
  while(temp!=NULL){
    if(strcmp(code,temp->data.id)==0){
        distanceMove += distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude);
        longitude = temp->data.longitude;
        latitude = temp->data.latitude;
    }
    temp=temp->pNext;
  }
  return distanceMove;
}

void event_9(L1Item<NinjaInfo_t> *pHead){
  L1Item<NinjaInfo_t> *temp = pHead;
  L1List<NinjaInfo_t> tempList;
  tempList.push_back(temp->data);
  while(temp!=NULL){
    checkAdd(temp->data,tempList);
    temp = temp->pNext;
  }
  L1Item<NinjaInfo_t> *newTemp = tempList.getHead();
  char ninjaMoveBest[ID_MAX_LENGTH];
  double maxMoveDistance =0;
  while(newTemp!=NULL){
    if(distanceMove(newTemp->data.id,pHead)>maxMoveDistance){
      maxMoveDistance = distanceMove(newTemp->data.id,pHead);
      strncpy(ninjaMoveBest, newTemp->data.id , ID_MAX_LENGTH - 1);      
    }
    newTemp=newTemp->pNext;
  }
  cout << ninjaMoveBest;
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
        event_3(nList.getHead());
        break;
      }
      case 4:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        if(temp!=NULL){
          char idBigest[ID_MAX_LENGTH];
          strncpy(idBigest, temp->data.id, ID_MAX_LENGTH - 1);
          while(temp!=NULL){
            if(strcmp(idBigest,temp->data.id)<0){
              strncpy(idBigest, temp->data.id, ID_MAX_LENGTH - 1);
            }
            temp=temp->pNext;
          }
          cout << idBigest;
          break;
        } else{
          break;
        }
      }
      case 5:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        time_t timeMove;
        bool exist = false;
        double longitude;
        double latitude;
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        while(temp!=NULL){
          if(strcmp(id,temp->data.id)==0){
            if(!exist){
              exist = true;
              longitude = temp->data.longitude;
              latitude = temp->data.latitude;
            } else {
              if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)>0.005){
                timeMove = temp->data.timestamp;
                goto outCase5;
              }
            }
          }
          temp=temp->pNext;
        }
        outCase5:
        if(!exist){
          cout << -1;
        } else{
          char timeChar[26];
          strPrintTime(timeChar,timeMove);
          cout << timeChar;
        }
        break;
      }
      case 6:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        time_t timeNotMove;
        time_t justMove;
        bool exist = false;
        bool moving = false;
        double longitude;
        double latitude;
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
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
        } else{
          cout << -1;
        }
        break;
      }
      case 7:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        int count=0;
        bool exist = false;
        bool moving = true;
        double longitude;
        double latitude;
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
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
        if(!exist){
          cout << -1;
        } else{
          cout << count;
        }
        break;
      }
      case 8:{
        L1Item<NinjaInfo_t> *temp = nList.getHead();
        char id[ID_MAX_LENGTH];
        double distanceMove=0;
        bool exist = false;
        double longitude;
        double latitude;
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
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
        if(!exist){
          cout << -1;
        } else{
          cout << distanceMove;
        }
        break;
      }
      case 9:{
        event_9(nList.getHead());
        break;
      }
      case 11:{
        break;
      }
    }


    cout << endl;
    return true;
}
