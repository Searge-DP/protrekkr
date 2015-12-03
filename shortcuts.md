<pre>
== Playing ==<br>
----<br>
<br>
RCTRL:                           Play song from row 0.<br>
LSHIFT + RCTRL:                  Play song from current row.<br>
RALT:                            Play pattern from row 0.<br>
LSHIFT + RALT:                   Play pattern from current row.<br>
Left mouse on '>':               Play song from row 0.<br>
Right mouse on '>':              Play song from current row.<br>
Left mouse on '|>':              Play pattern from row 0.<br>
Right mouse on '|>':             Play pattern from current row.<br>
Left mouse on 'Edit/Record':     Edit mode on/off.<br>
Right mouse on 'Edit/Record':    Record mode on/off.<br>
<br>
== Editing ==<br>
----<br>
<br>
LSHIFT + ESCAPE:                 Switch large patterns view on/off<br>
TAB:                    Go to next track<br>
LSHIFT + TAB:                    Go to prev. track<br>
LCTRL + TAB:                    Go to next note in track<br>
LCTRL + LSHIFT + TAB:           Go to prev. note in track<br>
SPACE:                           Toggle Edit mode On & Off<br>
(Also stop if the song is being played)<br>
SHIFT SPACE:                     Toggle Record mode On & Off<br>
(Wait for a key note to be pressed<br>
or a midi in message to be received)<br>
DOWN ARROW:                      1 Line down<br>
UP ARROW:                        1 Line up<br>
LEFT ARROW:                      1 Row left<br>
RIGHT ARROW:                     1 Row right<br>
PREV. PAGE:                      16 Arrows Up<br>
NEXT PAGE:                       16 Arrows Down<br>
HOME / END:                      Top left / Bottom right of pattern<br>
LCTRL + HOME / END:              First / last track<br>
F5, F6, F7, F8, F9:              Jump to 0, 1/4, 2/4, 3/4, 4/4 lines of the patterns<br>
<br>
+ - (Numeric keypad):           Next / Previous pattern<br>
LCTRL + LEFT / RIGHT:           Next / Previous pattern<br>
LCTRL + LALT + LEFT / RIGHT:    Next / Previous position<br>
<br>
LALT + LEFT / RIGHT:           Next / Previous instrument<br>
LSHIFT + M:                      Toggle mute state of the current channel<br>
LCTRL + LSHIFT + M:             Solo the current track / Unmute all<br>
LSHIFT + F1 to F11:              Select a tab/panel<br>
LCTRL + 1 to 4:                 Select a copy buffer<br>
<br>
== Tracking ==<br>
-----<br>
<br>
1st and 2nd keys rows:           Upper octave row<br>
3rd and 4th keys rows:           Lower octave row<br>
RSHIFT:                          Insert a note off<br>
/ and * (Numeric keypad)<br>
or F1 F2:                        -1 or +1 octave<br>
INSERT / BACKSPACE:              Insert or Delete a line in current track<br>
or current selected block.<br>
LSHIFT + INSERT / BACKSPACE:     Insert or Delete a line in current pattern<br>
DELETE (NOT BACKSPACE):          Empty a column or a selected block.<br>
<br>
== Blocks ==<br>
----<br>
<br>
(Blocks can also be selected with the mouse by holding the right button<br>
and scrolling the pattern with the mouse wheel).<br>
<br>
LCTRL + A:          Select entire current track<br>
LCTRL + LSHIFT + A: Select entire current pattern<br>
LALT + A:          Select entire column note in a track<br>
LALT + LSHIFT + A: Select all notes of a track<br>
LCTRL + X:          Cut the selected block and copy it into the block-buffer<br>
LCTRL + C:          Copy the selected block into the block-buffer<br>
LCTRL + V:          Paste the data from the block buffer into the pattern<br>
LCTRL + I:          Interpolate selected data from the first<br>
to the last row of a selection<br>
<br>
example:<br>
(assuming only the 2 effects data columns are selected)<br>
<br>
C-3  04  ..  ..  09  00 ---> C-3  04  ..  ..  09  00<br>
C-3  04  ..  ..  09  00 ---> C-3  04  ..  ..  09  02<br>
C-3  04  ..  ..  09  00 ---> C-3  04  ..  ..  09  05<br>
C-3  04  ..  ..  09  00 ---> C-3  04  ..  ..  09  08<br>
C-3  04  ..  ..  09  00 ---> C-3  04  ..  ..  09  0A<br>
C-3  04  ..  ..  09  00 ---> C-3  04  ..  ..  09  0D<br>
C-3  04  ..  ..  09  10 ---> C-3  04  ..  ..  09  10<br>
<br>
Cool to make cutoff transitions, etc...<br>
(You can also switch on the Slider Rec to On,<br>
and perform parameter-live-recording, such as cutoff,<br>
resonance or panning tweaking, etc..)<br>
<br>
Note: this command (as well as the randomize one below)<br>
only works for volume/panning and fx datas columns.<br>
<br>
LSHIFT + ARROWS<br>
PREV. PAGE<br>
NEXT PAGE: Select a block<br>
<br>
LCTRL + R:          Randomize the select columns of a selection,<br>
works similar to CTRL + I, but it randomizes values<br>
instead of interpolating them.<br>
<br>
LCTRL + U:          Transpose the note of a selection to 1 seminote higher<br>
LCTRL + D:          Transpose the note of a selection to 1 seminote lower<br>
LCTRL + LSHIFT + U: Transpose the note of a selection to 1 seminote higher<br>
(only for the current instrument)<br>
LCTRL + LSHIFT + D: Transpose the note of a selection to 1 seminote lower<br>
(only for the current instrument)<br>
LCTRL + H:          Transpose the note of a selection to 1 octave higher<br>
LCTRL + L:          Transpose the note of a selection to 1 octave lower<br>
LCTRL + LSHIFT + H: Transpose the note of a selection to 1 octave higher<br>
(only for the current instrument)<br>
LCTRL + LSHIFT + L: Transpose the note of a selection to 1 octave lower<br>
(only for the current instrument)<br>
LCTRL + W:          Save the current selection into a file<br>
<br>
== Misc. ==<br>
----<br>
<br>
LALT + ENTER:     Switch between full screen / windowed mode<br>
LALT + F4:        Exit program (Windows only)<br>
LCTRL + S:         Save current module<br>
LSHIFT + S:         Switch top right panel to synths list<br>
LSHIFT + I:         Switch top right panel to instruments list<br>
</pre>