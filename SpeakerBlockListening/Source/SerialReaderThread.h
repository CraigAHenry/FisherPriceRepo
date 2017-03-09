/******************************************************************************
 @copyright  Copyright 2015 ROLI Ltd.
 Serial terminal reading of an arbitrary kind.
 Opens a device and provides:
 * An abstract way of parsing the input.
 * A callback when data has been framed.
 *******************************************************************************/

#include "Classes.h"
#include "MidiBuffers.h"

template<typename Buffers>

class SerialReaderThread  : private Thread
{
public:


    SerialReaderThread (Buffers& b)
    : Thread ("SerialRead"), buffers (b),
     fileDescriptor (-1), failed (true), hasStarted (false)
    {
    }

    ~SerialReaderThread()
    {
        stopThread (1000);
    }

    //==========================================================================
    // the size is an arbitrary number: data comes in at about 100us/byte
    // so it's got to be enough to allow a reasonable buffer.
    bool open (const char* serialPort)
    {
        portName = serialPort;

        startThread ();

        while (! hasStarted)
            Thread::sleep (2);

        return ! failed;
    }

    //==========================================================================
    bool openExisting (const char* serialPort, const int fileDescriptor)
    {
        this->fileDescriptor = fileDescriptor;
        this->portName = serialPort;

        startThread ();

        while (! hasStarted)
            Thread::sleep (2);

        return ! failed;
    }
    
private:
    //==========================================================================
    Buffers& buffers;
    String portName;
    int fileDescriptor;
    volatile bool hasStarted, failed;


    //==========================================================================
    void run() override
    {
        if (fileDescriptor == -1)
        {
            // not open already, so open a file
            fileDescriptor = ::open (portName.toRawUTF8(), O_RDONLY | O_NOCTTY | O_NONBLOCK);
        }

        if (fileDescriptor == -1)
        {
            // error condition
            failed = true;
            hasStarted = true;
            return;
        }

        ::fsync (fileDescriptor);

        if (! setBaudRate (fileDescriptor))
        {
            failed = true;
            hasStarted = true;
            return;
        }

        failed = false;
        hasStarted = true;

        ::fsync (fileDescriptor);

        uint8 buffer[1024];
        uint8 stringBuffer[1024];
        int stringLoc = 0;
        int consecutiveReadFails = 0;

        while (! threadShouldExit())
        {
            const ssize_t len = ::read (fileDescriptor, buffer, sizeof (buffer));

            if (len > 0)
            {
                consecutiveReadFails = 0;

                for (int i = 0; i < len; ++i)
                {
                    stringBuffer[stringLoc++] = buffer[i];

                    if (buffer[i] == '\n')
                    {
                        buffers.addBuffer(stringBuffer, stringLoc);
                        stringLoc = 0;
                    }
                }
            }
            else
            {
                if (++consecutiveReadFails > 1000)
                {
                    consecutiveReadFails = 0;
                    // Logger::writeToLog ("**** Burning  CPU in SerialReaderThread!");
                    Thread::wait (10);
                }
            }
        }
        
        ::close (fileDescriptor);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SerialReaderThread)
};
