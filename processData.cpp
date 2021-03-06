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
      return 0;
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
          if(2<getEndEvent(event.code)){
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
          if(event.code[2]!='\0'){
            return 13;
          } else{
            return -1;
          }
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
      if(1<getEndEvent(event.code)){
        return 5;
      }else{
        return -1;
      }
    }
    case '6':{
      if(1<getEndEvent(event.code)){
        return 6;
      }else{
        return -1;
      }
    }
    case '7':{
      if(1<getEndEvent(event.code)){
        return 7;
      }else{
        return -1;
      }
    }
    case '8':{
      if(1<getEndEvent(event.code)){
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

bool miniEvent14(L1Item<NinjaInfo_t> *pNode){
  if(pNode->data.id[0]=='\0'){
    return false;
  }
  L1Item<NinjaInfo_t> *temp = pNode->pFirst;
  L1Item<NinjaInfo_t> *listMove = new L1Item<NinjaInfo_t>();
  double longitude, latitude;
  longitude = listMove->data.longitude = temp->data.longitude;
  latitude = listMove->data.latitude = temp->data.latitude;
  for(int i=0; i< pNode->sizeId-1; i++){
    temp=temp->pNext;
    if(strcmp(temp->data.id,pNode->data.id)==0){
      if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)>0.005){
        L1Item<NinjaInfo_t> *nodeMove = new L1Item<NinjaInfo_t>();
        longitude =  nodeMove->data.longitude  = temp->data.longitude;
        latitude = nodeMove->data.latitude = temp->data.latitude;
        L1Item<NinjaInfo_t> *test = listMove;
        while(test->pNext!=NULL){
          test= test->pNext;
          if(distanceEarth(latitude,longitude,test->data.latitude,test->data.longitude)<=0.005){
            return true;
          }
        }
        nodeMove->pNext = listMove;
        listMove = nodeMove;
      }
    }
  }
  temp=temp->pNext;
  if(strcmp(temp->data.id,pNode->data.id)==0){
    if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)>0.005){
      L1Item<NinjaInfo_t> *test = listMove;
      while(test->pNext!=NULL){
        test= test->pNext;
        if(distanceEarth(temp->data.latitude,temp->data.longitude,test->data.latitude,test->data.longitude)<=0.005){
          return true;
        }
      }
    }
  }
  return false;
}

