// ------------------------------------------------------
// Protrekkr
// Based on Juan Antonio Arguelles Rius's NoiseTrekker.
//
// Copyright (C) 2008-2011 Franck Charlet.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL FRANCK CHARLET OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
// ------------------------------------------------------

// ------------------------------------------------------
// Includes
#include "include/editor_instrument.h"
#include "include/editor_sample.h"
#include "../samples/include/samples_pack.h"
#include "../files/include/files_list.h"

#include "../../release/distrib/replay/lib/include/samples_unpack.h"
#include "../../release/distrib/replay/lib/include/wavpack.h"

#include "../../release/distrib/replay/lib/include/endianness.h"

#include "../files/include/files.h"
#include "../ui/include/requesters.h"

// ------------------------------------------------------
// Variables
extern REQUESTER Overwrite_Requester;

int Allow_Buttons;
int Allow_Sliders;
int Allow_Buttons_Pushed;
int Allow_Global;
int Allow_Global_Pushed;
int Allow_Global_Sliders;

int Instrs_ykar = 0;
int Instrs_items = 128;
int Instrs_index = 0;
int Instrs_curr = 0;
int Instrs_last_index = -1;

extern char Mp3_BitRate[MAX_INSTRS];
extern int Type_Mp3_BitRate[];
extern char At3_BitRate[MAX_INSTRS];
extern int Type_At3_BitRate[];

void Lock_Sample(int instr_nbr, int split);

// ------------------------------------------------------
// Functions
void set_instr_global(void)
{
    int i;
    Allow_Global = BUTTON_NORMAL | BUTTON_DISABLED;
    Allow_Global_Pushed = BUTTON_PUSHED | BUTTON_DISABLED;
    Allow_Global_Sliders = FALSE;
    
    for(i = 0; i < 16; i++)
    {
        if(SampleType[Current_Instrument][i])
        {
            Allow_Global = BUTTON_NORMAL;
            Allow_Global_Pushed = BUTTON_PUSHED;
            Allow_Global_Sliders = TRUE;
            return;
        }
    }
}

