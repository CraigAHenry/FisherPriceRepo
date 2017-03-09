#include "../JuceLibraryCode/JuceHeader.h"
#include <termios.h>




static bool setBaudRate (int fileDescriptor)
{
    (void) fileDescriptor;

    struct termios tio;

    if (tcgetattr (fileDescriptor, &tio) < 0)
    {
        return false;
    }

    tio.c_cflag = CLOCAL | CREAD | CS8;

    cfsetspeed (&tio, B9600);

    if (tcsetattr (fileDescriptor, TCSAFLUSH, &tio) != 0)
    {
        return false;
    }
    //#endif

    return true;
}
