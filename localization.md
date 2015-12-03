<pre>
In order to keep a constant layout for the keyboard, the tracker uses locale<br>
keyboards text definitions which are located within the skins directory.<br>
<br>
These files contains the full name of the region on the first line<br>
and the 37 ASCII codes used for that particular type of keyboard<br>
(the keys layout) following on 4 rows.<br>
<br>
To add a new keyboard definition:<br>
<br>
first copy an already existing file and rename it after the keyboard's country<br>
it is supposed to describe, modify the 4 rows then edit the skin.xml file<br>
and insert it's file's name into the value key of the "keyboards" tag<br>
along with the others.<br>
<br>
Load (or reload) the tracker and select the new keyboard<br>
in the Misc. Setup panel.<br>
<br>
Hexadecimal notation is allowed in the form 0xXXXX or just plain ASCII.<br>
(it *may* work with unicode characters but i haven't tested it).<br>
<br>
You can eventually submit a new keyboard layout at: hitchhikr@australia.edu<br>
</pre>