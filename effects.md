<pre>
== General ==<br>
----<br>
<br>
Command '0000': No Effect<br>
<br>
Command '01xx': Pitch Up (Disabled when using Arpeggio or Vibrato)<br>
xx = Speed<br>
<br>
Command '02xx': Pitch Down (Disabled when using Arpeggio or Vibrato)<br>
xx = Speed<br>
<br>
Command '03xx': Set Volume<br>
xx = Volume level<br>
<br>
Command '04xx': Trance Slicer<br>
xx = Delay ticks before muting the volume (from 0 to 6)<br>
(note that the volume stays muted at the next rows)<br>
<br>
Command '05xx': Glider (Disabled when using Arpeggio or Vibrato)<br>
xx = Speed<br>
<br>
Command '06xx': Pattern Loop<br>
00 = Sets the loop point<br>
xx = Loops xx times<br>
<br>
Command '07xx': FX Synchro<br>
xx = Any data<br>
<br>
Command '08xx': Set Filter Cut Off<br>
xx = Cut Off level<br>
<br>
Command '09xx': Set Sample Play Offset (256 bytes steps)<br>
xx = Offset<br>
<br>
Command '0Axx': Randomize Filter Cut Off<br>
xx = Amplitude<br>
<br>
Command '0Bxx': Filter Cut Off Slide Up<br>
xx = Speed<br>
<br>
Command '0Cxx': Filter Cut Off Slide Down<br>
xx = Speed<br>
<br>
Command '0Dxx': Jump To Next Sequencer Position (aka Pattern Break)<br>
xx = Pattern row<br>
<br>
Command '0Exx': Note Retrigger<br>
xx = Tick<br>
<br>
Command '0Fxx': Set Number Of Ticks Per Beat<br>
xx = Ticks<br>
<br>
Command '10xx': Set Delay/Echo Send<br>
xx = Send Level<br>
<br>
Command '11xx': Set Reverb Send<br>
xx = Send Level<br>
<br>
Command '12xx': Set Distortion Threshold<br>
xx = Threshold Level<br>
<br>
Command '13xx': Set Distortion Clamp<br>
xx = Clamp Level<br>
<br>
Command '14xx': Set Filter Resonance<br>
xx = Resonance Level<br>
<br>
Command '15xx': Set Filter Type<br>
xx = Filter to use<br>
<br>
00 = LoPass -12db filter<br>
01 = HiPass filter<br>
02 = BandPass filter<br>
03 = BandReject filter<br>
04 = No Filter<br>
05 = LoPass -24db filter<br>
06 = LoPass -48db filter<br>
07 = LP-24 [Stereo] filter<br>
08 = A. Mod. [Mono] filter<br>
09 = A. Mod. [Stereo] filter<br>
0A = Single [Mono] filter<br>
0B = Single [Stereo] filter<br>
0C = ParaEq -15db filter<br>
0D = ParaEq -6db filter<br>
0E = ParaEq +6db filter<br>
0F = ParaEq +15db filter<br>
10 = Custom Delta filter<br>
11 = Comp. Distort L filter<br>
12 = Comp. Distort M filter<br>
13 = Comp. Distort H filter<br>
14 = Comp. Distort filter<br>
15 = W-HP12 [Mono] filter<br>
16 = W-HP12 [Stereo] filter<br>
17 = W-HP24 [Mono] filter<br>
<br>
Command '16xx': Set Filter LFO Carrier position<br>
xx = Position<br>
<br>
Command '17xx': Auto Fade In Track<br>
xx = Ticks<br>
<br>
C-7 00 .. .. 1710.... << Turn auto fading on<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
G-6 00 .. .. 0000.... << Volume will start at instrument level<br>
--- .. .. .. 0000....    and will be faded in too<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 1700.... << Turn it off (volume stays at current level)<br>
<br>
Command '18xx': Auto Fade Out Track<br>
xx = Ticks<br>
<br>
Same behaviour as above.<br>
<br>
Command '19xx': Volume Slide Up<br>
xx = Speed<br>
<br>
Command '1Axx': Volume Slide Down<br>
xx = Speed<br>
<br>
Command '1Bxy': Arpeggio<br>
x = Second relative semi tone<br>
y = Third relative semi tone<br>
<br>
C-7 00 .. .. 1B37.... << Turn it on<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 1B38.... << Change datas<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 1B00.... << Turn it off<br>
<br>
Command '1Cxx': Set Global Volume<br>
xx = Volume level<br>
<br>
Command '1Dxy': Vibrato<br>
x = Speed<br>
y = Depth<br>
<br>
C-7 00 .. .. 1D46.... << Turn it on<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 1D7F.... << Change data<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 0000....<br>
--- .. .. .. 1D00.... << Turn it off<br>
<br>
Command '1E0x': Select Instrument Playing Way<br>
0 = Play forward<br>
1 = Play backward<br>
<br>
Command '1Fxx': Position Jump<br>
xx = New position<br>
<br>
Command '20xx': Fine Volume Slide Up<br>
xx = Amount<br>
<br>
Command '21xx': Fine Volume Slide Down<br>
xx = Amount<br>
<br>
Command '22xx': Fine Pitch Up<br>
xx = Amount<br>
<br>
Command '23xx': Fine Pitch Down<br>
xx = Amount<br>
<br>
Command '240x': Turn flanger on/off<br>
0 = Turn it off<br>
1 = Turn it on<br>
<br>
Command '25xx': Set shuffle value<br>
xx = Amount<br>
<br>
Command '26xx': Set reverb filter cutoff<br>
xx = Amount<br>
<br>
Command '27xx': Set reverb filter resonance<br>
xx = Amount<br>
<br>
Command 'F0xx': Set BPM Speed<br>
xx = BPM<br>
<br>
== 303 Triggering ==<br>
-----<br>
<br>
Command '31xy': Trigger 303 Bass Line (Unit 1)<br>
x = Bank (A-D)<br>
y = Pattern (1-8)<br>
'00' will trigger current selected pattern<br>
<br>
Command '32xy': Trigger 303 Bass Line (Unit 2)<br>
x = Bank (A-D)<br>
y = Pattern (1-8)<br>
'00' will trigger current selected pattern<br>
<br>
== 303 Controllers ==<br>
----<br>
<br>
Where 'xx' is a number between $00 and $FF (hex):<br>
<br>
Command '33xx': Set 303 (Unit 1) Filter Cutoff<br>
Command '34xx': Set 303 (Unit 2) Filter Cutoff<br>
Command '35xx': Set 303 (Unit 1) Filter Resonance<br>
Command '36xx': Set 303 (Unit 2) Filter Resonance<br>
Command '37xx': Set 303 (Unit 1) Filter Env Mod<br>
Command '38xx': Set 303 (Unit 2) Filter Env Mod<br>
Command '39xx': Set 303 (Unit 1) Filter Decay<br>
Command '3Axx': Set 303 (Unit 2) Filter Decay<br>
Command '3Bxx': Set 303 (Unit 1) Accent<br>
Command '3Cxx': Set 303 (Unit 2) Accent<br>
Command '3Dxx': Set 303 (Unit 1) Tune<br>
Command '3Exx': Set 303 (Unit 2) Tune<br>
Command '41xx': Set 303 (Unit 1) Volume<br>
Command '42xx': Set 303 (Unit 2) Volume<br>
<br>
== Volume column ==<br>
----<br>
<br>
Command 'xx': Set Volume (00 to 40)<br>
<br>
Command 'Fx': Note Cut<br>
x = row number where the note should be cut<br>
<br>
== Panning column ==<br>
----<br>
<br>
Command 'xx': Panning (00 to 80)<br>
<br>
Command '90': Send Midi message<br>
Send the command and data specified<br>
in the fx/data columns to Midi OUT selected device.<br>
<br>
ex: 90 4050<br>
Send command 0x40 with data 0x50.<br>
<br>
== Midi ==<br>
----<br>
<br>
Command '80xx': Set Patch Bank<br>
(might not work on all midi equipments)<br>
(won't work in the replay routine)<br>
<br>
Read in the [faq] how you can send midiout controller messages<br>
and read the manual of your gear to learn how send RRPN ones<br>
using midiout, also, you might find here the midi implementation table<br>
for your hardware (or it could also be displayed on the device's LCD screen).<br>
</pre>