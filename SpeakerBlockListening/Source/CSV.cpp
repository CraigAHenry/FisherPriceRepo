/*
 ==============================================================================

 CSV.cpp
 Created: 8 Nov 2016 5:03:10pm
 Author:  Craig Henry

 ==============================================================================
 */

#include "CSV.h"
#include <algorithm>
#include <array>
using namespace std;

//reads a CSV file if it exists into a 2D array of integers
bool readCSV(const String& fileName, double (*roundValues2D)[8])
{
    String fileLocation = "/Users/craighenry/Documents/R&D/Speaker BLOCK/" + fileName;
    File CSVfile(fileLocation);
    FileInputStream fileStreamIn(CSVfile);

    if(fileStreamIn.openedOk())
    {
        for(int round = 0; round < 5; round++)
        {
            //reads the next line from the file into the buffer. If this line is a null character it reads the next line again.
            String buffer = fileStreamIn.readNextLine();;
            if(buffer == "\0")
            {
                buffer = fileStreamIn.readNextLine();
            }

            // prevents the header line of the csv file from being read into the array
            if(round != 0)
            {

                //reads through each line, reading the substrings between the first two commas into the 2D array. The substring after it has been read is deleted from the string
                for(int speaker = 0; speaker < 8; speaker++)
                {
                    String speakerBuffer;
                    int firstCommaIndex = buffer.indexOfChar(0, ',');
                    int secondCommaIndex = buffer.indexOfChar(firstCommaIndex + 1, ',');
                    speakerBuffer = buffer.substring(firstCommaIndex + 1, secondCommaIndex);

                    if(speakerBuffer.contains("("))
                    {
                        int firstBracketIndex = speakerBuffer.indexOfChar(0, '(');
                        speakerBuffer = speakerBuffer.substring(0, firstBracketIndex);
                    }

                    if(speakerBuffer == "\0")
                    {
                        return true;
                    }

                    roundValues2D[round - 1][speaker] = speakerBuffer.getDoubleValue();
                    buffer = buffer.substring(firstCommaIndex + 1);
                }
            }
        }
        return true;
    }
    return false;
}

// write a CSV file for the individual for each round. This should be updated each time a slider is moved.
// Also checks to see a file already exists, if it does it reads from it and then alters that file.
void writeIndividualCSV(const String& name, const String& otherFileName, double(*roundValues2D)[8], double (*speakerOrder)[8], String* roundValues, String* Comment, bool& read)
{
    // if the filename indicates not to stores these values then the function is returned early
    if(otherFileName == "DONTSTORE")
    {
        return;
    }

    //creates a file location for the csv file
    String fileName = name + "overall.csv";
    String fileLocation = "/Users/craighenry/Documents/R&D/Speaker BLOCK/csvfiles/" + fileName;
    File CSVFile(fileLocation);

    // if the csv files exists and has not been read then read the csv file and update the array of strings.
    // This only happens once as read made true. This means this only occurs when leaving the demo (upon clicked the next round button)
    // if the file does not exist it is created and read is also made true to prevent an empty file being read.
    if(CSVFile.exists() && !read)
    {
        read = readCSV(("csvfiles/" + fileName), roundValues2D);

        for(int i = 0; i < 4; i++)
        {
            updateRowString(roundValues2D, speakerOrder, roundValues, Comment, i);
        }
    }
    else if(!CSVFile.exists())
    {
        CSVFile.create();
        read = true;
    }

    // open an output stream to the same location. Rewrite the file with the new updated values.
    FileOutputStream fileStreamOut(CSVFile);
    fileStreamOut.setPosition(0);
    fileStreamOut.truncate();
    if(fileStreamOut.openedOk())
    {
        fileStreamOut.writeString("Speaker, 1, 2, 3, 4, 5, 6, 7, 8\n");
        fileStreamOut.writeString("RoundOne," + roundValues[0] + "\n");
        fileStreamOut.writeString("RoundTwo," + roundValues[1] + "\n");
        fileStreamOut.writeString("RoundThree," + roundValues[2] + "\n");
        fileStreamOut.writeString("RoundFour," + roundValues[3] + "\n");
    }
}


//Search for name given and update the correct row. If no name present append data.
void attributeCSV(const String& name, const String& fileName, const int& roundNumber, const String* roundValues, const String* Comment)
{
    // if the filename indicates not to stores these values then the function is returned early
    if(fileName == "DONTSTORE")
    {
        return;
    }
    vector<String> beginning;
    vector<String> end;

    StringRef nameRef = StringRef(name);
    bool nameFound = false;

    int counter = 0;

    const String fileLocation = "/Users/craighenry/Documents/R&D/Speaker BLOCK/csvfiles/" + fileName;
    File CSVfile(fileLocation);
// if the file already exists read from it into the beginning string vector. Search each line for the name of the participant.
// If the name is found read the rest of the file into the end string vector. If the file does not exist create a new file
    if(CSVfile.exists())
    {
        FileInputStream fileStreamIn(CSVfile);
        while(fileStreamIn.openedOk() && !fileStreamIn.isExhausted() )
        {
            if(!nameFound)
            {
                String buffer;
                beginning.push_back((fileStreamIn.readNextLine()/* + "\n"*/));
                buffer = beginning[counter].substring(0,beginning[counter].indexOfChar(','));
                nameFound = buffer.contains(nameRef);
            }
            else if(nameFound)
            {
                end.push_back((fileStreamIn.readNextLine() /* + "\n"*/));
            }
            counter++;
        }
    }
    else if (!CSVfile.exists())
    {
        CSVfile.create();
    }

// if no name is found append the round data to the end of the file and return.
// else rewrite the entire file. Write from beginning minus the string with the name in it (size()-1). Input the new data.
// write from end.


    FileOutputStream fileStreamOut(CSVfile);
    if(fileStreamOut.openedOk())
    {
        if(!nameFound)
        {
            //append data
            String outString = name + "," + roundValues[roundNumber] + "," + Comment[roundNumber] + "\n" + "\0";
            fileStreamOut.writeString(outString);
            return;
        }
        else
        {
            fileStreamOut.setPosition(0);
            fileStreamOut.truncate();

            for(int i = 0; i < beginning.size() - 1; i++)
            {
                fileStreamOut.writeString(beginning[i]);
            }

            fileStreamOut.writeString(name + "," + roundValues[roundNumber] + "," + Comment[roundNumber] + "\n" + "\0");

            for(int i = 0; i < end.size(); i++)
            {
                fileStreamOut.writeString(end[i]);
            }
        }
    }
    return;
}

