/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Calibration.h"
#include "Motor.h"



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent,
                               public Slider::Listener,
                               public Button::Listener,
                               public TextEditor::Listener,
                               public ChangeListener,
                               public Timer
{
public:
    //==============================================================================
    MidiBuffers buffer;
    SerialWriterThread serialWriter;
    SerialReaderThread<MidiBuffers> serialReader;

    MainContentComponent()
    :
        serialReader(buffer),
        state (Stopped)


    {

        addAndMakeVisible(nameBox);
        nameBox.addListener(this);

        addAndMakeVisible(nameLabel);
        nameLabel.setText("Full Name", dontSendNotification);
        nameLabel.attachToComponent(&nameBox, true);

        addAndMakeVisible(roundTitle);
        addAndMakeVisible(roundDescription);
        roundDescription.setJustificationType(Justification::topLeft);
        addAndMakeVisible(error);
     //==============================================================================
        // SLIDERS

        addAndMakeVisible (sliderOne);
        sliderOne.setSliderStyle(juce::Slider::LinearVertical);
        sliderOne.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderOne.setRange (0, 100, 1);
        sliderOne.addListener (this);

        addAndMakeVisible (sliderOneLabel);
        sliderOneLabel.setText ("1", dontSendNotification);

        addAndMakeVisible (sliderTwo);
        sliderTwo.setSliderStyle(juce::Slider::LinearVertical);
        sliderTwo.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderTwo.setRange (0, 100, 1);
        sliderTwo.addListener (this);

        addAndMakeVisible (sliderTwoLabel);
        sliderTwoLabel.setText ("2", dontSendNotification);

        addAndMakeVisible (sliderThree);
        sliderThree.setSliderStyle(juce::Slider::LinearVertical);
        sliderThree.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderThree.setRange (0, 100, 1);
        sliderThree.addListener (this);

        addAndMakeVisible (sliderThreeLabel);
        sliderThreeLabel.setText ("3", dontSendNotification);


        addAndMakeVisible (sliderFour);
        sliderFour.setSliderStyle(juce::Slider::LinearVertical);
        sliderFour.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderFour.setRange (0, 100, 1);
        sliderFour.addListener (this);

        addAndMakeVisible (sliderFourLabel);
        sliderFourLabel.setText ("4", dontSendNotification);


        addAndMakeVisible (sliderFive);
        sliderFive.setSliderStyle(juce::Slider::LinearVertical);
        sliderFive.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderFive.setRange (0, 100, 1);
        sliderFive.addListener (this);

        addAndMakeVisible (sliderFiveLabel);
        sliderFiveLabel.setText ("5", dontSendNotification);


        addAndMakeVisible (sliderSix);
        sliderSix.setSliderStyle(juce::Slider::LinearVertical);
        sliderSix.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderSix.setRange (0, 100, 1);
        sliderSix.addListener (this);

        addAndMakeVisible (sliderSixLabel);
        sliderSixLabel.setText ("6", dontSendNotification);


        addAndMakeVisible (sliderSeven);
        sliderSeven.setSliderStyle(juce::Slider::LinearVertical);
        sliderSeven.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderSeven.setRange (0, 100, 1);
        sliderSeven.addListener (this);

        addAndMakeVisible (sliderSevenLabel);
        sliderSevenLabel.setText ("7", dontSendNotification);

        addAndMakeVisible (sliderEight);
        sliderEight.setSliderStyle(juce::Slider::LinearVertical);
        sliderEight.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
        sliderEight.setRange (0, 100, 1);
        sliderEight.addListener (this);

        addAndMakeVisible (sliderEightLabel);
        sliderEightLabel.setText ("8", dontSendNotification);

        
        addAndMakeVisible(scaleOne);
        scaleOne.setText ("Excellent", dontSendNotification);
        scaleOne.setJustificationType(Justification::centredRight);

        addAndMakeVisible(scaleTwo);
        scaleTwo.setText("Good", dontSendNotification);
        scaleTwo.setJustificationType(Justification::centredRight);

        addAndMakeVisible(scaleThree);
        scaleThree.setText("Fair", dontSendNotification);
        scaleThree.setJustificationType(Justification::centredRight);

        addAndMakeVisible(scaleFour);
        scaleFour.setText("Poor", dontSendNotification);
        scaleFour.setJustificationType(Justification::centredRight);

        addAndMakeVisible(scaleFive);
        scaleFive.setText("Bad", dontSendNotification);
        scaleFive.setJustificationType(Justification::centredRight);



        //==============================================================================
        // BUTTONS



        addAndMakeVisible (roundButton);
        roundButton.setButtonText ("Next");
        roundButton.addListener(this);

        addAndMakeVisible (prevRoundButton);
        prevRoundButton.setButtonText ("Previous");
        prevRoundButton.addListener(this);




        addAndMakeVisible (oneButton);
        oneButton.setButtonText ("One");
        oneButton.addListener(this);

        addAndMakeVisible (twoButton);
        twoButton.setButtonText ("Two");
        twoButton.addListener(this);

        addAndMakeVisible (threeButton);
        threeButton.setButtonText ("Three");
        threeButton.addListener(this);

        addAndMakeVisible (fourButton);
        fourButton.setButtonText ("Four");
        fourButton.addListener(this);

        addAndMakeVisible (fiveButton);
        fiveButton.setButtonText ("Five");
        fiveButton.addListener(this);

        addAndMakeVisible (sixButton);
        sixButton.setButtonText ("Six");
        sixButton.addListener(this);

        addAndMakeVisible (sevenButton);
        sevenButton.setButtonText ("Seven");
        sevenButton.addListener(this);

        addAndMakeVisible (eightButton);
        eightButton.setButtonText ("Eight");
        eightButton.addListener(this);

        addAndMakeVisible(AButton);
        AButton.setButtonText ("Reference");
        AButton.addListener(this);

        addAndMakeVisible(BButton);
        BButton.setButtonText ("LUT");
        BButton.addListener(this);



        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.addListener (this);
        playButton.setColour (TextButton::buttonColourId, Colours::green);
        playButton.setEnabled (false);

        addAndMakeVisible (&stopButton);
        stopButton.setButtonText ("Stop");
        stopButton.addListener (this);
        stopButton.setColour (TextButton::buttonColourId, Colours::red);
        stopButton.setEnabled (false);

        addAndMakeVisible(&loopButton);
        loopButton.setButtonText("Loop");
        loopButton.addListener(this);
        loopButton.setColour (TextButton::buttonColourId, Colours::lightblue);


        addAndMakeVisible(&commentBox);
        commentBox.addListener(this);
        
        //PLAYER

        addAndMakeVisible (transportLabel);
        addAndMakeVisible (transportSlider);
        transportSlider.setSliderStyle(Slider::ThreeValueHorizontal);
        transportSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        transportSlider.addListener(this);

        

        startTimer(10);



        
        setSize (800, 600);

        formatManager.registerBasicFormats();       // [1]
        transportSource.addChangeListener(this);   // [2]

        setAudioChannels (2, 2);
        deviceManager.enableInputLevelMeasurement(true);

        int threadAttemptCounter = 0;
        while (!threadSuccess)
        {
            threadSuccess = openThreads(buffer, serialWriter, serialReader);
            if (++threadAttemptCounter > 2)
            {
                std::cout << "device not found \n \0";
                break;
            }
        }




//defaults settings
        changeRoundSettings(currentRound);

    }

    ~MainContentComponent()
    {
        shutdownAudio();
        roundButton.removeListener (this);
        updatePosition(serialWriter, -2);
    }

    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (Colours::lightgrey);


        // You can add your drawing code here!
    }

    void resized() override
    {
        const int sliderTop = 150;
        const int sliderLeft = 150;
        const int sliderSeparation = 50;
        const int labelOffset = 16;
        const int labelOffsetTop = - 10;
        const int buttonTop = sliderTop + 160;

        nameBox.setBounds(sliderLeft, 20, 150, 25);
        error.setBounds(sliderLeft + 150, 20, 400, 25);

        roundTitle.setBounds(sliderLeft, 65, 150, 25);
        roundDescription.setBounds(35, 95, 800, 75);

        sliderOne.setBounds (sliderLeft, sliderTop, 50, 150);
        sliderOneLabel.setBounds(sliderLeft + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderTwo.setBounds (sliderLeft + sliderSeparation, sliderTop, 50, 150);
        sliderTwoLabel.setBounds(sliderLeft + sliderSeparation + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderThree.setBounds (sliderLeft + (sliderSeparation * 2), sliderTop, 50, 150);
        sliderThreeLabel.setBounds(sliderLeft + (sliderSeparation * 2) + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderFour.setBounds (sliderLeft + (sliderSeparation * 3), sliderTop, 50, 150);
        sliderFourLabel.setBounds(sliderLeft + (sliderSeparation * 3) + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderFive.setBounds (sliderLeft + (sliderSeparation * 4), sliderTop, 50, 150);
        sliderFiveLabel.setBounds(sliderLeft + (sliderSeparation * 4) + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderSix.setBounds (sliderLeft + (sliderSeparation * 5), sliderTop, 50, 150);
        sliderSixLabel.setBounds(sliderLeft + (sliderSeparation * 5) + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderSeven.setBounds (sliderLeft + (sliderSeparation * 6), sliderTop, 50, 150);
        sliderSevenLabel.setBounds(sliderLeft + (sliderSeparation * 6) + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        sliderEight.setBounds (sliderLeft + (sliderSeparation * 7), sliderTop, 50, 150);
        sliderEightLabel.setBounds(sliderLeft + (sliderSeparation * 7) + labelOffset, sliderTop + labelOffsetTop, 20, 15);

        scaleOne.setBounds ( sliderLeft - 65 , sliderTop , 75, 15);
        scaleTwo.setBounds ( sliderLeft - 65 , sliderTop + 30, 75, 15);
        scaleThree.setBounds ( sliderLeft - 65 , sliderTop + 60, 75, 15);
        scaleFour.setBounds ( sliderLeft - 65 , sliderTop + 90, 75, 15);
        scaleFive.setBounds ( sliderLeft - 65 , sliderTop + 120, 75, 15);



        roundButton.setBounds (sliderLeft + (sliderSeparation * 9), sliderTop + 120, 50, 15);

        prevRoundButton.setBounds(sliderLeft + (sliderSeparation * 9), sliderTop + 135, 50, 15);

        oneButton.setBounds (sliderLeft, buttonTop, 50, 15);

        twoButton.setBounds (sliderLeft + (sliderSeparation), buttonTop, 50, 15);

        threeButton.setBounds (sliderLeft + (sliderSeparation * 2), buttonTop, 50, 15);

        fourButton.setBounds (sliderLeft + (sliderSeparation * 3), buttonTop, 50, 15);

        fiveButton.setBounds (sliderLeft + (sliderSeparation * 4), buttonTop, 50, 15);

        sixButton.setBounds (sliderLeft + (sliderSeparation * 5), buttonTop, 50, 15);

        sevenButton.setBounds (sliderLeft + (sliderSeparation * 6), buttonTop, 50, 15);

        eightButton.setBounds (sliderLeft + (sliderSeparation * 7), buttonTop, 50, 15);

        commentBox.setBounds(sliderLeft/2, buttonTop + 20, 700, 85);

        AButton.setBounds ( 115, 425, 100, 20);
        BButton.setBounds ( 220, 425, 100, 20);

        inputLevelLabel.setBounds(115, 375, 100, 20);

        transportSlider.setBounds(10, 500, getWidth() - 20, 80);
        transportLabel.setBounds(300, 500, getWidth() - 20, 20);

        playButton.setBounds (115, 450, 100, 20);
        stopButton.setBounds (220, 450, 100, 20);
        loopButton.setBounds (325, 450, 100, 20);
        
        
    }
    
    //==============================================================================
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {


        inputLevel = deviceManager.getCurrentInputLevel();

        if (readerSource == nullptr)
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }

            transportSource.getNextAudioBlock (bufferToFill);


    }

    void releaseResources() override
    {
        transportSource.releaseResources();
    }

    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &transportSource)
        {
            if (transportSource.isPlaying())
                changeState (Playing);
            else if ((state==Stopping) || (state==Playing))
                changeState (Stopped);
            else if (Pausing == state)
                changeState (Paused);
        }
    }


    //==============================================================================


    void textEditorTextChanged(TextEditor& texteditor) override
    {
        if(&texteditor == &nameBox)
        {
            Name = nameBox.getText();
            nameSubmitted = true;
            error.setText(" ", dontSendNotification);
        }
        else if(&texteditor == &commentBox)
        {
            Comment[roundNumber] = commentBox.getText();
            updateRowString(roundValues2D, speakerOrder, roundValues, Comment, roundNumber);
        }
    }

    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &transportSlider)
        {
            if (transportSource.getLengthInSeconds() != 0)
            {
                if (slider == &transportSlider)
                {
                    transportSource.setPosition(transportSlider.getValue());
                    updateLabelFromSlider(state);
                }
            }
        }

        if(slider == &sliderOne ||slider == &sliderTwo ||slider == &sliderThree ||slider == &sliderFour ||slider == &sliderFive ||slider == &sliderSix ||slider == &sliderSeven || slider == &sliderEight )
        {

            sliderValues[(int)speakerOrder[roundNumber][0]] = sliderOne.getValue();
            sliderValues[(int)speakerOrder[roundNumber][1]]= sliderTwo.getValue();
            sliderValues[(int)speakerOrder[roundNumber][2]]= sliderThree.getValue();
            sliderValues[(int)speakerOrder[roundNumber][3]] = sliderFour.getValue();
            sliderValues[(int)speakerOrder[roundNumber][4]] = sliderFive.getValue();
            sliderValues[(int)speakerOrder[roundNumber][5]] = sliderSix.getValue();
            sliderValues[(int)speakerOrder[roundNumber][6]] = sliderSeven.getValue();
            sliderValues[(int)speakerOrder[roundNumber][7]] = sliderEight.getValue();
            update2DArray(sliderValues, roundValues2D, roundNumber);
            updateRowString(roundValues2D, speakerOrder, roundValues, Comment, roundNumber);
            writeIndividualCSV(Name, fileName, roundValues2D, speakerOrder, roundValues, Comment, read);
        }
    }
    
    void buttonClicked (Button* button) override
    {

        if (button == &playButton)  playButtonClicked();
        if (button == &stopButton)  stopButtonClicked();
        if (button == &loopButton)  loopButtonClicked();

        if(button ==&roundButton && roundNumber == -2) roundButtonClicked();
        else if (button == &roundButton && nameSubmitted && roundNumber < 4) roundButtonClicked();
        else if (button == &roundButton && !nameSubmitted)
        {
            error.setColour(juce::Label::textColourId, Colours::red) ;
            error.setText("Please submit your full name before going to the next round", dontSendNotification);
        }

        if (button == &prevRoundButton && roundNumber != 0 && roundNumber > -2) prevRoundButtonClicked();

        if (button == &AButton) AButtonClicked();
        if (button == &BButton) BButtonClicked();
        if(orderRead)
        {   
            if (button == &oneButton) positionButtonClicked(1, (int)speakerOrder[roundNumber][0] + 1);
            if (button == &twoButton) positionButtonClicked(2, (int)speakerOrder[roundNumber][1] + 1);
            if (button == &threeButton) positionButtonClicked(3, (int)speakerOrder[roundNumber][2] + 1);
            if (button == &fourButton) positionButtonClicked(4, (int)speakerOrder[roundNumber][3] + 1);
            if (button == &fiveButton) positionButtonClicked(5, (int)speakerOrder[roundNumber][4] + 1);
            if (button == &sixButton) positionButtonClicked(6, (int)speakerOrder[roundNumber][5] + 1);
            if (button == &sevenButton) positionButtonClicked(7, (int)speakerOrder[roundNumber][6] + 1);
            if (button == &eightButton) positionButtonClicked(8, (int)speakerOrder[roundNumber][8] + 1);
        }
        else
        {
            if (button == &oneButton) positionButtonClicked(1, 1);
            if (button == &twoButton) positionButtonClicked(2, 2);
            if (button == &threeButton) positionButtonClicked(3,3);
            if (button == &fourButton) positionButtonClicked(4, 4);
            if (button == &fiveButton) positionButtonClicked(5, 5);
            if (button == &sixButton) positionButtonClicked(6, 6);
            if (button == &sevenButton) positionButtonClicked(7, 7);
            if (button == &eightButton) positionButtonClicked(8, 8);
            
        }
    }

    void playButtonClicked()
    {


        if ((state == Stopped) || (state== Paused))
            changeState (Starting);
        else if (state == Playing)
            changeState(Pausing);
    }

    void stopButtonClicked()
    {
        if (state == Paused)
            changeState (Stopped);
        else
            changeState (Stopping);
    }

    void loopButtonClicked()
    {
        if (looping == false)
        {
            looping = true;
            loopButton.setColour (TextButton::buttonColourId, Colours::cornflowerblue);


        }
        else
        {
            looping = false;
            loopButton.setColour (TextButton::buttonColourId, Colours::lightblue);

        }
    }

    void roundButtonClicked()
    {

        // for calibration and demo rounds

        if(currentRound == Calibration)
        {
            roundNumber++;
            changeRoundSettings(currentRound);
            return;
        }
        else if(currentRound == Demo)
        {
            int decision =NativeMessageBox::showOkCancelBox(AlertWindow::AlertIconType::NoIcon , "Begin?", "You are now leaving the demo, would you like to begin? If the app closes at any point: re-open, enter your full name again and pick up where you left off.");
            if (decision == 0)
            {
                return;
            }
        }

        attributeCSV(Name, fileName, roundNumber, roundValues, Comment);
        roundNumber++;


        
        changeRoundSettings(currentRound);

        if(roundNumber != 4)
        {
            for(int i = 0; i < 8; i++)
            {

                std::cout << speakerOrder[roundNumber][i];

            }
            std::cout << '\n';

            updateSliderValues(roundValues2D, roundNumber);
        }
        
    }

    void prevRoundButtonClicked()
    {

        roundNumber --;

        for(int i = 0; i < 7; i++)
        {
            std::cout << speakerOrder[roundNumber][i];
        }
        std::cout << '\n';

        updateSliderValues(roundValues2D, roundNumber);
        changeRoundSettings(currentRound);

    }

    void positionButtonClicked(int buttonNumber, int position)
    {


        if (position !=0)
        {
            buttonUnderTest = buttonNumber;
            driverUnderTest = position;
            changeSource(buttonNumber);

            if(position == 8)
            {
                position = reference;
            }
            
            if(!LUT)
            {
                BButtonClicked();
            }
        }
        updatePosition(serialWriter, position);
    }

    void AButtonClicked()
    {
        LUT = false;
        positionButtonClicked(0, 0);
        AButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
        BButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
    }

    void BButtonClicked()
    {
        LUT = true;
        positionButtonClicked(buttonUnderTest, driverUnderTest);
        AButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        BButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
    }



    void disableButtons(const bool& moving, bool& oldMoving)
    {
        if(moving == true && oldMoving == false)
        {
            oneButton.setEnabled(false);
            twoButton.setEnabled(false);
            threeButton.setEnabled(false);
            fourButton.setEnabled(false);
            fiveButton.setEnabled(false);
            sixButton.setEnabled(false);
            sevenButton.setEnabled(false);
            eightButton.setEnabled(false);
            oldMoving = true;
        }
        if(moving == false && oldMoving == true)
        {
            oneButton.setEnabled(true);
            twoButton.setEnabled(true);
            threeButton.setEnabled(true);
            fourButton.setEnabled(true);
            fiveButton.setEnabled(true);
            sixButton.setEnabled(true);
            sevenButton.setEnabled(true);
            eightButton.setEnabled(true);
            oldMoving = false;
        }
    }

    void changeSource(const int buttonNumber)
    {
        sliderOne.setEnabled(false);
        sliderTwo.setEnabled(false);
        sliderThree.setEnabled(false);
        sliderFour.setEnabled(false);
        sliderFive.setEnabled(false);
        sliderSix.setEnabled(false);
        sliderSeven.setEnabled(false);
        sliderEight.setEnabled(false);
        oneButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        twoButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        threeButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        fourButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        fiveButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        sixButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        sevenButton.setColour (TextButton::buttonColourId, Colours::lightgrey);
        eightButton.setColour (TextButton::buttonColourId, Colours::lightgrey);


        if (buttonNumber == 1)
        {
            sliderOne.setEnabled(true);
            oneButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][0]) + "   button = 1 \n";
        }
        else if (buttonNumber == 2)
        {
            sliderTwo.setEnabled(true);
            twoButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][1]) + "   button = 2 \n";

        }
        else if (buttonNumber == 3)
        {
            sliderThree.setEnabled(true);
            threeButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][2]) + "   button = 3 \n";

        }
        else if (buttonNumber == 4)
        {
            sliderFour.setEnabled(true);
            fourButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][3]) + "   button = 4 \n";

        }
        else if (buttonNumber == 5)
        {
            sliderFive.setEnabled(true);
            fiveButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][4]) + "   button = 5 \n";

        }
        else if (buttonNumber == 6)
        {
            sliderSix.setEnabled(true);
            sixButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][5]) + "   button = 6 \n";

        }
        else if (buttonNumber == 7)
        {
            sliderSeven.setEnabled(true);
            sevenButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][6]) + "   button = 7 \n";

        }

        else if (buttonNumber == 8)
        {
            sliderEight.setEnabled(true);
            eightButton.setColour (TextButton::buttonColourId, Colours::darkgrey);
            std::cout << "speaker = " + String(speakerOrder[roundNumber][7]) + "   button = 8 \n";

        }
        
        
        

    }



    enum roundSettings
    {   Calibration = -2,
        Demo,
        RoundOne,
        RoundTwo,
        RoundThree,
        RoundFour,
        Finished
    };

    void changeRoundSettings(roundSettings& currentRound)
    {
        if (currentRound != roundNumber)
        {

            if(state == Playing)
            {
                stopButtonClicked();
            }

            if(roundNumber == -2)
            {
                currentRound = Calibration;
            }
            else if(roundNumber == -1)
            {
                currentRound = Demo;
            }
            else if(roundNumber == 0)
            {
                currentRound = RoundOne;
            }
            else if (roundNumber == 1)
            {
                currentRound = RoundTwo;
            }
            else if (roundNumber == 2)
            {
                currentRound = RoundThree;
            }

            else if (roundNumber == 3)
            {
                currentRound = RoundFour;
            }
            else
            {
                currentRound = Finished;
            }
        }



            switch (currentRound)
            {
                case Calibration:
                    open("/Users/craighenry/Documents/Music/pinknoise.wav");
                    positionButtonClicked(1, 1);
                    roundTitle.setText("Calibration", dontSendNotification);
                    roundDescription.setText("Calibrate the level of each speaker. First set all the speakers to zero volume manually, increase them until they are all within 3dB of 70dBA. Then press the calibrate button for each speaker.", dontSendNotification);
                    addAndMakeVisible(&inputLevelLabel);
                    scaleOne.setText(">73dBA", dontSendNotification);
                    scaleTwo.setText("70dBA", dontSendNotification);
                    scaleThree.setText("67dBA", dontSendNotification);
                    scaleFour.setText("64dBA", dontSendNotification);
                    scaleFive.setText("<61dBA", dontSendNotification);
                    sliderOne.setEnabled(false);
                    sliderTwo.setEnabled(false);
                    sliderThree.setEnabled(false);
                    sliderFour.setEnabled(false);
                    sliderFive.setEnabled(false);
                    sliderSix.setEnabled(false);
                    sliderSeven.setEnabled(false);
                    sliderEight.setEnabled(false);


                    fileName = "DONTSTORE";
                    break;

                case Demo:
                    open("/Users/craighenry/Documents/Music/AdamShort.wav");
                    roundTitle.setText("Demo Round", dontSendNotification);
                    roundDescription.setText("This is the demo round: each round you will be presented with a 10 second loop. Please evaluate each speaker according to your general preference by using the sliders. Please leave any comments in the text box, for example, what you liked about your favourite speaker each round or a small comment on each speaker.", dontSendNotification);
                    inputLevelLabel.removeFromDesktop();
                    scaleOne.setText ("Excellent", dontSendNotification);
                    scaleTwo.setText("Good", dontSendNotification);
                    scaleThree.setText("Fair", dontSendNotification);
                    scaleFour.setText("Poor", dontSendNotification);
                    scaleFive.setText("Bad", dontSendNotification);
                    fileName = "DONTSTORE";
                    positionButtonClicked(4, 4);

                    break;

                case RoundOne:
                    open("/Users/craighenry/Documents/Music/BurnShort.wav");
                    roundTitle.setText("Round One", dontSendNotification);
                    roundDescription.setText("Description of what is required of the listener for round one", dontSendNotification);
                    fileName = "RoundOne.csv";
                    nameBox.setReadOnly(true);
                    writeIndividualCSV(Name, fileName, roundValues2D, speakerOrder, roundValues, Comment, read);
                    speakerOrderCSV(speakerOrder, Name, orderRead);
                    positionButtonClicked(1, speakerOrder[roundNumber][0] + 1);
                    break;

                case RoundTwo:
                    open("/Users/craighenry/Documents/Music/AdamShort.wav");
                    roundTitle.setText("Round Two", dontSendNotification);
                    roundDescription.setText("Description of what is required of the listener for round two", dontSendNotification);
                    fileName = "RoundTwo.csv";
                    positionButtonClicked(1, speakerOrder[roundNumber][0] + 1);
                    break;

                case RoundThree:
                    open("/Users/craighenry/Documents/Music/FightShort.wav");
                    roundTitle.setText("Round Three", dontSendNotification);
                    roundDescription.setText("Description of what is required of the listener for round three", dontSendNotification);
                    fileName = "RoundThree.csv";
                    positionButtonClicked(1, speakerOrder[roundNumber][0] + 1);
                    break;

                case RoundFour:
                    open("/Users/craighenry/Documents/Music/EarthShort.wav");
                    roundTitle.setText("Round Four", dontSendNotification);
                    roundDescription.setText("Description of what is required of the listener for round four", dontSendNotification);
                    fileName = "RoundFour.csv";
                    positionButtonClicked(1, speakerOrder[roundNumber][0] + 1);
                    break;

                case Finished:
                    roundTitle.setText("Finished!", dontSendNotification);
                    roundDescription.setText("That was the last round, thanks, you may now close the application.", dontSendNotification);
                    fileName = "DONTSTORE";
                    break;

            }
            updateSliderValues(roundValues2D, roundNumber);
    }

    void updateSliderValues(double(*roundValues2D)[8], const int& roundNumber)
    {
        if(roundNumber == -1 || roundNumber == -2 || roundNumber == 4)
        {
            return;
        }

        sliderOne.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][0]]);
        sliderTwo.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][1]]);
        sliderThree.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][2]]);
        sliderFour.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][3]]);
        sliderFive.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][4]]);
        sliderSix.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][5]]);
        sliderSeven.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][6]]);
        sliderEight.setValue(roundValues2D[roundNumber][(int)speakerOrder[roundNumber][7]]);
        
    }






