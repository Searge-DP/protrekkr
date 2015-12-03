![http://protrekkr.googlecode.com/svn/trunk/protrekkr.jpg](http://protrekkr.googlecode.com/svn/trunk/protrekkr.jpg)
<pre>
ProTrekkr (formerly known as NoiseTrekker by Juan Antonio Arguelles Rius aka Arguru) is<br>
a tracker program combining a software synthesizer together with a traditional samples<br>
tracker which can be used to create electronic music (like psytrance, trance goa,<br>
hard acid, IDM, chip, techno, etc.) for small sized intros, demos or games.<br>
<br>
Currently the tracker is available on Windows, Linux, Amiga OS4, AROS and Mac OSX.<br>
<br>
Check http://code.google.com/p/protrekkr/wiki/introduction for more infos.<br>
<br>
<br>
Recent history.txt entries:<br>
<br>
V2.5.4<br>
<br>
- Fixed 2 issues with interpolate command: it wouldn't work on all effects<br>
and the whole commmand column is now properly filled with the first value.<br>
- Input was partially disabled when caps lock was turned on.<br>
- Using right mouse button on "pattern lines" arrows will now increase/decrease value by 8.<br>
- F5 to F9 keys now jumps to 0, 1/4, 2/4, 3/4, 4/4 of the patterns lines.<br>
- Changed the way the number of patterns is calculated when saving a song,<br>
the tracker now looks for any used (scratch) patterns and save them within the .ptk module.<br>
- Fixed an issue in digibooster import function which was due to a MSVC compiler quirk.<br>
<br>
V2.5.3<br>
<br>
- 303 units speeds can now be scaled.<br>
- Added effects 26 & 27 (set reverb cutoff & resonance).<br>
- Some notes were missed in multi-notes channels sometimes.<br>
- Fixed a bug occuring with automatic note offs on the synth.<br>
- Ptk can now import DigiBooster v1.x modules (.digi).<br>
- Tracker could hang sometimes when calculating a song length.<br>
<br>
V2.5.2<br>
<br>
- Slightly improved the smoothing of the reverb (making it sound a bit less metallic).<br>
- Added an option to tune the 2 303 units together.<br>
- Tracker crashed when using insert command on track 0.<br>
<br>
V2.5.1<br>
<br>
- Tracks are only shadowed during playing.<br>
- Added cutomizable resonance for reverb filter.<br>
- Tracker could crash when loading an instrument over another one<br>
which was still playing.<br>
- Autosave function was broken.<br>
- Added auto backup function, the tracker will create a backup<br>
of any existing old module version before overwriting the new one.<br>
- Reverb threshold delays table was lacking some values.<br>
<br>
V2.5.0<br>
<br>
- Improved midi in/out support (notably by adding velocity).<br>
- Default instruments volumes are always turned on now<br>
as they're used for midi output.<br>
- Added 3 new themes.<br>
- Tracker sometimes crashed at exit when using midi.<br>
- Mouse wheel activated for horizontal patterns slider.<br>
- Fixed a small issue with vu meters values.<br>
- Number of effects columns is now selectable (from 1 to 4).<br>
- Added synth oscillators combiner.<br>
- Each track now have separate volume.<br>
- Added lo/med/hi bands equalizers for each track.<br>
- Delay send had precedence over command 10<br>
when updating track tab during play.<br>
- Fixed up reverb code (should sound cleaner too)<br>
and added stereo separation parameter.<br>
- Flanger speeded up.<br>
- Right mouse button in lists arrows is now active<br>
(jump to previous/next letter group for files lists).<br>
- Added 13 new (converted) modules for testing purposes<br>
also improved (?) older modules to take advantage of new features.<br>
- A file name can now be passed as argument to the tracker, it will<br>
be loaded at startup (can load any file recognized by the tracker).<br>
(this can be used to associate .ptk files to the tracker).<br>
- Default repeat loop row is now 0 (was disabled before).<br>
- Improved .mod/.ft import.<br>
- Glide effect (5) should now work with synth instruments.<br>
- Tracks data weren't displayed properly sometimes.<br>
- Fixed a bug in tracks filters.<br>
- Implemented insert or delete track functions.<br>
- Tracks can now be rendered to .wav in their own separate file.<br>
- Tracks panning changing are now smoothed.<br>
- Live recording strategy improved.<br>
- Implemented a midi automation system to control elements of the tracker<br>
from a midi device (like a master keyboard).<br>
- Added effect 25: Set shuffle value.<br>
- Metronome implemented (used during recording).<br>
- Fullscreen mode is now used with current screen resolution.<br>
- Handled latency at recording startup (so visuals should be synched to audio).<br>
- Fixed midi handling for big endian machines.<br>
- Fixed a bug in the reverb that only occured on big endian machines.<br>
<br>
V2.1.4<br>
<br>
- Added duplicate function to samples editor: increase sample by selection length<br>
and copy it's content into the newly created space.<br>
- Added Insert function to samples editor: increase sample by selection length<br>
and insert zeroes into the newly created space.<br>
- Looks like the signal reduction hack is no longer necessary on Linux.<br>
- Linux 32 bit executable now available.<br>
<br>
V2.1.3<br>
<br>
- Window can now be resized.<br>
- Zero command added to sample editor (used to clear selections without removing them from samples).<br>
- Fixed a small issue with patterns blocks selection.<br>
- Loading some modules or instruments would crash the tracker due to unrecognized packing schemes.<br>
- Fixed a bug that could freeze the tracker under AROS (& possibly Amiga OS4).<br>
<br>
V2.1.2<br>
<br>
- Fixed flanger filter (now using individual buffers / track).<br>
- Fixed 06xx command (was always jumping 1 line too far).<br>
- Added loading support for 1, 2 & 3 channels FastTracker I modules.<br>
- Added flight.ptk & warlock.ptk.<br>
<br>
V2.1.1<br>
<br>
- Patterns slider wasn't always properly resized when switching<br>
from large to small patterns view.<br>
- Some buttons weren't properly disabled in Disk IO tab.<br>
- Added buttons to reduce or expand the number of notes in each track header.<br>
- Max number of notes in a track is now 16.<br>
<br>
V2.1.0<br>
<br>
- Fixed 2 bugs in the replay (which can now be slightly smaller).<br>
- Lengths of individual packed waveforms are now displayed.<br>
- Songs can now be rendered to wav files (like before)<br>
or directly used to create instruments waveforms.<br>
- Added primitive.ptk by Mice of Brainstorm.<br>
- Fixed a bug in the sample editor which prevented it to work properly<br>
with waveforms of more than 2 megabytes.<br>
- In continuous scroll mode, the patterns scrollbar (& the arrows)<br>
now reflect the global length and can be used to browse through entire song<br>
(and not just the current pattern like before).<br>
- Implemented an internal compression scheme (based on wavpack) so<br>
samples packing is available on every platforms.<br>
The compression is rather good but the depacker is bigger than when using<br>
codecs (a few kb kkrunched).<br>
- Properties.h files weren't always saved at the right place.<br>
<br>
V2.0.2<br>
<br>
- Moog Lo & Moog band filters buffers weren't reseted properly<br>
resulting in some "scratchy" sound sometimes.<br>
- Added tracks compressors (can eat some CPU time).<br>
- Tracks polyphony was kinda broken.<br>
- Fixed a small issue with the flanger.<br>
<br>
V2.0.1<br>
<br>
- Big tracker & replay speed up.<br>
- Volume of instruments were left at 0 when loading waveforms.<br>
- Added the possibility to only delete the current instrument split.<br>
- Fixed an issue within .ptp saving function.<br>
<br>
V2.0<br>
<br>
- Tempo can now go down to 20 BPM.<br>
- 303 units entirely modified, now they should behave<br>
and sound a bit more like the one found in Propellerhead's Rebirth.<br>
- Files & dirs entries are now sorted alphabetically.<br>
- Input zones are now displayed with altered colors.<br>
- 6 default color themes are now available.<br>
- Range selection in sample editor speeded up.<br>
- .mod import function is now much more accurate<br>
(note: it can also import FastTracker 1 .ft modules).<br>
- Fixed a bug in samples looping (1 byte was always missing from the loop).<br>
- Improved shadow patterns rendering.<br>
- Patterns shading is also displayed for track which are turned off<br>
in the sequencer (shading can be turned on/off globally).<br>
- Improved sample editor:<br>
- Speeded up (especially while selecting) and overall cleaner processing.<br>
- Middle mouse button can now be used to zoom in/out.<br>
- Added cut/copy/paste with 4 copy buffers.<br>
- Crop function (remove everything from a waveform but the selection).<br>
- Zap (delete a selected part of a waveform without copying it).<br>
- Select view / Select all.<br>
- Reverse (invert the selected part of a waveform).<br>
- Selection shifting.<br>
- Added position jump effect (1F) (Can be combined with pattern break (0D)).<br>
- Added fine volume slide up and down effects (20 & 21).<br>
- Added fine pitch up and down effects (22 & 23).<br>
- Speed can now go up to 32 ticks/beat.<br>
- BPM weren't refreshed properly on screen when being changed inside patterns.<br>
- Multi-notes channels weren't re-initialized properly when loading new modules<br>
which could lead to a crash.<br>
- Instruments used without notes won't retrig the note but only change<br>
the waveform (like in the original protracker).<br>
- Filelists won't be redrawn after a loading process<br>
and they won't jump back to the top after a saving one either.<br>
- Fixed a bug in Pattern loop command (6).<br>
- Splitted the play button into 2, 1st one to play song,<br>
2nd one to play pattern, right mouse button on those to play song<br>
or pattern from current row (using left mouse button starts from top row).<br>
Shortcuts:<br>
RCTRL: Play song from start of pattern.<br>
LSHIFT + RCTRL: Play song from current position.<br>
RALT: Play pattern from start of pattern.<br>
LSHIFT + RALT: Play pattern from current position.<br>
- Added transposing capability to the instruments remapping function.<br>
- Changed LCTRL+H & LCTRL+LSHIFT+H to LCTRL+K & LCTRL+LSHIFT+K.<br>
- Default patterns zoom is now selectable.<br>
- Effect 10 (Delay send) was inneffective when Track tab was selected.<br>
- Overall better accuracy in replaying and volume ramping.<br>
- Global volume of instruments weren't saved in .pti files.<br>
- Using non existant instruments in patterns should now be handled properly.<br>
- Converted some tunes from FastTracker 1 for test purposes.<br>
- Instruments amplifications are now modulating synths only when necessary<br>
(meaning: only when the instruments are going through the synths).<br>
- Volumes columns and effect 3 are now calculated differently<br>
and are cummulative:<br>
<br>
c-3  0 .. .. ........<br>
<br>
will play instrument 0 at it's former volume.<br>
<br>
c-3  0 20 .. ........<br>
<br>
will play instrument 0 at roughly 50% of it's volume.<br>
<br>
c-3  0 .. .. 0380....<br>
<br>
will play instrument 0 at roughly 50% of it's volume.<br>
<br>
c-3  0 20 .. 0380....<br>
<br>
will play instrument 0 at roughly 25% of it's volume.<br>
- Fixed a bug in note retrig effect if no note was specified<br>
(now it takes the last played note as it should).<br>
- Rewrote the latency handling routines in a more robust & precise way.<br>
- Fixed the right mouse button caret horizontal scrolling.<br>
- Added effect 24: turn flanger on/off.<br>
- Salvaged 3 NoiseTrekker beta version modules,<br>
they really don't sound like in the original one as i had to rework them, though.<br>
- Real numbers of used patterns are now counted when saving a .ptk.<br>
- Fixed a small issue with keyboard handling in message boxes.<br>
- Added Moog Lo & Moog band filters for synth instruments.<br>
- Fixed a bug in .ptp saving & replay: some instruments infos were scrambled.<br>
</pre>