//Array of strings is used to write the CSV file
void updateRowString(double (*roundValues2D)[8], double(*speakerOrder)[8], String* roundValues, String* Comment, const int& roundNumber)
{
    if(roundNumber == -1)
    {
        return;
    }



    array<double, 8> order;
    for(int i = 0; i < 8; i++)
    {
        order[i] = speakerOrder[roundNumber][i];
    }


    String sliderValue = String(roundValues2D[roundNumber][0]) + "(" + String((distance(order.begin(), find(order.begin(), order.end(), 0))) + 1) + ")";
    for(int i = 1; i < 8; i++)

    {
        sliderValue = sliderValue + "," + String(roundValues2D[roundNumber][i]) + "(" + String((distance(order.begin(), find(order.begin(), order.end(), i))) + 1) + ")";
    }

    roundValues[roundNumber] = sliderValue + "," + Comment[roundNumber] + "\0";
}

//2D Array of ints is used internally to set the sliders per round
void update2DArray(const double* sliderValues, double (*roundValues2D)[8], const int& roundNumber)
{
    if(roundNumber == -1 || roundNumber == -2)
    {
        return;
    }
    
    for (int i = 0; i < 8; i++)
    {
        roundValues2D[roundNumber][i]=sliderValues[i];
    }
}

void createRandomOrder(double (*speakerOrder)[8])
{
    random_device rd;
    mt19937 mt(rd());
    for(int round = 0; round < 4; round++)
    {
        vector<int> elements { 0, 1, 2, 3, 4, 5, 6, 7};

        auto currentIndexCounter = elements.size() - 1;

        for (auto iter = elements.rbegin(); iter != elements.rend();
             ++iter, --currentIndexCounter)
        {
            // get int distribution with new range
            uniform_int_distribution<> dis(0, currentIndexCounter);
            const int randomIndex = dis(mt);

            if (*iter != elements.at(randomIndex))
            {
                std::swap(elements.at(randomIndex), *iter);
            }
        }

        for(int i = 0; i < elements.size(); i++)
        {
            speakerOrder[round][i] = elements[i];
        }
    }
}


void speakerOrderCSV(double (*speakerOrder)[8], const String& name, bool& orderRead)
{
    if(orderRead)
    {
        return;
    }

    //creates a file location for the csv file
    String fileName = name + "order.csv";
    String fileLocation = "/Users/craighenry/Documents/R&D/Speaker BLOCK/ordercsv/" + fileName;
    File CSVFile(fileLocation);

    // if the csv files exists and has not been read then read the csv file and update the array of strings.
    // This only happens once as read made true. This means this only occurs when leaving the demo (upon clicked the next round button)
    // if the file does not exist it is created and read is also made true to prevent an empty file being read.
    if(CSVFile.exists())
    {
        readCSV(("ordercsv/" + fileName), speakerOrder);
        orderRead = true;
        return;

    }
    else if(!CSVFile.exists())
    {
        CSVFile.create();
        createRandomOrder(speakerOrder);
        orderRead = true;
    }

    FileOutputStream fileStreamOut(CSVFile);
    if(fileStreamOut.openedOk())
    {
        fileStreamOut.writeString("Speaker Order," + name + "\n");
        for(int round = 0; round < 4; round++)
        {
            String buffer;

            buffer = String("\"Round " + String(round + 1) + "\" ,");

            for(int i = 0; i < 8; i++)
            {

                buffer = buffer + String(speakerOrder[round][i]) + ",";
            }

            fileStreamOut.writeString(buffer +"\n");
        }
    }
    
}


void writeCalibrationCSV(float* calibrationSettings)
{
    String fileName = "calibrationSettings";
    String fileLocation = "/Users/craighenry/Documents/R&D/Speaker BLOCK/calibrationcsv/" + fileName;
    File CSVFile(fileLocation);

    FileOutputStream fileStreamOut(CSVFile);

    fileStreamOut.setPosition(0);
    fileStreamOut.truncate();

    String buffer;

    for(int i = 0; i < 6; i++)
    {
        buffer = buffer + String(calibrationSettings[i]) + ",";
    }
    buffer = buffer + String(calibrationSettings[6]) + "\n";
    fileStreamOut.writeString(buffer);

}