void event14(L1Item<NinjaInfo_t> *pList, int &x){
  L1Item<NinjaInfo_t> *temp = pList;
  if(temp==NULL){
    return;
  } else {
    event14(temp->pNext,x);
    if(miniEvent14(temp)){
      x++;
      cout << " " << temp->data.id;
    };
    return;
  }

}

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {
    int eventProcess = switchEvent(event);
    if(eventProcess<0){
      return false;
    }if(eventProcess==14){
      cout << 14 << ":";
    } else if(eventProcess==13) {
      return true;
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
        if(nList.listSize==0){
          cout << "empty";
          break;
        }
        char idMaxEvent4[ID_MAX_LENGTH];
        idMaxEvent4[0]='\0';        
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.id[0]!='\0'){
            if(strcmp(idMaxEvent4,temp->data.id)<0){
              strncpy(idMaxEvent4, temp->data.id, ID_MAX_LENGTH - 1);
            }
          }
          temp=temp->pNext;
        }
        cout << idMaxEvent4;
        break;
      }
      case 5:{
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        L1Item<NinjaInfo_t> *pCheckExist = nList.list;
        while(pCheckExist!=NULL){
          if(strcmp(id,pCheckExist->data.id)==0){
            L1Item<NinjaInfo_t> *temp = pCheckExist->pFirst;
            time_t timeMove, timeFirst;
            timeMove = timeFirst = temp->data.timestamp;
            bool empty = false;
            bool tempBool = true;
            bool moveFirst=false;
            double longitude = pCheckExist->pFirst->data.longitude;
            double latitude = pCheckExist->pFirst->data.latitude;
            for(int i=0; i< pCheckExist->sizeId;i++){
              temp=temp->pNext;
              if(strcmp(temp->data.id,id)==0){
                empty=true;
                if(distanceEarth(latitude,longitude,temp->data.latitude,temp->data.longitude)>0.005){
                  empty= false;
                  if(tempBool){
                    moveFirst = true;
                  }
                  timeMove = temp->data.timestamp;
                  break;
                }
                tempBool= false;
              }
            }
            char timeChar[26];
            if(empty){
              cout << "empty";
              goto outCase5;
            } else if(moveFirst){
              strPrintTime(timeChar,timeFirst);
            } else{
              strPrintTime(timeChar,timeMove);
            }
            cout << timeChar;
            goto outCase5;
          }
          pCheckExist= pCheckExist->pNext;
        }
        cout << -1;
        outCase5:
        break;
      }
      case 6:{
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        L1Item<NinjaInfo_t> *pCheckExist = nList.list;
        while(pCheckExist!=NULL){
          if(strcmp(id,pCheckExist->data.id)==0){
            if(pCheckExist->data.numStand==0){
              cout <<  "Non-stop";
              goto outCase6;
            }
            L1Item<NinjaInfo_t> *temp = pCheckExist->pFirst;
            time_t timeNotMove, justMove;
            timeNotMove = temp->data.timestamp;
            bool moving = false;
            double longitude = pCheckExist->pFirst->data.longitude;
            double latitude = pCheckExist->pFirst->data.latitude;
            for(int i=0; i< pCheckExist->sizeId;i++){
              temp=temp->pNext;
              if(strcmp(temp->data.id,id)==0){
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
            char timeChar[26];
            strPrintTime(timeChar,timeNotMove);
            cout << timeChar;
            goto outCase6;
          }
          pCheckExist= pCheckExist->pNext;
        }
        cout << -1;
        outCase6:
        break;
      }
      case 7:{
        L1Item<NinjaInfo_t> *temp = nList.list;
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        while(temp!=NULL){
          if(strcmp(id,temp->data.id)==0){
            cout << temp->data.numStand;
            goto case7_gate;
          }
          temp=temp->pNext;
        }
        cout << -1;
        case7_gate:
        break;
      }
      case 8:{
        L1Item<NinjaInfo_t> *temp = nList.list;
        char id[ID_MAX_LENGTH];
        strncpy(id, event.code+1 , ID_MAX_LENGTH - 1);
        while(temp!=NULL){
          if(strcmp(id,temp->data.id)==0){
            cout << temp->data.dMove;
            goto case8_gate;
          }
          temp=temp->pNext;
        }
        cout << -1;
        case8_gate:
        break;
      }
      case 9:{
        if(nList.listSize==0){
          cout << -1;
          break;
        }
        char idDisMoveMax[ID_MAX_LENGTH];
        double distanceMoveMax = -1;
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.dMove>=distanceMoveMax&&temp->data.id[0]!='\0'){
            distanceMoveMax = temp->data.dMove;
            strncpy(idDisMoveMax, temp->data.id, ID_MAX_LENGTH - 1);
          }
          temp=temp->pNext;
        }
        cout << idDisMoveMax ;
        break;
      }
      case 10:{
        if(nList.listSize==0){
          cout << -1;
          break;
        }
        char idTimeMoveMax[ID_MAX_LENGTH];
        double timeMoveMax = -1;
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.tMove>=timeMoveMax&&temp->data.id[0]!='\0'){
            timeMoveMax = temp->data.tMove;
            strncpy(idTimeMoveMax, temp->data.id, ID_MAX_LENGTH - 1);
          }
          temp=temp->pNext;
        }
        cout << idTimeMoveMax;
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
        if(nList.listSize==0){
          cout << -1;
          break;
        }
        char idTimeStandMax[ID_MAX_LENGTH];
        double timeStandMax = -1;
        L1Item<NinjaInfo_t> *temp = nList.list;
        while(temp!=NULL){
          if(temp->data.tStand>=timeStandMax&&temp->data.id[0]!='\0'){
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
        int num=0;
        event14(nList.list,num);
        if(num==0){
          cout << " " <<  -1;
        }
        break;
      }
    }


    cout <<  endl;
    return true;
}
