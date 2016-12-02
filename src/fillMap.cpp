#include "fillMap.h"

fillMap::fillMap()
{
    //ctor
}

fillMap::~fillMap()
{
    //dtor
}

/*********************************************
* This function will parse the CSV file      *
* PARAM: File - file stream                  *
* Rerun: unordered map                       *
*                                            *
*                                            *
**********************************************/
unordered_map<string,fillMap::location> fillMap::parseCSV(ifstream& file){
    string line;
    unordered_map<string , location> unorderedMap;
        while(getline(file,line)){    //read line from file

            string field="";
            stringstream strstr(line);
            while(  getline(strstr,field,',')){
                    if (field[0]!='"'){             //after ID field.

                            string word;
                            location temp;
                            int numOffield=0;
                            while(getline(strstr,word,'"')) //Get all the fields by the " delimiter.
                            {

                                if(word[0] == ','){
                                    continue;
                                }
                                switch (numOffield) {


                                case 1:
                                    temp.name = word;
                                    numOffield++;
                                    break;

                                case 2:
                                    temp.fullName = word;
                                    numOffield++;
                                    break;

                                case 3:
                                    temp.parents = word;
                                    numOffield++;
                                    break;

                                case 4:
                                    temp.code = word;
                                    numOffield++;
                                    break;

                                case 5:
                                    temp.parentCode= word;
                                    numOffield++;
                                    break;

                                case 6:
                                    temp.type = word;
                                    numOffield++;
                                    break;

                                default:
                                    numOffield++;
                                    break;


                                }


                            }

                            unorderedMap[field] = temp;
                    }//end if


           }


    }



return unorderedMap;


}

/*********************************************
* This function will search the data model   *
* and return all needed information          *
* PARAM: ID - item id , map - data model     *
* Rerun: structure with answer               *
*                                            *
*                                            *
**********************************************/
fillMap::structAnswer fillMap::getDataAlgorith (string& id,unordered_map<string,fillMap::location>& funcMap){

    string  parents;
    string field;
    structAnswer temp;

    parents = funcMap[id].parents;


    stringstream strstr  (parents);
    while(  getline(strstr,field,',')){         //Check all fathers for the needed details
            string type = funcMap[field].type;

        if (type =="City"){
            temp.city = funcMap[field].name;

        }
        else if (type  == "Province" || type  =="State"){
            temp.regionState = funcMap[field].name;

        }

        else if (type  =="Country"){
            temp.country = funcMap[field].name;

        }
        else if (type  =="Postal Code"){
            temp.postalCode = funcMap[field].name;



        }

    }
            string type = funcMap[id].type;    //Check the item if he fits the needed data

        if (type =="City"){
            temp.city = funcMap[id].name;

        }
        else if (type  == "Province" || type  =="State"){
            temp.regionState = funcMap[id].name;

        }

        else if (type  =="Country"){
            temp.country = funcMap[id].name;

        }
        else if (type  =="Postal Code"){
            temp.postalCode = funcMap[id].name;



        }
    temp.answerCode=funcMap[id].code;
    temp.answerName = funcMap[id].name;

    //funcMap[id].answer = temp;

return temp;
}
