# Documentation

XIA Pixie-16 digitizer at MANDELA manual attached above :-)

XIA Pixie-16 digitizer 2018 manual: https://www.xia.com/wp-content/uploads/2018/12/Pixie16_UserManual.pdf

PAASS and poll2 acquisition codes for Pixie-16: https://github.com/UWCNuclear/paass-lc

ISOLDE Decay Station code to convert the raw data produced by the Pixie-16 digitizers into ROOT format : https://github.com/rlica/xia4ids

# How to set up xia4ids at MANDELA

**Step 1.**	To download xia4ids, paste the following line in your terminal:

    git clone https://github.com/rlica/xia4ids
    
**Step 2.**	Open your .bashrc file (gedit ~/.bashrc) and add the following line before saving and closing the file:

    PATH=$PATH:~/xia4ids/bin/

**Step 3.**	Paste the following command in the terminal:

    source ~/.bashrc

**Step 4.**	To compile, go to ~/xia4ids/ and type:

    make
   
# How to create histograms and matrices with xia4ids at MANDELA

**Step 1.** Create an analysis directory with 4 subdirectories: cal, conf, logs, and raw.

**Step 2.** Create a calibration file and a configuration file.

**Step 3.**	To run, type "xia4ids" followed by the name of your config file and calibration file [optional] :

    xia4ids config_file calibrationFile
    
Otherwise, you can run the Autosort_root script by giving it the run number: 

    ./Autosort_root run_number

**Step 4.**	To look at histograms and fit peaks with GRSISORT [see https://github.com/UWCNuclear/UbuntuSetUp]:

    grsisort -l filename.root
    

***Notes:*** Singles histograms are defined in xia4ids/inc/define_root.hh and filled in xia4ids/inc/read_ldf.hh
 
