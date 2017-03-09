/*
 ==============================================================================

 SerialWriter.h
 Created: 23 Nov 2016 4:06:35pm
 Author:  Craig Henry

 ==============================================================================
 */

#ifndef SERIALWRITER_H_INCLUDED
#define SERIALWRITER_H_INCLUDED

/******************************************************************************
 @copyright  Copyright 2015 ROLI Ltd.
 Serial terminal writing of an arbitrary kind.
 Opens a device and provides:
 * Threadsafe reading and writing.
 * Buffering of output data.
 * Software FIFO transmission (limits blocking).
 For console-type access, use writeString to write a line at a time.
 Otherwise, write a byte at a time using writeByte.
 *******************************************************************************/



class SerialWriterThread : private Thread
{
public:
    SerialWriterThread()
    : Thread ("SerialWrite"),
    fifo (fifoSize),
    fileDescriptor (-1)
    {
    }

    ~SerialWriterThread()
    {
        stopThread (500);

        if (fileDescriptor != -1)
            ::close (fileDescriptor);
    }

    //==========================================================================
    bool open (const char* serialPort)
    {
        portName = serialPort;
        fileDescriptor = ::open (serialPort, O_RDWR | O_NOCTTY | O_NONBLOCK);

        if (fileDescriptor == -1)
        {
            perror(sys_errlist[errno]);
            return false;
        }

        startThread();

        return true;
    }

    //==========================================================================
    const int getFileDescriptor() const noexcept
    {
        return fileDescriptor;
    }

    //==========================================================================
    const char* getPortName() const noexcept
    {
        return portName.getCharPointer();
    }

    //==========================================================================
    bool write (const void* data, size_t numBytes)
    {
        jassert (data != nullptr);
        jassert (numBytes >= 0 && numBytes < fifoSize);

        uint8 escapedData [1025];
        jassert (numBytes < sizeof (escapedData));

        for (int i = 0; i < (int) numBytes; ++i)
        {
            const uint8 b = static_cast<const uint8*>(data) [i];
            escapedData[i] = b == 0x0a ? 0xfa : b;  // substitute line-feed char
        }

        // add EOL character
        escapedData [numBytes++] = 0xff;

        int start1, size1, start2, size2;
        fifo.prepareToWrite ((int) numBytes, start1, size1, start2, size2);

        if (size1 + size2 < (int) numBytes)
        {
            return false;
        }

        if (size1 > 0) memcpy (writeFifo + start1, escapedData, (size_t) size1);
        if (size2 > 0) memcpy (writeFifo + start2, addBytesToPointer (escapedData, size1), (size_t) size2);

        fifo.finishedWrite (size1 + size2);
        notify();
        return true;
    }

private:
    enum
    {
        fifoSize = 4096,
        chunkSizeToProcess = 1024
    };

    AbstractFifo fifo;
    uint8 writeFifo[fifoSize];

    int fileDescriptor;
    String portName;

    //==========================================================================
    void run() override
    {
        while (! threadShouldExit())
        {
            int start1, size1, start2, size2;
            fifo.prepareToRead ((int) chunkSizeToProcess, start1, size1, start2, size2);

            if (size1 > 0)
            {
                auto result = ::write (fileDescriptor, writeFifo + start1, (size_t) size1);
                fifo.finishedRead (size1);

                if (size2 > 0)
                {
                    result =::write (fileDescriptor, writeFifo + start2, (size_t) size2);
                    fifo.finishedRead (size2);
                }

                (void) result;
            }

            wait (100);
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SerialWriterThread)
};



#endif  // SERIALWRITER_H_INCLUDED
