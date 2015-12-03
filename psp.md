<pre>
The replay routine of the tracker is available for the PlayStation Portable,<br>
it uses the 2nd processor so the occupation time of main CPU is really minimal.<br>
<br>
This is an experiment and this console isn't a PC so you'd better go very easy<br>
on the dsp effects and channels polyphony, especially the flanger is a really heavy<br>
toll because the media engine doesn't have any integrated hardware sin/cos<br>
or pow instructions (the vfpu is only available for the main CPU).<br>
<br>
After a few extra measurements i noticed that the compressor (the 2 sliders right<br>
beside the top left vu-meters) can also heavy on the processor due to it's logarithmic<br>
functions and tracks polyphonies should be avoided by reducing their values<br>
to a minimum whenever possible.<br>
<br>
Samples depacking with the PSP codecs isn't implemented yet<br>
(so samples packing should be set to "none" in that case).<br>
</pre>