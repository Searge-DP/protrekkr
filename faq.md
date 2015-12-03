<pre>
Q> No Fasttracker support, no 53194 tracks ?<br>
No etc...?, "m... i dont like the gui, the key shortcuts,<br>
you should have to..."<br>
<br>
A1> Get a compiler and code the best tracker ever. I'm sure you'll do fine.<br>
A2> Use fastracker, impulse tracker, buzz or whatever stuff you want.<br>
A3> Use your browser and search for some stuff...<br>
<br>
----<br>
Q> I Cannot run the program! Any idea ?<br>
<br>
A> If u have got a SBLive, try disabling EMU driver on your soundcard.<br>
Be sure you have got lastest DirectX drivers for your stuff (gfx/sfx card)<br>
and DirectX6.1 or above installed.<br>
(Microsoft DirectX 6.1 or above is required to run ptk)<br>
Ptk won't run on Windows NT, it should run on Windows 95, 98, 2k, xp<br>
and (possibly) vista. Also, might not work with some goofy gfx/sfx cards.<br>
<br>
----<br>
Q> Well, the program runs ok but ... how I can quit it ?<br>
<br>
A> Click 2 times on the exit button.<br>
Or just close the window if you're running ptk in windows mode.<br>
Alternatively, you can also use the key combo: LALT + F4.<br>
<br>
----<br>
Q> Ehh Everything sounds clicks, distorted and weird !!?<br>
<br>
Plan A> Try to use higher latency in Misc. Setup section.<br>
This means that the CPU is not having enough time to render/fill<br>
the audio buffer data, and this produce clicking...<br>
Plan B> Buy a faster computer.<br>
<br>
----<br>
Q> How I play 303 patterns in ptk ?<br>
<br>
A> Use ptk command 31xy and 32xy. 31xy will trigger pattern 'y' (1-8)<br>
from bank 'x' (A-D) from the first 303 unit<br>
(ptk has got 2 303 units, just like Rebirth).<br>
<br>
Example:<br>
<br>
--- .. .. .. 31A3.... << Play the 3th pattern of the bank A of the 1st 303 unit.<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
Off .. .. .. 0000.... << Switch the 303 unit off.<br>
<br>
The 303 unit 1 will be assigned to the track 0 stream.<br>
<br>
This means, that panning, fx setup, filter settings of the track will be<br>
applied to the sound of the 303 unit 1.<br>
<br>
To play the second 303 unit, use the same method but with 32xy command<br>
instead of 31. To stop 303 playing (patterns are played "looped" continuously)<br>
just put a note off (Right shift key) on the track were it was triggered.<br>
<br>
Also, using -3100- or -3200- will replay the patterns that are currently<br>
selected on the 303 editor. Can be handy while composing basslines.<br>
<br>
Btw: 303 engine will not "eat" the track sampler/csynth engine,<br>
so you can have both playing ex. a bassdrum and a 303 line<br>
on the same track.<br>
<br>
Also, both 303 units can be triggered in the same track.<br>
Well, just play with them :].<br>
<br>
----<br>
Q> Oh!, the 303 sounds great, will you code a 'buzz' port ?<br>
<br>
A> Nope.<br>
<br>
----<br>
Q> How I can record 303 or the tracks tweakings on the fly ?<br>
<br>
A> Press the "Live Rec: OFF" (top/left of the screen) button<br>
and, voila, the 303 tweakings or current track are autofilled on pattern<br>
while the tune is being played.<br>
<br>
----<br>
Q> How I can alter 303s CutOff, Resonance, etc.. on the pattern while playing ?<br>
<br>
A> Easy, just use the 303 special pattern commands.<br>
They're very useful to automatize 303 stuff.<br>
<br>
----<br>
Q> How to use Midi In/Out ?<br>
<br>
A> First of all, midi in & out capabilities of this program are rather<br>
*primitive* to say the least.<br>
<br>
Follow these steps:<br>
<br>
1 - Go to Misc. Setup section and select a midi in or out device to use<br>
(ptk only supports one device at a time).<br>
<br>
2 - Go to instrument section, and select a MIDI PRG<br>
(the default is N/A, which means no midi program selected).<br>
<br>
3 - Go to track section and here u can assign a midi channel<br>
to each track of ptk.<br>
<br>
4 - Play notes :]. Note off works. F'x' note cut command also works too,<br>
and note-volume command (speed) is supported.<br>
<br>
Also, you can change midicontrollers in the tracker,<br>
using '90' in the panning row:<br>
<br>
ex:<br>
<br>
C-3 02 .. .. 0000....<br>
<br>
--- .. .. 90 xxyy.... << This will set the value<br>
--- .. .. .. 0000....    of the controller n.'xx' to 'yy' (both in hex)<br>
--- .. .. .. 0000....<br>
<br>
So "--- .. .. 90 2040...." will set the controller number $20(32) to $40(64).<br>
<br>
You will need the midi implementation table of your gear to know<br>
what you can change with midi controller messages.<br>
Probably, it's located at the end of the manual =].<br>
<br>
----<br>
Q> Audio & Midi are not synchronized, what I can do ?<br>
<br>
A1> Buy a commercial software package.<br>
A2> Well, there is a nasty trick to synchronize both.<br>
It's a bit hardcore but work with me:<br>
<br>
Simply put one line down to all midi notes on your pattern (use Insert key)<br>
and go to 'Misc. Setup', adjust the latency and just search a value<br>
that will make sound sync both audio/midi.<br>
<br>
----<br>
Q> The stock Sin/Saw/Pulse and Rnd waveforms are too simple/common,<br>
is there a way to use something more complex/rich ?<br>
<br>
A> You have to ability to redirect the waveforms of the instruments<br>
through the synth pipe by selecting the "wav" option for the oscillator<br>
you're using for this synth instrument, samples can be used as wavetables<br>
to replace the stock signals.<br>
<br>
----<br>
Q> Will you support VST instruments in a future?<br>
<br>
A> Yes, as specified here http://code.google.com/p/protrekkr/issues/list but<br>
that's not really a priority, the main goal of the tracker is to be a<br>
all-in-one program with a compact & re-usable replay routine.<br>
</pre>