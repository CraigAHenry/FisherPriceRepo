/******************************************************************************
 @copyright  Copyright 2015 ROLI Ltd.
 MidiBuffers.h : place to put MIDI messages.
 Allows thread-safe retrieval.
 by Ben Supper
 *******************************************************************************/

class MidiBuffers
{
public:
    MidiBuffers() {}

    //==========================================================================
    bool addBuffer (const uint8* data, size_t numBytes) noexcept
    {
        {
            const ScopedLock lock (rwLock);

            if (bufCount < numBuffers)
            {
                buffers[bufWrite].addData (data, numBytes);
                bufWrite = (bufWrite + 1) % numBuffers;
                ++bufCount;
                waitableEvent.signal();
                return true;
            }
        }

        // just drop the packet in the event of an overflow
        //SeaboardLogger::logWarning ("MidiBuffers ran out of buffers!");
        return false;
    }

    //==========================================================================
    struct MidiEvent
    {
        MidiEvent() noexcept  : numBytes (0) {}

        void reset() noexcept
        {
            numBytes = 0;
        }

        void startMessage (const uint8 byte) noexcept
        {
            jassert (byte >= 0x80);
            data[0] = byte;
            numBytes = 1;
        }

        void addData (const uint8* inData, size_t inNumBytes) noexcept
        {
            if (inNumBytes < (size_t) numElementsInArray (data))
            {
                memcpy (data, inData, inNumBytes);
                numBytes = (int) inNumBytes;
            }
            else
            {
                //SeaboardLogger::logWarning ("MidiEvent buffer too short!");
            }
        }

        bool hasValidStatusByte() const noexcept
        {
            return numBytes != 0;
        }


        int numBytes;
        uint8 data[1024]; // NB: this size will be enough for anything from the STM32

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiEvent)
    };

    //==========================================================================
    // this will block until there's data

    bool isThereData()
    {
        if (bufCount == 0)
            return false;
        else
            return true;
    }

    const MidiEvent* getNextBuffer() noexcept
    {
        if (bufCount == 0)
        {
            waitableEvent.reset(); // no pending signals
            waitableEvent.wait(-1);
        }

        return &buffers[bufRead];
    }

    void releaseBuffer() noexcept
    {
        const ScopedLock lock (rwLock);
        buffers[bufRead].reset();
        bufRead = (bufRead + 1) % numBuffers;
        --bufCount;
    }

private:
    //==========================================================================
    enum { numBuffers = 16 };

    int bufWrite, bufRead, bufCount;
    MidiEvent buffers[numBuffers];
    CriticalSection rwLock;
    WaitableEvent waitableEvent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiBuffers)
};