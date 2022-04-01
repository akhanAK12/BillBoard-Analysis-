
/* ---------------------------------------------
Program 4: BillBoard Analysis

Course: CS 141, Fall 2021. Tues 11am & 5pm lab
System: xCode
Author: Mustafa Rushdi and Arij Khan
---------------------------------------------
*/
#include <iostream>

#include <fstream>

#include <sstream>

#include <string>

#include <cassert>

#include <vector>

using namespace std;

struct Song {

  public: int year;
  int month;
  int day;
  int rank;
  int lastWeekRank;
  int peakRank;
  int weeksOnBoard;
  string date;
  string songName;
  string artist;
  string tempString;

};
//funvtion displays menu option after user selcts file
void DisplayMessage() {
  cout << "Select a menu option: " << endl;
  cout << "   1. Display overall information about the data" << endl;
  cout << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year" << endl;
  cout << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year" << endl;
  cout << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year" << endl;
  cout << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search" << endl;
  cout << "   6. Exit\n";
  cout << "Your choice --> ";
}
//function reads in file and stores file information into vector
//stoi- converts string into integer
void readWordsFile(string fileName, vector < Song > & billBoard) {
  ifstream inFile;
  inFile.open(fileName, ios:: in );
  assert(inFile.fail() == false);
  string cell;
  string line = "";
  Song newSong;
  getline(inFile, line);
  while (getline(inFile, line)) {
    int month;
    int day;
    int year;
    int rank;
    int lastWeekRank;
    int peakRank;
    int weeksOnBoard;
    string songName, artist, tempString;
    stringstream stream(line);
    getline(stream, cell, ',');
    //To get date as a string
    stringstream streamDate(cell);
    //To get Date"day"
    getline(streamDate, tempString, '/');
    month = stoi(tempString);
    newSong.month = month;
    //To get Date"month"
    getline(streamDate, tempString, '/');
    day = stoi(tempString);
    newSong.day = day;
    //To get Date"year"
    getline(streamDate, tempString, ',');
    year = stoi(tempString);
    newSong.year = year;
    //To get rank
    getline(stream, tempString, ',');
    if (tempString == "") {
      rank = -1;
    } else {
      rank = stoi(tempString);
      newSong.rank = rank;
    }
    //To get song name
    getline(stream, tempString, ',');
    songName = tempString;
    newSong.songName = songName;
    //TO get artist name
    getline(stream, tempString, ',');
    artist = tempString;
    newSong.artist = artist;
    //To get lastWeekRank
    getline(stream, tempString, ',');
    if (tempString == "") {
      lastWeekRank = -1;
    } else {
      lastWeekRank = stoi(tempString);
      newSong.lastWeekRank = lastWeekRank;
    }
    //To get peakRank
    getline(stream, tempString, ',');
    if (tempString == "") {
      peakRank = -1;
    } else {
      peakRank = stoi(tempString);
      newSong.peakRank = peakRank;
    }
    //To get weeksOnBoard
    getline(stream, tempString, ',');
    if (tempString == "") {
      weeksOnBoard = -1;
    } else {
      weeksOnBoard = stoi(tempString);
      newSong.weeksOnBoard = weeksOnBoard;
    }
    billBoard.push_back(newSong);
  }
}
//function checks if users year input is within files years range
bool checkYearSelection(int yearSelection, int menuOptionOne) {
  if (menuOptionOne == 1) {
    if (yearSelection >= 1960 && yearSelection <= 1980) {
      return true;
    } else {
      cout << " No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
      cout << endl;
      return false;
    }
  }
  if (menuOptionOne == 2) {
    if (yearSelection >= 1980 && yearSelection <= 2000) {
      return true;
    } else{
      cout << " No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
      cout << endl;
      return false;
    }
  }
  if (menuOptionOne == 3) {
    if (yearSelection >= 2001 && yearSelection <= 2021) {
      return true;
    } else {
      cout << " No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
      cout << endl;
      return false;
    }
  }
    return false; 
}
//function checks if users decade input is within the files range
bool checkDecadeSelection(int decadeSelection, int menuOptionOne) {
  if (menuOptionOne == 1) {
    if (decadeSelection >= 1960 && decadeSelection <= 1980) {
      return true;
    } else {
      cout << " No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
      cout << endl;
      return false;
    }
  }
  if (menuOptionOne == 2) {
    if (decadeSelection >= 1980 && decadeSelection <= 2000) {
      return true;
    } else {
      cout << " No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
      cout << endl;
      return false;
    }
  }
  if (menuOptionOne == 3) {
    if (decadeSelection >= 2001 && decadeSelection <= 2021) {
      return true;
    } else {
      cout << " No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
      cout << endl;
      return false;
    }
  }
    return false;
}
//converting all words into upper case
//menuOption 5
string uppercaseIt(string name) {
  
  for(int i =0; i < name.size(); i++){
    name.at(i) = toupper(name.at(i));
    }
  return name;
}

