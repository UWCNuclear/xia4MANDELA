# Documentation

XIA Pixie-16 digitizer at MANDELA manual: Attached above :-)

XIA Pixie-16 digitizer 2018 manual: https://www.xia.com/wp-content/uploads/2018/12/Pixie16_UserManual.pdf

PAASS and poll2 acquisition codes for Pixie-16: https://github.com/UWCNuclear/paass-lc

ISOLDE Decay Station code to convert the raw data produced by the Pixie-16 digitizers into ROOT format : https://github.com/rlica/xia4ids

#  How to acquire data with POLL2 (.ldf files)

**Step 1.** Place the parameter file (example attached above) in the "acq" directory.

**Step 2.** To start POLL2, navigate to the "acq" directory and type:

    poll2
   
**Step 3.** To start the acqusition, type in the terminal:

    run

POLL2 will then display the run number, e.g. "Run 1 started on Monday March 14 12:00:00 2022"

**Step 4.** To stop the run, enter the command:

    stop
    
The .ldf file is created in the same directory.    
      
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

**Step 1.** Edit the calibration and configuration files to your setup configuration (files attached above).

**Step 2.**	To run, type "xia4ids" followed by the name of your config file and calibration file [optional] :

    xia4ids config_file calibrationFile
    
You can also run the Autosort_root script by giving it the run number to sort (first, give it permission to excute with "chmod +x Autosort_root") : 

    ./Autosort_root run_number

**Step 3.**	To look at histograms and fit peaks with GRSISort [see https://github.com/UWCNuclear/UbuntuSetUp]:

    grsisort -l filename.root
    

***Notes:*** Singles histograms are defined in xia4ids/inc/define_root.hh and filled in xia4ids/inc/read_ldf.hh
 
