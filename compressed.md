<pre>
These modules can be recognized as they're using the ".ptp" extension<br>
(regular modules use ".ptk"), they can be reloaded inside the tracker so the<br>
musician can actually hear how damaged by the lossy compression they've been.<br>
<br>
While these files may have a bigger size than their .ptk counterparts,<br>
they're internally organized to maximize packing ratio so using a any generic<br>
data compressor on them will produce a much smaller file than what could be<br>
achieved by packing a .ptk file.<br>
<br>
There are two commands related to compressed modules in the tracker:<br>
<br>
"Save .ptp":<br>
Create a module with extension ".ptp" in the current directory.<br>
<br>
"Calc .ptp size":<br>
Calculate (roughly) the size that the module would take once used in an intro.<br>
<br>
Note that compressed modules generated on big endian platforms and little endian<br>
ones aren't compatible between them.<br>
----<br>
<br>
Samples inside .ptp modules can be packed, the user have the ability to select<br>
the packing algorithm which'll be used on a per sample basis,<br>
the available compression schemes are all lossy.<br>
<br>
GSM:<br>
Suitable for drums/snares.<br>
<br>
MP3:<br>
Suitable for longer samples like cymbals (it's tuned to pack at 64kbits).<br>
<br>
ADPCM:<br>
Can give better result than GSM (but samples are a bit bigger).<br>
<br>
True Speech:<br>
Suitable for human voices<br>
(you can use some track effects to cover the radio like quality).<br>
<br>
At3 (PSP Only):<br>
This one is similar to MP3 compression, it will be handled in the PSP<br>
replay routine only (but it's not handled yet).<br>
<br>
8 Bit:<br>
The samples (every 2 samples in fact) are packed to 8 bits<br>
and interpolated to 16 bits when depacked this give a bit better results<br>
than adpcm but compress less.<br>
<br>
None:<br>
Suitable for very short (chiptune like) samples<br>
(if you want to keep perfect quality).<br>
<br>
Note that this is the only way to save packed samples if the tracker<br>
has been compiled without codecs supports.<br>
<br>
The .ptp are the only modules format recognized by the replay routine.<br>
<br>
Note:<br>
The MP3 compression might not work on a bare bone Windows 2000<br>
(it works on any others).<br>
<br>
Note2:<br>
When a packing is selected for a sample (other than none)<br>
samples are reconstructed by interpolation.<br>
----<br>
<br>
Alongside with the .ptp are the optional .psm files which contain synchro<br>
informations related to the effect "07" used within the patterns;<br>
The .psm file format is as follow:<br>
<br>
Header:<br>
<br>
1.w: number of synchros data entries<br>
<br>
Synchro data:<br>
<br>
1.b: position<br>
1.b: row<br>
1.b: fx data (as specified within the tracker)<br>
<br>
Note:<br>
The fx data part is removed from the .ptp files and moved to the .psm files<br>
and only one fx per position/row is saved.<br>
</pre>