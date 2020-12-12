# qk8055

##Introduction
qk8055 is a demonstration program for the Velleman K8055 Board written using the Qt5 framework in C++.  The program only runs under linux at this time.

![qk8055 Application](images/screenshot.png)

## Background
I wrote this application because I wanted a graphical interface to my Velleman K8055 experimental boards.  I also wanted learn the capabilities of QT5 especially the Translator class.  I have included translation files for "en" and "fr" in order to confirm the translations can be created and accessed. I have only included 3 translations in the "fr" file as a proof of concept.  The translations were created using "Google Translate" and may not be accurate.

## Prerequisites  
The following prerequisites are required for qk8055:   

  * libk8055  (See below)
  * Qt5
  * Qt5 Development Files
  * Qt5 Linguistics
  * Qt5 Linguistics Development Files
  * CMake

Due to the differences in package names across distributions I leave it to you to find the correct package for your distribution. 

## libk8055
qk8055 requires the k8055 C library written by Sven Lindberg.  There are a number of modification required to the Makefile, libk8055 and vellman.rules file for the k8055 demonstration program supplied with the library as well as qk8055 to operate correctly.

How to obtain the library and the required modifications are explained in [lib8055.md](lib8055.md).

## Installation
Download the source code from [qk8055 GitHub Homepage](https://github.com/g7mzr/qk8055) either using `git clone`, as a tar file or from the "Releases" for the latest stable release.

Once you have the source code `cd` to the "qk8055" directory and execute the following commands:

  * mkdir build
  * cd build
  * cmake ..
  * make

If the build is successful then you can run qk8055 as follows:

  * ./src/qk8055


