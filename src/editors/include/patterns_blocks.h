// ------------------------------------------------------
// Protrekkr
// Written by Franck Charlet
// Based on the work of Juan Antonio Arguelles Rius 
// ------------------------------------------------------

#ifndef _PATTERNS_BLOCKS_H_
#define _PATTERNS_BLOCKS_H_

// ------------------------------------------------------
// Enumerations
enum COLUMN_TYPE
{
    NOTE,
    INSTRHI,
    INSTRLO,
    VOLUMEHI,
    VOLUMELO,
    PANNINGHI,
    PANNINGLO,
    EFFECTHI,
    EFFECTLO,
    EFFECTDATHI,
    EFFECTDATLO
};

// ------------------------------------------------------
// Functions
int Init_Block_Work(void);
void Mark_Block_Start(int start_nibble, int start_track, int start_line);
void Mark_Block_End(int start_nibble, int start_track, int start_line, int Modif);
int Delete_Selection(int Position);
void Copy_Selection_To_Buffer(int Position);
void Paste_Selection_From_Buffer(int Position);
void Cut_Selection(int Position);
void Copy_Selection(int Position);
void Paste_Block(int Position);
void Interpolate_Block(int Position);
void Randomize_Block(int Position);
void Semitone_Up_Block(int Position);
void Semitone_Down_Block(int Position);
void Instrument_Semitone_Up_Block(int Position);
void Instrument_Semitone_Down_Block(int Position);
void Select_Track_Block(void);
void Select_Pattern_Block(void);
void Select_Note_Block(void);
void Calc_selection(void);
void Unselect_Selection(void);
void Select_Block_Keyboard(int Type);
void Insert_Pattern_Line(int Position);
void Insert_Track_Line(int track, int Position);
void Remove_Pattern_Line(int Position);
void Remove_Track_Line(int track, int Position);
void Clear_Patterns_Pool(void);
void Clear_Track_Data(int offset);
int Alloc_Patterns_Pool(void);
int Get_Max_Nibble_Track(char *Buffer, int track);
int Get_Track_Nibble_Start(char *Buffer, int track);
int Get_Track_From_Nibble(char *Buffer, int nibble);
void Select_All_Notes_Block(void);
int Get_Max_Nibble_Track_From_Nibble(char *Buffer, int nibble);
int Get_Byte_From_Column(char *Buffer, int column);
COLUMN_TYPE Get_Column_Type(char *Buffer, int column);
int Get_Track_Relative_Column(char *Buffer, int column);
int Get_Max_Nibble_All_Tracks(void);
void Clear_Buff(void);

#endif