void Draw_Instrument_Ed(void)
{
    Draw_Editors_Bar(USER_SCREEN_INSTRUMENT_EDIT);

    Gui_Draw_Button_Box(0, (Cur_Height - 153), fsize, 130, "", BUTTON_NORMAL | BUTTON_DISABLED);

    switch(seditor)
    {
        case 0:
            Gui_Draw_Flat_Box("Instrument Editor [Sample]");

            Gui_Draw_Button_Box(640, (Cur_Height - 134), 39, 16, "Pack:", BUTTON_NORMAL | BUTTON_DISABLED);

            Gui_Draw_Button_Box(8, (Cur_Height - 72), 44, 16, "F.Decay", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(8, (Cur_Height - 54), 44, 16, "Def.Vol", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(8, (Cur_Height - 108), 134, 16, "Loop Tempo Auto Sync.", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(8, (Cur_Height - 90), 134, 16, "Synchro Length (In Lines)", BUTTON_NORMAL | BUTTON_DISABLED);

            Gui_Draw_Button_Box(382, (Cur_Height - 62), 44, 16, "Amplify", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(382, (Cur_Height - 44), 44, 16, "Tune", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(382, (Cur_Height - 134), 64, 16, "Length", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(382, (Cur_Height - 116), 64, 16, "Loop Start", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(382, (Cur_Height - 98), 64, 16, "Loop End", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(382, (Cur_Height - 80), 64, 16, "Loop Type", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(510, (Cur_Height - 134), 58, 16, "Split", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(510, (Cur_Height - 116), 58, 16, "Base Note", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(510, (Cur_Height - 98), 58, 16, "Midi Prog.", BUTTON_NORMAL | BUTTON_DISABLED);

            Gui_Draw_Button_Box(729, (Cur_Height - 134), 60, 16, "Mp3 BitRate", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_CENTERED);
            Gui_Draw_Button_Box(729, (Cur_Height - 98), 60, 16, "At3 BitRate", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_CENTERED);
            break;

        case 1:
            Gui_Draw_Flat_Box("Instrument Editor [Loop Editor]");
            Gui_Draw_Button_Box(427, (Cur_Height - 130), 58, 16, "LS. Value", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(427, (Cur_Height - 112), 58, 16, "LE. Value", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(20, (Cur_Height - 130), 56, 16, "Loop Start", BUTTON_NORMAL | BUTTON_DISABLED);
            Gui_Draw_Button_Box(20, (Cur_Height - 112), 403, 68, "", BUTTON_NORMAL);
            break;
    } //Switch Sampler Screen
}

void Actualize_Instrument_Ed(int typex, char gode)
{
    int FineTune_Value;
    int Allow_GSM = BUTTON_DISABLED;
    int Allow_MP3 = BUTTON_DISABLED;
    int Allow_ADPCM = BUTTON_DISABLED;
    int Allow_TRUESPEECH = BUTTON_DISABLED;
    int Allow_AT3 = BUTTON_DISABLED;

    Check_Loops();

    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT)
    {

#if defined(__GSM_CODEC__)
        Allow_GSM = 0;
#endif
#if defined(__MP3_CODEC__)
        Allow_MP3 = 0;
#endif
#if defined(__ADPCM_CODEC__)
        Allow_ADPCM = 0;
#endif
#if defined(__TRUESPEECH_CODEC__)
        Allow_TRUESPEECH = 0;
#endif
#if defined(__AT3_CODEC__)
        Allow_AT3 = 0;
#endif

        if(SampleType[Current_Instrument][Current_Instrument_Split])
        {
            Allow_Buttons = BUTTON_NORMAL;
            Allow_Buttons_Pushed = BUTTON_PUSHED;
            Allow_Sliders = TRUE;
        }
        else
        {
            Allow_Buttons = BUTTON_NORMAL | BUTTON_DISABLED;
            Allow_Buttons_Pushed = BUTTON_PUSHED | BUTTON_DISABLED;
            Allow_Sliders = FALSE;
        }
        set_instr_global();

        switch(seditor)
        {
            case 0:
                Gui_Draw_Button_Box(268, (Cur_Height - 134), 88, 16, "Fine Loop Editor", Allow_Buttons | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(268, (Cur_Height - 108), 88, 16, "Save Instrument", Allow_Global | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(268, (Cur_Height - 90), 88, 16, "Export .Wav File", Allow_Buttons | BUTTON_TEXT_CENTERED);

                // Instrument editor mode
                if(gode == 0 || gode == 1)
                {
                    if(Sample_Amplify[Current_Instrument][Current_Instrument_Split] > 4.0f) Sample_Amplify[Current_Instrument][Current_Instrument_Split] = 4.0f;
                    if(Sample_Amplify[Current_Instrument][Current_Instrument_Split] < 0) Sample_Amplify[Current_Instrument][Current_Instrument_Split] = 0;
                    Realslider(426, (Cur_Height - 62), (int) (Sample_Amplify[Current_Instrument][Current_Instrument_Split] * 32.0f), Allow_Sliders);
                    outlong_small(575, (Cur_Height - 62), (int) (Sample_Amplify[Current_Instrument][Current_Instrument_Split] * 100.0f), 1, 56, BUTTON_NORMAL | BUTTON_DISABLED);
                }

                if(gode == 0 || gode == 2)
                {
                    FineTune_Value = Finetune[Current_Instrument][Current_Instrument_Split];
                    if(FineTune_Value > 127)
                    {
                        Finetune[Current_Instrument][Current_Instrument_Split] = 127;
                    }
                    if(FineTune_Value < -127)
                    {
                        Finetune[Current_Instrument][Current_Instrument_Split] = -127;
                    }
                    Realslider(426, (Cur_Height - 44), 64 + (Finetune[Current_Instrument][Current_Instrument_Split] / 2), Allow_Sliders);
                    outlong_small(575, (Cur_Height - 44), (long) Finetune[Current_Instrument][Current_Instrument_Split], 0, 56, BUTTON_NORMAL | BUTTON_DISABLED);
                }

                if(gode == 0 || gode == 3)
                {
                    if(FDecay[Current_Instrument][Current_Instrument_Split] > 0.015625f) FDecay[Current_Instrument][Current_Instrument_Split] = 0.015625f;
                    if(FDecay[Current_Instrument][Current_Instrument_Split] < 0.0f) FDecay[Current_Instrument][Current_Instrument_Split] = 0.0f;
                    Realslider(52, (Cur_Height - 72), (int) (FDecay[Current_Instrument][Current_Instrument_Split] * 8192.0f), Allow_Sliders);
                    outlong(201, (Cur_Height - 72), (int) (FDecay[Current_Instrument][Current_Instrument_Split] * 8192.0f), 0);
                }

                char temprout[256];
                if(gode == 0)
                {
                    if(typex == 0 || typex == 1 || typex == 2)
                    {
                        if(SampleType[Current_Instrument][Current_Instrument_Split] != 0)
                        {
                            if(SampleChannels[Current_Instrument][Current_Instrument_Split] == 2)
                            {
                                sprintf(temprout, "%s [Stereo]", SampleName[Current_Instrument][Current_Instrument_Split]);
                            }
                            else
                            {
                                sprintf(temprout, "%s [Mono]", SampleName[Current_Instrument][Current_Instrument_Split]);
                            }
                        }
                        else
                        {
                            sprintf(temprout, "No Sample Loaded");
                        }
                        Gui_Draw_Button_Box(7, (Cur_Height - 134), 256, 16, temprout, BUTTON_NORMAL | BUTTON_DISABLED);
                    }
                } // typex

                if(gode == 0 || gode == 4)
                {
                    outlong(448, (Cur_Height - 134), SampleLength[Current_Instrument][Current_Instrument_Split], 0);
                }

                if(gode == 0 || gode == 5)
                {
                    outlong(448, (Cur_Height - 116), LoopStart[Current_Instrument][Current_Instrument_Split], 0);
                    outlong(448, (Cur_Height - 98), LoopEnd[Current_Instrument][Current_Instrument_Split], 0);

                    switch(LoopType[Current_Instrument][Current_Instrument_Split])
                    {
                        case SMP_LOOP_FORWARD:
                            Gui_Draw_Button_Box(448, (Cur_Height - 80), 60, 16, "Forward", Allow_Buttons_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(448 + 62, (Cur_Height - 80), 58, 16, "Ping Pong", Allow_Buttons | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(448 + 62 * 2 - 2, (Cur_Height - 80), 60, 16, "Off", Allow_Buttons | BUTTON_TEXT_CENTERED);
                            break;

                        case SMP_LOOP_PINGPONG:
                            Gui_Draw_Button_Box(448, (Cur_Height - 80), 60, 16, "Forward", Allow_Buttons | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(448 + 62, (Cur_Height - 80), 58, 16, "Ping Pong", Allow_Buttons_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(448 + 62 * 2 - 2, (Cur_Height - 80), 60, 16, "Off", Allow_Buttons | BUTTON_TEXT_CENTERED);
                            break;

                        case SMP_LOOP_NONE:
                            Gui_Draw_Button_Box(448, (Cur_Height - 80), 60, 16, "Forward", Allow_Buttons | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(448 + 62, (Cur_Height - 80), 58, 16, "Ping Pong", Allow_Buttons | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(448 + 62 * 2 - 2, (Cur_Height - 80), 60, 16, "Off", Allow_Buttons_Pushed | BUTTON_TEXT_CENTERED);
                            break;
                    }
                }

                if(gode == 0 || gode == 8)
                {
                    value_box(570, (Cur_Height - 134), Current_Instrument_Split, BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
                    value_box3(570, (Cur_Height - 116), Basenote[Current_Instrument][Current_Instrument_Split], Allow_Buttons | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                }

                if(gode == 0 || gode == 9)
                {
                    value_box3(570, (Cur_Height - 116), Basenote[Current_Instrument][Current_Instrument_Split], Allow_Buttons | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                }
                if(gode == 0 || gode == 10)
                {

#if !defined(__NO_MIDI__)
                    if(Midiprg[Current_Instrument] == -1)
                    {
                        Gui_Draw_Button_Box(570, (Cur_Height - 98), 16, 16, "\03", BUTTON_NORMAL | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                        Gui_Draw_Button_Box(570 + 44, (Cur_Height - 98), 16, 16, "\04", BUTTON_NORMAL | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
#else
                        Gui_Draw_Button_Box(570, (Cur_Height - 98), 16, 16, "\03", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_CENTERED);
                        Gui_Draw_Button_Box(570 + 44, (Cur_Height - 98), 16, 16, "\04", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_CENTERED);
#endif

                        Gui_Draw_Button_Box(570 + 18, (Cur_Height - 98), 24, 16, "-", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_CENTERED);

#if !defined(__NO_MIDI__)
                    }
                    else
                    {
                        Gui_Draw_Arrows_Number_Box(570, (Cur_Height - 98), Midiprg[Current_Instrument], BUTTON_NORMAL | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                    }

                    Actualize_Instruments_Synths_List(1);
#endif
                }
                if(gode == 0 || gode == 12)
                {
                    if(beatsync[Current_Instrument])
                    {
                        Gui_Draw_Button_Box(144, (Cur_Height - 108), 28, 16, "Off", Allow_Global | BUTTON_TEXT_CENTERED);
                        Gui_Draw_Button_Box(176, (Cur_Height - 108), 28, 16, "On", Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                    }
                    else
                    {
                        Gui_Draw_Button_Box(144, (Cur_Height - 108), 28, 16, "Off", Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                        Gui_Draw_Button_Box(176, (Cur_Height - 108), 28, 16, "On", Allow_Global | BUTTON_TEXT_CENTERED);
                    }
                }

                if(gode == 0 || gode == 13)
                {
                    Gui_Draw_Arrows_Number_Box(144, (Cur_Height - 90), beatlines[Current_Instrument], Allow_Global | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                }

                if(gode == 0 || gode == 15)
                {
                    if(Sample_Vol[Current_Instrument] > 1.0f) Sample_Vol[Current_Instrument] = 1.0f;
                    if(Sample_Vol[Current_Instrument] < 0.0f) Sample_Vol[Current_Instrument] = 0.0f;
                    Realslider(52, (Cur_Height - 54), (int) (Sample_Vol[Current_Instrument] * 128.0f), TRUE);
                    outlong(201, (Cur_Height - 54), (int) (Sample_Vol[Current_Instrument] * 100.0f), 1);
                }

                if(gode == 0 || gode == 16)
                {
                    switch(SampleCompression[Current_Instrument])
                    {
                        case SMP_PACK_GSM:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_MP3:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_ADPCM:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_TRUESPEECH:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_AT3:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_8BIT:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_INTERNAL:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global | BUTTON_TEXT_CENTERED);
                            break;
                        case SMP_PACK_NONE:
                            Gui_Draw_Button_Box(681, (Cur_Height - 134), 39, 16, "Internal", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116), 39, 16, "Gsm", Allow_GSM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116), 39, 16, "Mp3", Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 1), 80, 16, "ADPCM", Allow_ADPCM | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 2), 80, 16, "True Speech", Allow_TRUESPEECH | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 3), 80, 16, "At3 (PSP only)", Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(640, (Cur_Height - 116) + (18 * 4), 39, 16, "8 Bit", Allow_Global | BUTTON_TEXT_CENTERED);
                            Gui_Draw_Button_Box(681, (Cur_Height - 116) + (18 * 4), 39, 16, "None", Allow_Global_Pushed | BUTTON_TEXT_CENTERED);
                            break;
                    }
                    if(gode == 16) gode = 19;
                }

                if(gode == 0 || gode == 17)
                {
                    if(Mp3_BitRate[Current_Instrument] < 0) Mp3_BitRate[Current_Instrument] = 0;
                    if(Mp3_BitRate[Current_Instrument] > 5) Mp3_BitRate[Current_Instrument] = 5;
                    Gui_Draw_Arrows_Number_Box(729, (Cur_Height - 116), Type_Mp3_BitRate[Mp3_BitRate[Current_Instrument]], Allow_MP3 | Allow_Global | BUTTON_TEXT_CENTERED);
                    if(gode == 17) gode = 19;
                }

                if(gode == 0 || gode == 18)
                {
                    if(At3_BitRate[Current_Instrument] < 0) At3_BitRate[Current_Instrument] = 0;
                    if(At3_BitRate[Current_Instrument] > 2) At3_BitRate[Current_Instrument] = 2;
                    Gui_Draw_Arrows_Number_Box(729, (Cur_Height - 80), Type_At3_BitRate[At3_BitRate[Current_Instrument]], Allow_AT3 | Allow_Global | BUTTON_TEXT_CENTERED);
                    if(gode == 18) gode = 19;
                }

                if(gode == 0 || gode == 19)
                {
                    if(SamplesSwap[Current_Instrument])
                    {
                        Gui_Draw_Button_Box(729, (Cur_Height - 116) + (18 * 4), 60, 16, "Lock / All", Allow_Global_Pushed | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                    }
                    else
                    {
                        Gui_Draw_Button_Box(729, (Cur_Height - 116) + (18 * 4), 60, 16, "Lock / All", Allow_Global | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                    }
                    if(gode == 19)
                    {
                        int i;
                        if(SamplesSwap[Current_Instrument])
                        {
                            // Perform the samples lock on all splits
                            for(i = 0; i < 16; i++)
                            {
                                Lock_Sample(Current_Instrument, i);
                            }
                        }
                        else
                        {
                            // Unlock them
                            for(i = 0; i < 16; i++)
                            {
                                Restore_WaveForm(Current_Instrument, 0, i);
                                Restore_WaveForm(Current_Instrument, 1, i);
                                if(RawSamples_Swap[Current_Instrument][0][i])
                                {
                                    free(RawSamples_Swap[Current_Instrument][0][i]);
                                    RawSamples_Swap[Current_Instrument][0][i] = NULL;
                                }
                                if(RawSamples_Swap[Current_Instrument][1][i])
                                {
                                    free(RawSamples_Swap[Current_Instrument][1][i]);
                                    RawSamples_Swap[Current_Instrument][1][i] = NULL;
                                }
                            }
                        }
                    }
                    if(SamplesSwap[Current_Instrument])
                    {
                        outlong(729, (Cur_Height - 134) + (18 * 4), SampleLength_Packed[Current_Instrument][Current_Instrument_Split], 0);
                    }
                    else
                    {
                        outlong(729, (Cur_Height - 134) + (18 * 4), SampleLength[Current_Instrument][Current_Instrument_Split], 0);
                    }
                }

                if(gode == 16 || gode == 17 || gode == 18 || gode == 19)
                {
                    Actualize_Instruments_Synths_List(1);
                }

                break;

            case 1:

                Gui_Draw_Button_Box(427, (Cur_Height - 94), 58, 16, "Exit Editor", Allow_Buttons | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(78, (Cur_Height - 130), 16, 16, "\05", Allow_Buttons | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                Gui_Draw_Button_Box(96, (Cur_Height - 130), 16, 16, "\03", Allow_Buttons | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(176, (Cur_Height - 130), 16, 16, "\04", Allow_Buttons | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(194, (Cur_Height - 130), 16, 16, "\06", Allow_Buttons | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                Gui_Draw_Button_Box(220, (Cur_Height - 130), 56, 16, "Loop End", Allow_Buttons | BUTTON_DISABLED);
                Gui_Draw_Button_Box(278, (Cur_Height - 130), 16, 16, "\05", Allow_Buttons | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                Gui_Draw_Button_Box(296, (Cur_Height - 130), 16, 16, "\03", Allow_Buttons | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(376, (Cur_Height - 130), 16, 16, "\04", Allow_Buttons | BUTTON_TEXT_CENTERED);
                Gui_Draw_Button_Box(394, (Cur_Height - 130), 16, 16, "\06", Allow_Buttons | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);

                // Fine loop editor mode
                switch(typex)
                {
                    case 0:
                        outlong(487, (Cur_Height - 130), *(RawSamples[Current_Instrument][0][Current_Instrument_Split] + LoopStart[Current_Instrument][Current_Instrument_Split]), 0);
                        outlong(114, (Cur_Height - 130), LoopStart[Current_Instrument][Current_Instrument_Split], 0);
                        actuloop = 1;
                        break;

                    case 1:
                        outlong(487, (Cur_Height - 112), *(RawSamples[Current_Instrument][0][Current_Instrument_Split] + LoopEnd[Current_Instrument][Current_Instrument_Split]), 0);
                        outlong(314, (Cur_Height - 130), LoopEnd[Current_Instrument][Current_Instrument_Split], 0);
                        actuloop = 2;
                        break;

                    case 2:
                        outlong(487, (Cur_Height - 130), *(RawSamples[Current_Instrument][0][Current_Instrument_Split] + LoopStart[Current_Instrument][Current_Instrument_Split]), 0);
                        outlong(487, (Cur_Height - 112), *(RawSamples[Current_Instrument][0][Current_Instrument_Split] + LoopEnd[Current_Instrument][Current_Instrument_Split]), 0);
                        outlong(114, (Cur_Height - 130), LoopStart[Current_Instrument][Current_Instrument_Split], 0);
                        outlong(314, (Cur_Height - 130), LoopEnd[Current_Instrument][Current_Instrument_Split], 0);
                        actuloop = 3;
                        break;
                }

                break;
        } // draw sampleeditor
    } //User screen == 2
}

void Mouse_Sliders_Instrument_Ed(void)
{
    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT)
    {
        if(SampleType[Current_Instrument][Current_Instrument_Split])
        {
            if(zcheckMouse(426, (Cur_Height - 62), 148, 16))
            {
                gui_action = GUI_CMD_SET_INSTRUMENT_AMPLI;
            }
            if(zcheckMouse(436, (Cur_Height - 44), 128, 16))
            {
                gui_action = GUI_CMD_SET_INSTRUMENT_FINETUNE;
            }
            if(zcheckMouse(52, (Cur_Height - 72), 148, 16))
            {
                gui_action = GUI_CMD_SET_INSTRUMENT_DECAY;
            }
        }
        if(zcheckMouse(52, (Cur_Height - 54), 148, 16))
        {
            Sample_Vol[Current_Instrument] = float(Mouse.x - 62) * 0.0078125f;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 15;
        }
    }
}

void Mouse_Left_Instrument_Ed(void)
{
    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT && seditor == 1)
    {
        if(zcheckMouse(96, (Cur_Height - 130), 16, 16) &&
           LoopStart[Current_Instrument][Current_Instrument_Split] > 0 &&
           SampleType[Current_Instrument][Current_Instrument_Split])
        {
            LoopStart[Current_Instrument][Current_Instrument_Split]--;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 5;
        }
        if(zcheckMouse(176, (Cur_Height - 130), 16, 16) &&
           LoopStart[Current_Instrument][Current_Instrument_Split] < LoopEnd[Current_Instrument][Current_Instrument_Split] &&
           SampleType[Current_Instrument][Current_Instrument_Split])
        {
            LoopStart[Current_Instrument][Current_Instrument_Split]++;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 5;
        }
        if(zcheckMouse(296, (Cur_Height - 130), 16, 16) &&
           LoopEnd[Current_Instrument][Current_Instrument_Split] > LoopStart[Current_Instrument][Current_Instrument_Split] &&
           SampleType[Current_Instrument][Current_Instrument_Split])
        {
            LoopEnd[Current_Instrument][Current_Instrument_Split]--;
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 5;
        }
        if(zcheckMouse(376, (Cur_Height - 130), 16, 16) &&
           LoopEnd[Current_Instrument][Current_Instrument_Split] < SampleLength[Current_Instrument][Current_Instrument_Split] &&
           SampleType[Current_Instrument][Current_Instrument_Split])
        {
            LoopEnd[Current_Instrument][Current_Instrument_Split]++;
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 5;
        }
        // Return to instrument editor
        if(zcheckMouse(427, (Cur_Height - 94), 58, 16))
        {
            seditor = 0;
            gui_action = GUI_CMD_SELECT_INSTRUMENT_EDIT;
        }
    }

    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT && seditor == 0)
    {
        if(zcheckMouse(570, (Cur_Height - 134), 16, 16) && Current_Instrument_Split > 0)
        {
            Current_Instrument_Split--;
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 0;
            Renew_Sample_Ed();
        }
        if(zcheckMouse(614, (Cur_Height - 134), 16, 16) && Current_Instrument_Split < 15)
        {
            Current_Instrument_Split++;
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 0;
            Renew_Sample_Ed();
        }

#if !defined(__NO_MIDI__)
        if(zcheckMouse(570, (Cur_Height - 98), 16, 16) && Midiprg[Current_Instrument] > -1)
        {
            Midiprg[Current_Instrument]--;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 10;
        }
        if(zcheckMouse(614, (Cur_Height - 98), 16, 16) && Midiprg[Current_Instrument] < 127)
        {
            Midiprg[Current_Instrument]++;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 10;
        }
#endif

        if(Allow_Global_Sliders)
        {
            if(zcheckMouse(144, (Cur_Height - 108), 28, 16))
            {
                beatsync[Current_Instrument] = FALSE;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 12;
            }
            if(zcheckMouse(176, (Cur_Height - 108), 28, 16))
            {
                beatsync[Current_Instrument] = TRUE;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 12;
            }
        }

        if(Allow_Global_Sliders)
        {
            if(zcheckMouse(144, (Cur_Height - 90), 16, 16) && beatlines[Current_Instrument] > 1)
            {
                beatlines[Current_Instrument]--;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 13;
            }
            if(zcheckMouse(188, (Cur_Height - 90), 16, 16) && beatlines[Current_Instrument] < 128)
            {
                beatlines[Current_Instrument]++;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 13;
            }
        }

        // Go to loop editor
        if(zcheckMouse(268, (Cur_Height - 134), 88, 16) && SampleType[Current_Instrument][Current_Instrument_Split])
        {
            seditor = 1;
            gui_action = GUI_CMD_SELECT_INSTRUMENT_EDIT;
        }

        if(Allow_Global_Sliders)
        {
            if(zcheckMouse(268, (Cur_Height - 108), 88, 16))
            {
                if(File_Exist_Req("%s"SLASH"%s.pti", Dir_Instrs, nameins[Current_Instrument]))
                {
                    Display_Requester(&Overwrite_Requester, GUI_CMD_SAVE_INSTRUMENT);
                }
                else
                {
                    gui_action = GUI_CMD_SAVE_INSTRUMENT;
                }
            }
        }

        // Export .wav
        if(zcheckMouse(268, (Cur_Height - 90), 88, 16) && SampleType[Current_Instrument][Current_Instrument_Split])
        {
            char Name[MAX_PATH];
            if(strlen(SampleName[Current_Instrument][Current_Instrument_Split]))
            {
                sprintf(Name, "%s", SampleName[Current_Instrument][Current_Instrument_Split]);
            }
            else
            {
                sprintf(Name, "Untitled.wav");
            }
            if(File_Exist_Req("%s"SLASH"%s", Dir_Samples, Name))
            {
                Display_Requester(&Overwrite_Requester, GUI_CMD_EXPORT_WAV);
            }
            else
            {
                gui_action = GUI_CMD_EXPORT_WAV;
            }
        }

        if(zcheckMouse(570, (Cur_Height - 116), 16, 16) &&
           Basenote[Current_Instrument][Current_Instrument_Split] > 0 &&
           SampleType[Current_Instrument][Current_Instrument_Split])
        {
            Basenote[Current_Instrument][Current_Instrument_Split]--;
            teac = 9;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
        }

        if(zcheckMouse(614, (Cur_Height - 116), 16, 16) &&
           Basenote[Current_Instrument][Current_Instrument_Split] < 119 &&
           SampleType[Current_Instrument][Current_Instrument_Split])
        {
            Basenote[Current_Instrument][Current_Instrument_Split]++;
            teac = 9;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
        }

        if(Allow_Global_Sliders)
        {

            // Select Internal
            if(zcheckMouse(681, (Cur_Height - 134), 39, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_INTERNAL)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_INTERNAL;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }

#if defined(__GSM_CODEC__)
            // Select GSM
            if(zcheckMouse(640, (Cur_Height - 116), 39, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_GSM)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_GSM;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }
#endif

#if defined(__MP3_CODEC__)
            // Select MP3
            if(zcheckMouse(681, (Cur_Height - 116), 39, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_MP3)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_MP3;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }
#endif

#if defined(__ADPCM_CODEC__)
            // Select ADPCM
            if(zcheckMouse(640, (Cur_Height - 116) + (18 * 1), 80, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_ADPCM)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_ADPCM;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }
#endif

#if defined(__TRUESPEECH_CODEC__)
            // Select TRUESPEECH
            if(zcheckMouse(640, (Cur_Height - 116) + (18 * 2), 80, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_TRUESPEECH)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_TRUESPEECH;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }
#endif

#if defined(__AT3_CODEC__)
            // Select AT3
            if(zcheckMouse(640, (Cur_Height - 116) + (18 * 3), 80, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_AT3)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_AT3;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }
#endif

            // Select 8BIT
            if(zcheckMouse(640, (Cur_Height - 116) + (18 * 4), 39, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_8BIT)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_8BIT;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }

            // Select NONE
            if(zcheckMouse(681, (Cur_Height - 116) + (18 * 4), 39, 16))
            {
                if(SampleCompression[Current_Instrument] != SMP_PACK_NONE)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SampleCompression[Current_Instrument] = SMP_PACK_NONE;
                teac = 16;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            }

#if defined(__MP3_CODEC__)
            // Mp3 BitRate
            if(zcheckMouse(729, (Cur_Height - 116), 16, 16))
            {
                if(SampleCompression[Current_Instrument] == SMP_PACK_MP3)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SamplesSwap[Current_Instrument] = FALSE;
                Mp3_BitRate[Current_Instrument]--;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 17;
            }

            // Mp3 BitRate
            if(zcheckMouse(729 + 44, (Cur_Height - 116), 16, 16))
            {
                if(SampleCompression[Current_Instrument] == SMP_PACK_MP3)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SamplesSwap[Current_Instrument] = FALSE;
                Mp3_BitRate[Current_Instrument]++;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 17;
            }
#endif

#if defined(__AT3_CODEC__)
            // At3 BitRate
            if(zcheckMouse(729, (Cur_Height - 80), 16, 16))
            {
                if(SampleCompression[Current_Instrument] == SMP_PACK_AT3)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SamplesSwap[Current_Instrument] = FALSE;
                At3_BitRate[Current_Instrument]--;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 18;
            }

            // At3 BitRate
            if(zcheckMouse(729 + 44, (Cur_Height - 80), 16, 16))
            {
                if(SampleCompression[Current_Instrument] == SMP_PACK_AT3)
                {
                    SamplesSwap[Current_Instrument] = FALSE;
                }
                SamplesSwap[Current_Instrument] = FALSE;
                At3_BitRate[Current_Instrument]++;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 18;
            }
#endif

            // Lock sample
            if(zcheckMouse(729, (Cur_Height - 116) + (18 * 4), 60, 16))
            {
                SamplesSwap[Current_Instrument] = !SamplesSwap[Current_Instrument];
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 19;
            }

        }

        if(SampleType[Current_Instrument][Current_Instrument_Split])
        {
            if(zcheckMouse(448, (Cur_Height - 80), 60, 16))
            {
                LoopType[Current_Instrument][Current_Instrument_Split] = SMP_LOOP_FORWARD;
                teac = 5;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                draw_sampled_wave = TRUE;
            }
            if(zcheckMouse(448 + 62, (Cur_Height - 80), 58, 16))
            {
                LoopType[Current_Instrument][Current_Instrument_Split] = SMP_LOOP_PINGPONG;
                teac = 5;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                draw_sampled_wave = TRUE;
            }
            if(zcheckMouse(448 + 62 * 2 - 2, (Cur_Height - 80), 60, 16))
            {
                LoopType[Current_Instrument][Current_Instrument_Split] = SMP_LOOP_NONE;
                teac = 5;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                draw_sampled_wave = TRUE;
            }
        }
    }
}

void Mouse_Right_Instrument_Ed(void)
{
    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT && seditor == 0)
    {
        if(Allow_Global_Sliders)
        {
            if(zcheckMouse(144, (Cur_Height - 90), 16, 16) && beatlines[Current_Instrument] > 1)
            {
                beatlines[Current_Instrument] -= 16;
                if(beatlines[Current_Instrument] < 1) beatlines[Current_Instrument] = 1;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 13;
            }

            if(zcheckMouse(188, (Cur_Height - 90), 16, 16) && beatlines[Current_Instrument] < 128)
            {
                beatlines[Current_Instrument] += 16;
                if(beatlines[Current_Instrument] > 128) beatlines[Current_Instrument] = 128;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 13;
            }
        }

#if !defined(__NO_MIDI__)
        if(zcheckMouse(570, (Cur_Height - 98), 16, 16) && Midiprg[Current_Instrument] > -1)
        {
            if(Midiprg[Current_Instrument] > 14) Midiprg[Current_Instrument] -= 16;
            else Midiprg[Current_Instrument] = -1;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 10;
        }

        if(zcheckMouse(614, (Cur_Height - 98), 16, 16) && Midiprg[Current_Instrument] < 127)
        {
            if(Midiprg[Current_Instrument] < 111) Midiprg[Current_Instrument] += 16;
            else Midiprg[Current_Instrument] = 127;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 10;
        }
#endif

        if(Allow_Global_Sliders)
        {
            // Lock all samples
            if(zcheckMouse(729, (Cur_Height - 116) + (18 * 4), 60, 16))
            {
                int i;
                int j;
                int Lock;
                for(i = 0; i < MAX_INSTRS; i++)
                {
                    Lock = FALSE;
                    for(j = 0; j < 16; j++)
                    {
                        if(SampleType[i][j])
                        {
                            Lock = TRUE;
                            break;
                        }
                    }
                    if(Lock)
                    {
                        SamplesSwap[i] = !SamplesSwap[i];

                        if(SamplesSwap[i])
                        {
                            for(j = 0; j < 16; j++)
                            {
                                Lock_Sample(i, j);
                            }
                        }
                        else
                        {
                            for(j = 0; j < 16; j++)
                            {
                                Restore_WaveForm(i, 0, j);
                                Restore_WaveForm(i, 1, j);
                                if(RawSamples_Swap[i][0][j])
                                {
                                    free(RawSamples_Swap[i][0][j]);
                                    RawSamples_Swap[i][0][j] = NULL;
                                }
                                if(RawSamples_Swap[i][1][j])
                                {
                                    free(RawSamples_Swap[i][1][j]);
                                    RawSamples_Swap[i][1][j] = NULL;
                                }
                            }
                        }
                    }
                }
                if(SamplesSwap[Current_Instrument])
                {
                    Gui_Draw_Button_Box(729, (Cur_Height - 116) + (18 * 4), 60, 16, "Lock / All", Allow_Global_Pushed | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                    outlong(729, (Cur_Height - 134) + (18 * 4), SampleLength_Packed[Current_Instrument][Current_Instrument_Split], 0);
                }
                else
                {
                    Gui_Draw_Button_Box(729, (Cur_Height - 116) + (18 * 4), 60, 16, "Lock / All", Allow_Global | BUTTON_TEXT_CENTERED | BUTTON_RIGHT_MOUSE);
                    outlong(729, (Cur_Height - 134) + (18 * 4), SampleLength[Current_Instrument][Current_Instrument_Split], 0);
                }
                Actualize_Instruments_Synths_List(1);
            }
        }

        if(SampleType[Current_Instrument][Current_Instrument_Split])
        {
            if(zcheckMouse(570, (Cur_Height - 116), 16, 16) && Basenote[Current_Instrument][Current_Instrument_Split] > 0)
            {
                if(Basenote[Current_Instrument][Current_Instrument_Split] > 11) Basenote[Current_Instrument][Current_Instrument_Split] -= 12;
                else Basenote[Current_Instrument][Current_Instrument_Split] = 0;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 9;
            }

            if(zcheckMouse(614, (Cur_Height - 116), 16, 16) && Basenote[Current_Instrument][Current_Instrument_Split] < 119)
            {
                if(Basenote[Current_Instrument][Current_Instrument_Split] < 107) Basenote[Current_Instrument][Current_Instrument_Split] += 12;
                else Basenote[Current_Instrument][Current_Instrument_Split] = 119;
                gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
                teac = 9;
            }
        }
    }
}

void Afloop(void)
{
    int iose;
    if(actuloop == 1 || actuloop == 3)
    {
        for(int a = 0; a < 200; a++)
        {
            Uint32 ose = a + LoopStart[Current_Instrument][Current_Instrument_Split];
            if(ose < SampleLength[Current_Instrument][Current_Instrument_Split])
            {
                int v = *(RawSamples[Current_Instrument][0][Current_Instrument_Split] + ose) / 1024;
                DrawVLine(a + 222, (Cur_Height - 46), (Cur_Height - 78) - v, COL_VUMETER);
                DrawVLine(a + 222, (Cur_Height - 78) - v, (Cur_Height - 110), COL_BACKGROUND);
            }
            else
            {
                DrawVLine(a + 22, (Cur_Height - 110), (Cur_Height - 46), COL_BACKGROUND);
            }
        }
        DrawHLine((Cur_Height - 110), 22, 421, COL_BLACK);
        DrawHLine((Cur_Height - 46), 22, 421, COL_BLACK);
        DrawVLine(22, (Cur_Height - 110), (Cur_Height - 46), COL_BLACK);
        DrawVLine(421, (Cur_Height - 110), (Cur_Height - 46), COL_BLACK);
    }

    if(actuloop == 2 || actuloop == 3)
    {
        for(int b = 0; b < 200; b++)
        {
            Uint32 ose = (LoopEnd[Current_Instrument][Current_Instrument_Split] - 200) + b;
            iose = ose;
            if(iose > -1 && ose < SampleLength[Current_Instrument][Current_Instrument_Split])
            {
                int v = *(RawSamples[Current_Instrument][0][Current_Instrument_Split] + ose) / 1024;
                DrawVLine(b + 22, (Cur_Height - 46), (Cur_Height - 78) - v, COL_VUMETERPEAK);
                DrawVLine(b + 22, (Cur_Height - 78) - v, (Cur_Height - 110), COL_BACKGROUND);
            }
            else
            {
                DrawVLine(b + 22, (Cur_Height - 110), (Cur_Height - 46), COL_BACKGROUND);
            }
        }
        DrawHLine((Cur_Height - 110), 22, 421, COL_BLACK);
        DrawHLine((Cur_Height - 46), 22, 421, COL_BLACK);
        DrawVLine(22, (Cur_Height - 110), (Cur_Height - 46), COL_BLACK);
        DrawVLine(421, (Cur_Height - 110), (Cur_Height - 46), COL_BLACK);
    }
    actuloop = 0;
}

void Mouse_Left_Repeat_Instrument_Ed(void)
{
    int32 *Cur_Loop_Start = (int32 *) &LoopStart[Current_Instrument][Current_Instrument_Split];
    int32 *Cur_Loop_End = (int32 *) &LoopEnd[Current_Instrument][Current_Instrument_Split];

    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT && seditor == 1)
    {
        gui_action = GUI_CMD_NOP;

        if(zcheckMouse(78, (Cur_Height - 130), 16, 16) && *Cur_Loop_Start > 0)
        {
            *Cur_Loop_Start -= 1;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 5;
        }
        if(zcheckMouse(194, (Cur_Height - 130), 16, 16) && *Cur_Loop_Start < *Cur_Loop_End)
        {
            *Cur_Loop_Start += 1;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 5;
        }
        if(zcheckMouse(278, (Cur_Height - 130), 16, 16) && *Cur_Loop_End > *Cur_Loop_Start)
        {
            *Cur_Loop_End -= 1;
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 5;
        }
        if(zcheckMouse(394, (Cur_Height - 130), 16, 16) && *Cur_Loop_End < (int32) SampleLength[Current_Instrument][Current_Instrument_Split])
        {
            *Cur_Loop_End += 1;
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 5;
        }
    }
}

void Mouse_Sliders_Right_Instrument_Ed(void)
{
    int32 *Cur_Loop_Start = (int32 *) &LoopStart[Current_Instrument][Current_Instrument_Split];
    int32 *Cur_Loop_End = (int32 *) &LoopEnd[Current_Instrument][Current_Instrument_Split];

    if(userscreen == USER_SCREEN_INSTRUMENT_EDIT && seditor == 1)
    {
        gui_action = GUI_CMD_NOP;

        if(zcheckMouse(78, (Cur_Height - 130), 16, 16) && *Cur_Loop_Start > 0)
        {
            *Cur_Loop_Start -= 10;
            if(*Cur_Loop_Start < 0) *Cur_Loop_Start = 0;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 5;
        }
        if(zcheckMouse(194, (Cur_Height - 130), 16, 16) && *Cur_Loop_Start < *Cur_Loop_End)
        {
            *Cur_Loop_Start += 10;
            if(*Cur_Loop_Start > *Cur_Loop_End) *Cur_Loop_Start = *Cur_Loop_End;
            gui_action = GUI_CMD_UPDATE_INSTRUMENT_ED;
            teac = 5;
        }
        if(zcheckMouse(278, (Cur_Height - 130), 16, 16) && *Cur_Loop_End > *Cur_Loop_Start)
        {
            *Cur_Loop_End -= 10;
            if(*Cur_Loop_End < *Cur_Loop_Start)
            {
                *Cur_Loop_End = *Cur_Loop_Start;
            }
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 5;
        }
        if(zcheckMouse(394, (Cur_Height - 130), 16, 16) && *Cur_Loop_End <
           (int32) SampleLength[Current_Instrument][Current_Instrument_Split])
        {
            *Cur_Loop_End += 10;
            if(*Cur_Loop_End > (int32) SampleLength[Current_Instrument][Current_Instrument_Split])
            {
                *Cur_Loop_End = SampleLength[Current_Instrument][Current_Instrument_Split];
            }
            gui_action = GUI_CMD_UPDATE_LOOP_EDITOR_ED;
            teac = 5;
        }
    }
}

// ------------------------------------------------------
// Display the instruments or synths list on screen
void Dump_Instruments_Synths_List(int xr, int yr)
{
    char Line[200];
    int i;
    int Nbr_Splits;
    int Font;

    switch(Scopish)
    {
        case SCOPE_ZONE_INSTR_LIST:
        case SCOPE_ZONE_SYNTH_LIST:

            SetColor(COL_BACKGROUND);
            bjbox(xr - 1, yr + 1, Cur_Width - 412, 137);

            for(int counter = 0; counter < 11; counter++)
            {
                int rel_val = Instrs_index + counter;

                if(Instrs_index + counter < MAX_INSTRS)
                {
                    if(Instrs_index + counter == Current_Instrument)
                    {
                        SetColor(COL_PUSHED_MED);
                        bjbox(xr - 1, yr + (counter * 12) + 1, Cur_Width - 413, 12);
                    }

                    switch(Scopish)
                    {
                        // View instruments
                        case SCOPE_ZONE_INSTR_LIST:

                            Nbr_Splits = 0;
                            Font = USE_FONT_LOW;
                            for(i = 0; i < MAX_INSTRS_SPLITS; i++)
                            {
                                if(SampleType[rel_val][i])
                                {
                                    Nbr_Splits++;
                                }
                            }
                            if(Nbr_Splits) Font = USE_FONT;

                            sprintf(Line, "%.2x:", rel_val);
                            PrintString(xr, yr + (counter * 12), Font, Line);
                            sprintf(Line, "%s", nameins[rel_val]);
                            PrintString(xr + 18, yr + (counter * 12), Font, Line);
        
                            sprintf(Line, "%s", nameins[rel_val]);
                            PrintString(xr + 18, yr + (counter * 12), Font, Line);
                            switch(Nbr_Splits)
                            {
                                case 0:
                                    sprintf(Line, "No waveform");
                                    break;

                                case 1:
                                    if(SamplesSwap[rel_val])
                                    {
                                        sprintf(Line, "*Locked* (%d)", Nbr_Splits);
                                    }
                                    else
                                    {
                                        sprintf(Line, "%d waveform", Nbr_Splits);
                                    }
                                    break;

                                default:
                                    if(SamplesSwap[rel_val])
                                    {
                                        sprintf(Line, "*Locked* (%d)", Nbr_Splits);
                                    }
                                    else
                                    {
                                        sprintf(Line, "%d waveforms", Nbr_Splits);
                                    }
                                    break;
                            }
                            PrintString(xr + (Cur_Width - 632), yr + (counter * 12), Font, Line);

                            if(Nbr_Splits)
                            {
                                switch(SampleCompression[rel_val])
                                {
#if defined(__GSM_CODEC__)
                                    case SMP_PACK_GSM:
                                        sprintf(Line, "Pck: Gsm");
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
#endif
#if defined(__MP3_CODEC__)
                                    case SMP_PACK_MP3:
                                        sprintf(Line, "Pck: Mp3 (%d)", Type_Mp3_BitRate[Mp3_BitRate[rel_val]]);
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
#endif
#if defined(__TRUESPEECH_CODEC__)
                                    case SMP_PACK_TRUESPEECH:
                                        sprintf(Line, "Pck: TrueSp.");
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
#endif
#if defined(__ADPCM_CODEC__)
                                    case SMP_PACK_ADPCM:
                                        sprintf(Line, "Pck: ADPCM");
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
#endif
#if defined(__AT3_CODEC__)
                                    case SMP_PACK_AT3:
                                        sprintf(Line, "Pck: At3 (%d)", Type_At3_BitRate[At3_BitRate[rel_val]]);
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
#endif
                                    case SMP_PACK_8BIT:
                                        sprintf(Line, "Pck: 8 Bit");
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
                                    case SMP_PACK_NONE:
                                        sprintf(Line, "Pck: None");
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
                                    case SMP_PACK_INTERNAL:
                                        sprintf(Line, "Pck: Internal");
                                        PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, Line);
                                        break;
                                }
                            }
                            else
                            {
                                PrintString(xr + (Cur_Width - 560), yr + (counter * 12), Font, "Pck: -");
                            }

                            if(Midiprg[rel_val] == -1)
                            {
                                sprintf(Line, "Midi prog.: -");
                                PrintString(xr + (Cur_Width - 480), yr + (counter * 12), Font, Line);
                            }
                            else
                            {
                                sprintf(Line, "Midi prog.: %.2d", Midiprg[rel_val]);
                                PrintString(xr + (Cur_Width - 480), yr + (counter * 12), USE_FONT, Line);
                            }
                            break;

                        // View synths
                        case SCOPE_ZONE_SYNTH_LIST:

                            Font = USE_FONT_LOW;
                            if(Synthprg[rel_val])
                            {
                                Font = USE_FONT;
                            }
                            
                            sprintf(Line, "%.2x:", rel_val);
                            PrintString(xr, yr + (counter * 12), Font, Line);

                            sprintf(Line, "%s", PARASynth[rel_val].presetname);
                            PrintString(xr + 18, yr + (counter * 12), Font, Line);

                            int instr_to_search = Synthprg[rel_val];
                            if(instr_to_search == 0)
                            {
                                sprintf(Line, "No waveform");
                            }
                            else
                            {
                                Nbr_Splits = 0;
                                if(instr_to_search == 1) instr_to_search = rel_val;
                                else instr_to_search -= 2;
                                for(i = 0; i < MAX_INSTRS_SPLITS; i++)
                                {
                                    if(SampleType[instr_to_search][i])
                                    {
                                        Nbr_Splits++;
                                    }
                                }
                                switch(Nbr_Splits)
                                {
                                    case 0:
                                        sprintf(Line, "No waveform");
                                        break;

                                    case 1:
                                        sprintf(Line, "%d waveform", Nbr_Splits);
                                        break;

                                    default:
                                        sprintf(Line, "%d waveforms", Nbr_Splits);
                                        break;
                                }
                            }
                            PrintString(xr + (Cur_Width - 632), yr + (counter * 12), Font, Line);

                            if(Synthprg[rel_val] == 0)
                            {
                                sprintf(Line, "No Instr.");
                                PrintString(xr + (Cur_Width - 540), yr + (counter * 12), Font, Line);
                            }
                            else if(Synthprg[rel_val] == 1)
                            {
                                sprintf(Line, "Rel. Instr.: Curr");
                                PrintString(xr + (Cur_Width - 540), yr + (counter * 12), USE_FONT, Line);
                            }
                            else
                            {
                                sprintf(Line, "Rel. Instr.: %.2x", Synthprg[rel_val] - 2);
                                PrintString(xr + (Cur_Width - 540), yr + (counter * 12), USE_FONT, Line);
                            }
                            break;
                    }
                }
            }

            break;
    }
}

// ------------------------------------------------------
// Redraw the instruments or synths list
void Actualize_Instruments_Synths_List(int modeac)
{
    int const brolim = Instrs_items - 11;
    char Line[200];
    int i;
    int j;
    int Nbr_Entries = 0;

    switch(Scopish)
    {
        case SCOPE_ZONE_INSTR_LIST:
        case SCOPE_ZONE_SYNTH_LIST:

            if(modeac == 0)
            {
                if(Instrs_ykar > 70) Instrs_ykar = 70;
                if(Instrs_ykar < 0) Instrs_ykar = 0;
                Instrs_index = (Instrs_ykar * brolim) / 70;
            }

            if(modeac == 2)
            {
                if(Current_Instrument >= Instrs_index + 11)
                {
                    Instrs_index += Current_Instrument - (Instrs_index + 10);
                }

                if(Current_Instrument < Instrs_index)
                {
                    Instrs_index -= Instrs_index - Current_Instrument;
                }
            }

            if(Instrs_index > brolim) Instrs_index = brolim;
            if(Instrs_index < 0) Instrs_index = 0;
            if(modeac != 0)
            {
                if(brolim)
                {
                    Instrs_ykar = (Instrs_index * 70) / brolim;
                }
                else
                {
                    Instrs_ykar = (Instrs_index * 70);
                }
            }

            Draw_Lists_Slider(Instrs_ykar);
            Dump_Instruments_Synths_List(395, 41);

            Gui_Draw_Button_Box(394, 24, Cur_Width - 522, 16, "", BUTTON_NORMAL | BUTTON_DISABLED);
            switch(Scopish)
            {
                case SCOPE_ZONE_INSTR_LIST:

                    Nbr_Entries = 0;
                    for(j = 0; j < MAX_INSTRS; j++)
                    {
                        for(i = 0; i < MAX_INSTRS_SPLITS; i++)
                        {
                            if(SampleType[j][i])
                            {
                                Nbr_Entries++;
                            }
                        }
                    }
                    sprintf(Line, "Instruments List (%d)", Nbr_Entries);
                    PrintString(398, 26, USE_FONT, Line);
                    break;

                case SCOPE_ZONE_SYNTH_LIST:
                    Nbr_Entries = 0;
                    for(i = 0; i < MAX_INSTRS; i++)
                    {
                        if(Synthprg[i])
                        {
                            Nbr_Entries++;
                        }
                    }
                    sprintf(Line, "Synths List (%d)", Nbr_Entries);
                    PrintString(398, 26, USE_FONT, Line);
                    break;
            }

            break;
    }
}

// ------------------------------------------------------
// Lock a sample in order to test it
void Lock_Sample(int instr_nbr, int split)
{
    int PackedLen = 0;
    short *PackedSample;
    short *Dest_Buffer;
    short *Sample_Dest_Buffer;
    int iSmp;
    short Sample1;
    short Sample2;

#if defined(__TRUESPEECH_CODEC__) || defined(__ADPCM_CODEC__)
    short *AlignedSample;
    int Aligned_Size;
#endif

    short *Sample;
    short *Smp_Dats;
    int Size;
    char Pack_Type;
    int BitRate;
    int i;

    for(i = 0; i < SampleChannels[instr_nbr][split]; i++)
    {
        PackedSample = NULL;
        Smp_Dats = NULL;
        Dest_Buffer = NULL;
        Sample_Dest_Buffer = NULL;
        Smp_Dats = NULL;
        Size = SampleLength[instr_nbr][split];
        Sample = RawSamples[instr_nbr][i][split];
        Pack_Type = SampleCompression[instr_nbr];
        BitRate = SampleCompression[instr_nbr] == SMP_PACK_MP3 ?
                                                  Type_Mp3_BitRate[Mp3_BitRate[instr_nbr]] :
                                                  Type_At3_BitRate[At3_BitRate[instr_nbr]];
        if(RawSamples_Swap[instr_nbr][i][split])
        {
            free(RawSamples_Swap[instr_nbr][i][split]);
            RawSamples_Swap[instr_nbr][i][split] = NULL;
        }

        RawSamples_Swap[instr_nbr][i][split] = (short *) malloc(Size * 2 + 8);
        memset(RawSamples_Swap[instr_nbr][i][split], 0, Size * 2 + 8);

        Save_WaveForm(instr_nbr, i, split);

        Dest_Buffer = (short *) malloc(Size * 2 + 8);
        memset(Dest_Buffer, 0, Size * 2 + 8);

        if(Pack_Type != SMP_PACK_NONE)
        {
            // Halve the sample
            Size /= 2;
            Smp_Dats = (short *) malloc(Size * 2 + 8);
            memset(Smp_Dats, 0, Size * 2 + 8);
            for(iSmp = 0; iSmp < Size; iSmp++)
            {
                Smp_Dats[iSmp] = *(Sample + (iSmp * 2));
            }
            Sample = Smp_Dats;
        }

        // Pack it first
        switch(Pack_Type)
        {
#if defined(__AT3_CODEC__)
            case SMP_PACK_AT3:
                PackedSample = (short *) malloc(Size * 2 + 8);
                memset(PackedSample, 0, Size * 2 + 8);
                PackedLen = ToAT3(Sample, PackedSample, Size * 2, BitRate);
                break;
#endif
#if defined(__GSM_CODEC__)
            case SMP_PACK_GSM:
                PackedSample = (short *) malloc(Size * 2 + 8);
                memset(PackedSample, 0, Size * 2 + 8);
                PackedLen = ToGSM(Sample, PackedSample, Size * 2);
                break;
#endif
#if defined(__MP3_CODEC__)
            case SMP_PACK_MP3:
                PackedSample = (short *) malloc(Size * 2 + 8);
                memset(PackedSample, 0, Size * 2 + 8);
                PackedLen = ToMP3(Sample, PackedSample, Size * 2, BitRate);
                break;
#endif
#if defined(__TRUESPEECH_CODEC__)
            case SMP_PACK_TRUESPEECH:
                Aligned_Size = (Size * 2) + 0x400;
                AlignedSample = (short *) malloc(Aligned_Size + 8);
                if(AlignedSample)
                {
                    memset(AlignedSample, 0, Aligned_Size + 8);
                    memcpy(AlignedSample, Sample, Size * 2);
                    // Size must be aligned
                    PackedSample = (short *) malloc(Aligned_Size + 8);
                    if(PackedSample)
                    {
                        memset(PackedSample, 0, Aligned_Size + 8);
                        PackedLen = ToTrueSpeech(AlignedSample, PackedSample, Aligned_Size);
                    }
                    free(AlignedSample);
                }
                break;
#endif
#if defined(__ADPCM_CODEC__)
            case SMP_PACK_ADPCM:
                Aligned_Size = (Size * 2) + 0x1000;
                AlignedSample = (short *) malloc(Aligned_Size + 8);
                if(AlignedSample)
                {
                    memset(AlignedSample, 0, Aligned_Size + 8);
                    memcpy(AlignedSample, Sample, Size * 2);
                    // Size must be aligned
                    PackedSample = (short *) malloc(Aligned_Size + 8);
                    if(PackedSample)
                    {
                        memset(PackedSample, 0, Aligned_Size + 8);
                        PackedLen = ToADPCM(AlignedSample, PackedSample, Aligned_Size);
                    }
                    free(AlignedSample);
                }
                break;
#endif
            case SMP_PACK_8BIT:
                PackedSample = (short *) malloc(Size * 2 + 8);
                memset(PackedSample, 0, Size * 2 + 8);
                // (Size is the size in samples)
                // (PackedLen is the size in bytes)
                PackedLen = To8Bit(Sample, PackedSample, Size);
                break;

            case SMP_PACK_INTERNAL:
                PackedSample = (short *) malloc(Size * 2 + 8);
                memset(PackedSample, 0, Size * 2 + 8);
                PackedLen = ToInternal(Sample, PackedSample, Size);
                break;

            case SMP_PACK_NONE:
                PackedLen = 0;
                break;
        }

        // Depack it now
        if(PackedLen)
        {
            SampleLength_Packed[instr_nbr][split] = PackedLen;
            switch(Pack_Type)
            {
#if defined(__AT3_CODEC__)
                case SMP_PACK_AT3:
                    UnpackAT3((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size, BitRate);
                    break;
#endif
#if defined(__GSM_CODEC__)
                case SMP_PACK_GSM:
                    UnpackGSM((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size);
                    break;
#endif
#if defined(__MP3_CODEC__)
                case SMP_PACK_MP3:
                    UnpackMP3((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size, BitRate);
                    break;
#endif
#if defined(__TRUESPEECH_CODEC__)
                case SMP_PACK_TRUESPEECH:
                    UnpackTrueSpeech((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size);
                    break;
#endif
#if defined(__ADPCM_CODEC__)
                case SMP_PACK_ADPCM:
                    UnpackADPCM((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size);
                    break;
#endif
                case SMP_PACK_8BIT:
                    Unpack8Bit((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size);
                    break;

                case SMP_PACK_INTERNAL:
                    UnpackInternal((Uint8 *) PackedSample, Dest_Buffer, PackedLen, Size);
                    break;
            }
        }
        else
        {
            SampleLength_Packed[instr_nbr][split] = Size;
            if(Pack_Type != SMP_PACK_NONE)
            {
                memcpy(Dest_Buffer, Sample, Size * 2);
            }
        }

        if(Pack_Type != SMP_PACK_NONE)
        {
            // Interpolate the sample
            Sample_Dest_Buffer = RawSamples[instr_nbr][i][split];

            for(iSmp = 0; iSmp < Size; iSmp++)
            {
                Sample1 = Dest_Buffer[iSmp];
                Sample2 = Dest_Buffer[iSmp + 1];
                if(iSmp == Size - 1)
                {
                    if(LoopType[instr_nbr][split])
                    {
                        Sample2 = Sample_Dest_Buffer[LoopStart[instr_nbr][split]];
                    }
                    else
                    {
                        Sample2 = Dest_Buffer[iSmp];
                    }
                }
                Sample_Dest_Buffer[(iSmp * 2)] = Sample1;
                Sample_Dest_Buffer[(iSmp * 2) + 1] = Sample1 + ((Sample2 - Sample1) / 2);
            }
        }
        if(Dest_Buffer) free(Dest_Buffer);
        if(PackedSample) free(PackedSample);
        if(Smp_Dats) free(Smp_Dats);
    }
}

// ------------------------------------------------------
// Copy a sample into the back buffer
void Save_WaveForm(int Instr_Nbr, int Channel, int Split)
{
    int i;

    if(RawSamples[Instr_Nbr][Channel][Split] && RawSamples_Swap[Instr_Nbr][Channel][Split])
    {
        for(i = 0; i < (int) SampleLength[Instr_Nbr][Split]; i++)
        {
            RawSamples_Swap[Instr_Nbr][Channel][Split][i] = RawSamples[Instr_Nbr][Channel][Split][i];
        }
    }
}

// ------------------------------------------------------
// Copy a sample from the back buffer
void Restore_WaveForm(int Instr_Nbr, int Channel, int Split)
{
    int i;

    if(RawSamples[Instr_Nbr][Channel][Split] && RawSamples_Swap[Instr_Nbr][Channel][Split])
    {
        for(i = 0; i < (int) SampleLength[Instr_Nbr][Split]; i++)
        {
            RawSamples[Instr_Nbr][Channel][Split][i] = RawSamples_Swap[Instr_Nbr][Channel][Split][i];
        }
    }
}
