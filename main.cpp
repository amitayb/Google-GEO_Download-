#include <mutex>
#include <stdlib.h>
#include "fillMap.h"
#include "threadQueue.h"


using namespace std;
threadQueue mainQueue;
unordered_map<string , fillMap::location> unorderedMapfinal;
mutex m;
condition_variable cv;
string data;
 void printAnswer(fillMap::structAnswer answer){
     cout<<"Item Name: "<<answer.answerName<<endl;
     cout<<"CODE: "<<answer.answerCode<<endl;

     cout<<endl<<"Country Name: "<<answer.country<<endl;
     cout<<"Region/Stat Name: "<<answer.regionState<<endl;
     cout<<"City Name: "<<answer.city<<endl;
     cout<<"Postal Code Number: "<<answer.postalCode<<endl;

 }
 void insertToDB(){

    fillMap::structAnswer temp1;

    temp1= mainQueue.pop();
    /************ SQL Query ******************/
   /* insert into ans_table (name,code,country,regionState,city,postalCode)
			values (temp1.answerName,temp1.answerCode,temp1.country,temp1.regionState,temp1.city,answer.postalCode);
      commit;
   */
   /****************************************/


   printAnswer(temp1);
   insertToDB();



}
 void connectDB(){

     cout<<"sqlplus USERNAME/PASSWORD@INSTACE"<<endl;
     insertToDB();

 }


 void downloadFile (){

   int status  = system("curl  -o geo-table.csv https://storage.googleapis.com/adx-rtb-dictionaries/geo-table.csv");
    if (status <0){
        cout<< "ERROR in Download file"<<endl;
    }


 }

void getData(){
    string inputID;

    fillMap::structAnswer finalAnswer;

    clock_t start;
    double duration;
    cout<<"Enter ID:"<<endl;
    getline(cin,inputID);
    start = clock();
    finalAnswer  = unorderedMapfinal[inputID].answer;

    mainQueue.push(finalAnswer);
    duration = (1000*( clock() - start ) / (double) CLOCKS_PER_SEC);





    cout<<"Time in Milisecs: "<< duration <<endl<<endl;
    getData();

}
int openFileAndParse(){
    unique_lock<mutex> lk(m);
    ifstream file1 ("geo-table.csv");
    if (file1.good()){


   fillMap fMap ;
   unorderedMapfinal = fMap.parseCSV(file1);
    file1.close();
    cout<<"Parse completed setting all answers."<<endl;
    //Getting all answers into map
    for(auto it = unorderedMapfinal.begin();it!= unorderedMapfinal.end();++it){
            string tempid;
            tempid = it-> first;
            unorderedMapfinal[tempid].answer  = fMap.getDataAlgorith(tempid , unorderedMapfinal);
    }//Getting all answers into map

    lk.unlock();
    cv.notify_one();
    return 0;


    }

    else{
        file1.close();
        cout<<"File was not found!!!!!"<<endl;
        return 1;
    }


}
int* gethour(){
    string temp;
       // current date/time based on current system
   time_t now = time(0);
   tm *ltm = localtime(&now);
   int hourMin[2];
   hourMin[0] =ltm->tm_hour;
   hourMin[1] = ltm->tm_min ;

    return hourMin;


}
        /** \brief set  timer to 08:00 AM and run download script
         *
         * \param
         * \param
         * \return
         *
         */

void  runDownload(){
    int *hourmin = gethour();

    int sleephours,sleepminutes;
    if (hourmin[0] >=8 and hourmin[0]!=0)
    {
         sleephours = 23-((*hourmin)-8);
    }
    else
    {
        sleephours=7-hourmin[0];
    }
    sleepminutes = 60 - hourmin[1];
    cout << "Time to next download: "<<sleephours << " hours and "<<sleepminutes<<" mins "<<endl;
    std::this_thread::sleep_for(chrono::minutes(sleepminutes));
    std::this_thread::sleep_for(chrono::hours(sleephours));               //Set the timer

     downloadFile();
    int stat =  openFileAndParse();
    if (stat != 0){
        cout<< "ERROR in parse file after download file"<<endl;
    }

runDownload(); //set timer again


}

int main()
{
    cout<<"Main thread: " <<this_thread::get_id()<<endl;
    thread download(downloadFile);
    download.join();
    thread schedule(runDownload);
    schedule.detach();
    int statusfromfile = openFileAndParse();

    if (statusfromfile == 0){
    thread readerthread(connectDB);
    readerthread.detach();



    getData();
    }





    return 0;
}
