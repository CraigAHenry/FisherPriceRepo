/*
  ==============================================================================

    Motor.h
    Created: 24 Nov 2016 10:28:56am
    Author:  Craig Henry

  ==============================================================================
*/

#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED
#include "SerialReaderThread.h"
#include "SerialWriterThread.h"

// open serial bidirectional communication with the arduino. Return true if successful.
bool openThreads(MidiBuffers& buffer, SerialWriterThread& serialWriter, SerialReaderThread<MidiBuffers>& serialReader)
{

    bool serialWriterOpen =serialWriter.open("/dev/tty.usbmodem14111");
    Thread::sleep(1000);
    bool serialReaderOpen =serialReader.openExisting(serialWriter.getPortName(), serialWriter.getFileDescriptor());
    Thread::sleep(1000);
    bool success = (serialReaderOpen && serialWriterOpen);

    return success;
}


// read from the reader thread. The only data being sent by the arduino is a bool reporting whether or not the speaker table is on the move. This information is read into the equivalent bool in app.
void moving(SerialReaderThread<MidiBuffers>& serialReader, MidiBuffers& buffer, bool& movingBool)
{
    bool isThereData = buffer.isThereData();
    String s;
    while (isThereData)
    {
        const MidiBuffers::MidiEvent* event;
        event = buffer.getNextBuffer();
        s = String((const char*)event->data, (const size_t)event->numBytes);
        std::cout << s;

        buffer.releaseBuffer();
        isThereData = buffer.isThereData();
        char movingChar;
        movingChar = s.operator[](0);

        if (movingChar == '0')
        {
            movingBool = false;
        }
        else if (movingChar =='1')
        {
            movingBool = true;
        }
    }

}



// tell the arduino which position to move to
void updatePosition(SerialWriterThread& serialWriter, int desiredPosition)
{
    serialWriter.write(&desiredPosition, 1);
}




#endif  // MOTOR_H_INCLUDED
