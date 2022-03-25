# Documentation

XIA Pixie-16 digitizer at MANDELA manual and parameter optimization script: Attached above :-)

XIA Pixie-16 digitizer 2018 manual: https://www.xia.com/wp-content/uploads/2018/12/Pixie16_UserManual.pdf

PAASS and poll2 acquisition codes for Pixie-16 and instructions from JJ: https://github.com/UWCNuclear/paass-lc

ISOLDE Decay Station code to convert the raw data produced by the Pixie-16 digitizers into ROOT format : https://github.com/rlica/xia4ids

#  How to acquire data with POLL2 (.ldf files)

**Step 1.** Place the .set parameter file (example attached above) in the "acq" directory.

**Step 2.** To start POLL2, navigate to the "acq" directory and type:

    poll2
   
**Step 3.** To start the acqusition, type in the terminal:

    run

POLL2 will then display the run number, e.g. "Run 1 started on Monday March 14 12:00:00 2022"

**Step 4.** To stop the run, enter the command:

    stop
    
The .ldf file is created in the same directory.    
      
# How to install xia4ids on Ubuntu

**Step 1.**	To download xia4ids, paste the following line in your terminal:

    git clone https://github.com/rlica/xia4ids
    
**Step 2.**	Open your .bashrc file (gedit ~/.bashrc) and add the following line before saving and closing the file:

    PATH=$PATH:~/xia4ids/bin/

**Step 3.**	Paste the following command in the terminal:

    source ~/.bashrc

**Step 4.**	To compile, go to ~/xia4ids/ and type:

    make
    
(On Centos, you might need to add "-ltbb" in the Makefile at the end of line 21.)
   
# How to create histograms with xia4ids at MANDELA

**Step 1.** To download the sample calibration and configuration files for MANDELA, paste the following line in your terminal:

    git clone https://github.com/UWCNuclear/xia4mandela

**Step 2.**	Move to the xia4mandela directory and create a "raw" directory and copy your .ldf file to the raw directory:

    cd xia4mandela
    mkdir raw

**Step 3.**	Edit the calibration file in "cal" and the configuration file in "conf" to your setup configuration.

**Step 4.**	You can run the Autosort_root script in the xia4mandela directory by giving it the run number to sort (first, give it permission to excute with "chmod +x Autosort_root") : 

    ./Autosort_root run_number
    
Otherwise, you can run by typing "xia4ids" followed by the name of your config file and calibration file [optional] :

    xia4ids conf/config_mandela cal/first.cal

**Step 5.**	To look at histograms and fit peaks with GRSISort [see https://github.com/UWCNuclear/UbuntuSetUp]:

    grsisort -l RunXXX.root
    

***Notes:*** Singles histograms are defined in xia4ids/inc/define_root.hh and filled in xia4ids/inc/read_ldf.hh

**Run008 from our XIA:**

hstats showing data in channel 0 only, not in channel 1

Multiplicity from 1 to 2 with Fold = 1, Fold = 2 changes Multiplicity tree to 2 only :-)

**Run145 from IDS:**

hstats from 1 to 33

Multiplicity from 0 to 7 with Fold = 1, Fold = 4 doesn't change Multiplicity tree?? Changing run_unit doesn't change Timestamp tree?? No .txt files are created when uncommenting coincidences??

***Check list:***

Check that the Run008 sorted with xia4ids is the same as from poll2 ROOT histograms. If possible?

Check the time units on our XIA/POLL2 (us?)

Check if there is a multiplicity=2 condition on our XIA/POLL2? Are singles collected?

Check trace length

Check the time gate in our configuration file for xia4ids 

Look into "Correlation mode", what is it? Is it coincidences?? What are the .txt files produced?

Look into sorting error: XiaListModeDataDecoder::ReadBuffer : Eventlength (91) does not correspond to header length (4) and trace length (16383)

In src/Unpacker.cpp:

        // Sanity check for event length (formula in PIXIE manual)
        // One last check to ensure event length matches what we think it
        // should be.
        if (traceLength / 2 + headerLength != eventLength) {

***Done!:***

ERROR: In configuration file 'conf/config_root_online'. Dettypes=1, Modules=0: In read_conf.hh, line 163: Module numbering starts from 0, therefore when using only 1 module, "modules" = 0 and xia4ids doesn't sort. We are able to go around it by keeping a spare line.

Check if we need to switch detector type from crystal (1) to beta (3) for your NaI(Tl): It looks like the detector type number is only used to group the entries