int main() {
  vector < Song > billBoard;
  int menuOptionOne;
  int menuOption;
  char OptionTwoSelection;
  string FileName;
  int decadeSelection;
  double yearSelection;
  //displays billBoard analysis
  cout << "Program 4: BillBoard Analysis " << endl;
  cout << "CS 141, Spring 2022, UIC " << endl;
  cout << " " << endl;
  cout << "This program will analyze weekly Billboard data spanning from 1960 - 2020." << endl;
  cout << endl;
  cout << "Select file option:" << endl;
  cout << "   1. To analyze charts top 50: 1960 - 1980 data file" << endl;
  cout << "   2. To analyze charts top 50: 1981 - 2000 data file" << endl;
  cout << "   3. To analyze charts top 50: 2001 - 2020 data file" << endl;
  cout << "Your choice --> ";
  cin >> menuOptionOne;
  cout << "\n";
    //depending on users input, certain file will be read
  if (menuOptionOne == 1 || menuOptionOne == 2 || menuOptionOne == 3) {
    if (menuOptionOne == 1) {
      FileName = "charts_top50_1960_1980.csv";
      readWordsFile(FileName, billBoard);
      cout << endl;
    } else if (menuOptionOne == 2) {
      FileName = "charts_top50_1981_2000.csv";
      readWordsFile(FileName, billBoard);
      cout << endl;
    } else if (menuOptionOne == 3) {
      FileName = "charts_top50_2001_2020.csv";
      readWordsFile(FileName, billBoard);
      cout << endl;
    }
    //if user does not enter a valid input from 1-3, then error message will be outputed
  } else{
    cout << "Invalid value. Exiting Program.";
    exit(0);
  }
  while (true) {

    DisplayMessage();
    cin >> menuOption;
    bool equal = false;
    //option 1
    if (menuOption == 1) {
      vector < string > uniqueSongs;
        //for loop loops through billBoard vector
      for (int i = 0; i < billBoard.size(); i++) {
          //for loop loops through uniqueSongs vector
        for (int j = 0; j < uniqueSongs.size(); j++) {
          //if statement checks if songName in billBoard vector is the same as uniqueSongs vector
          if (billBoard.at(i).songName == uniqueSongs.at(j)) {
            equal = true;
            continue;
          }
        }
        //if songName is not equal between the two vectors then add the songName in billBoard at that index position into uniqueSongs vector
        if (equal == false) {
          uniqueSongs.push_back(billBoard.at(i).songName);
        }
        equal = false;
      }
     //display message
      cout << "Total number of rows: " << billBoard.size() << endl;
      cout << "Number of unique songs represented in the dataset: " << uniqueSongs.size() << endl;
    }

    if (menuOption == 2) {

      int count = 0;
      string element = "";
      string element2 = "";
      int tempCount = 0;
      vector < string > NumberOneSong;
      vector < int > position;
      cout << "Enter D to select a decade or Y to select a year.";
      cout << "Your choice --> ";
      cin >> OptionTwoSelection;
        // while loop used to indicate if user doesnt input y or d it display error message then allows the user to try again and enter the right one
      while (toupper(OptionTwoSelection) != 'D' && toupper(OptionTwoSelection) != 'Y') {
        cout << "Invalid entry. Try again. " << endl;
        cout << "Enter D to select a decade or Y to select a year. " << endl;
        cout << "Your choice --> ";
        cin >> OptionTwoSelection;
        continue;
      }
      if (OptionTwoSelection == 'D' || OptionTwoSelection == 'd') {
        cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010). ";
        cin >> decadeSelection;
          // checks if user decade selection is in range
        if (checkDecadeSelection(decadeSelection, menuOptionOne)) {
          for (int i = 0; i < billBoard.size(); i++) {
            // below varaibles allow to give the computer the right maximum decade and minimal decade needed to run through
            int negation = decadeSelection % 10;
            int minDecade = decadeSelection - negation;
            int maxDecade = minDecade + 10;
              // if statment used to run through a certain decade
            if (billBoard.at(i).year >= minDecade && billBoard.at(i).year < maxDecade) {
                // used to find all songs ranked number on in vector
              if (billBoard.at(i).rank == 1) {
                  //any song ranked number one is pushed back into a new vector
                NumberOneSong.push_back(billBoard.at(i).songName);
                NumberOneSong.push_back(billBoard.at(i).artist);
                string tempElement = billBoard.at(i).songName;
                string tempElement2 = billBoard.at(i).artist;
                int tempCount = 0;
                for (int j = 0; j < NumberOneSong.size(); j++) {
                    // both songs are similar to each other in each vector i add one to tempcount
                  if (NumberOneSong.at(j) == tempElement) {
                    tempCount++;
                      // if the temp count is greater to the previous count I give the new variable elemnt the value of temp elemnt then push back
                    if (tempCount > count) {
                      element = tempElement;
                      element2 = tempElement2;
                      count = tempCount;
                      position.clear();
                      position.push_back(j);
                    }
                    //else statment used to see occurenses within the vector are the same
                    else if (tempCount == count) {
                      element = tempElement;
                      element2 = tempElement2;
                      count = tempCount;
                      position.push_back(j);
                    }
                  }
                }
              }
            }
          }
          // loop through a vector that has all possiblle outcomes with somes with the highes occurances loop through and print all
          cout << "The song(s) with the most #1 occurrences for selected time period is:" << endl;
          for(int i=0; i < position.size(); i++){
          cout << "Song Title: " << NumberOneSong.at(position.at(i)) << endl;
          cout << "Artist: " << NumberOneSong.at(position.at(i) + 1) << endl;
          cout << "# of occurrences: " << count << endl;
            }

        }

      } else if (OptionTwoSelection == 'Y' || OptionTwoSelection == 'y') {
        cout << "Enter the year you would like to choose (e.g. 2001).";
        cin >> yearSelection;
          //check if users input yearSelection is in range
        if (checkYearSelection(yearSelection, menuOptionOne)) {
          for (int i = 0; i < billBoard.size(); i++) {
            // Seperate song so that are number one in bill board data
            if (yearSelection == billBoard.at(i).year) {
              if (billBoard.at(i).rank == 1) {
                NumberOneSong.push_back(billBoard.at(i).songName);
                NumberOneSong.push_back(billBoard.at(i).artist);

                string tempElement = billBoard.at(i).songName;
                string tempElement2 = billBoard.at(i).artist;
                int tempCount = 0;
                for (int j = 0; j < NumberOneSong.size(); j++) {
                  if (NumberOneSong.at(j) == tempElement) {
                    tempCount++;
                    // if the temp count is greater than the previous count I give the new variable elemnt the value of temp elemnt then push back
                    if (tempCount > count) {
                      element = tempElement;
                      element2 = tempElement2;
                      count = tempCount;
                      position.clear();
                      position.push_back(j);
                    //else statment used to see occurenses within the vector are the same
                    } else if (tempCount == count) {
                      element = tempElement;
                      element2 = tempElement2;
                      count = tempCount;
                      position.push_back(j);
                    }
                  }
                }
              }
            }
          }
          // loop through a vector that has all possiblle outcomes with somes with the highes occurances loop through and print all
          cout << "The song(s) with the most #1 occurrences for selected time period is:" << endl;
          for (int i = 0; i < position.size(); i++) {
            cout << "Song Title: " << NumberOneSong.at(position.at(i)) << endl;
            cout << "Artist: " << NumberOneSong.at(position.at(i) + 1) << endl;
            cout << "# of occurrences: " << count << endl;
          }

        }
      }
    }
      //menuOption 3
    if (menuOption == 3) {
        //max eqauls to starting value of weeksOnBoard in the file
      int max = billBoard.at(0).weeksOnBoard;
      int index = 0;
      cout << "Enter D to select a decade or Y to select a year.";
      cout << "Your choice --> ";
      cin >> OptionTwoSelection;
     // while loop used to indicate if user doesnt input y or d it display error message then allows the user to try again and enter the right one
      while (toupper(OptionTwoSelection) != 'D' && toupper(OptionTwoSelection) != 'Y') {
        cout << "Invalid entry. Try again. " << endl;
        cout << "Enter D to select a decade or Y to select a year. " << endl;
        cout << "Your choice --> ";
        cin >> OptionTwoSelection;
        continue;
      }
        
      if (OptionTwoSelection == 'D' || OptionTwoSelection == 'd') {
        cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010). ";
        cin >> decadeSelection;
          // checks if user decade selection is in range
        if (checkDecadeSelection(decadeSelection, menuOptionOne)) {
          for (int i = 0; i < billBoard.size(); i++) {
              // below variable allow to give the computure the right maximum decade and minimal decade needed to run through
            int negation = decadeSelection % 10;
            int minDecade = decadeSelection - negation;
            int maxDecade = minDecade + 10;
              // if statment used to run through a certain decade
            if (billBoard.at(i).year >= minDecade && billBoard.at(i).year < maxDecade){
                //if previous max is less than the weeksOnBoard then it will replace the max value
                if (max < billBoard.at(i).weeksOnBoard) {
                  max = billBoard.at(i).weeksOnBoard;
                  index = i; //holding the spot of the line in the file with the highest number of (weeks on board)
                }
                //if the weeksOnBoard has the same value then print the first song
                else if(max == billBoard.at(i).weeksOnBoard)
                {
                  max = billBoard.at(i).weeksOnBoard;
                }
            }
          }
          cout << "The song with the highest number of weeks on the charts is: " << endl;
          cout << "          " << billBoard.at(index).songName << " by " << billBoard.at(index).artist << " with " << billBoard.at(index).weeksOnBoard << " weeks on the chart." << endl;
        }
      } else if (OptionTwoSelection == 'Y' || OptionTwoSelection == 'y') {
        cout << "Enter the year you would like to choose (e.g. 2001).";
        cin >> yearSelection;
        cout << endl;
        if (checkYearSelection(yearSelection, menuOptionOne)) {
          for (int i = 0; i < billBoard.size(); i++) {
            if (yearSelection == billBoard.at(i).year) {
              if (max < billBoard.at(i).weeksOnBoard) {
                max = billBoard.at(i).weeksOnBoard;
                index=i;
              }
            }
          }
          cout << "The song with the highest number of weeks on the charts is: " << endl;
          cout << "          " << billBoard.at(index).songName << " by " << billBoard.at(index).artist << " with " << billBoard.at(index).weeksOnBoard << " weeks on the chart." << endl;
        }
      }
    }
      //menuOption 4
    if (menuOption == 4) {

      int max = billBoard.at(0).lastWeekRank - billBoard.at(0).rank;
      vector <int> position;
      cout << "Enter D to select a decade or Y to select a year.";
      cout << "Your choice --> ";
      cin >> OptionTwoSelection;
        // while loop used to indicate if user doesnt input y or d it display error message then allows the user to try again and enter the right one
      while (toupper(OptionTwoSelection) != 'D' && toupper(OptionTwoSelection) != 'Y') {
        cout << "Invalid entry. Try again. " << endl;
        cout << "Enter D to select a decade or Y to select a year. " << endl;
        cout << "Your choice --> ";
        cin >> OptionTwoSelection;
        continue;
      }
      if (OptionTwoSelection == 'D' || OptionTwoSelection == 'd') {
        cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010). ";
        cin >> decadeSelection;
        int totalRank = 0;
        if (checkDecadeSelection(decadeSelection, menuOptionOne)) {
          for (int i = 0; i < billBoard.size(); i++) {
            totalRank = billBoard.at(i).lastWeekRank - billBoard.at(i).rank;
            int negation = decadeSelection % 10;
            int minDecade = decadeSelection - negation;
            int maxDecade = minDecade + 10;
              //iterates through selected decade
            if (billBoard.at(i).year >= minDecade && billBoard.at(i).year < maxDecade) {
                //max less than totalRank then max replaces its value with the value totalRank, the index gets pushed into a new vector
              if (max < totalRank) {
                max = totalRank;
                position.clear();
                position.push_back(i);
                  // if totalRank == max then replace the max with the totalRank, pushback that index into a new vector
                }else if(totalRank == max){
                max = totalRank;
                position.push_back(i);
              }
            }
            totalRank = 0;
          }
        //loops through the vector with all posible results and outputting
          cout << endl;
          cout << "The song(s) with the greatest climb from previous week to current week position: " << endl;
          for(int i = 0; i < position.size(); i++){
          cout << "Song Title: " << billBoard.at(position.at(i)).songName << endl;
          cout << "\t Artist: " << billBoard.at(position.at(i)).artist << endl;
          cout << "\t Week of: " << billBoard.at(position.at(i)).month << "/" << billBoard.at(position.at(i)).day << "/" << billBoard.at(position.at(i)).year << endl;
          cout << "\t Previous Week Position: " << billBoard.at(position.at(i)).lastWeekRank << endl;
          cout << "\t Current Week Position: " << billBoard.at(position.at(i)).rank << endl;
          cout << "\t Difference of " << billBoard.at(position.at(i)).lastWeekRank - billBoard.at(position.at(i)).rank << " between previous week and current week position " << endl;
          cout << endl;
        }
      }
    }else if (OptionTwoSelection == 'Y' || OptionTwoSelection == 'y') {
        cout << "Enter the year you would like to choose (e.g. 2001).";
        cin >> yearSelection;
        cout << endl;
        int totalRank = 0;
        if (checkYearSelection(yearSelection, menuOptionOne)) {
          for (int i = 0; i < billBoard.size(); i++) {
              //if users year input is == to vectors year then it will only iterate through that certain year
            if (yearSelection == billBoard.at(i).year) {
            totalRank = billBoard.at(i).lastWeekRank - billBoard.at(i).rank;
            //checks if user year entered is == to the billBoard year that holds the years in the file
              if (max < totalRank) {
                max = totalRank;
                position.clear();
                position.push_back(i);
                // if totalRank == max then replace the max with the totalRank, pushback that index into a new vector
                }else if(totalRank == max){
                max = totalRank;
                position.push_back(i);
              }
            }
          }
          cout << endl;
          cout << "The song(s) with the greatest climb from previous week to current week position: " << endl;
          for(int i = 0; i < position.size(); i++){
          cout << "Song Title: " << billBoard.at(position.at(i)).songName << endl;
          cout << "\t Artist: " << billBoard.at(position.at(i)).artist << endl;
          cout << "\t Week of: " << billBoard.at(position.at(i)).month << "/" << billBoard.at(position.at(i)).day << "/" << billBoard.at(position.at(i)).year << endl;
          cout << "\t Previous Week Position: " << billBoard.at(position.at(i)).lastWeekRank << endl;
          cout << "\t Current Week Position: " << billBoard.at(position.at(i)).rank << endl;
          cout << "\t Difference of " << billBoard.at(position.at(i)).lastWeekRank -  billBoard.at(position.at(i)).rank << " between previous week and current week position " << endl;
          cout << endl;
          }
        }
      }
      cout << endl;
    }
    if (menuOption == 5) {
    // ignores the previous input
      cin.ignore();
      vector < string > SongName;
      vector < string > SongArtist;
      vector < int > SongMonth;
      vector < int > SongDay;
      vector < int > SongYear;
      vector < int > SongNumber;
      string artistName;
      string artistOriginal;
      int count = 0;
      cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: ";
      // user enters artist name
      getline(cin, artistName);
     // users input for artist name becomes upper cased
      artistName = uppercaseIt(artistName);
      for (int i = 0; i < billBoard.size(); i++) {
          // artist original eqauls to the artist name within the vector
        artistOriginal = billBoard.at(i).artist;
        artistOriginal = uppercaseIt(artistOriginal);
          //if the user enters a artist name that is withing the vector goes to the nested if statement
        if (artistOriginal.find(artistName) != -1) {
            //finds songs with rank 1
          if (billBoard.at(i).rank == 1) {
            SongName.push_back(billBoard.at(i).songName);
            SongArtist.push_back(billBoard.at(i).artist);
            SongMonth.push_back(billBoard.at(i).month);
            SongDay.push_back(billBoard.at(i).day);
            SongYear.push_back(billBoard.at(i).year);
            SongNumber.push_back(billBoard.at(i).rank);
          }
        }
      }
        // if song is the vector has something in it proceed
     if(SongName.size() != 0){
         // used to indicated the max number of outputs and min which is the size of the vector
      int ResultsToPrint = min(10, (int) SongName.size());
      cout << "Retrieval of first 10 #1 records found based upon search by artist name:" << endl;
         // loops through the condition and prints results
      for (int i = 0; i < ResultsToPrint; i++) {
        count++;
        cout << count << ')' << "   Song: " << SongName.at(i) << endl;
        cout << "   Artist: " << SongArtist.at(i) << endl;
        cout << "   Week of: " << SongMonth.at(i) << "/" << SongDay.at(i) << "/" << SongYear.at(i) << endl;
        cout << "   Week Position: " << SongNumber.at(i) << endl;
        cout << endl;
      }
      cout << endl;
      }
        // if the vector has othing in it meaning there were no matching then output the message
      else if(SongName.size() ==0 ){
        cout << "No matching artists were found." << endl;
      }
    }
      // menu option 6 exists the program
    if (menuOption == 6) {
      exit(0);
    }
    //used to indicated if the user doesnt eneter a menu option withing 1 and 6
    else if (menuOption != 1 && menuOption != 2 && menuOption != 3 && menuOption != 4 && menuOption != 5 && menuOption != 6) {
      cout << endl;
      cout << "Invalid value.  Please re-enter a value from the menu options below." << endl;
      cout << endl;
    }
    //to end while(true) loop
  }
  //TI end int main
}


