# Documentation

XIA Pixie-16 digitizer at MANDELA manual attached above :-)

XIA Pixie-16 digitizer 2018 manual: https://www.xia.com/wp-content/uploads/2018/12/Pixie16_UserManual.pdf

PAASS and poll2 acquisition codes for Pixie-16: https://github.com/UWCNuclear/paass-lc

ISOLDE Decay Station code to convert the raw data produced by the Pixie-16 digitizers into ROOT format : https://github.com/rlica/xia4ids

# How to set up xia4MANDELA

**Step 1.**	To download xia4MANDELA, paste the following line in your terminal:

    git clone https://github.com/UWCNuclear/xia4MANDELA.git

**Step 2.**	Open your .bashrc file (gedit ~/.bashrc) and add the following line before saving and closing the file:

    PATH=$PATH:~/xia4MANDELA/bin/

**Step 3.**	Paste the following command in the terminal:

    source ~/.bashrc

**Step 4.**	To compile, go to ~/xia4MANDELA/ and type:

    make
   
# How to create histograms and matrices with xia4MANDELA

To run, type "xia4MANDELA" followed by the name of your config file and calibration file [optional] :

    xia4MANDELA config_file calibrationFile