private:
    //==============================================================================

    // Your private member variables go here...
    Slider sliderOne;
    Label sliderOneLabel;
    Slider sliderTwo;
    Label sliderTwoLabel;
    Slider sliderThree;
    Label sliderThreeLabel;
    Slider sliderFour;
    Label sliderFourLabel;
    Slider sliderFive;
    Label sliderFiveLabel;
    Slider sliderSix;
    Label sliderSixLabel;
    Slider sliderSeven;
    Label sliderSevenLabel;
    Slider sliderEight;
    Label sliderEightLabel;

    Label error;
    Label roundTitle;
    Label roundDescription;

    Label scaleOne;
    Label scaleTwo;
    Label scaleThree;
    Label scaleFour;
    Label scaleFive;

    TextButton roundButton;
    TextButton prevRoundButton;

    TextButton oneButton;
    TextButton twoButton;
    TextButton threeButton;
    TextButton fourButton;
    TextButton fiveButton;
    TextButton sixButton;
    TextButton sevenButton;
    TextButton eightButton;

    TextButton AButton;
    TextButton BButton;

    TextEditor nameBox;
    Label nameLabel;

    TextEditor commentBox;

    Slider transportSlider;
    Label transportLabel;

    TextButton playButton;
    TextButton stopButton;
    TextButton loopButton;

    String lengthTime;
    String timeElapsed;

    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping,
        Paused,
        Pausing,
        Changing
    };

    TransportState state;

    int reference = 4;

    int driverUnderTest = 4;
    int buttonUnderTest = 4;
    bool LUT = false;
    bool looping = false;
    bool read = false;
    bool orderRead = false;
    double sliderValues[8];
    int roundNumber = -1;
    double roundValues2D [4][8];
    double speakerOrder[4][8];
    String roundValues[4];
    String Name;
    String fileName = "RoundOne.csv";
    String previousFileName;
    bool nameSubmitted = false;
    bool momentarypause = false;
    bool movingBool = false;
    bool oldMovingBool = false;
    bool threadSuccess = false;

    roundSettings currentRound = Demo;

    String Comment[4];

    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    Random random;

    double inputLevel = 0;
    Label inputLevelLabel;


    void timerCallback() override
    {
        if(threadSuccess)
        {
            moving(serialReader, buffer, movingBool);
        }
        
        if(movingBool && state == Playing)
        {
            playButtonClicked();
            momentarypause = true;
        }
        if(!movingBool && momentarypause)
        {
            playButtonClicked();
            momentarypause = false;
        }


        disableButtons(movingBool, oldMovingBool);

        const RelativeTime position (transportSource.getCurrentPosition());


        const int minutes = ((int) position.inMinutes()) % 60;
        const int seconds = ((int) position.inSeconds()) % 60;
        const int millis  = ((int) position.inMilliseconds()) % 1000;


        const String currentTime  = (String::formatted ("%02d:%02d:%03d", minutes, seconds, millis));
        timeElapsed = currentTime + " / " + lengthTime;
        transportSlider.setValue(transportSource.getCurrentPosition(),dontSendNotification);
        transportLabel.setText (timeElapsed, dontSendNotification);


        if (transportSource.getCurrentPosition() > transportSlider.getMaxValue() - 0.01)
        {
            if(looping == true)
            {
                transportSource.setPosition(transportSlider.getMinValue());
            }
            else if (looping == false)
            {
                stopButtonClicked();
            }
        }


        if(roundNumber == -2)
        {
            // get volume and set to currentPosition Slider;
            inputLevelLabel.setText(String(inputLevel), dontSendNotification);
            
        }
    }

    void updateLabelFromSlider(TransportState currentState)
    {   changeState(Changing);
        timerCallback();
        changeState(currentState);
    }

    void changeState (TransportState newState)
    {
        if (state != newState)
        {
            state = newState;

            switch (state)
            {
                case Stopped:                           // [3]
                    stopButton.setEnabled (false);
                    playButton.setEnabled (true);
                    playButton.setButtonText("Play");
                    stopButton.setButtonText("Stop");
                    transportSource.setPosition (transportSlider.getMinValue());
                    transportSlider.setValue(transportSlider.getMinValue());

                    break;

                case Starting:                          // [4]
                    transportSource.start();
                    break;

                case Playing:                           // [5]
                    stopButton.setEnabled (true);
                    playButton.setButtonText("Pause");
                    stopButton.setButtonText("Stop");
                    break;

                case Stopping:                          // [6]
                    transportSource.stop();
                    break;

                case Paused:
                    playButton.setButtonText("Resume");
                    stopButton.setButtonText("Return to start");
                    break;

                case Pausing:
                    transportSource.stop();
                    break;

                case Changing:
                    timerCallback();
                    break;

            }
        }
    }

    void open(String Address)
    {
            File file (Address);
            AudioFormatReader* reader = formatManager.createReaderFor (file);

            if (reader != nullptr)
            {
                ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource (reader, true);
                transportSource.setSource (newSource, 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                readerSource = newSource.release();
            }
            const RelativeTime total (transportSource.getLengthInSeconds());
            const int minutest = ((int) total.inMinutes()) % 60;
            const int secondst = ((int) total.inSeconds()) % 60;
            const int millist  = ((int) total.inMilliseconds()) % 1000;
            lengthTime  = (String::formatted ("%02d:%02d:%03d", minutest, secondst, millist));
            transportLabel.setText("00:00:00 / " + lengthTime, dontSendNotification);

            transportSlider.setRange(0, transportSource.getLengthInSeconds());
        transportSlider.setMaxValue(transportSource.getLengthInSeconds());
    }



    //==========================================================================



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
